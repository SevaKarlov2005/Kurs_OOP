#include "ticketproxymodel.h"

TicketProxyModel::TicketProxyModel(QLineEdit* num_ticket_edit, QLineEdit* num_passport_edit, QLineEdit* num_flight_edit, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->num_ticket_edit = num_ticket_edit;
    this->num_passport_edit = num_passport_edit;
    this->num_flight_edit = num_flight_edit;

    connect(this->num_ticket_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->num_passport_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->num_flight_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
}

bool TicketProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool num_ticket_flag;
    bool num_passport_flag;
    bool num_flight_flag;

    QString num_ticket = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)).toString();
    num_ticket_flag = num_ticket == this->num_ticket_edit->text() || this->num_ticket_edit->text() == "";

    QString num_passport = sourceModel()->data(sourceModel()->index(source_row, 1, source_parent)).toString();
    num_passport_flag = num_passport == this->num_passport_edit->text() || this->num_passport_edit->text() == "";

    QString num_flight = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toString();
    num_flight_flag = num_flight == this->num_flight_edit->text() || this->num_flight_edit->text() == "";

    return num_ticket_flag && num_passport_flag && num_flight_flag;
}
