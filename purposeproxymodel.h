#ifndef PURPOSEPROXYMODEL_H
#define PURPOSEPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QComboBox>

class PurposeProxyModel : public QSortFilterProxyModel
{
private:
    QLineEdit* num_flight_edit;
    QLineEdit* num_certificate_edit;
    QComboBox* nomination_box;
public:
    explicit PurposeProxyModel(QLineEdit* num_flight_edit, QLineEdit* num_certificate_edit, QComboBox* nomination_box, QObject *parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // PURPOSEPROXYMODEL_H
