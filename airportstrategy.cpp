#include "airportstrategy.h"

void AirportStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO airport (airport_name, rainfall, direction, speed, temperature) "
                        "VALUES "
                        "("
                        "'%1', "
                        "%2, "
                        "%3, "
                        "%4, "
                        "%5"
                        ")")
                .arg(str_list[0])
                .arg(str_list[1])
                .arg(str_list[2])
                .arg(str_list[3])
                .arg(str_list[4]));
}

void AirportStrategy::Update(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("UPDATE airport "
                        "SET "
                        "airport_name = '%1', "
                        "rainfall = %2, "
                        "direction = %3, "
                        "speed = %4, "
                        "temperature = %5 "
                        "WHERE airport_name = '%6'")
                .arg(str_list[5])
                .arg(str_list[6])
                .arg(str_list[7])
                .arg(str_list[8])
                .arg(str_list[9])
                .arg(str_list[0]));
}

void AirportStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split('*', Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM airport "
                        "WHERE airport_name = '%1'")
                    .arg(str_list[0]));
}
