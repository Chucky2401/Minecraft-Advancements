#ifndef DATEETHEUREFILTERPROXYMODEL_H
#define DATEETHEUREFILTERPROXYMODEL_H

#include <QDateTime>
#include <QSortFilterProxyModel>

class DateEtHeureFilterProxyModel : public QSortFilterProxyModel
{
public:
    DateEtHeureFilterProxyModel(QObject *parent = 0);

    QDateTime filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(QDateTime date);

    QDateTime filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(QDateTime date);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    //bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool dateInRange(QDateTime date) const;

    QDateTime minDate;
    QDateTime maxDate;
};

#endif // DATEETHEUREFILTERPROXYMODEL_H
