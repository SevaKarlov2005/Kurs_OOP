#include "ticketwindow.h"
#include "ui_ticketwindow.h"

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

}

void TicketWindow::ChangeTicket()
{

}

void TicketWindow::RemoveTicket()
{

}
