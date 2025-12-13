#include "staffproxymodel.h"

StaffProxyModel::StaffProxyModel(QLineEdit* num_certificate_edit, QLineEdit* surname_edit, QLineEdit* name_edit,
                                 QLineEdit* patronym_edit, QComboBox* profession_box, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->num_certificate_edit = num_certificate_edit;
    this->surname_edit = surname_edit;
    this->name_edit = name_edit;
    this->patronym_edit = patronym_edit;
    this->profession_box = profession_box;

    connect(this->num_certificate_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->surname_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->name_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->patronym_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->profession_box, &QComboBox::currentIndexChanged, this, &QSortFilterProxyModel::invalidate);
}

bool StaffProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool num_certificate_flag;
    bool surname_flag;
    bool name_flag;
    bool patronym_flag;
    bool profession_flag;

    QString num_certificate = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)).toString();
    num_certificate_flag = num_certificate == this->num_certificate_edit->text() || this->num_certificate_edit->text() == "";

    QString surname = sourceModel()->data(sourceModel()->index(source_row, 1, source_parent)).toString();
    surname_flag = surname == this->surname_edit->text() || this->surname_edit->text() == "";

    QString name = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toString();
    name_flag = name == this->name_edit->text() || this->name_edit->text() == "";

    QString patronym = sourceModel()->data(sourceModel()->index(source_row, 3, source_parent)).toString();
    patronym_flag = patronym == this->patronym_edit->text() || this->patronym_edit->text() == "";

    QString profession = sourceModel()->data(sourceModel()->index(source_row, 4, source_parent)).toString();
    profession_flag = profession == this->profession_box->currentText();

    return num_certificate_flag && surname_flag && name_flag && patronym_flag && profession_flag;
}
