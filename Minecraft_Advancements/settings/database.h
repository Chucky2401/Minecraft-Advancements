#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDriver>

#include "settings.h"


class database
{
public:
    database();
    ~database();
    void initialisation(bool test = false);

    bool createConnection(QString name);
    bool initialisationTable();
    void closeConnection(QString name);
    bool isOpen(QString name);
    QSqlDatabase getBase();
    void resetAll();
    void resetError();
    QString getError();
    void setError(QString error);

    void startTransaction();
    void stopTransaction(bool error = false);

private:
    QSqlDatabase base;
    QString lastBddError;

    class Settings param;
};

#endif // DATABASE_H
