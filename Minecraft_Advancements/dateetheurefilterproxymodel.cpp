#include "dateetheurefilterproxymodel.h"

#include <QtWidgets>


DateEtHeureFilterProxyModel::DateEtHeureFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}


void DateEtHeureFilterProxyModel::setFilterMinimumDate(QDateTime date)
{
    minDate = date;
    invalidateFilter();
}


void DateEtHeureFilterProxyModel::setFilterMaximumDate(QDateTime date)
{
    maxDate = date;
    invalidateFilter();
}


bool DateEtHeureFilterProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex index0 = sourceModel()->index(sourceRow, 5, sourceParent);
    qDebug() << "Source Row" << sourceRow;

    return dateInRange(sourceModel()->data(index0).toDateTime());
}


bool DateEtHeureFilterProxyModel::dateInRange(QDateTime date) const
{
    return (!minDate.isValid() || date >= minDate)
            && (!maxDate.isValid() || date <= maxDate);
}
