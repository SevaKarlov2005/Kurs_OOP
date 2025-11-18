#include "purposestrategy.h"

void PurposeStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO purpose (name, id_flight, id_staff)"
                        "VALUES"
                        "("
                        "'%s',"
                        "(SELECT id_flight FROM flight WHERE num_flight = '%s'),"
                        "(SELECT id_staff FROM staff WHERE num_certificate = '%s')"
                        ")")
                    .arg(str_list[0])
                    .arg(str_list[1])
                    .arg(str_list[2]));
}

void PurposeStrategy::Update(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("UPDATE purpose"
                        "SET"
                        "name = '%s',"
                        "id_flight = (SELECT id_flight FROM flight WHERE num_flight = '%s'),"
                        "id_staff = (SELECT id_staff FROM staff WHERE num_certificate = '%s')"
                        "WHERE num_ticket = '%s'")
                    .arg(str_list[3])
                    .arg(str_list[4])
                    .arg(str_list[5])
                    .arg(str_list[0]));
}

void PurposeStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM purpose"
                        "WHERE"
                        "id_flight = (SELECT id_flight FROM flight WHERE num_flight = '%s') AND"
                        "id_staff = (SELECT id_staff FROM staff WHERE num_certificate = '%s')")
                    .arg(str_list[1])
                    .arg(str_list[2]));
}
