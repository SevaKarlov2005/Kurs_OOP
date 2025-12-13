#ifndef AIRPORTWINDOW_H
#define AIRPORTWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "airporttablemodel.h"
#include "airportproxymodel.h"

namespace Ui {
class AirportWindow;
}

class AirportWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::AirportWindow *ui;
    DataBase* database;
    AirportTableModel* source_model;
    AirportProxyModel* proxy_model;
public:
    explicit AirportWindow(DataBase* db, QWidget *parent = nullptr);
    ~AirportWindow();
    void AddAirport();
    void ChangeAirport();
    void RemoveAirport();
};

#endif // AIRPORTWINDOW_H
