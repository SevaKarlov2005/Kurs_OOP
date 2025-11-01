#include "ticketstrategy.h"

void TicketStrategy::Insert(QSqlQuery* query, const QString& data)
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO ticket (num_ticket, id_passenger, id_flight)"
                        "VALUES"
                        "("
                        "'%s',"
                        "(SELECT id_pessenger FROM passenger WHERE num_passport = '%s'),"
                        "(SELECT id_flight FROM flight WHERE num_flight = '%s')"
                        ")")
                    .arg(str_list[0])
                    .arg(str_list[1])
                    .arg(str_list[2]));
}

void TicketStrategy::Update(QSqlQuery* query, const QString& data)
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("UPDATE ticket"
                        "SET"
                        "num_ticket = '%s',"
                        "id_passenger = (SELECT id_passenger FROM passenger WHERE num_passport = '%s'),"
                        "id_flight = (SELECT id_flight FROM flight WHERE num_flight = '%s')"
                        "WHERE num_ticket = '%s'")
                    .arg(str_list[3])
                    .arg(str_list[4])
                    .arg(str_list[5])
                    .arg(str_list[0]));
}

void TicketStrategy::Delete(QSqlQuery* query, const QString& data)
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM ticket"
                        "WHERE num_ticket = '%s'")
                    .arg(str_list[0]));
}
