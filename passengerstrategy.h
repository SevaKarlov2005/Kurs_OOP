#ifndef PASSENGERSTRATEGY_H
#define PASSENGERSTRATEGY_H

#include "datastrategy.h"

class PassengerStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) override;
    void Update(QSqlQuery* query, const QString& data) override;
    void Delete(QSqlQuery* query, const QString& data) override;
};

#endif // PASSENGERSTRATEGY_H
