#include "airportdialog.h"
#include "ui_airportdialog.h"

#include <QRegularExpressionValidator>

AirportDialog::AirportDialog(Airport* airport, unsigned short mod, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AirportDialog)
{
    ui->setupUi(this);

    if (mod == 1)
        ui->airport_name_edit->setEnabled(false);

    if (airport)
    {
        ui->airport_name_edit->setText(airport->GetName());
        ui->rainfall_spin->setValue(airport->GetRainfall());
        ui->speed_spin->setValue(airport->GetSpeed());
        ui->direction_spin->setValue(airport->GetDirection());
        ui->temperature_spin->setValue(airport->GetTemperature());
    }

    QRegularExpressionValidator* val = new QRegularExpressionValidator(this);
    val->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    ui->airport_name_edit->setValidator(val);

    connect(ui->airport_name_edit, &QLineEdit::textChanged, this, &AirportDialog::Validation);
    connect(ui->rainfall_spin, &QSpinBox::valueChanged, this, &AirportDialog::Validation);
    connect(ui->speed_spin, &QSpinBox::valueChanged, this, &AirportDialog::Validation);
    connect(ui->direction_spin, &QSpinBox::valueChanged, this, &AirportDialog::Validation);
    connect(ui->temperature_spin, &QSpinBox::valueChanged, this, &AirportDialog::Validation);
}

AirportDialog::~AirportDialog()
{
    delete ui;
}

void AirportDialog::Validation() const
{
    if (ui->airport_name_edit->text().length() > 0 && ui->airport_name_edit->text().length() <= 30)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

Airport AirportDialog::GetData() const
{
    return Airport(ui->airport_name_edit->text(), ui->rainfall_spin->value(), ui->speed_spin->value(),
                   ui->direction_spin->value(), ui->temperature_spin->value());
}
