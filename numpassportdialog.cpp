#include "numpassportdialog.h"
#include "ui_numpassportdialog.h"

#include <QRegularExpressionValidator>

NumPassportDialog::NumPassportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NumPassportDialog)
{
    ui->setupUi(this);

    QRegularExpressionValidator* val = new QRegularExpressionValidator(this);
    val->setRegularExpression(QRegularExpression("[0-9]{4}-[0-9]{6}"));
    ui->num_passport_edit->setValidator(val);

    connect(ui->num_passport_edit, &QLineEdit::textChanged, this, &NumPassportDialog::Validation);
}

NumPassportDialog::~NumPassportDialog()
{
    delete ui;
}

void NumPassportDialog::Validation() const
{
    if (ui->num_passport_edit->text().length() == 11)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

QString NumPassportDialog::GetData() const
{
    return ui->num_passport_edit->text();
}
