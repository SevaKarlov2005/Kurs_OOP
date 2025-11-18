#include "flightstrategy.h"

void FlightStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO flight (num_flight, company, id_from, id_to, date, time, state, all_place, free_place)"
                        "VALUES"
                        "("
                        "'%s',"
                        "'%s',"
                        "(SELECT id_airport FROM airport WHERE airport_name = '%s'),"
                        "(SELECT id_airport FROM airport WHERE airport_name = '%s'),"
                        "'%s',"
                        "'%s',"
                        "'%s',"
                        "%s,"
                        "%s"
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

    query->exec(QString("UPDATE flight"
                        "SET num_flight = '%s',"
                        "company = '%s,"
                        "id_from = (SELECT id_airport FROM airport WHERE airport_name = '%s'),"
                        "id_to = (SELECT id_airport FROM airport WHERE airport_name = '%s'),"
                        "date = '%s',"
                        "time = '%s',"
                        "state = '%s',"
                        "all_place = %s,"
                        "free_place = %s"
                        "WHERE num_flight = '%s'")
                    .arg(str_list[9])
                    .arg(str_list[10])
                    .arg(str_list[11])
                    .arg(str_list[12])
                    .arg(str_list[13])
                    .arg(str_list[14])
                    .arg(str_list[15])
                    .arg(str_list[16])
                    .arg(str_list[17]));
}

void FlightStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM flight"
                        "WHERE num_flight = '%s'")
                    .arg(str_list[0]));
}
