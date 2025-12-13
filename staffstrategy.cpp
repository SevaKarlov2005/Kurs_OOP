#include "staffstrategy.h"

void StaffStrategy::Insert(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("INSERT INTO staff (num_certificate, surname, name, patronym, profession) "
                        "VALUES "
                        "("
                        "'%1', "
                        "'%2', "
                        "'%3', "
                        "'%4', "
                        "'%5'"
                        ")")
                .arg(str_list[0])
                .arg(str_list[1])
                .arg(str_list[2])
                .arg(str_list[3])
                .arg(str_list[4]));
}

void StaffStrategy::Update(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("UPDATE staff "
                        "SET "
                        "num_certificate = '%1', "
                        "surname = '%2', "
                        "name = '%3', "
                        "patronym = '%4', "
                        "profession = '%5' "
                        "WHERE num_certificate = '%6'")
                    .arg(str_list[5])
                    .arg(str_list[6])
                    .arg(str_list[7])
                    .arg(str_list[8])
                    .arg(str_list[9])
                    .arg(str_list[0]));
}

void StaffStrategy::Delete(QSqlQuery* query, const QString& data) const
{
    QStringList str_list = data.split("*", Qt::SkipEmptyParts);

    query->exec(QString("DELETE FROM staff "
                        "WHERE num_certificate = '%1'")
                    .arg(str_list[0]));
}
