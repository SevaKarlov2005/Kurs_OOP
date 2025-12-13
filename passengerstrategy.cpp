#include "passengerstrategy.h"

void PassengerStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO passenger (num_passport, place_passport, date_passport, surname, name, patronym, birthday)"
                        "VALUES "
                        "("
                        "'%1', "
                        "'%2', "
                        "'%3', "
                        "'%4', "
                        "'%5', "
                        "'%6', "
                        "'%7'"
                        ")")
                    .arg(str_list[0])
                    .arg(str_list[1])
                    .arg(str_list[2])
                    .arg(str_list[3])
                    .arg(str_list[4])
                    .arg(str_list[5])
                    .arg(str_list[6]));
}

void PassengerStrategy::Update(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("UPDATE passenger "
                        "SET "
                        "num_passport = '%1', "
                        "place_passport = '%2', "
                        "date_passport = '%3', "
                        "surname = '%4', "
                        "name = '%5', "
                        "patronym = '%6', "
                        "birthday = '%7' "
                        "WHERE num_passport = '%8'")
                    .arg(str_list[7])
                    .arg(str_list[8])
                    .arg(str_list[9])
                    .arg(str_list[10])
                    .arg(str_list[11])
                    .arg(str_list[12])
                    .arg(str_list[13])
                    .arg(str_list[0]));
}

void PassengerStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM passenger "
                        "WHERE num_passport = '%1'")
                    .arg(str_list[0]));
}
