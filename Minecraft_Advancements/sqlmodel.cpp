#include "sqlmodel.h"

SqlModel::SqlModel(QObject *parent)
    : QSqlQueryModel(parent)
{

}

QVariant SqlModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (value.isValid() && role == Qt::DisplayRole) {
        if (index.column() == 3 && value == "true")
            return "oui";
        else if (index.column() == 3 && value == "false")
            return "non";
    }
    if (role == Qt::ForegroundRole && index.column() == 2) {
        QModelIndex qmiValeurProgresFait = index.siblingAtColumn(3);
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "true")
            return QVariant::fromValue(QColor(Qt::darkGreen));
    }

    if (role == Qt::ForegroundRole && index.column() == 5) {
        QModelIndex qmiValeurProgresFait = index.siblingAtColumn(7);
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "ET")
            return QVariant::fromValue(QColor(Qt::darkRed));
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "OU")
            return QVariant::fromValue(QColor(Qt::blue));
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "UNE")
            return QVariant::fromValue(QColor(Qt::darkYellow));
    }
    return value;
}
