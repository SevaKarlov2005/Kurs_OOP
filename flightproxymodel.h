#ifndef FLIGHTPROXYMODEL_H
#define FLIGHTPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QComboBox>

class FlightProxyModel : public QSortFilterProxyModel
{
private:
    QLineEdit* num_flight_edit;
    QLineEdit* company_edit;
    QLineEdit* from_edit;
    QLineEdit* to_edit;
    QLineEdit* date_edit;
    QLineEdit* time_edit;
    QComboBox* state_box;
    QLineEdit* all_place_edit;
    QLineEdit* free_place_edit;
public:
    explicit FlightProxyModel(QLineEdit* num_flight_edit, QLineEdit* company_edit, QLineEdit* from_edit,
                              QLineEdit* to_edit, QLineEdit* date_edit, QLineEdit* time_edit,
                              QComboBox* state_box, QLineEdit* all_place_edit, QLineEdit* free_place_edit,
                              QObject *parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // FLIGHTPROXYMODEL_H
