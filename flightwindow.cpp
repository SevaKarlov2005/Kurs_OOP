#include "flightwindow.h"
#include "ui_flightwindow.h"

#include <QMessageBox>
#include "flightdialog.h"
#include "numflightdialog.h"

FlightWindow::FlightWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlightWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new FlightTableModel(this->database, this);

    this->proxy_model = new FlightProxyModel(ui->num_flight_edit, ui->company_edit, ui->from_edit,
                                             ui->to_edit, ui->date_edit, ui->time_edit,
                                             ui->state_box, ui->all_place_edit, ui->free_place_edit,
                                             this);
    this->proxy_model->setSourceModel(this->source_model);

    ui->flight_table->setModel(this->proxy_model);

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val4 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val5 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val6 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val7 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val8 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));
    val2->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val3->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val4->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val5->setRegularExpression(QRegularExpression("(0[1-9]|[12][0-9]|3[01]).(0[1-9]|1[0-2]).[0-9]{4}"));
    val6->setRegularExpression(QRegularExpression("([01][0-9]|2[0-3]):[0-5][0-9]"));
    val7->setRegularExpression(QRegularExpression("[0-9]{4}"));
    val8->setRegularExpression(QRegularExpression("[0-9]{4}"));

    ui->num_flight_edit->setValidator(val1);
    ui->company_edit->setValidator(val2);
    ui->from_edit->setValidator(val3);
    ui->to_edit->setValidator(val4);
    ui->date_edit->setValidator(val5);
    ui->time_edit->setValidator(val6);
    ui->all_place_edit->setValidator(val7);
    ui->free_place_edit->setValidator(val8);

    connect(ui->add_button, &QPushButton::clicked, this, &FlightWindow::AddFlight);
    connect(ui->change_button, &QPushButton::clicked, this, &FlightWindow::ChangeFlight);
    connect(ui->delete_button, &QPushButton::clicked, this, &FlightWindow::RemoveFlight);


}

FlightWindow::~FlightWindow()
{
    delete ui;
}

void FlightWindow::AddFlight()
{
    FlightDialog add_dialog(NULL, this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (add_dialog.exec() == 1)
    {
        Flight flight = add_dialog.GetData();
        bool (*func)(const Flight&, const Flight&) = [](const Flight& a, const Flight& b)
        {
            return a.GetNumFlight() == b.GetNumFlight();
        };

        // Проверка на существование рейса с таким номером
        if (this->database->FindFlight(flight, func) != -1)
        {
            box.setText("Авиарейс с таким номером уже есть в системе!");
            box.exec();
        }
        else
        {
            // Проверка на существование аэропорта вылета (from)
            bool (*findAirportFunc)(const Airport&, const Airport&) = [](const Airport& a, const Airport& b)
            {
                return a.GetName() == b.GetName();
            };

            if (this->database->FindAirport(Airport(flight.GetFrom(), 0, 0, 0, 0), findAirportFunc) == -1)
            {
                box.setText("Система не смогла добавить авиарейс!");
                box.exec();
                return;
            }

            // Проверка на существование аэропорта назначения (to)
            if (this->database->FindAirport(Airport(flight.GetTo(), 0, 0, 0, 0), findAirportFunc) == -1)
            {
                box.setText("Система не смогла добавить авиарейс!");
                box.exec();
                return;
            }

            // Проверка временных условий для статусов рейса
            QDateTime now = QDateTime::currentDateTime();
            QDateTime flightDateTime(flight.GetDate(), flight.GetTime());
            qint64 minutesDiff = now.msecsTo(flightDateTime) / 60000;

            FlightState state = flight.GetState();
            bool timeConditionValid = true;

            if (state == FlightState::ON_TIME || state == FlightState::DELAYED)
            {
                if (minutesDiff < 240)
                {
                    timeConditionValid = false;
                }
            }
            else if (state == FlightState::CHECK_IN)
            {
                if (minutesDiff < 40)
                {
                    timeConditionValid = false;
                }
            }
            else if (state == FlightState::BOARDING)
            {
                if (minutesDiff < 20)
                {
                    timeConditionValid = false;
                }
            }

            if (!timeConditionValid)
            {
                box.setText("Система не смогла добавить авиарейс!");
                box.exec();
            }
            else
            {
                this->database->AddFlight(flight, true);

                box.setText("Авиарейс добавлен в систему!");
                box.exec();
            }
        }
    }
}

void FlightWindow::ChangeFlight()
{
    NumFlightDialog old_dialog(this);
    QMessageBox box;
    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (old_dialog.exec() == 1)
    {
        QString old_num_flight = old_dialog.GetData();

        int i = this->database->FindFlight(Flight(old_num_flight, "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                           [](const Flight& a, const Flight& b)
                                           {
                                               return a.GetNumFlight() == b.GetNumFlight();
                                           });

        if (i == -1)
        {
            box.setText("Авиарейса с таким номером нет в системе!");
            box.exec();
            return;
        }

        Flight flight = this->database->GetFlight(i);
        FlightDialog upd_dialog(&flight, this);

        if (upd_dialog.exec() == 1)
        {
            Flight new_flight = upd_dialog.GetData();

            QDateTime now = QDateTime::currentDateTime();
            QDateTime flightDateTime(new_flight.GetDate(), new_flight.GetTime());
            qint64 minutesDiff = now.msecsTo(flightDateTime) / 60000;

            FlightState state = new_flight.GetState();

            if (state == FlightState::ON_TIME || state == FlightState::DELAYED)
            {
                if (minutesDiff < 240)
                {
                    box.setText("Система не смогла обновить авиарейс!");
                    box.exec();
                    return;
                }
            }
            else if (state == FlightState::CHECK_IN)
            {
                if (minutesDiff < 40)
                {
                    box.setText("Система не смогла обновить авиарейс!");
                    box.exec();
                    return;
                }
            }
            else if (state == FlightState::BOARDING)
            {
                if (minutesDiff < 20)
                {
                    box.setText("Система не смогла обновить авиарейс!");
                    box.exec();
                    return;
                }
            }

            int g;
            this->database->ChangeState(false);

            while ((g = this->database->FindTicket(Ticket("", "", old_num_flight),
                                                   [](const Ticket& a, const Ticket& b)
                                                   {
                                                       return a.GetNumFlight() == b.GetNumFlight();
                                                   })) != -1)
            {
                Ticket ticket = this->database->GetTicket(g);
                ticket.SetNumFlight(new_flight.GetNumFlight());
                this->database->UpdateTicket(ticket, g, true);
            }

            while ((g = this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, old_num_flight, ""),
                                                    [](const Purpose& a, const Purpose& b)
                                                    {
                                                        return a.GetNumFlight() == b.GetNumFlight();
                                                    })) != -1)
            {
                Purpose purpose = this->database->GetPurpose(g);
                purpose.SetNumFlight(new_flight.GetNumFlight());
                this->database->UpdatePurpose(purpose, g, true);
            }

            this->database->ChangeState(true);
            this->database->UpdateFlight(new_flight, i, true);

            box.setText("Система обновила авиарейс!");
            box.exec();
        }
    }
}

void FlightWindow::RemoveFlight()
{
    NumFlightDialog del_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (del_dialog.exec() == 1)
    {
        QString num_flight = del_dialog.GetData();
        bool (*func)(const Flight&, const Flight&) = [](const Flight& a, const Flight& b)
        {
            return a.GetNumFlight() == b.GetNumFlight();
        };

        if (this->database->FindFlight(Flight(num_flight, "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0), func) == -1)
        {
            box.setText("Авиарейса с таким номером нет в системе!");
            box.exec();
        }
        else
        {
            this->database->ChangeState(false);

            int i;

            while ((i = this->database->FindTicket(Ticket("", "", num_flight),
                                                   [](const Ticket& a, const Ticket& b)
                                                   {
                                                       return a.GetNumFlight() == b.GetNumFlight();
                                                   })) != -1)
            {
                this->database->RemoveTicket(i, true);
            }

            while ((i = this->database->FindPurpose(Purpose(Nomination::FIRST_PILOT, num_flight, ""),
                                                    [](const Purpose& a, const Purpose& b)
                                                    {
                                                        return a.GetNumFlight() == b.GetNumFlight();
                                                    })) != -1)
            {
                this->database->RemovePurpose(i, true);
            }

            this->database->ChangeState(true);

            this->database->RemoveFlight(this->database->FindFlight(Flight(num_flight, "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0), func), true);

            box.setText("Авиарейс и связанные с ним данные удалены из системы!");
            box.exec();
        }
    }
}

void FlightWindow::CheckFlights()
{
    unsigned length = this->database->GetFlightSize();
    QDateTime now;
    QDateTime selected;
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    for (unsigned i = 0; i < length; i++)
    {
        Flight flt = this->database->GetFlight(i);

        now = QDateTime::currentDateTime();
        selected = QDateTime(flt.GetDate(), flt.GetTime());

        if ((flt.GetState() == FlightState::ON_TIME || flt.GetState() == FlightState::DELAYED) && qAbs(now.msecsTo(selected) / 60000) <= 240)
        {
            box.setText("На авиарейс с номером " + flt.GetNumFlight() + " пора объявить регистрацию!");
            box.exec();

            break;
        }
        else if (flt.GetState() == FlightState::CHECK_IN && qAbs(now.msecsTo(selected) / 60000) <= 20)
        {
            box.setText("На авиарейс с номером " + flt.GetNumFlight() + " пора объявить посадку!");
            box.exec();

            break;
        }
        else if (flt.GetState() == FlightState::BOARDING && qAbs(now.msecsTo(selected) / 60000) == 0)
        {
            box.setText("Авиарейсу с номером " + flt.GetNumFlight() + " пора на взлётную полосу!");
            box.exec();

            break;
        }
        else if (flt.GetState() == FlightState::CANCELLED || flt.GetState() == FlightState::DIVERTED)
        {
            box.setText("Авиарейс с номером " + flt.GetNumFlight() + " возможно стоит удалить из системы!");
            box.exec();

            break;
        }
    }
}
