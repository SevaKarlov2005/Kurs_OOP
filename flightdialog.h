#ifndef FLIGHTDIALOG_H
#define FLIGHTDIALOG_H

#include <QDialog>
#include "flight.h"

namespace Ui {
class FlightDialog;
}

class FlightDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::FlightDialog *ui;
public:
    explicit FlightDialog(Flight* flight, unsigned short mod, QWidget *parent = nullptr);
    ~FlightDialog();
    void Validation() const;
    Flight GetData() const;
};

#endif // FLIGHTDIALOG_H
