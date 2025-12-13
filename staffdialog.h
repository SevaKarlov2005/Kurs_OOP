#ifndef STAFFDIALOG_H
#define STAFFDIALOG_H

#include <QDialog>
#include "staff.h"

namespace Ui {
class StaffDialog;
}

class StaffDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::StaffDialog *ui;
public:
    explicit StaffDialog(Staff* staff, QWidget *parent = nullptr);
    ~StaffDialog();
    void Validation() const;
    Staff GetData() const;
};

#endif // STAFFDIALOG_H
