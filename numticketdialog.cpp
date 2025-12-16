#include "numticketdialog.h"
#include "ui_numticketdialog.h"

#include <QRegularExpressionValidator>

NumTicketDialog::NumTicketDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NumTicketDialog)
{
    ui->setupUi(this);

    QRegularExpressionValidator* val = new QRegularExpressionValidator(this);
    val->setRegularExpression(QRegularExpression("[0-9]{9}"));
    ui->num_ticket_edit->setValidator(val);

    connect(ui->num_ticket_edit, &QLineEdit::textChanged, this, &NumTicketDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

NumTicketDialog::~NumTicketDialog()
{
    delete ui;
}

void NumTicketDialog::Validation() const
{
    if (ui->num_ticket_edit->text().length() == 9)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

QString NumTicketDialog::GetData() const
{
    return ui->num_ticket_edit->text();
}
