#ifndef STAFFPROXYMODEL_H
#define STAFFPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QComboBox>

class StaffProxyModel : public QSortFilterProxyModel
{
private:
    QLineEdit* num_certificate_edit;
    QLineEdit* surname_edit;
    QLineEdit* name_edit;
    QLineEdit* patronym_edit;
    QComboBox* profession_box;
public:
    explicit StaffProxyModel(QLineEdit* num_certificate_edit, QLineEdit* surname_edit, QLineEdit* name_edit,
                             QLineEdit* patronym_edit, QComboBox* profession_box, QObject *parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // STAFFPROXYMODEL_H
