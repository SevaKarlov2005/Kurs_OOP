#ifndef AIRPORTSTRATEGY_H
#define AIRPORTSTRATEGY_H

#include "datastrategy.h"

class AirportStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) override;
    void Update(QSqlQuery* query, const QString& data) override;
    void Delete(QSqlQuery* query, const QString& data) override;
};

#endif // AIRPORTSTRATEGY_H
