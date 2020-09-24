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
            return QDateTime::fromString(value.toString(), "yyyy-MM-dd hh:m:ss").toString("dd/MM/yyyy hh:mm:ss");
        }
    }

    if (role == Qt::DecorationRole) {
        QVariant qvValue = QSqlQueryModel::data(index, Qt::DisplayRole);
        QString valeur = qvValue.toString();
        if (index.column() == 5) {
            if (valeur.contains("/")) {
                return QVariant::fromValue(QIcon(valeur));
            }
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

    if (role == Qt::ToolTipRole) {
        QVariant qvValue = QSqlQueryModel::data(index, Qt::DisplayRole);
        QString valeur = qvValue.toString();
        if(index.column() == 5) {
            if (valeur.contains("/")) {
                return QString("<img src=\"" + valeur + "\" width=\"167\" height=\"100\">");
            }
        } else if (index.column() == 4) {
            return QString(valeur);
        }
    }
    return value;
}
