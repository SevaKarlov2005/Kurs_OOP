#ifndef AIRPORTNAMEDIALOG_H
#define AIRPORTNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class AirportNameDialog;
}

class AirportNameDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::AirportNameDialog *ui;
public:
    explicit AirportNameDialog(QWidget *parent = nullptr);
    ~AirportNameDialog();
    void Validation() const;
    QString GetData() const;
};

#endif // AIRPORTNAMEDIALOG_H
