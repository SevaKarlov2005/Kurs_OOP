#ifndef AIRPORTDIALOG_H
#define AIRPORTDIALOG_H

#include <QDialog>
#include "Airport.h"

namespace Ui {
class AirportDialog;
}

class AirportDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::AirportDialog *ui;
public:
    explicit AirportDialog(Airport* airport, unsigned short mod, QWidget *parent = nullptr);
    ~AirportDialog();
    void Validation() const;
    Airport GetData() const;
};

#endif // AIRPORTDIALOG_H
