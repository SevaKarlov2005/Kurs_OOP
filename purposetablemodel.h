#ifndef PURPOSETABLEMODEL_H
#define PURPOSETABLEMODEL_H

#include <QAbstractTableModel>
#include "database.h"

class PurposeTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    DataBase* database;
public:
    explicit PurposeTableModel(DataBase* db, QObject *parent = nullptr);
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

#endif // PURPOSETABLEMODEL_H
