#include "passengertablemodel.h"

PassengerTableModel::PassengerTableModel(DataBase* db, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->database = db;

    connect(this->database, &DataBase::ChangePassenger, this, &PassengerTableModel::Update);
    connect(this->database, &DataBase::Reload, this, &PassengerTableModel::Reload);
}

QVariant PassengerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        if (orientation == Qt::Orientation::Horizontal)
        {
            switch(section)
            {
            case 0: return "Номер паспорта";
            case 1: return "Место выдачи\nпаспорта";
            case 2: return "Дата выдачи\nпаспорта";
            case 3: return "Фамилия";
            case 4: return "Имя";
            case 5: return "Отчество";
            case 6: return "Дата рождения";
            default: return QVariant();
            }
        }
        else
            return section + 1;
    }
}

int PassengerTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->database->GetPassengerSize();
}

int PassengerTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 7;
}

QVariant PassengerTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole) || index.row() >= (int)this->database->GetPassengerSize())
        return QVariant();
    else
    {
        switch(index.column())
        {
        case 0: return this->database->GetPassenger(index.row()).GetNumPassport();
        case 1: return this->database->GetPassenger(index.row()).GetPlacePassport();
        case 2: return this->database->GetPassenger(index.row()).GetDatePassport();
        case 3: return this->database->GetPassenger(index.row()).GetSurname();
        case 4: return this->database->GetPassenger(index.row()).GetName();
        case 5: return this->database->GetPassenger(index.row()).GetPatronym();
        case 6: return this->database->GetPassenger(index.row()).GetBirthday();
        default: return QVariant();
        }
    }
}

void PassengerTableModel::AddRow()
{
    beginInsertRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endInsertRows();
}

void PassengerTableModel::DeleteRow()
{
    beginRemoveRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endRemoveRows();
}

void PassengerTableModel::ChangeRow()
{
    emit dataChanged(index(this->database->GetIndex() / 10, 0), index(this->database->GetIndex() / 10, 6));
}

void PassengerTableModel::Update()
{
    if (this->database->GetIndex() % 10 == 1)
        AddRow();
    else if (this->database->GetIndex() % 10 == 2)
        ChangeRow();
    else if (this->database->GetIndex() % 10 == 3)
        DeleteRow();
}

void PassengerTableModel::Reload()
{
    beginResetModel();
    endResetModel();
}
