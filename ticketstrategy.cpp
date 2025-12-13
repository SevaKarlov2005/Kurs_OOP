#include "ticketstrategy.h"

void TicketStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO ticket (num_ticket, id_passenger, id_flight) "
                        "VALUES "
                        "("
                        "'%1', "
                        "(SELECT id_passenger FROM passenger WHERE num_passport = '%2'), "
                        "(SELECT id_flight FROM flight WHERE num_flight = '%3')"
                        ")")
                    .arg(str_list[0])
                    .arg(str_list[1])
                    .arg(str_list[2]));
}

void TicketStrategy::Update(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("UPDATE ticket "
                        "SET "
                        "num_ticket = '%1', "
                        "id_passenger = (SELECT id_passenger FROM passenger WHERE num_passport = '%2'), "
                        "id_flight = (SELECT id_flight FROM flight WHERE num_flight = '%3') "
                        "WHERE num_ticket = '%4'")
                    .arg(str_list[3])
                    .arg(str_list[4])
                    .arg(str_list[5])
                    .arg(str_list[0]));
}

void TicketStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM ticket "
                        "WHERE num_ticket = '%1'")
                    .arg(str_list[0]));
}
