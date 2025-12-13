#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
#include "ticket.h"

namespace Ui {
class TicketDialog;
}

class TicketDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::TicketDialog *ui;
public:
    explicit TicketDialog(Ticket* ticket, QWidget *parent = nullptr);
    ~TicketDialog();
    void Validation() const;
    Ticket GetData() const;
};

#endif // TICKETDIALOG_H
