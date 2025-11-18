#ifndef TICKETSTRATEGY_H
#define TICKETSTRATEGY_H

#include "datastrategy.h"

class TicketStrategy : public DataStrategy
{
public:
    void Insert(QSqlQuery* query, const QString& data) const override;
    void Update(QSqlQuery* query, const QString& data) const override;
    void Delete(QSqlQuery* query, const QString& data) const override;
};

#endif // TICKETSTRATEGY_H
