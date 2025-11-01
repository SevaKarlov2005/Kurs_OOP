#ifndef STAFFSTRATEGY_H
#define STAFFSTRATEGY_H

#include "datastrategy.h"

class StaffStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) override;
    void Update(QSqlQuery* query, const QString& data) override;
    void Delete(QSqlQuery* query, const QString& data) override;
};

#endif // STAFFSTRATEGY_H
