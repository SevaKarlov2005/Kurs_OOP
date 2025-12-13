#include "flightproxymodel.h"

FlightProxyModel::FlightProxyModel(QLineEdit* num_flight_edit, QLineEdit* company_edit, QLineEdit* from_edit,
                                   QLineEdit* to_edit, QLineEdit* date_edit, QLineEdit* time_edit,
                                   QComboBox* state_box, QLineEdit* all_place_edit, QLineEdit* free_place_edit,
                                   QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->num_flight_edit = num_flight_edit;
    this->company_edit = company_edit;
    this->from_edit = from_edit;
    this->to_edit = to_edit;
    this->date_edit = date_edit;
    this->time_edit = time_edit;
    this->state_box = state_box;
    this->all_place_edit = all_place_edit;
    this->free_place_edit = free_place_edit;

    connect(this->num_flight_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->company_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->from_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->to_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->date_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->time_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->state_box, &QComboBox::currentIndexChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->all_place_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->free_place_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
}

bool FlightProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool num_flight_flag;
    bool company_flag;
    bool from_flag;
    bool to_flag;
    bool date_flag;
    bool time_flag;
    bool state_flag;
    bool all_place_flag;
    bool free_place_flag;

    QString num_flight = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)).toString();
    num_flight_flag = num_flight == this->num_flight_edit->text() || this->num_flight_edit->text() == "";

    QString company = sourceModel()->data(sourceModel()->index(source_row, 1, source_parent)).toString();
    company_flag = company == this->company_edit->text() || this->company_edit->text() == "";

    QString from = sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toString();
    from_flag = from == this->from_edit->text() || this->from_edit->text() == "";

    QString to = sourceModel()->data(sourceModel()->index(source_row, 3, source_parent)).toString();
    to_flag = to == this->to_edit->text() || this->to_edit->text() == "";

    QString date = sourceModel()->data(sourceModel()->index(source_row, 4, source_parent)).toString();
    date_flag = date == this->date_edit->text() || this->date_edit->text() == "";

    QString time = sourceModel()->data(sourceModel()->index(source_row, 5, source_parent)).toString();
    time_flag = time == this->time_edit->text() || this->time_edit->text() == "";

    QString state = sourceModel()->data(sourceModel()->index(source_row, 6, source_parent)).toString();
    state_flag = state == this->state_box->currentText();

    unsigned short all_place = (unsigned short)sourceModel()->data(sourceModel()->index(source_row, 7, source_parent)).toInt();
    all_place_flag = all_place == (unsigned short)this->all_place_edit->text().toInt() || this->all_place_edit->text() == "";

    unsigned short free_place = (unsigned short)sourceModel()->data(sourceModel()->index(source_row, 8, source_parent)).toInt();
    free_place_flag = free_place == (unsigned short)this->free_place_edit->text().toInt() || this->free_place_edit->text() == "";

    return num_flight_flag && company_flag && from_flag && to_flag && date_flag && time_flag && state_flag && all_place_flag && free_place_flag;
}
