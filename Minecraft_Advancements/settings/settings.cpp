#include "settings.h"

Settings::Settings() {
    m_qsAppdataPath = qEnvironmentVariable("APPDATA");
    m_qsPathRoamingBdd = m_qsAppdataPath + "\\BlackWizard Company\\bdd\\";

}

void Settings::initialisation(bool test) {
    if (test) {
    }
    iniParam = new QSettings(QSettings::IniFormat, QSettings::UserScope, "BlackWizard Company", "Minecraft Advancements");

    bddPath = this->getIniBddPath();
    if (bddPath == settingDefaultString){
        this->setBddPath(m_qsPathRoamingBdd);
    }

    if (test){
        this->setBddName("minecraft_Advancements-TEST.db");
    } else {
        this->setBddName("minecraft_Advancements.db");
    }

    geometrie = this->getIniGeometrie();
    etat = this->getIniEtat();
    restoreSizePos = this->getIniRestoreSizePos();
    this->setRestoreSizePos(restoreSizePos);

    geometrieDock = this->getIniGeometrieDock();
    this->setGeometrieDock(geometrieDock);

    dockIsFloating = this->getIniDockIsFloating();
    this->setDockIsFloating(dockIsFloating);

    m_verificationAutoMiseAJour = this->getIniVerificationAutoMiseAJour();
    this->setVerificationAutoMiseAJour(m_verificationAutoMiseAJour);

    m_nombreJourMiseAJour = this->getIniNombreJourMiseAJour();
    this->setNombreJourMiseAJour(m_nombreJourMiseAJour);

    m_derniereVerificationMiseAJour = this->getIniDerniereVerificationMiseAJour();
    if (m_derniereVerificationMiseAJour == QDate(1900, 01, 01)){
        m_derniereVerificationMiseAJour = QDate::currentDate();
        this->setDerniereVerificationMiseAJour(m_derniereVerificationMiseAJour);
    }

    m_miseAJourBeta = this->getIniMiseAJourBeta();
    this->setMiseAJourBeta(m_miseAJourBeta);

    m_restoreData = this->getIniRestoreData();
    this->setRestoreData(m_restoreData);

    m_messageConfirmationFermeture = this->getIniMessageConfirmationFermeture();
    this->setMessageConfirmationFermeture(m_messageConfirmationFermeture);

    m_version = this->getIniVersion();
    this->setVersion(m_version);

    m_dossierBlazeAndCave = this->getIniDossierBlazeAndCave();
    this->setDossierBlazeAndCave(m_dossierBlazeAndCave);

    m_milestones = this->getIniMilestones();
    this->setMilestones(m_milestones);

    m_statistics = this->getIniStatistics();
    this->setStatistics(m_statistics);

    m_fichierAdvancementsPerso = this->getIniFichierAdvancementsPerso();
    this->setFichierAdvancementsPerso(m_fichierAdvancementsPerso);
}

QString Settings::getPath() {
    QString qsFichier = iniParam->fileName();
    QStringList qslCheminComplet = qsFichier.split("/");
    QString qsChemin;

    for (int i = 0 ; i < qslCheminComplet.count() ; i++) {
        if (i != qslCheminComplet.count()-1) {
            qsChemin += qslCheminComplet.at(i) + "/";
        }
    }
    return qsChemin;
}

void Settings::setBddPath(QString path){
    this->bddPath = path;
    iniParam->setValue("bdd/path", path);
}

QString Settings::getBddPath(){
    return this->bddPath;
}

QString Settings::getIniBddPath(){
    return iniParam->value("bdd/path", settingDefaultString).toString();
}

void Settings::setBddName(QString name){
    this->bddName = name;
    //iniParam->setValue("bdd/name", name);
}

QString Settings::getBddName(){
    return this->bddName;
}

void Settings::setGeometrie(QByteArray geometrie){
    this->geometrie = geometrie;
    iniParam->setValue("fenetre/geometrie", geometrie);
}

void Settings::setEtat(QByteArray etat){
    this->etat = etat;
    iniParam->setValue("fenetre/etat", etat);
}

void Settings::setGeometrieEtat(QByteArray geometrie, QByteArray etat){
    this->geometrie = geometrie;
    this->etat = etat;
    iniParam->setValue("fenetre/geometry", geometrie);
    iniParam->setValue("fenetre/state", etat);
}

QByteArray Settings::getIniGeometrie(){
    return iniParam->value("fenetre/geometry", settingDefaultByteArray).toByteArray();
}

QByteArray Settings::getGeometrie(){
    return this->geometrie;
}

QByteArray Settings::getIniEtat(){
    return iniParam->value("fenetre/state", settingDefaultByteArray).toByteArray();
}

QByteArray Settings::getEtat(){
    return this->etat;
}

void Settings::setGeometrieDock(QByteArray geometrie) {
    this->geometrieDock = geometrie;
    iniParam->setValue("dock/ope/geometry", geometrie);
}

QByteArray Settings::getIniGeometrieDock() {
    return iniParam->value("dock/ope/geometry", settingDefaultByteArray).toByteArray();
}

QByteArray Settings::getGeometrieDock() {
    return this->geometrieDock;
}

void Settings::setDockIsFloating(bool floating) {
    this->dockIsFloating = floating;
    iniParam->setValue("dock/ope/floating", floating);
}

bool Settings::getIniDockIsFloating() {
    return iniParam->value("dock/ope/floating", settingDefaultBool).toBool();
}

bool Settings::getDockIsFloating() {
    return this->dockIsFloating;
}

void Settings::setRestoreSizePos(bool enabled){
    this->restoreSizePos = enabled;
    iniParam->setValue("fenetre/restoreSizePos", enabled);
}

bool Settings::getIniRestoreSizePos(){
    return iniParam->value("fenetre/restoreSizePos", settingDefaultBool).toBool();
}

bool Settings::getRestoreSizePos(){
    return this->restoreSizePos;
}

void Settings::setVerificationAutoMiseAJour(bool enabled){
    this->m_verificationAutoMiseAJour = enabled;
    iniParam->setValue("miseAJour/automatique", enabled);
}

bool Settings::getIniVerificationAutoMiseAJour(){
    return iniParam->value("miseAJour/automatique", settingDefaultBool).toBool();
}

bool Settings::getVerificationAutoMiseAJour(){
    return this->m_verificationAutoMiseAJour;
}

void Settings::setNombreJourMiseAJour(int nombreJour){
    this->m_nombreJourMiseAJour = nombreJour;
    iniParam->setValue("miseAJour/nombreJour", nombreJour);
}

int Settings::getIniNombreJourMiseAJour(){
    return iniParam->value("miseAJour/nombreJour", 7).toInt();
}

int Settings::getNombreJourMiseAJour(){
    return m_nombreJourMiseAJour;
}

void Settings::setDerniereVerificationMiseAJour(QDate date){
    this->m_derniereVerificationMiseAJour = date;
    qDebug() << "\tsetDerniereVerificationMiseAjour - Date : " << date;
    iniParam->setValue("miseAJour/derniereVerification", date);
}

QDate Settings::getIniDerniereVerificationMiseAJour(){
    return iniParam->value("miseAJour/derniereVerification", QDate(1900, 01, 01)).toDate();
}

QDate Settings::getDerniereVerificationMiseAJour(){
    return m_derniereVerificationMiseAJour;
}

QDate Settings::getProchaineVerificationMiseAjour() {
    return m_derniereVerificationMiseAJour.addDays(this->m_nombreJourMiseAJour);
}

void Settings::setMiseAJourBeta(bool enabled) {
    this->m_miseAJourBeta = enabled;
    iniParam->setValue("miseAJour/beta", enabled);
}

bool Settings::getIniMiseAJourBeta() {
    return iniParam->value("miseAJour/beta", settingDefaultBool).toBool();
}

bool Settings::getMiseAJourBeta() {
    return this->m_miseAJourBeta;
}

void Settings::setRestoreData(bool enabled) {
    this->m_restoreData = enabled;
    iniParam->setValue("data/restore", enabled);
}

bool Settings::getIniRestoreData() {
    return iniParam->value("data/restore", true).toBool();
}

bool Settings::getRestoreData() {
    return m_restoreData;
}

void Settings::setMessageConfirmationFermeture(bool enabled){
    this->m_messageConfirmationFermeture = enabled;
    iniParam->setValue("fenetre/confirmationFermeture", enabled);
}

bool Settings::getIniMessageConfirmationFermeture(){
    return iniParam->value("fenetre/confirmationFermeture", true).toBool();
}

bool Settings::getMessageConfirmationFermeture(){
    return m_messageConfirmationFermeture;
}

void Settings::setVersion(QString version) {
    this->m_version = version;
    iniParam->setValue("data/version", version);
}

QString Settings::getIniVersion() {
    return iniParam->value("data/version", settingDefaultString).toString();
}

QString Settings::getVersion() {
    return m_version;
}

void Settings::setDossierBlazeAndCave(QString dossier) {
    this->m_dossierBlazeAndCave = dossier;
    iniParam->setValue("data/dossierBAC", dossier);
}

QString Settings::getIniDossierBlazeAndCave() {
    return iniParam->value("data/dossierBAC", settingDefaultString).toString();
}

QString Settings::getDossierBlazeAndCave() {
    return m_dossierBlazeAndCave;
}

void Settings::setMilestones(bool enabled) {
    this->m_milestones = enabled;
    iniParam->setValue("data/milestones", enabled);
}

bool Settings::getIniMilestones() {
    return iniParam->value("data/milestones", true).toBool();
}

bool Settings::getMilestones() {
    return m_milestones;
}

void Settings::setStatistics(bool enabled) {
    this->m_statistics = enabled;
    iniParam->setValue("data/statistics", enabled);
}

bool Settings::getIniStatistics() {
    return iniParam->value("data/statistics", true).toBool();
}

bool Settings::getStatistics() {
    return m_statistics;
}

void Settings::setFichierAdvancementsPerso(QString fichier) {
    this->m_fichierAdvancementsPerso = fichier;
    iniParam->setValue("data/advancementsPerso", fichier);
}

QString Settings::getIniFichierAdvancementsPerso() {
    return iniParam->value("data/advancementsPerso", settingDefaultString).toString();
}

QString Settings::getFichierAdvancementsPerso() {
    return m_fichierAdvancementsPerso;
}
