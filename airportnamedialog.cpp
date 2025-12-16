#include "airportnamedialog.h"
#include "ui_airportnamedialog.h"

#include <QRegularExpressionValidator>

AirportNameDialog::AirportNameDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AirportNameDialog)
{
    ui->setupUi(this);

    QRegularExpressionValidator* val = new QRegularExpressionValidator(this);
    val->setRegularExpression(QRegularExpression("([A-Z][a-z]+-[A-Z][a-z]+|[А-Я][а-я]+-[А-Я][а-я]+)"));
    ui->airport_name_edit->setValidator(val);

    connect(ui->airport_name_edit, &QLineEdit::textChanged, this, &AirportNameDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

AirportNameDialog::~AirportNameDialog()
{
    delete ui;
}

void AirportNameDialog::Validation() const
{
    if (ui->airport_name_edit->text().length() > 0 && ui->airport_name_edit->text().length() <= 30)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

QString AirportNameDialog::GetData() const
{
    return ui->airport_name_edit->text();
}
