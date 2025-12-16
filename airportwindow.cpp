#include "airportwindow.h"
#include "ui_airportwindow.h"

#include <QMessageBox>
#include "airportdialog.h"
#include "airportnamedialog.h"

AirportWindow::AirportWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AirportWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new AirportTableModel(this->database, this);

    this->proxy_model = new AirportProxyModel(ui->name_edit, ui->rainfall_edit, ui->speed_edit,
                                                           ui->direction_edit, ui->temperature_edit, this);
    this->proxy_model->setSourceModel(this->source_model);

    ui->airport_table->setModel(this->proxy_model);

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val4 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val5 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val2->setRegularExpression(QRegularExpression("[0-9]{4}"));
    val3->setRegularExpression(QRegularExpression("[0-9]{4}"));
    val4->setRegularExpression(QRegularExpression("[0-9]{4}"));
    val5->setRegularExpression(QRegularExpression("[-]?[0-9]{4}"));

    ui->name_edit->setValidator(val1);
    ui->rainfall_edit->setValidator(val2);
    ui->direction_edit->setValidator(val3);
    ui->speed_edit->setValidator(val4);
    ui->temperature_edit->setValidator(val5);

    connect(ui->add_button, &QPushButton::clicked, this, &AirportWindow::AddAirport);
    connect(ui->change_button, &QPushButton::clicked, this, &AirportWindow::ChangeAirport);
    connect(ui->delete_button, &QPushButton::clicked, this, &AirportWindow::RemoveAirport);
}

AirportWindow::~AirportWindow()
{
    delete ui;
}

void AirportWindow::AddAirport()
{
    AirportDialog add_dialog(NULL, this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (add_dialog.exec() == 1)
    {
        Airport airport = add_dialog.GetData();
        bool (*func)(const Airport&, const Airport&) = [](const Airport& a, const Airport& b)
        {
            return a.GetName() == b.GetName();
        };

        if (this->database->FindAirport(airport, func) != -1)
        {
            box.setText("Аэропорт с таким названием уже есть в системе!");
            box.exec();
        }
        else
        {
            this->database->AddAirport(airport, true);

            box.setText("Аэропорт добавлен в систему!");
            box.exec();
        }
    }
}

void AirportWindow::ChangeAirport()
{
    AirportNameDialog old_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (old_dialog.exec() == 1)
    {
        QString name = old_dialog.GetData();

        int i = this->database->FindAirport(Airport(name, 0, 0, 0, 0), [](const Airport& a, const Airport& b)
                                            {
                                                return a.GetName() == b.GetName();
                                            });

        if (i == -1)
        {
            box.setText("Аэропорта с таким названием нет в системе!");
            box.exec();
        }
        else
        {
            Airport airport = this->database->GetAirport(i);
            AirportDialog upd_dialog(&airport, this);

            if (upd_dialog.exec() == 1)
            {
                Airport new_airport = upd_dialog.GetData();

                int j = this->database->FindAirport(new_airport, [](const Airport& a, const Airport& b)
                                                  {
                                                      return a.GetName() == b.GetName();
                                                  });

                if (j != -1)
                {
                    box.setText("Система не смогла обновить аэропорт!");
                    box.exec();
                }
                else
                {
                    int g;

                    this->database->ChangeState(false);

                    while ((g = this->database->FindFlight(Flight("", "", airport.GetName(), "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                           [](const Flight& a, const Flight& b)
                                                           {
                                                               return a.GetFrom() == b.GetFrom();
                                                           })) != -1)
                    {
                        Flight flt = this->database->GetFlight(g);
                        flt.SetFrom(new_airport.GetName());
                        this->database->UpdateFlight(flt, g, true);
                    }

                    while ((g = this->database->FindFlight(Flight("", "", "", airport.GetName(), QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                           [](const Flight& a, const Flight& b)
                                                           {
                                                               return a.GetTo() == b.GetTo();
                                                           })) != -1)
                    {
                        Flight flt = this->database->GetFlight(g);
                        flt.SetTo(new_airport.GetName());
                        this->database->UpdateFlight(flt, g, true);
                    }

                    this->database->ChangeState(true);
                    this->database->UpdateAirport(new_airport, i, true);

                    box.setText("Система обновила аэропорт!");
                    box.exec();
                }
            }
        }
    }
}

void AirportWindow::RemoveAirport()
{
    AirportNameDialog del_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (del_dialog.exec() == 1)
    {
        QString name = del_dialog.GetData();
        bool (*func)(const Airport&, const Airport&) = [](const Airport& a, const Airport& b)
        {
            return a.GetName() == b.GetName();
        };

        if (this->database->FindAirport(Airport(name, 0, 0, 0, 0), func) == -1)
        {
            box.setText("Аэропорта с таким названием нет в системе!");
            box.exec();
        }
        else
        {
            this->database->ChangeState(false);

            int i;
            int j;

            while ((i = this->database->FindFlight(Flight("", "", name, name, QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                   [](const Flight& a, const Flight& b)
                                                   {
                                                        return a.GetFrom() == b.GetFrom() || a.GetTo() == b.GetTo();
                                                   })) != -1)
            {
                if (this->database->GetFlight(i).GetFrom() == name || this->database->GetFlight(i).GetTo() == name)
                {
                    while ((j = this->database->FindTicket(Ticket("", "", this->database->GetFlight(i).GetNumFlight()),
                                                           [](const Ticket& a, const Ticket& b)
                                                           {
                                                               return a.GetNumFlight() == b.GetNumFlight();
                                                           })) != -1)
                    {
                        this->database->RemoveTicket(j, true);
                    }

                    while ((j = this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, this->database->GetFlight(i).GetNumFlight(), ""),
                                                         [](const Purpose& a, const Purpose& b)
                                                         {
                                                             return a.GetNumFlight() == b.GetNumFlight();
                                                         })) != -1)
                    {
                        this->database->RemovePurpose(j, true);
                    }

                    this->database->RemoveFlight(i, true);
                }
            }

            this->database->ChangeState(true);

            this->database->RemoveAirport(this->database->FindAirport(Airport(name, 0, 0, 0, 0), func), true);

            box.setText("Аэропорт и связанные с ним данные удалены из системы!");
            box.exec();
        }
    }
}
