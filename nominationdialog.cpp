#include "nominationdialog.h"
#include "ui_nominationdialog.h"

#include <QRegularExpressionValidator>

NominationDialog::NominationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NominationDialog)
{
    ui->setupUi(this);

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));
    val2->setRegularExpression(QRegularExpression("(БП|ПЛ|ИН)-[0-9]{6}"));

    ui->num_flight_edit->setValidator(val1);
    ui->num_certificate_edit->setValidator(val2);

    connect(ui->num_flight_edit, &QLineEdit::textChanged, this, &NominationDialog::Validation);
    connect(ui->num_certificate_edit, &QLineEdit::textChanged, this, &NominationDialog::Validation);
}

NominationDialog::~NominationDialog()
{
    delete ui;
}

void NominationDialog::Validation() const
{
    if (ui->num_flight_edit->text().length() == 7 && ui->num_certificate_edit->text().length() == 9)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

QString NominationDialog::GetData() const
{
    return ui->num_flight_edit->text() + "*" + ui->num_certificate_edit->text();
}
