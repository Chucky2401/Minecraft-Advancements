#ifndef FRM_PRINCIPALE_H
#define FRM_PRINCIPALE_H

#include <Qt>
#include <QTextDocument>
#include <QMainWindow>
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
#include "settings/settings.h"
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

public:
    FRM_Principale(QWidget *parent = nullptr, bool test = false);
    ~FRM_Principale();

protected:
    void closeEvent(QCloseEvent *event);

private:
    //GUI
    Ui::FRM_Principale *ui;
    // Booléen
    bool ouvertureEnCours;
    bool m_bErreurExtraction;
    bool m_bVersionOK;
    bool m_bProgresVanillaOK;
    bool m_bProgresBlazeandcaveOK;
    bool m_bProgresPersoOK;
    // Utile
    QTemporaryDir m_tempDir;
    QString m_qsAppDataPath;
    QString m_qsUserName;
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
    QVariantMap m_qvmJsonProgresPerso;
    // BlazeandCave
    QDir m_qdDossierAdvancementsBlazeAndCave;
    QString m_qsDossierAExclure;
    // Listing Progrés
    bool bTousLesProgres;
    QList<QStandardItem *> m_qlLigneProgres;
    QStandardItemModel *m_qsimProgresRealisation;
    QSortFilterProxyModel *proxModelFiltreOrigine;
    QSortFilterProxyModel *proxyModelFiltreTitre;
    QSortFilterProxyModel *proxyModelFiltreProgresFinis;
    QSortFilterProxyModel *proxyModelFiltreConditionFaite;
    QSortFilterProxyModel *proxyModelFiltreTypeCondition;
    DateEtHeureFilterProxyModel *proxyModelFiltreDate;
    QAbstractItemModel *m_defaultModelCompleter;
    QCompleter *m_defaultCompleter;
    QCompleter *m_sansCompleter;
    // Settings
    class Settings *param;
    DIA_Parametres *diaParametres;
    DIA_apropos *diaAPropos;
    // Mise à jour
    QNetworkAccessManager *m_qnamManager;
    QByteArray m_qbaDonneesTelechargees;
    // TEST
    bool m_test;

signals:
    void downloaded(bool ecrireFichierUpdate);
    void fermeture();

private slots:
    //Data
    QString hashLangue();
    QString numeroIndex();
    //Configuration
    void choixLauncher(int index);
    void choixVersion(int index);
    void choixFichierAdvancements(bool checked);
    void extraireProgres(bool checked);
    void selectionDossierBlazeandcave(bool checked);
    void exclureStats(int statut);
    // Lecture et affichage
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
