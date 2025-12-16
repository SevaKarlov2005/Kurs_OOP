#include "flightdialog.h"
#include "ui_flightdialog.h"

FlightDialog::FlightDialog(Flight* flight, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FlightDialog)
{
    ui->setupUi(this);

    if (flight)
    {
        ui->num_flight_edit->setText(flight->GetNumFlight());
        ui->company_edit->setText(flight->GetCompany());
        ui->from_edit->setText(flight->GetFrom());
        ui->to_edit->setText(flight->GetTo());
        ui->date_date->setDate(flight->GetDate());
        ui->time_time->setTime(flight->GetTime());
        ui->state_box->setCurrentIndex(flight->GetState());
        ui->all_place_spin->setValue(flight->GetAllPlace());
        ui->free_place_spin->setValue(flight->GetFreePlace());
    }

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val4 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));
    val2->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val3->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    val4->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));

    ui->num_flight_edit->setValidator(val1);
    ui->company_edit->setValidator(val2);
    ui->from_edit->setValidator(val3);
    ui->to_edit->setValidator(val4);

    connect(ui->num_flight_edit, &QLineEdit::textChanged, this, &FlightDialog::Validation);
    connect(ui->company_edit, &QLineEdit::textChanged, this, &FlightDialog::Validation);
    connect(ui->from_edit, &QLineEdit::textChanged, this, &FlightDialog::Validation);
    connect(ui->to_edit, &QLineEdit::textChanged, this, &FlightDialog::Validation);
    connect(ui->date_date, &QDateEdit::dateChanged, this, &FlightDialog::Validation);
    connect(ui->time_time, &QTimeEdit::timeChanged, this, &FlightDialog::Validation);
    connect(ui->state_box, &QComboBox::currentIndexChanged, this, &FlightDialog::Validation);
    connect(ui->all_place_spin, &QSpinBox::valueChanged, this, &FlightDialog::Validation);
    connect(ui->free_place_spin, &QSpinBox::valueChanged, this, &FlightDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

FlightDialog::~FlightDialog()
{
    delete ui;
}

void FlightDialog::Validation() const
{
    if (ui->num_flight_edit->text().length() == 7 &&
        ui->company_edit->text().length() > 0 && ui->company_edit->text().length() <= 30 &&
        ui->from_edit->text().length() > 0 && ui->from_edit->text().length() <= 30 &&
        ui->to_edit->text().length() > 0 && ui->to_edit->text().length() <= 30 &&
        (ui->date_date->date() > QDate::currentDate() || (ui->date_date->date() == QDate::currentDate() && ui->time_time->time() >= QTime::currentTime())) &&
        ui->all_place_spin->value() > 0 && ui->free_place_spin->value() <= ui->all_place_spin->value())
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

Flight FlightDialog::GetData() const
{
    return Flight(ui->num_flight_edit->text(), ui->company_edit->text(), ui->from_edit->text(),
                  ui->to_edit->text(), ui->date_date->date(), ui->time_time->time(), (FlightState)ui->state_box->currentIndex(),
                  ui->all_place_spin->value(), ui->free_place_spin->value());
}
