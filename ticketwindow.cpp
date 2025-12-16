#include "ticketwindow.h"
#include "ui_ticketwindow.h"

#include <QMessageBox>
#include "ticketdialog.h"
#include "numticketdialog.h"

TicketWindow::TicketWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TicketWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new TicketTableModel(this->database, this);

    this->proxy_model = new TicketProxyModel(ui->num_ticket_edit, ui->num_passport_edit, ui->num_flight_edit, this);

    this->proxy_model->setSourceModel(this->source_model);

    ui->ticket_table->setModel(this->proxy_model);

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[0-9]{9}"));
    val2->setRegularExpression(QRegularExpression("[0-9]{4}-[0-9]{6}"));
    val3->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));

    ui->num_ticket_edit->setValidator(val1);
    ui->num_passport_edit->setValidator(val2);
    ui->num_flight_edit->setValidator(val3);

    connect(ui->add_button, &QPushButton::clicked, this, &TicketWindow::AddTicket);
    connect(ui->change_button, &QPushButton::clicked, this, &TicketWindow::ChangeTicket);
    connect(ui->delete_button, &QPushButton::clicked, this, &TicketWindow::RemoveTicket);
}

TicketWindow::~TicketWindow()
{
    delete ui;
}

void TicketWindow::AddTicket()
{
    TicketDialog add_dialog(NULL, this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (add_dialog.exec() == 1)
    {
        Ticket ticket = add_dialog.GetData();
        bool (*func)(const Ticket&, const Ticket&) = [](const Ticket& a, const Ticket& b)
        {
            return a.GetNumTicket() == b.GetNumTicket();
        };

        // Проверка на существование билета с таким номером
        if (this->database->FindTicket(ticket, func) != -1)
        {
            box.setText("Авиабилет с таким номером уже есть в системе!");
            box.exec();
        }
        else
        {
            // Проверка на существование пассажира
            bool (*findPassengerFunc)(const Passenger&, const Passenger&) = [](const Passenger& a, const Passenger& b)
            {
                return a.GetNumPassport() == b.GetNumPassport();
            };

            if (this->database->FindPassenger(Passenger(ticket.GetNumPassport(), "", QDate(), "", "", "", QDate()), findPassengerFunc) == -1)
            {
                box.setText("Система не смогла добавить авиабилет!");
                box.exec();
                return;
            }

            // Проверка на существование рейса
            bool (*findFlightFunc)(const Flight&, const Flight&) = [](const Flight& a, const Flight& b)
            {
                return a.GetNumFlight() == b.GetNumFlight();
            };

            int flightIndex = this->database->FindFlight(Flight(ticket.GetNumFlight(), "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0), findFlightFunc);

            if (flightIndex == -1)
            {
                box.setText("Система не смогла добавить авиабилет!");
                box.exec();
                return;
            }

            // Проверка наличия свободных мест
            Flight flight = this->database->GetFlight(flightIndex);
            if (flight.GetFreePlace() <= 0)
            {
                box.setText("Система не смогла добавить авиабилет!");
                box.exec();
                return;
            }

            // Уменьшаем количество свободных мест
            flight.SetFreePlace(flight.GetFreePlace() - 1);
            this->database->UpdateFlight(flight, flightIndex, true);

            // Добавляем билет
            this->database->AddTicket(ticket, true);

            box.setText("Авиабилет добавлен в систему!");
            box.exec();
        }
    }
}

void TicketWindow::ChangeTicket()
{
    NumTicketDialog old_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (old_dialog.exec() == 1)
    {
        QString old_num_ticket = old_dialog.GetData();

        int i = this->database->FindTicket(Ticket(old_num_ticket, "", ""),
                                           [](const Ticket& a, const Ticket& b)
                                           {
                                               return a.GetNumTicket() == b.GetNumTicket();
                                           });

        if (i == -1)
        {
            box.setText("Авиабилета с таким номером нет в системе!");
            box.exec();
        }
        else
        {
            Ticket ticket = this->database->GetTicket(i);
            TicketDialog upd_dialog(&ticket, this);

            if (upd_dialog.exec() == 1)
            {
                Ticket new_ticket = upd_dialog.GetData();

                int j = this->database->FindTicket(new_ticket,
                                                   [](const Ticket& a, const Ticket& b)
                                                   {
                                                       return a.GetNumTicket() == b.GetNumTicket();
                                                   });

                if (j != -1)
                {
                    box.setText("Система не смогла обновить авиабилет!");
                    box.exec();
                }
                else
                {
                    // Если изменился рейс, обновляем количество мест
                    if (ticket.GetNumFlight() != new_ticket.GetNumFlight())
                    {
                        // Освобождаем место на старом рейсе
                        int oldFlightIndex = this->database->FindFlight(Flight(ticket.GetNumFlight(), "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                                        [](const Flight& a, const Flight& b)
                                                                        {
                                                                            return a.GetNumFlight() == b.GetNumFlight();
                                                                        });
                        if (oldFlightIndex != -1)
                        {
                            Flight oldFlight = this->database->GetFlight(oldFlightIndex);
                            oldFlight.SetFreePlace(oldFlight.GetFreePlace() + 1);
                            this->database->UpdateFlight(oldFlight, oldFlightIndex, true);
                        }

                        // Занимаем место на новом рейсе
                        int newFlightIndex = this->database->FindFlight(Flight(new_ticket.GetNumFlight(), "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                                        [](const Flight& a, const Flight& b)
                                                                        {
                                                                            return a.GetNumFlight() == b.GetNumFlight();
                                                                        });
                        if (newFlightIndex != -1)
                        {
                            Flight newFlight = this->database->GetFlight(newFlightIndex);
                            if (newFlight.GetFreePlace() > 0)
                            {
                                newFlight.SetFreePlace(newFlight.GetFreePlace() - 1);
                                this->database->UpdateFlight(newFlight, newFlightIndex, true);
                            }
                            else
                            {
                                box.setText("Система не смогла обновить авиабилет!");
                                box.exec();
                                return;
                            }
                        }
                    }

                    this->database->UpdateTicket(new_ticket, i, true);
                    box.setText("Система обновила авиабилет!");
                    box.exec();
                }
            }
        }
    }
}

void TicketWindow::RemoveTicket()
{
    NumTicketDialog del_dialog(this);
    QMessageBox box;

    box.setWindowTitle("Уведомление");
    box.setIcon(QMessageBox::Warning);

    if (del_dialog.exec() == 1)
    {
        QString num_ticket = del_dialog.GetData();
        bool (*func)(const Ticket&, const Ticket&) = [](const Ticket& a, const Ticket& b)
        {
            return a.GetNumTicket() == b.GetNumTicket();
        };

        if (this->database->FindTicket(Ticket(num_ticket, "", ""), func) == -1)
        {
            box.setText("Авиабилета с таким номером нет в системе!");
            box.exec();
        }
        else
        {
            this->database->ChangeState(false);

            int i = this->database->FindTicket(Ticket(num_ticket, "", ""), func);
            QString num_flight = this->database->GetTicket(i).GetNumFlight();
            int ind = this->database->FindFlight(Flight(num_flight, "", "", "", QDate(), QTime(), FlightState::ON_TIME, 0, 0),
                                                 [](const Flight& a, const Flight& b)
                                                 {
                                                     return a.GetNumFlight() == b.GetNumFlight();
                                                 });
            Flight flt = this->database->GetFlight(ind);

            flt.SetFreePlace(flt.GetFreePlace() + 1);
            this->database->UpdateFlight(flt, ind, true);

            this->database->ChangeState(true);

            this->database->RemoveTicket(i, true);

            box.setText("Авиабилет и связанные с ним данные удалены из системы!");
            box.exec();
        }
    }
}
