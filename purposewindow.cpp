#include "purposewindow.h"
#include "ui_purposewindow.h"

PurposeWindow::PurposeWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PurposeWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new PurposeTableModel(this->database, this);

    this->proxy_model = new PurposeProxyModel(ui->num_flight_edit, ui->num_certificate_edit, ui->nomination_box, this);

    this->proxy_model->setSourceModel(this->source_model);

    ui->purpose_table->setModel(this->proxy_model);

    connect(ui->add_button, &QPushButton::clicked, this, &PurposeWindow::AddPurpose);
    connect(ui->change_button, &QPushButton::clicked, this, &PurposeWindow::ChangePurpose);
    connect(ui->delete_button, &QPushButton::clicked, this, &PurposeWindow::RemovePurpose);
}

PurposeWindow::~PurposeWindow()
{
    delete ui;
}

void PurposeWindow::AddPurpose()
{

}

void PurposeWindow::ChangePurpose()
{

}

void PurposeWindow::RemovePurpose()
{

}
