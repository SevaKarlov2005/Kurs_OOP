#include "flighttablemodel.h"

FlightTableModel::FlightTableModel(DataBase* db, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->database = db;

    connect(this->database, &DataBase::ChangeFlight, this, &FlightTableModel::Update);
    connect(this->database, &DataBase::Reload, this, &FlightTableModel::Reload);
}

QVariant FlightTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        if (orientation == Qt::Orientation::Horizontal)
        {
            switch (section)
            {
            case 0: return "Номер\nавиарейса";
            case 1: return "Название\nавиакомпании";
            case 2: return "Аэропорт\nотправления";
            case 3: return "Аэропорт\nприбытия";
            case 4: return "Дата\nотправления";
            case 5: return "Время\nотправления";
            case 6: return "Статус";
            case 7: return "Количество\nмест\nвсего";
            case 8: return "Количество\nсвободных\nмест";
            default: return QVariant();
            }
        }
        else
            return section + 1;
    }
}

int FlightTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->database->GetFlightSize();
}

int FlightTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 9;
}

QVariant FlightTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole) || index.row() >= (int)this->database->GetFlightSize())
        return QVariant();
    else
    {
        QString states[6] = {"По расписанию", "Регистрация", "Посадка", "Вылетел", "Задерживается", "Отменён"};

        switch (index.column())
        {
        case 0: return this->database->GetFlight(index.row()).GetNumFlight();
        case 1: return this->database->GetFlight(index.row()).GetCompany();
        case 2: return this->database->GetFlight(index.row()).GetFrom();
        case 3: return this->database->GetFlight(index.row()).GetTo();
        case 4: return this->database->GetFlight(index.row()).GetDate();
        case 5: return this->database->GetFlight(index.row()).GetTime();
        case 6: return states[this->database->GetFlight(index.row()).GetState()];
        case 7: return this->database->GetFlight(index.row()).GetAllPlace();
        case 8: return this->database->GetFlight(index.row()).GetFreePlace();
        default: return QVariant();
        }
    }
}

void FlightTableModel::AddRow()
{
    beginInsertRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endInsertRows();
}

void FlightTableModel::DeleteRow()
{
    beginRemoveRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endRemoveRows();
}

void FlightTableModel::ChangeRow()
{
    emit dataChanged(index(this->database->GetIndex() / 10, 0), index(this->database->GetIndex() / 10, 8));
}

void FlightTableModel::Update()
{
    if (this->database->GetIndex() % 10 == 1)
        AddRow();
    else if (this->database->GetIndex() % 10 == 2)
        ChangeRow();
    else if (this->database->GetIndex() % 10 == 3)
        DeleteRow();
}

void FlightTableModel::Reload()
{
    beginResetModel();
    endResetModel();
}
