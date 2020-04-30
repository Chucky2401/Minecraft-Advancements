#ifndef FRM_PRINCIPALE_H
#define FRM_PRINCIPALE_H

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
    // Divers
    bool m_test;
    QTemporaryDir m_tempDir;
    QString m_qsAppDataPath;
    // Cache
    bool m_bUpdateProgres;
    QDir m_qdDossierAdvancedments;
    QString m_qs7zBin;
    QStringList m_qsl7zipArguments;
    QProcess *m_qp7zProcess;
    // Minecraft
    QString m_qsDossierMinecraft;
    QString m_qsDossierVersion;
    QStringList m_qslListVersionJar;
    QString m_qsDossierSauvegarde;

private slots:
    //Configuration
    void choixLauncher(int index);
    void choixVersion(int index);
    void choixDossierSauvegarde(bool checked);
    void extraireProgres(bool checked);
    void readJSON(bool checked);
};
#endif // FRM_PRINCIPALE_H
