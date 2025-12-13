#ifndef NUMFLIGHTDIALOG_H
#define NUMFLIGHTDIALOG_H

#include <QDialog>

namespace Ui {
class NumFlightDialog;
}

class NumFlightDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::NumFlightDialog *ui;
public:
    explicit NumFlightDialog(QWidget *parent = nullptr);
    ~NumFlightDialog();
    void Validation() const;
    QString GetData() const;
};

#endif // NUMFLIGHTDIALOG_H
