#ifndef PASSENGERDIALOG_H
#define PASSENGERDIALOG_H

#include <QDialog>
#include "passenger.h"

namespace Ui {
class PassengerDialog;
}

class PassengerDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::PassengerDialog *ui;
public:
    explicit PassengerDialog(Passenger* passenger, QWidget *parent = nullptr);
    ~PassengerDialog();
    void Validation() const;
    Passenger GetData() const;
};

#endif // PASSENGERDIALOG_H
