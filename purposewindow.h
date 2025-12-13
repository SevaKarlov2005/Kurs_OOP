#ifndef PURPOSEWINDOW_H
#define PURPOSEWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "purposetablemodel.h"
#include "purposeproxymodel.h"

namespace Ui {
class PurposeWindow;
}

class PurposeWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::PurposeWindow *ui;
    DataBase* database;
    PurposeTableModel* source_model;
    PurposeProxyModel* proxy_model;
public:
    explicit PurposeWindow(DataBase* db, QWidget *parent = nullptr);
    ~PurposeWindow();
    void AddPurpose();
    void ChangePurpose();
    void RemovePurpose();
};

#endif // PURPOSEWINDOW_H
