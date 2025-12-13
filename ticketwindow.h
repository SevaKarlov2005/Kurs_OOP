#ifndef TICKETWINDOW_H
#define TICKETWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "tickettablemodel.h"
#include "ticketproxymodel.h"

namespace Ui {
class TicketWindow;
}

class TicketWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::TicketWindow *ui;
    DataBase* database;
    TicketTableModel* source_model;
    TicketProxyModel* proxy_model;
public:
    explicit TicketWindow(DataBase* db, QWidget *parent = nullptr);
    ~TicketWindow();
    void AddTicket();
    void ChangeTicket();
    void RemoveTicket();
};

#endif // TICKETWINDOW_H
