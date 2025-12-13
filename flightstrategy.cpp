#include "flightstrategy.h"
#include <QDebug>

void FlightStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO flight (num_flight, company, id_from, id_to, date, time, state, all_place, free_place) "
                        "VALUES "
                        "("
                        "'%1', "
                        "'%2', "
                        "(SELECT id_airport FROM airport WHERE airport_name = '%3'), "
                        "(SELECT id_airport FROM airport WHERE airport_name = '%4'), "
                        "'%5', "
                        "'%6', "
                        "'%7', "
                        "%8, "
                        "%9"
                        ")")
                    .arg(str_list[0])
                    .arg(str_list[1])
                    .arg(str_list[2])
                    .arg(str_list[3])
                    .arg(str_list[4])
                    .arg(str_list[5])
                    .arg(str_list[6])
                    .arg(str_list[7])
                    .arg(str_list[8]));
}

void FlightStrategy::Update(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("UPDATE flight "
                        "SET num_flight = '%1', "
                        "company = '%2', "
                        "id_from = (SELECT id_airport FROM airport WHERE airport_name = '%3'), "
                        "id_to = (SELECT id_airport FROM airport WHERE airport_name = '%4'), "
                        "date = '%5', "
                        "time = '%6', "
                        "state = '%7', "
                        "all_place = %8, "
                        "free_place = %9 "
                        "WHERE num_flight = '%10'")
                    .arg(str_list[9])
                    .arg(str_list[10])
                    .arg(str_list[11])
                    .arg(str_list[12])
                    .arg(str_list[13])
                    .arg(str_list[14])
                    .arg(str_list[15])
                    .arg(str_list[16])
                    .arg(str_list[17])
                    .arg(str_list[0]));
}

void FlightStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM flight "
                        "WHERE num_flight = '%1'")
                    .arg(str_list[0]));
}
