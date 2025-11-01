#ifndef PURPOSESTRATEGY_H
#define PURPOSESTRATEGY_H

#include "datastrategy.h"

class PurposeStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) override;
    void Update(QSqlQuery* query, const QString& data) override;
    void Delete(QSqlQuery* query, const QString& data) override;
};

#endif // PURPOSESTRATEGY_H
