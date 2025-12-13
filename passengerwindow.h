#ifndef PASSENGERWINDOW_H
#define PASSENGERWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "passengertablemodel.h"
#include "passengerproxymodel.h"

namespace Ui {
class PassengerWindow;
}

class PassengerWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::PassengerWindow *ui;
    DataBase* database;
    PassengerTableModel* source_model;
    PassengerProxyModel* proxy_model;
public:
    explicit PassengerWindow(DataBase* db, QWidget *parent = nullptr);
    ~PassengerWindow();
    void AddPassenger();
    void ChangePassenger();
    void RemovePassenger();
};

#endif // PASSENGERWINDOW_H
