#ifndef AIRPORTSTRATEGY_H
#define AIRPORTSTRATEGY_H

#include "datastrategy.h"

class AirportStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) const override;
    void Update(QSqlQuery* query, const QString& data) const override;
    void Delete(QSqlQuery* query, const QString& data) const override;
};

#endif // AIRPORTSTRATEGY_H
