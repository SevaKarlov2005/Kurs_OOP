#include "purposetablemodel.h"

PurposeTableModel::PurposeTableModel(DataBase* db, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->database = db;

    connect(this->database, &DataBase::ChangeTicket, this, &PurposeTableModel::Update);
    connect(this->database, &DataBase::Reload, this, &PurposeTableModel::Reload);
}

QVariant PurposeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0: return "Номер авиарейса";
            case 1: return "Номер удостоверения";
            case 2: return "Назначение";
            default: return QVariant();
            }
        }
        else
            return section + 1;
    }
}

int PurposeTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->database->GetPurposeSize();
}

int PurposeTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 3;
}

QVariant PurposeTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole) || index.row() >= (int)this->database->GetPurposeSize())
        return QVariant();

    else
    {
        QString states[5] = {"Первый пилот", "Второй пилот", "Старший бортпроводник", "Младший бортпроводник", "Бортовой инженер"};

        switch (index.column())
        {
        case 0: return this->database->GetPurpose(index.row()).GetNumFlight();
        case 1: return this->database->GetPurpose(index.row()).GetNumCertificate();
        case 2: return states[this->database->GetPurpose(index.row()).GetName()];
        default: return QVariant();
        }
    }
}

void PurposeTableModel::AddRow()
{
    beginInsertRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endInsertRows();
}

void PurposeTableModel::DeleteRow()
{
    beginRemoveRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endRemoveRows();
}

void PurposeTableModel::ChangeRow()
{
    emit dataChanged(index(this->database->GetIndex() / 10, 0), index(this->database->GetIndex() / 10, 2));
}

void PurposeTableModel::Update()
{
    if (this->database->GetIndex() % 10 == 1)
        AddRow();
    else if (this->database->GetIndex() % 10 == 2)
        ChangeRow();
    else if (this->database->GetIndex() % 10 == 3)
        DeleteRow();
}

void PurposeTableModel::Reload()
{
    beginResetModel();
    endResetModel();
}
