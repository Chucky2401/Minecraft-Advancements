#ifndef FRM_PRINCIPALE_H
#define FRM_PRINCIPALE_H

#include <Qt>
#include <QTextDocument>
#include <QMainWindow>

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

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class FRM_Principale; }
QT_END_NAMESPACE

class FRM_Principale : public QMainWindow
{
    Q_OBJECT

public:
    FRM_Principale(QWidget *parent = nullptr, bool test = false);
    ~FRM_Principale();

private:
    //GUI
    Ui::FRM_Principale *ui;
    // Booléen
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
    // Listing Progrés
    bool bTousLesProgres;
    QList<QStandardItem *> m_qlLigneProgres;
    QStandardItemModel *m_qsimProgresRealisation;
    QSortFilterProxyModel *proxModelFiltreOrigine;
    QSortFilterProxyModel *proxyModelFiltreTitre;
    QSortFilterProxyModel *proxyModelFiltreProgresFinis;
    QSortFilterProxyModel *proxyModelFiltreConditionFaite;
    // TEST
    bool m_test;

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
    // Lecture et affichage
    void readJSONsVanilla(bool checked);
    void readJSONsBlazeandcave(bool checked);
    void readAllJsons(bool checked);
    void filtreTableOrigine(QString filtre);
    void filtreTableTitre(QString filtre);
    void filtreTableProgresFinis(QString filtre);
    void filtreTableConditionFait(QString filtre);
    // TEST
    void TEST(bool checked);
};
#endif // FRM_PRINCIPALE_H
