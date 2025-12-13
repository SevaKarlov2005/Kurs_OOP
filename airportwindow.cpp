#include "airportwindow.h"
#include "ui_airportwindow.h"

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
    this->database->AddAirport(Airport("AMOGUS", 49, 23, 90, -10), true);
}

void AirportWindow::ChangeAirport()
{
    this->database->UpdateAirport(Airport("BAMOGUS", 49, 60, 90, -10), 2, true);
}

void AirportWindow::RemoveAirport()
{
    this->database->RemoveAirport(2, true);
}
