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
        else if (index.column() == 7 && value != "") {
            //QDateTime qdtDateFait = QDateTime::fromString(value.toString(), "yyyy-MM-dd hh:mm:ss");
            return QDateTime::fromString(value.toString(), "yyyy-MM-dd hh:m:ss").toString("dd/MM/yyyy hh:mm:ss");
        }
    }

    if (role == Qt::ForegroundRole && index.column() == 2) {
        QModelIndex qmiValeurProgresFait = index.siblingAtColumn(3);
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "oui")
            return QVariant::fromValue(QColor(Qt::darkGreen));
    }

    if (role == Qt::ForegroundRole && index.column() == 5) {
        QModelIndex qmiValeurProgresFait = index.siblingAtColumn(8);
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "ET")
            return QVariant::fromValue(QColor(Qt::darkRed));
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "OU")
            return QVariant::fromValue(QColor(Qt::blue));
        if (qmiValeurProgresFait.data(Qt::DisplayRole) == "UNE")
            return QVariant::fromValue(QColor(Qt::darkYellow));
    }
    return value;
}
