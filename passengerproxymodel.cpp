#include "passengerproxymodel.h"

PassengerProxyModel::PassengerProxyModel(QLineEdit* num_passport_edit, QLineEdit* place_passport_edit, QLineEdit* date_passport_edit,
                                         QLineEdit* surname_edit, QLineEdit* name_edit, QLineEdit* patronym_edit,
                                         QLineEdit* birthday_edit, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->num_passport_edit = num_passport_edit;
    this->place_passport_edit = place_passport_edit;
    this->date_passport_edit = date_passport_edit;
    this->surname_edit = surname_edit;
    this->name_edit = name_edit;
    this->patronym_edit = patronym_edit;
    this->birthday_edit = birthday_edit;

    connect(this->num_passport_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->place_passport_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->date_passport_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->surname_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->name_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->patronym_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->birthday_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
}

bool PassengerProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool num_passport_flag;
    bool place_passport_flag;
    bool date_passport_flag;
    bool surname_flag;
    bool name_flag;
    bool patronym_flag;
    bool birthday_flag;

    QString num_passport = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)).toString();
    num_passport_flag = num_passport == this->num_passport_edit->text() || this->num_passport_edit->text() == "";

    QString place_passport = sourceModel()->data(sourceModel()->index(source_row, 1, source_parent)).toString();
    place_passport_flag = place_passport == this->place_passport_edit->text() || this->place_passport_edit->text() == "";

    QString date_passport = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toString();
    date_passport_flag = date_passport == this->date_passport_edit->text() || this->date_passport_edit->text() == "";

    QString surname = sourceModel()->data(sourceModel()->index(source_row, 3, source_parent)).toString();
    surname_flag = surname == this->surname_edit->text() || this->surname_edit->text() == "";

    QString name = sourceModel()->data(sourceModel()->index(source_row, 4, source_parent)).toString();
    name_flag = name == this->name_edit->text() || this->name_edit->text() == "";

    QString patronym = sourceModel()->data(sourceModel()->index(source_row, 5, source_parent)).toString();
    patronym_flag = patronym == this->patronym_edit->text() || this->patronym_edit->text() == "";

    QString birthday = sourceModel()->data(sourceModel()->index(source_row, 6, source_parent)).toString();
    birthday_flag = birthday == this->birthday_edit->text() || this->birthday_edit->text() == "";

    return num_passport_flag && place_passport_flag && date_passport_flag && surname_flag && name_flag && patronym_flag && birthday_flag;
}
