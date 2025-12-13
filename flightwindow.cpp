#include "flightwindow.h"
#include "ui_flightwindow.h"

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

}

void FlightWindow::ChangeFlight()
{

}

void FlightWindow::RemoveFlight()
{

}
