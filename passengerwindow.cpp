#include "passengerwindow.h"
#include "ui_passengerwindow.h"

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

}

void PassengerWindow::ChangePassenger()
{

}

void PassengerWindow::RemovePassenger()
{

}
