#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QVariant>
#include <QByteArray>
#include <QDebug>
#include <QDate>
#include <QDir>
#include <QFile>


class Settings
{
public:
    Settings();

    void initialisation(bool test = false);

    QString getPath();
    void setGeometrie(QByteArray geometrie);
    void setEtat(QByteArray etat);
    void setGeometrieEtat(QByteArray geometrie, QByteArray etat);
    QByteArray getIniGeometrie();
    QByteArray getGeometrie();
    QByteArray getIniEtat();
    QByteArray getEtat();

    void setRestoreSizePos(bool enabled);
    bool getIniRestoreSizePos();
    bool getRestoreSizePos();

    void setVerificationAutoMiseAJour(bool enabled);
    bool getIniVerificationAutoMiseAJour();
    bool getVerificationAutoMiseAJour();

    void setNombreJourMiseAJour(int nombreJour);
    int getIniNombreJourMiseAJour();
    int getNombreJourMiseAJour();

    void setDerniereVerificationMiseAJour(QDate date);
    QDate getIniDerniereVerificationMiseAJour();
    QDate getDerniereVerificationMiseAJour();
    QDate getProchaineVerificationMiseAjour();

    void setMiseAJourBeta(bool enabled);
    bool getIniMiseAJourBeta();
    bool getMiseAJourBeta();

    void setMessageConfirmationFermeture(bool enabled);
    bool getIniMessageConfirmationFermeture();
    bool getMessageConfirmationFermeture();


private:
    const QVariant settingDefaultString = "DNE";
    const QVariant settingDefaultInt = -1;
    const QVariant settingDefaultBool = false;
    const QVariant settingDefaultByteArray = "DNE";

    QString m_qsAppdataPath;
    QSettings *iniParam;
    QString imagePath;
    QString bddPath;
    QString bddName;
    bool farming;
    bool autoExpand;
    bool restoreRecipe;
    QList<QVariant> lastRecipe;
    int quantiteLastRecipe;
    QByteArray geometrie;
    QByteArray etat;
    bool restoreSizePos;
    bool m_visibiliteFarming;
    bool m_visibiliteDeploiementAuto;
    bool m_verificationAutoMiseAJour;
    int m_nombreJourMiseAJour;
    QDate m_derniereVerificationMiseAJour;
    bool m_miseAJourBeta;
    bool m_messageConfirmationFermeture;

};

#endif // SETTINGS_H
