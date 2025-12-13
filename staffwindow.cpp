#include "staffwindow.h"
#include "ui_staffwindow.h"

StaffWindow::StaffWindow(DataBase* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StaffWindow)
{
    ui->setupUi(this);

    this->database = db;

    this->source_model = new StaffTableModel(this->database, this);

    this->proxy_model = new StaffProxyModel(ui->num_certificate_edit, ui->surname_edit, ui->name_edit,
                                            ui->patronym_edit, ui->profession_box, this);

    this->proxy_model->setSourceModel(this->source_model);

    ui->staff_table->setModel(this->proxy_model);

    connect(ui->add_button, &QPushButton::clicked, this, &StaffWindow::AddStaff);
    connect(ui->change_button, &QPushButton::clicked, this, &StaffWindow::ChangeStaff);
    connect(ui->delete_button, &QPushButton::clicked, this, &StaffWindow::RemoveStaff);
}

StaffWindow::~StaffWindow()
{
    delete ui;
}

void StaffWindow::AddStaff()
{

}

void StaffWindow::ChangeStaff()
{

}

void StaffWindow::RemoveStaff()
{

}
