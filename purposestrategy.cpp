#include "purposestrategy.h"

void PurposeStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO purpose (purpose_name, id_flight, id_staff) "
                        "VALUES "
                        "("
                        "'%1', "
                        "(SELECT id_flight FROM flight WHERE num_flight = '%2'), "
                        "(SELECT id_staff FROM staff WHERE num_certificate = '%3')"
                        ")")
                    .arg(str_list[0])
                    .arg(str_list[1])
                    .arg(str_list[2]));
}

void PurposeStrategy::Update(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("UPDATE purpose "
                        "SET "
                        "purpose_name = '%1', "
                        "id_flight = (SELECT id_flight FROM flight WHERE num_flight = '%2'), "
                        "id_staff = (SELECT id_staff FROM staff WHERE num_certificate = '%3') "
                        "WHERE "
                        "id_flight = (SELECT f.id_flight FROM flight as f WHERE f.num_flight = '%4') "
                        "AND "
                        "id_staff = (SELECT s.id_staff FROM staff as s WHERE s.num_certificate = '%5')")
                    .arg(str_list[3])
                    .arg(str_list[4])
                    .arg(str_list[5])
                    .arg(str_list[1])
                    .arg(str_list[2]));
}

void PurposeStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM purpose "
                        "WHERE "
                        "id_flight = (SELECT id_flight FROM flight WHERE num_flight = '%1') AND "
                        "id_staff = (SELECT id_staff FROM staff WHERE num_certificate = '%2')")
                    .arg(str_list[1])
                    .arg(str_list[2]));
}
