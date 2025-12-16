#include "ticketdialog.h"
#include "ui_ticketdialog.h"

#include <QRegularExpressionValidator>

TicketDialog::TicketDialog(Ticket* ticket, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TicketDialog)
{
    ui->setupUi(this);

    if (ticket)
    {
        ui->num_ticket_edit->setText(ticket->GetNumTicket());
        ui->num_passport_edit->setText(ticket->GetNumPassport());
        ui->num_flight_edit->setText(ticket->GetNumFlight());
    }

    QRegularExpressionValidator* val1 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val2 = new QRegularExpressionValidator(this);
    QRegularExpressionValidator* val3 = new QRegularExpressionValidator(this);

    val1->setRegularExpression(QRegularExpression("[0-9]{9}"));
    val2->setRegularExpression(QRegularExpression("[0-9]{4}-[0-9]{6}"));
    val3->setRegularExpression(QRegularExpression("[A-Z]{3}-[0-9]{3}"));

    ui->num_ticket_edit->setValidator(val1);
    ui->num_passport_edit->setValidator(val2);
    ui->num_flight_edit->setValidator(val3);

    connect(ui->num_ticket_edit, &QLineEdit::textChanged, this, &TicketDialog::Validation);
    connect(ui->num_passport_edit, &QLineEdit::textChanged, this, &TicketDialog::Validation);
    connect(ui->num_flight_edit, &QLineEdit::textChanged, this, &TicketDialog::Validation);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

TicketDialog::~TicketDialog()
{
    delete ui;
}

void TicketDialog::Validation() const
{
    if (ui->num_ticket_edit->text().length() == 9 &&
        ui->num_passport_edit->text().length() == 11 &&
        ui->num_flight_edit->text().length() == 7)
        ui->buttonBox->setEnabled(true);
    else
        ui->buttonBox->setEnabled(false);
}

Ticket TicketDialog::GetData() const
{
    return Ticket(ui->num_ticket_edit->text(), ui->num_passport_edit->text(), ui->num_flight_edit->text());
}
