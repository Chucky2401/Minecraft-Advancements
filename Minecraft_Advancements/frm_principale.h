#ifndef FRM_PRINCIPALE_H
#define FRM_PRINCIPALE_H

#include <Qt>
#include <QTextDocument>
#include <QMainWindow>
#include <QStatusBar>
#include <QProgressBar>
#include <QCloseEvent>

#include <QTemporaryDir>

#include <QStringList>
#include <QMessageBox>

#include <QDir>
#include <QDirIterator>
#include <QFileDialog>

#include <QProcess>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QMapIterator>

#include <QDateTime>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include <QCompleter>

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtXml>
#include <QProcess>

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

#include <QDebug>

#include "dateetheurefilterproxymodel.h"
#include "sqlmodel.h"
#include "settings/settings.h"
#include "settings/database.h"
#include "settings/dia_parametres.h"
#include "dia_apropos.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class FRM_Principale;
}

QT_END_NAMESPACE

class FRM_Principale : public QMainWindow
{
    Q_OBJECT

// Fonction public
public:
    FRM_Principale(QWidget *parent = nullptr, bool test = false);
    ~FRM_Principale();

// Fonctions privés
private:
    // Data
    QString hashLangue();
    QString numeroIndex();
    // Configuration
    QVariantMap ouvrirJson(QString fichier);
    void traitementFichierAdvancements(QString fichier);
    void traitementDossierBac(QString folder);
    void activationBoutonExtraction();
    void toutesLesTraductions(QVariantMap jsonLang);
    void toutesLesTraductionsListe();
    void definirModele();
    void effacerFiltreDate();
    void resetVue();
    void afficherMessage(int type, QString text, QString information, QString detail = "");

// Fonction protéger
protected:
    void closeEvent(QCloseEvent *event);

// Attributes privés
private:
    //GUI
    Ui::FRM_Principale *ui;
    QStatusBar *m_statusBar;
    QProgressBar *m_progressExtractionProgresVanilla;
    QLabel *m_labelExtractionProgresVanilla;
    // Constante
    const QString connectionName = "principal";
    // Booléen
    bool ouvertureEnCours;
    bool m_ouvertureJson;
    bool m_bErreurExtraction;
    bool m_bVersionOK;
    bool m_bProgresVanillaOK;
    bool m_bProgresBlazeandcaveOK;
    bool m_bProgresPersoOK;
    // Utile
    QTemporaryDir m_tempDir;
    QString m_qsAppDataPath;
    QString m_qsUserName;
    QMessageBox m_qmbMessage;
    // Cache
    bool m_bUpdateProgres;
    QDir m_qdDossierAdvancedments;
    QString m_qsFichierAdvancementsSolo;
    QString m_qsFichierLang;
    QString m_qs7zBin;
    QStringList m_qsl7zipArguments;
    QStringList m_qsl7zipArgumentsLang;
    QProcess *m_qp7zProcess;
    // Minecraft
    QString m_qsJSONVersion;
    QString m_qsDossierIndexes;
    QString m_qsFichierIndex;
    QString m_qsCleLang;
    QString m_qsDossierMinecraft;
    QString m_qsDossierVersion;
    QString m_qsDossierAssets;
    QString m_qsDossierObjects;
    QString m_qsNumeroVersion;
    QStringList m_qslListVersionJar;
    QString m_qsDossierSauvegarde;
    //QVariantMap m_qvmJsonProgresPerso;
    // Traduction
    QStringList m_qslClesToutesLesTrads;
    QStringList m_qslToutesLesTrads;
    // BlazeandCave
    QDir m_qdDossierAdvancementsBlazeAndCave;
    QString m_qsDossierAExclure;
    // Listing Progrés
    bool bTousLesProgres;
    QStringList m_qslRequeteComparaison;
    QList<QStandardItem *> m_qlLigneProgres;
    QStandardItemModel *m_qsimProgresRealisation;
    //QSortFilterProxyModel *proxModelFiltreOrigine;
    QSortFilterProxyModel *proxyModelFiltreTitre;
    //QSortFilterProxyModel *proxyModelFiltreProgresFinis;
    //QSortFilterProxyModel *proxyModelFiltreConditionFaite;
    //QSortFilterProxyModel *proxyModelFiltreTypeCondition;
    //DateEtHeureFilterProxyModel *proxyModelFiltreDate;
    QAbstractItemModel *m_defaultModelCompleter;
    QSqlQueryModel *plainModel;
    SqlModel *m_smProgresRealisation;
    QCompleter *m_defaultCompleter;
    QCompleter *m_sansCompleter;
    // Settings
    class Settings *param;
    class database bdd;
    DIA_Parametres *diaParametres;
    DIA_apropos *diaAPropos;
    // Mise à jour
    bool m_updateBetaVerifiee;
    QNetworkAccessManager *m_qnamManager;
    QByteArray m_qbaDonneesTelechargees;
    // TEST
    bool m_test;

// Signaux
signals:
    void downloaded(bool ecrireFichierUpdate);
    void fermeture();

// Slots privés
private slots:
    // GUI
    void dockWidgetOperationFloating(bool floating);
//    void dockWidgetOperationClosing(bool closing);
    //Configuration
    void choixLauncher(int index);
    //void choixVersion(int index);
    void choixVersion(QString text);
    void choixFichierAdvancements(bool checked);
    void extraireProgres(bool checked);
    void selectionDossierBlazeandcave(bool checked);
    void importProgresBlazeandcave(bool checked);
    void importProgresPerso(bool checked);
    void exclureStats(int statut);
    // Lecture et affichage
    void comparerLesProgres(bool checked);
    void readJSONsVanilla(bool checked);
    void readJSONsBlazeandcave(bool checked);
    void readAllJsons(bool checked);
    void filtreTableOrigine(QString filtre);
    void filtreTableTitre(QString filtre);
    void filtreTableProgresFinis(QString filtre);
    void filtreTableConditionFait(QString filtre);
    void filtreTableTypeCondition(QString filtre);
    void dateFilterChanged();
    void effacerLesFiltres(bool checked);
    void effacerFiltresSurLesDates(bool checked);
    void etatAutoCompletion(int etat);
    void dataSelectionnee(const QModelIndex index);
    // Impression
    void imprimerTable(bool checked);
    // Fenêtres complémentaire
    void ouvrirAPropos();
    void ouvrirParametres();
    // Mise à jour
    void verifierMiseAJour();
    void fichierTelecharge(QNetworkReply* pReply);
    void comparaisonVersion(bool ecrireFichier);
    // TEST
    void TEST(bool checked);
};
#endif // FRM_PRINCIPALE_H
