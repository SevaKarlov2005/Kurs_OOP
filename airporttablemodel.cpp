#include "airporttablemodel.h"

AirportTableModel::AirportTableModel(DataBase* db, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->database = db;

    connect(this->database, &DataBase::ChangeAirport, this, &AirportTableModel::Update);
    connect(this->database, &DataBase::Reload, this, &AirportTableModel::Reload);
}

QVariant AirportTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0: return "Название аэропорта";
            case 1: return "Количество осадков";
            case 2: return "Скорость ветра";
            case 3: return "Направление ветра";
            case 4: return "Температура";
            default: return QVariant();
            }
        }
        else
            return section + 1;
    }
}

int AirportTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->database->GetAirportSize();
}

int AirportTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 5;
}

QVariant AirportTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole) || index.row() >= (int)this->database->GetAirportSize())
        return QVariant();

    else
    {
        switch (index.column())
        {
        case 0: return this->database->GetAirport(index.row()).GetName();
        case 1: return this->database->GetAirport(index.row()).GetRainfall();
        case 2: return this->database->GetAirport(index.row()).GetSpeed();
        case 3: return this->database->GetAirport(index.row()).GetDirection();
        case 4: return this->database->GetAirport(index.row()).GetTemperature();
        default: return QVariant();
        }
    }
}

void AirportTableModel::AddRow()
{
    beginInsertRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endInsertRows();
}

void AirportTableModel::DeleteRow()
{
    beginRemoveRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endRemoveRows();
}

void AirportTableModel::ChangeRow()
{
    emit dataChanged(index(this->database->GetIndex() / 10, 0), index(this->database->GetIndex() / 10, 4));
}

void AirportTableModel::Update()
{
    if (this->database->GetIndex() % 10 == 1)
        AddRow();
    else if (this->database->GetIndex() % 10 == 2)
        ChangeRow();
    else if (this->database->GetIndex() % 10 == 3)
        DeleteRow();
}

void AirportTableModel::Reload()
{
    beginResetModel();
    endResetModel();
}
