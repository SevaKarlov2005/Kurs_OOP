#ifndef FLIGHTSTRATEGY_H
#define FLIGHTSTRATEGY_H

#include "datastrategy.h"

class FlightStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) const override;
    void Update(QSqlQuery* query, const QString& data) const override;
    void Delete(QSqlQuery* query, const QString& data) const override;
};

#endif // FLIGHTSTRATEGY_H
