#include "airportproxymodel.h"

AirportProxyModel::AirportProxyModel(QLineEdit* name_edit, QLineEdit* rainfall_edit, QLineEdit* speed_edit,
                                     QLineEdit* direction_edit, QLineEdit* temperature_edit, QObject *parent)
    : QSortFilterProxyModel{parent}
{
    this->name_edit = name_edit;
    this->rainfall_edit = rainfall_edit;
    this->speed_edit = speed_edit;
    this->direction_edit = direction_edit;
    this->temperature_edit = temperature_edit;

    connect(this->name_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->rainfall_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->speed_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->direction_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
    connect(this->temperature_edit, &QLineEdit::textChanged, this, &QSortFilterProxyModel::invalidate);
}

bool AirportProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool name_flag;
    bool rainfall_flag;
    bool speed_flag;
    bool direction_flag;
    bool temperature_flag;

    QString name = sourceModel()->data(sourceModel()->index(source_row, 0, source_parent)).toString();
    name_flag = name == this->name_edit->text() || this->name_edit->text() == "";

    unsigned short rainfall = (unsigned short)sourceModel()->data(sourceModel()->index(source_row, 1, source_parent)).toInt();
    rainfall_flag = rainfall == this->rainfall_edit->text().toInt() || this->rainfall_edit->text() == "";

    unsigned short speed = (unsigned short)sourceModel()->data(sourceModel()->index(source_row, 2, source_parent)).toInt();
    speed_flag = speed == this->speed_edit->text().toInt() || this->speed_edit->text() == "";

    unsigned short direction = (unsigned short)sourceModel()->data(sourceModel()->index(source_row, 3, source_parent)).toInt();
    direction_flag = direction == this->direction_edit->text().toInt() || this->direction_edit->text() == "";

    short temperature = (short)sourceModel()->data(sourceModel()->index(source_row, 4, source_parent)).toInt();
    temperature_flag = temperature == this->temperature_edit->text().toInt() || this->temperature_edit->text() == "";

    return name_flag && rainfall_flag && speed_flag && direction_flag && temperature_flag;
}
