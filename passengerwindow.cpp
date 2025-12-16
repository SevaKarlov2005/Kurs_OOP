#include "passengerwindow.h"
#include "ui_passengerwindow.h"

#include <QMessageBox>
#include "passengerdialog.h"
#include "numpassportdialog.h"

PassengerWindow::PassengerWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PassengerWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new PassengerTableModel(this->database, this);

    this->proxy_model = new PassengerProxyModel(ui->num_passport_edit, ui->place_passport_edit, ui->date_passport_edit,
                                                ui->surname_edit, ui->name_edit, ui->patronym_edit,
                                                ui->birthday_edit, this);

    this->proxy_model->setSourceModel(this->source_model);

    ui->passenger_table->setModel(this->proxy_model);

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val4 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val5 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val6 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val7 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[0-9]{4}-[0-9]{6}"));
    val2->setRegularExpression(QRegularExpression("([A-Z][a-z]+[- ][A-Z][a-z]+|[А-Я][а-я]+[- ][А-Я][а-я]+)"));
    val3->setRegularExpression(QRegularExpression("(0[1-9]|[12][0-9]|3[01]).(0[1-9]|1[0-2]).[0-9]{4}"));
    val4->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val5->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val6->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val7->setRegularExpression(QRegularExpression("(0[1-9]|[12][0-9]|3[01]).(0[1-9]|1[0-2]).[0-9]{4}"));

    ui->num_passport_edit->setValidator(val1);
    ui->place_passport_edit->setValidator(val2);
    ui->date_passport_edit->setValidator(val3);
    ui->surname_edit->setValidator(val4);
    ui->name_edit->setValidator(val5);
    ui->patronym_edit->setValidator(val6);
    ui->birthday_edit->setValidator(val7);

    connect(ui->add_button, &QPushButton::clicked, this, &PassengerWindow::AddPassenger);
    connect(ui->change_button, &QPushButton::clicked, this, &PassengerWindow::ChangePassenger);
    connect(ui->delete_button, &QPushButton::clicked, this, &PassengerWindow::RemovePassenger);
}

PassengerWindow::~PassengerWindow()
{
    delete ui;
}

void PassengerWindow::AddPassenger()
{
    PassengerDialog add_dialog(NULL, this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (add_dialog.exec() == 1)
    {
        Passenger passenger = add_dialog.GetData();
        bool (*func)(const Passenger&, const Passenger&) = [](const Passenger& a, const Passenger& b)
        {
            return a.GetNumPassport() == b.GetNumPassport();
        };

        if (this->database->FindPassenger(passenger, func) != -1)
        {
            box.setText("Пассажир с таким номером паспорта уже есть в системе!");
            box.exec();
        }
        else
        {
            this->database->AddPassenger(passenger, true);

            box.setText("Пассажир добавлен в систему!");
            box.exec();
        }
    }
}

void PassengerWindow::ChangePassenger()
{
    NumPassportDialog old_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (old_dialog.exec() == 1)
    {
        QString old_num_passport = old_dialog.GetData();

        int i = this->database->FindPassenger(Passenger(old_num_passport, "", QDate(), "", "", "", QDate()),
                                              [](const Passenger& a, const Passenger& b)
                                              {
                                                  return a.GetNumPassport() == b.GetNumPassport();
                                              });

        if (i == -1)
        {
            box.setText("Пассажира с таким номером паспорта нет в системе!");
            box.exec();
        }
        else
        {
            Passenger passenger = this->database->GetPassenger(i);
            PassengerDialog upd_dialog(&passenger, this);

            if (upd_dialog.exec() == 1)
            {
                Passenger new_passenger = upd_dialog.GetData();

                int j = this->database->FindPassenger(new_passenger,
                                                      [](const Passenger& a, const Passenger& b)
                                                      {
                                                          return a.GetNumPassport() == b.GetNumPassport();
                                                      });

                if (j != -1)
                {
                    box.setText("Система не смогла обновить пассажира!");
                    box.exec();
                }
                else
                {
                    int g;

                    this->database->ChangeState(false);

                    while ((g = this->database->FindTicket(Ticket("", old_num_passport, ""),
                                                           [](const Ticket& a, const Ticket& b)
                                                           {
                                                               return a.GetNumPassport() == b.GetNumPassport();
                                                           })) != -1)
                    {
                        Ticket ticket = this->database->GetTicket(g);
                        ticket.SetNumPassport(new_passenger.GetNumPassport());
                        this->database->UpdateTicket(ticket, g, true);
                    }

                    this->database->ChangeState(true);
                    this->database->UpdatePassenger(new_passenger, i, true);

                    box.setText("Система обновила пассажира!");
                    box.exec();
                }
            }
        }
    }
}

void PassengerWindow::RemovePassenger()
{
    NumPassportDialog del_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (del_dialog.exec() == 1)
    {
        QString num_passport = del_dialog.GetData();
        bool (*func)(const Passenger&, const Passenger&) = [](const Passenger& a, const Passenger& b)
        {
            return a.GetNumPassport() == b.GetNumPassport();
        };

        if (this->database->FindPassenger(Passenger(num_passport, "", QDate(), "", "", "", QDate()), func) == -1)
        {
            box.setText("Пассажира с таким номером паспорта нет в системе!");
            box.exec();
        }
        else
        {
            this->database->ChangeState(false);

            int i;

            while ((i = this->database->FindTicket(Ticket("", num_passport, ""),
                                                   [](const Ticket& a, const Ticket& b)
                                                   {
                                                       return a.GetNumPassport() == b.GetNumPassport();
                                                   })) != -1)
            {
                QString num_flight = this->database->GetTicket(i).GetNumFlight();
                int ind = this->database->FindFlight(Flight(num_flight, "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                     [](const Flight& a, const Flight& b)
                                                     {
                                                         return a.GetNumFlight() == b.GetNumFlight();
                                                     });
                Flight flt = this->database->GetFlight(ind);

                flt.SetFreePlace(flt.GetFreePlace() + 1);
                this->database->UpdateFlight(flt, ind, true);
                this->database->RemoveTicket(i, true);
            }

            this->database->ChangeState(true);

            this->database->RemovePassenger(this->database->FindPassenger(Passenger(num_passport, "", QDate(), "", "", "", QDate()), func), true);

            box.setText("Пассажир и связанные с ним данные удалены из системы!");
            box.exec();
        }
    }
}
