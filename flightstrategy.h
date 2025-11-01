#ifndef FLIGHTSTRATEGY_H
#define FLIGHTSTRATEGY_H

#include "datastrategy.h"

class FlightStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) override;
    void Update(QSqlQuery* query, const QString& data) override;
    void Delete(QSqlQuery* query, const QString& data) override;
};

#endif // FLIGHTSTRATEGY_H
