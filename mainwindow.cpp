#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->database = new DataBase("airport");

    this->airport_window = new AirportWindow(this->database, this);
    this->passenger_window = new PassengerWindow(this->database, this);
    this->staff_window = new StaffWindow(this->database, this);
    this->flight_window = new FlightWindow(this->database, this);
    this->ticket_window = new TicketWindow(this->database, this);
    this->purpose_window = new PurposeWindow(this->database, this);

    connect(ui->airport_button, &QPushButton::clicked, this, &MainWindow::OpenAirportWindow);
    connect(ui->passenger_button, &QPushButton::clicked, this, &MainWindow::OpenPassengerWindow);
    connect(ui->staff_button, &QPushButton::clicked, this, &MainWindow::OpenStaffWindow);
    connect(ui->flight_button, &QPushButton::clicked, this, &MainWindow::OpenFlightWindow);
    connect(ui->ticket_button, &QPushButton::clicked, this, &MainWindow::OpenTicketWindow);
    connect(ui->purpose_button, &QPushButton::clicked, this, &MainWindow::OpenPurposeWindow);
    connect(ui->load_button, &QPushButton::clicked, this, &MainWindow::Load);
    connect(ui->save_button, &QPushButton::clicked, this, &MainWindow::Save);
    connect(ui->cancel_button, &QPushButton::clicked, this, &MainWindow::Cancel);

    connect(this->database, &DataBase::ChangeAirport, this, &MainWindow::Update);
    connect(this->database, &DataBase::ChangePassenger, this, &MainWindow::Update);
    connect(this->database, &DataBase::ChangeStaff, this, &MainWindow::Update);
    connect(this->database, &DataBase::ChangeFlight, this, &MainWindow::Update);
    connect(this->database, &DataBase::ChangeTicket, this, &MainWindow::Update);
    connect(this->database, &DataBase::ChangePurpose, this, &MainWindow::Update);
}

MainWindow::~MainWindow()
{
    delete this->database;
}

void MainWindow::OpenAirportWindow()
{
    this->airport_window->show();
}

void MainWindow::OpenPassengerWindow()
{
    this->passenger_window->show();
}

void MainWindow::OpenStaffWindow()
{
    this->staff_window->show();
}

void MainWindow::OpenFlightWindow()
{
    this->flight_window->show();
}

void MainWindow::OpenTicketWindow()
{
    this->ticket_window->show();
}

void MainWindow::OpenPurposeWindow()
{
    this->purpose_window->show();
}

void MainWindow::Load()
{
    QMessageBox box;

    box.setWindowTitle("Предупреждение");
    box.setIcon(QMessageBox::Warning);
    box.setText("При загрузке данных несохранённые данные будут утеряны!\nЕсли вы хотите продолжить нажмите на кнопку OK.");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Cancel);

    if (box.exec() == QMessageBox::Ok)
    {
        this->database->Load();

        while (!this->caretaker.IsEmpty())
            this->caretaker.GetFirst();

        ui->save_button->setEnabled(false);
        ui->cancel_button->setEnabled(false);
    }
}

void MainWindow::Save()
{
    QMessageBox box;

    box.setWindowTitle("Предупреждение");
    box.setIcon(QMessageBox::Warning);
    box.setText("После сохранения изменений их нельзя будет отменить!\nЕсли вы хотите продолжить нажмите на кнопку OK.");
    box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box.setDefaultButton(QMessageBox::Cancel);

    if (box.exec() == QMessageBox::Ok)
    {
        while (!this->caretaker.IsEmpty())
            this->database->Save(this->caretaker.GetFirst());

        ui->save_button->setEnabled(false);
        ui->cancel_button->setEnabled(false);
    }
}

void MainWindow::Cancel()
{
    Memento memento = this->caretaker.GetLast();
    unsigned short count = memento.GetCount() - 1;

    this->database->SetPreviousState(memento);

    while (count > 0)
        this->database->SetPreviousState(this->caretaker.GetLast());

    if (this->caretaker.IsEmpty())
        ui->cancel_button->setEnabled(false);
}

void MainWindow::Update()
{
    this->caretaker.AddState(this->database->GetLastState());

    ui->save_button->setEnabled(true);
    ui->cancel_button->setEnabled(true);
}
