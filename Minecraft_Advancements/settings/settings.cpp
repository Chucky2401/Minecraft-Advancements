#include "settings.h"

Settings::Settings() {
    m_qsAppdataPath = qEnvironmentVariable("APPDATA");

}

void Settings::initialisation(bool test) {
    iniParam = new QSettings(QSettings::IniFormat, QSettings::UserScope, "BlackWizard Company", "Minecraft Advancements");

    geometrie = this->getIniGeometrie();
    etat = this->getIniEtat();
    restoreSizePos = this->getIniRestoreSizePos();
    this->setRestoreSizePos(restoreSizePos);

    m_verificationAutoMiseAJour = this->getIniVerificationAutoMiseAJour();
    this->setVerificationAutoMiseAJour(m_verificationAutoMiseAJour);

    m_nombreJourMiseAJour = this->getIniNombreJourMiseAJour();
    this->setNombreJourMiseAJour(m_nombreJourMiseAJour);

    m_derniereVerificationMiseAJour = this->getIniDerniereVerificationMiseAJour();
    if (m_derniereVerificationMiseAJour == QDate(1900, 01, 01)){
        m_derniereVerificationMiseAJour = QDate::currentDate();
        this->setDerniereVerificationMiseAJour(m_derniereVerificationMiseAJour);
    }

    m_messageConfirmationFermeture = this->getIniMessageConfirmationFermeture();
    this->setMessageConfirmationFermeture(m_messageConfirmationFermeture);
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
