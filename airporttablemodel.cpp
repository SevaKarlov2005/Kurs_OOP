#include "airporttablemodel.h"

AirportTableModel::AirportTableModel(DataBase* data_worker, QObject *parent)
    : QAbstractTableModel(parent)
{
    worker = data_worker;
}

QVariant AirportTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        if (orientation == Qt::Horizontal)
        {
            return section;
        }
        else
            return section;
    }
}

int AirportTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return worker->GetAirportSize();
}

int AirportTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 5;
}

QVariant AirportTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= worker->GetAirportSize() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return QVariant();
    else
    {
        if (index.column() == 0)
            return worker->GetAirport(index.row()).GetName();
        else if (index.column() == 1)
            return worker->GetAirport(index.row()).GetRainfall();
        else if (index.column() == 3)
            return worker->GetAirport(index.row()).GetDirection();
        else
            return QVariant();
    }
}
