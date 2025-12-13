#ifndef FLIGHTWINDOW_H
#define FLIGHTWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "flighttablemodel.h"
#include "flightproxymodel.h"

namespace Ui {
class FlightWindow;
}

class FlightWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::FlightWindow *ui;
    DataBase* database;
    FlightTableModel* source_model;
    FlightProxyModel* proxy_model;
public:
    explicit FlightWindow(DataBase* db, QWidget *parent = nullptr);
    ~FlightWindow();
    void AddFlight();
    void ChangeFlight();
    void RemoveFlight();
};

#endif // FLIGHTWINDOW_H
