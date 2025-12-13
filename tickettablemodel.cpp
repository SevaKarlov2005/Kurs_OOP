#include "tickettablemodel.h"

TicketTableModel::TicketTableModel(DataBase* db, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->database = db;

    connect(this->database, &DataBase::ChangeTicket, this, &TicketTableModel::Update);
    connect(this->database, &DataBase::Reload, this, &TicketTableModel::Reload);
}

QVariant TicketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0: return "Номер авиабилета";
            case 1: return "Номер паспорта";
            case 2: return "Номер авиарейса";
            default: return QVariant();
            }
        }
        else
            return section + 1;
    }
}

int TicketTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->database->GetTicketSize();
}

int TicketTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 3;
}

QVariant TicketTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole) || index.row() >= (int)this->database->GetTicketSize())
        return QVariant();

    else
    {
        switch (index.column())
        {
        case 0: return this->database->GetTicket(index.row()).GetNumTicket();
        case 1: return this->database->GetTicket(index.row()).GetNumPassport();
        case 2: return this->database->GetTicket(index.row()).GetNumFlight();
        default: return QVariant();
        }
    }
}

void TicketTableModel::AddRow()
{
    beginInsertRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endInsertRows();
}

void TicketTableModel::DeleteRow()
{
    beginRemoveRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endRemoveRows();
}

void TicketTableModel::ChangeRow()
{
    emit dataChanged(index(this->database->GetIndex() / 10, 0), index(this->database->GetIndex() / 10, 2));
}

void TicketTableModel::Update()
{
    if (this->database->GetIndex() % 10 == 1)
        AddRow();
    else if (this->database->GetIndex() % 10 == 2)
        ChangeRow();
    else if (this->database->GetIndex() % 10 == 3)
        DeleteRow();
}

void TicketTableModel::Reload()
{
    beginResetModel();
    endResetModel();
}
