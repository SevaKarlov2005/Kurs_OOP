#include "stafftablemodel.h"

StaffTableModel::StaffTableModel(DataBase* db, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->database = db;

    connect(this->database, &DataBase::ChangeStaff, this, &StaffTableModel::Update);
    connect(this->database, &DataBase::Reload, this, &StaffTableModel::Reload);
}

QVariant StaffTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    else
    {
        if (orientation == Qt::Orientation::Horizontal)
        {
            switch(section)
            {
            case 0: return "Номер удостоверения";
            case 1: return "Фамилия";
            case 2: return "Имя";
            case 3: return "Отчество";
            case 4: return "Профессия";
            default: return QVariant();
            }
        }
        else
            return section + 1;
    }
}

int StaffTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return this->database->GetStaffSize();
}

int StaffTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 5;
}

QVariant StaffTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole) || index.row() >= (int)this->database->GetStaffSize())
        return QVariant();
    else
    {
        QString states[3] = {"Пилот", "Бортпроводник", "Инженер"};

        switch(index.column())
        {
        case 0: return this->database->GetStaff(index.row()).GetNumCertificate();
        case 1: return this->database->GetStaff(index.row()).GetSurname();
        case 2: return this->database->GetStaff(index.row()).GetName();
        case 3: return this->database->GetStaff(index.row()).GetPatronym();
        case 4: return states[this->database->GetStaff(index.row()).GetProfession()];
        default: return QVariant();
        }
    }
}

void StaffTableModel::AddRow()
{
    beginInsertRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endInsertRows();
}

void StaffTableModel::DeleteRow()
{
    beginRemoveRows(QModelIndex(), this->database->GetIndex() / 10, this->database->GetIndex() / 10);
    endRemoveRows();
}

void StaffTableModel::ChangeRow()
{
    emit dataChanged(index(this->database->GetIndex() / 10, 0), index(this->database->GetIndex() / 10, 4));
}

void StaffTableModel::Update()
{
    if (this->database->GetIndex() % 10 == 1)
        AddRow();
    else if (this->database->GetIndex() % 10 == 2)
        ChangeRow();
    else if (this->database->GetIndex() % 10 == 3)
        DeleteRow();
}

void StaffTableModel::Reload()
{
    beginResetModel();
    endResetModel();
}
