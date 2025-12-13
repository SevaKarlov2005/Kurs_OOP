#ifndef NUMTICKETDIALOG_H
#define NUMTICKETDIALOG_H

#include <QDialog>

namespace Ui {
class NumTicketDialog;
}

class NumTicketDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NumTicketDialog *ui;
public:
    explicit NumTicketDialog(QWidget *parent = nullptr);
    ~NumTicketDialog();
    void Validation() const;
    QString GetData() const;
};

#endif // NUMTICKETDIALOG_H
