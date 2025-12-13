#ifndef TICKETPROXYMODEL_H
#define TICKETPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QLineEdit>

class TicketProxyModel : public QSortFilterProxyModel
{
private:
    QLineEdit* num_ticket_edit;
    QLineEdit* num_passport_edit;
    QLineEdit* num_flight_edit;
public:
    explicit TicketProxyModel(QLineEdit* num_ticket_edit, QLineEdit* num_passport_edit, QLineEdit* num_flight_edit, QObject *parent = nullptr);
     bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // TICKETPROXYMODEL_H
