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

    void setBddPath(QString path);
    QString getBddPath();
    QString getIniBddPath();

    void setBddName(QString name);
    QString getBddName();

    void setGeometrie(QByteArray geometrie);
    void setEtat(QByteArray etat);
    void setGeometrieEtat(QByteArray geometrie, QByteArray etat);
    QByteArray getIniGeometrie();
    QByteArray getGeometrie();
    QByteArray getIniEtat();
    QByteArray getEtat();

    void setGeometrieDock(QByteArray geometrie);
    QByteArray getIniGeometrieDock();
    QByteArray getGeometrieDock();

    void setDockIsFloating(bool floating);
    bool getIniDockIsFloating();
    bool getDockIsFloating();

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

    void setRestoreSizePos(bool enabled);
    bool getIniRestoreSizePos();
    bool getRestoreSizePos();

    void setRestoreData(bool enabled);
    bool getIniRestoreData();
    bool getRestoreData();

    void setMessageConfirmationFermeture(bool enabled);
    bool getIniMessageConfirmationFermeture();
    bool getMessageConfirmationFermeture();

    // Data FRM_PRINCIPALE
    void setVersion(QString version);
    QString getIniVersion();
    QString getVersion();

    void setDossierBlazeAndCave(QString dossier);
    QString getIniDossierBlazeAndCave();
    QString getDossierBlazeAndCave();

    void setMilestones(bool enabled);
    bool getIniMilestones();
    bool getMilestones();

    void setStatistics(bool enabled);
    bool getIniStatistics();
    bool getStatistics();

    void setFichierAdvancementsPerso(QString fichier);
    QString getIniFichierAdvancementsPerso();
    QString getFichierAdvancementsPerso();


private:
    const QVariant settingDefaultString = "DNE";
    const QVariant settingDefaultInt = -1;
    const QVariant settingDefaultBool = false;
    const QVariant settingDefaultByteArray = "DNE";

    QString m_qsAppdataPath;
    QString m_qsPathRoamingBdd;
    QSettings *iniParam;
    QString bddPath;
    QString bddName;
    QByteArray geometrie;
    QByteArray etat;
    QByteArray geometrieDock;
    bool restoreSizePos;
    bool restoreSizePosDock;
    bool dockIsFloating;
    bool m_verificationAutoMiseAJour;
    int m_nombreJourMiseAJour;
    QDate m_derniereVerificationMiseAJour;
    bool m_miseAJourBeta;
    bool m_restoreData;
    bool m_messageConfirmationFermeture;

    // Data FRM_PRINCIPALE
    QString m_version;
    QString m_dossierBlazeAndCave;
    bool m_milestones;
    bool m_statistics;
    QString m_fichierAdvancementsPerso;

};

#endif // SETTINGS_H
