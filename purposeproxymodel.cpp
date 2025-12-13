#include "purposeproxymodel.h"

PurposeProxyModel::PurposeProxyModel(QLineEdit* num_flight_edit, QLineEdit* num_certificate_edit, QComboBox* nomination_box, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->num_flight_edit = num_flight_edit;
    this->num_certificate_edit = num_certificate_edit;
    this->nomination_box = nomination_box;

    connect(this->num_flight_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->num_certificate_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->nomination_box, &QComboBox::currentIndexChanged, this, &QSortFilterProxyModel::invalidate);
}

bool PurposeProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool num_flight_flag;
    bool num_certificate_flag;
    bool nomination_flag;

    QString num_flight = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)).toString();
    num_flight_flag = num_flight == this->num_flight_edit->text() || this->num_flight_edit->text() == "";

    QString num_certificate = sourceModel()->data(sourceModel()->index(source_row, 1, source_parent)).toString();
    num_certificate_flag = num_certificate == this->num_certificate_edit->text() || this->num_certificate_edit->text() == "";

    QString nomination = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toString();
    nomination_flag = nomination == this->nomination_box->currentText();

    return num_flight_flag && num_certificate_flag && nomination_flag;
}
