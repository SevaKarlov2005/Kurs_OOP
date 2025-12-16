#include "numflightdialog.h"
#include "ui_numflightdialog.h"

#include <QRegularExpressionValidator>

NumFlightDialog::NumFlightDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NumFlightDialog)
{
    ui->setupUi(this);

    QRegularExpressionValidator* val = new QRegularExpressionValidator(this);
    val->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));
    ui->num_flight_edit->setValidator(val);

    connect(ui->num_flight_edit, &QLineEdit::textChanged, this, &NumFlightDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

NumFlightDialog::~NumFlightDialog()
{
    delete ui;
}

void NumFlightDialog::Validation() const
{
    if (ui->num_flight_edit->text().length() == 7)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

QString NumFlightDialog::GetData() const
{
    return ui->num_flight_edit->text();
}
