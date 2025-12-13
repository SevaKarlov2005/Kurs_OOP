#ifndef PASSENGERPROXYMODEL_H
#define PASSENGERPROXYMODEL_H

#include "qlineedit.h"
#include <QSortFilterProxyModel>

class PassengerProxyModel : public QSortFilterProxyModel
{
private:
    QLineEdit* num_passport_edit;
    QLineEdit* place_passport_edit;
    QLineEdit* date_passport_edit;
    QLineEdit* surname_edit;
    QLineEdit* name_edit;
    QLineEdit* patronym_edit;
    QLineEdit* birthday_edit;
public:
    explicit PassengerProxyModel(QLineEdit* num_passport_edit, QLineEdit* place_passport_edit, QLineEdit* date_passport_edit,
                                 QLineEdit* surname_edit, QLineEdit* name_edit, QLineEdit* patronym_edit,
                                 QLineEdit* birthday_edit, QObject *parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // PASSENGERPROXYMODEL_H
