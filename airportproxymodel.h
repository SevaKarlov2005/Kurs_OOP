#ifndef AIRPORTPROXYMODEL_H
#define AIRPORTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QLineEdit>

class AirportProxyModel : public QSortFilterProxyModel
{
private:
    QLineEdit* name_edit;
    QLineEdit* rainfall_edit;
    QLineEdit* speed_edit;
    QLineEdit* direction_edit;
    QLineEdit* temperature_edit;
public:
    explicit AirportProxyModel(QLineEdit* name_edit, QLineEdit* rainfall_edit, QLineEdit* speed_edit,
                               QLineEdit* direction_edit, QLineEdit* temperature_edit, QObject *parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // AIRPORTPROXYMODEL_H
