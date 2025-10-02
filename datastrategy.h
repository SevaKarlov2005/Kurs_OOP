#ifndef DATASTRATEGY_H
#define DATASTRATEGY_H

#include <QSqlQuery>

class DataStrategy
{
public:
    virtual ~DataStrategy();
    virtual void Insert(QSqlQuery* query, const QString& data) = 0;
    virtual void Update(QSqlQuery* query, const QString& data) = 0;
    virtual void Delete(QSqlQuery* query, const QString& data) = 0;
};

#endif // DATASTRATEGY_H
