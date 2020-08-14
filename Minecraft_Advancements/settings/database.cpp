#include "database.h"

database::database() {

}

database::~database() {
    this->base.close();
}

void database::initialisation(bool test) {
    param.initialisation(test);
}

/*
 * Fonction d'ouverture de la connexion à la Base de données
 */
bool database::createConnection(QString name)
{
    bool bCreationReussi = false;
    bool bConnexionReussi = false;
    bool bDossier = false;
    this->base = QSqlDatabase::addDatabase("QSQLITE", name);
    this->resetAll();

    if(!QDir(param.getBddPath()).exists()){
        qDebug() << "Le dossier pour la BDD n'existe pas";
        qInfo() << "Création dossier pour la BDD";
        if(QDir().mkdir(param.getBddPath())) {
            qInfo() << "Création dossier pour la BDD OK";
            bDossier = true;
        } else {
            setError("La création du dossier pour la base a échoué.");
            qCritical() << "Création dossier pour la BDD KO";
        }
    } else {
        bDossier = true;
    }

    if(bDossier && !QFile::exists(param.getBddPath()+param.getBddName())){
        qDebug() << param.getBddPath() + param.getBddName() << " - La base n'existe pas ! / " << name;
        QFile qfBaseDeDonnees(param.getBddPath() + param.getBddName());
        qfBaseDeDonnees.open(QIODevice::WriteOnly);
        qfBaseDeDonnees.close();

        this->base.setDatabaseName(param.getBddPath()+param.getBddName());
        if (!this->base.open()) {
            setError("La base n'a pas pu être créé");
            bConnexionReussi = false;
        } else {
            bConnexionReussi = true;
        }

        if(bConnexionReussi){
            bCreationReussi = initialisationTable();
            if(!bCreationReussi){
                setError("La base n'existe pas ou son initialisation a échoué");
                bConnexionReussi = false;
            }
        }
    } else {
        this->base.setDatabaseName(param.getBddPath()+param.getBddName());
        if (!this->base.open()) {
            setError(this->base.lastError().text());
            bConnexionReussi = false;
        } else {
            bConnexionReussi = true;
        }
    }

    return bConnexionReussi;
}

bool database::initialisationTable(){
    QFile qfSqlCreation(":/file/nms_database.db.sql");
    QByteArray line;
    QSqlQuery query(this->base);
    bool bExecutionRequeteEchoue = false;

    if(!qfSqlCreation.open(QIODevice::ReadOnly))
        qDebug() << "Echec Ouverture";

    startTransaction();

    while(!qfSqlCreation.atEnd()){
        line = qfSqlCreation.readLine();
        if(!bExecutionRequeteEchoue){
            qDebug() << line;
            if(!query.exec(line)){
                bExecutionRequeteEchoue = true;
            }
        }
    }

    stopTransaction(bExecutionRequeteEchoue);

    qfSqlCreation.close();
    return !bExecutionRequeteEchoue;
}

void database::closeConnection(QString name){
    QSqlDatabase::database(name);
    this->base.close();
    this->base.removeDatabase(name);
}

bool database::isOpen(QString name){
    QSqlDatabase::database(name);
    return base.isOpen();
}

QSqlDatabase database::getBase(){
    return this->base;
}

void database::resetAll(){
    resetError();
}

void database::resetError(){
    this->lastBddError = "";
}

QString database::getError(){
    return this->lastBddError;
}

void database::setError(QString error){
    this->lastBddError = error;
}

void database::startTransaction(){
    this->base.transaction();
}

void database::stopTransaction(bool error){
    if (error){
        bool retour = this->base.rollback();
        qDebug() << "Rollback / " << retour;
    } else {
        bool retour = this->base.commit();
        qDebug() << "Commit   / " << retour;
    }
}
