#ifndef SQLMODEL_H
#define SQLMODEL_H

#include <QSqlQueryModel>
#include <QtWidgets>

class SqlModel : public QSqlQueryModel
{
public:
    SqlModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &item, int role) const override;
};

#endif // SQLMODEL_H
