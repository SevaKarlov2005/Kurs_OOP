#ifndef STAFFSTRATEGY_H
#define STAFFSTRATEGY_H

#include "datastrategy.h"

class StaffStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) const override;
    void Update(QSqlQuery* query, const QString& data) const override;
    void Delete(QSqlQuery* query, const QString& data) const override;
};

#endif // STAFFSTRATEGY_H
