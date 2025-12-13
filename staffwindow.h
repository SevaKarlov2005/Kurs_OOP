#ifndef STAFFWINDOW_H
#define STAFFWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "stafftablemodel.h"
#include "staffproxymodel.h"

namespace Ui {
class StaffWindow;
}

class StaffWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::StaffWindow *ui;
    DataBase* database;
    StaffTableModel* source_model;
    StaffProxyModel* proxy_model;
public:
    explicit StaffWindow(DataBase* db, QWidget *parent = nullptr);
    ~StaffWindow();
    void AddStaff();
    void ChangeStaff();
    void RemoveStaff();
};

#endif // STAFFWINDOW_H
