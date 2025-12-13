#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "caretaker.h"
#include "airportwindow.h"
#include "passengerwindow.h"
#include "staffwindow.h"
#include "flightwindow.h"
#include "ticketwindow.h"
#include "purposewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    DataBase* database;
    Caretaker caretaker;
    AirportWindow* airport_window;
    PassengerWindow* passenger_window;
    StaffWindow* staff_window;
    FlightWindow* flight_window;
    TicketWindow* ticket_window;
    PurposeWindow* purpose_window;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void OpenAirportWindow();
    void OpenPassengerWindow();
    void OpenStaffWindow();
    void OpenFlightWindow();
    void OpenTicketWindow();
    void OpenPurposeWindow();
    void Load();
    void Save();
    void Cancel();
    void Update();
};
#endif // MAINWINDOW_H
