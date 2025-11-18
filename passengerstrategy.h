#ifndef PASSENGERSTRATEGY_H
#define PASSENGERSTRATEGY_H

#include "datastrategy.h"

class PassengerStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) const override;
    void Update(QSqlQuery* query, const QString& data) const override;
    void Delete(QSqlQuery* query, const QString& data) const override;
};

#endif // PASSENGERSTRATEGY_H
