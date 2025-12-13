#ifndef STAFFTABLEMODEL_H
#define STAFFTABLEMODEL_H

#include <QAbstractTableModel>
#include "database.h"

class StaffTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    DataBase* database;
public:
    explicit StaffTableModel(DataBase* db, QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void AddRow();
    void DeleteRow();
    void ChangeRow();
    void Update();
    void Reload();
};

#endif // STAFFTABLEMODEL_H
