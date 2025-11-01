#ifndef AIRPORTTABLEMODEL_H
#define AIRPORTTABLEMODEL_H

#include <QAbstractTableModel>
#include "database.h"

class AirportTableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    DataBase* worker;
public:
    explicit AirportTableModel(DataBase* data_worker, QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // AIRPORTTABLEMODEL_H
