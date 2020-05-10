#include "frm_principale.h"
#include "ui_frm_principale.h"

FRM_Principale::FRM_Principale(QWidget *parent, bool test)
    : QMainWindow(parent)
    , ui(new Ui::FRM_Principale), m_test(test) {

    ui->setupUi(this);
    qDebug() << test;

    if (test == false) {
        ui->qpbReadJSON->setVisible(test);
        ui->lineInDebug->setVisible(test);
    } else {
        ui->qpbReadJSON->setVisible(test);
        ui->lineInDebug->setVisible(test);
        connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(TEST(bool)));
        //connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(imprimerTable()));
    }

    ui->qgbFiltres->setEnabled(false);

    ui->qcbLangue->addItem("Français", QVariant("/fr_fr.lang"));
    ui->qcbLangue->addItem("English", QVariant("/en_us.lang"));
    //ui->qcbLangue->setCurrentIndex(0);

    this->setWindowTitle(QApplication::applicationName());
    this->setWindowIcon(QIcon(":/img/icons8_minecraft_logo_48px.png"));

    m_qsAppDataPath = qEnvironmentVariable("APPDATA");

    if (m_tempDir.isValid()) {
        qDebug() << m_tempDir.path();
    }

    m_bVersionOK = false;
    m_bProgresVanillaOK = false;
    m_bProgresBlazeandcaveOK = false;
    m_bProgresPersoOK = false;

    m_qs7zBin = "bin/7z.exe";
    m_qp7zProcess = new QProcess(this);
    m_bErreurExtraction = false;
    m_qsimProgresRealisation = new QStandardItemModel(0,6);

    proxModelFiltreOrigine = new QSortFilterProxyModel(this);
    proxyModelFiltreTitre = new QSortFilterProxyModel(this);
    proxyModelFiltreProgresFinis = new QSortFilterProxyModel(this);
    proxyModelFiltreConditionFaite = new QSortFilterProxyModel(this);

    bTousLesProgres = false;

    m_qsUserName = qgetenv("USERNAME");

    ui->qcbLauncher->addItem("", QVariant("EMPTY"));
    ui->qcbLauncher->addItem("Minecraft Launcher (Officiel Mojang)", QVariant("Mojang"));
    //ui->qcbLauncher->addItem("MultiMC", QVariant("MultiMC"));
    //ui->qcbLauncher->addItem("ATLauncher", QVariant("ATLauncher"));

    ui->qcbFiltreOrigine->addItem("");
    ui->qcbFiltreConditionFait->addItem("");
    ui->qcbFiltreConditionFait->addItem("oui");
    ui->qcbFiltreConditionFait->addItem("non");
    ui->qcbFiltreTitre->addItem("");
    ui->qcbFiltreProgresFinis->addItem("");
    ui->qcbFiltreProgresFinis->addItem("oui");
    ui->qcbFiltreProgresFinis->addItem("non");

    ui->qpbTraitementProgres->setVisible(false);
    ui->qpbTraitementProgres->setValue(0);

    connect(ui->qcbLauncher, SIGNAL(currentIndexChanged(int)), this, SLOT(choixLauncher(int)));
    connect(ui->qcbVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(choixVersion(int)));
    connect(ui->qpbSelectionFichierProgres, SIGNAL(clicked(bool)), this, SLOT(choixFichierAdvancements(bool)));
    connect(ui->qpbDossierBlazeandcave, SIGNAL(clicked(bool)), this, SLOT(selectionDossierBlazeandcave(bool)));
    connect(ui->qpbExtraireProgres, SIGNAL(clicked(bool)), this, SLOT(extraireProgres(bool)));
    connect(ui->qpbReadJSONsVanilla, SIGNAL(clicked(bool)), this, SLOT(readJSONsVanilla(bool)));
    connect(ui->qpbReadJSONsBlazeandcave, SIGNAL(clicked(bool)), this, SLOT(readJSONsBlazeandcave(bool)));
    connect(ui->qpbReadAllJSONs, SIGNAL(clicked(bool)), this, SLOT(readAllJsons(bool)));
    connect(ui->pbImprimer, SIGNAL(clicked(bool)), this, SLOT(imprimerTable(bool)));
    connect(ui->qcbFiltreProgresFinis, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableProgresFinis(QString)));
    connect(ui->qcbFiltreConditionFait, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableConditionFait(QString)));

    ui->qcbLauncher->setCurrentIndex(1);
    ui->qpbSelectionDossierLanceur->setVisible(false);
    ui->qpbExtraireProgres->setEnabled(false);
    ui->qlAdvancementsExtrait->setVisible(false);
    ui->qlLangExtraite->setVisible(false);
    ui->qlProgresPersoOuvert->setVisible(false);
    ui->qpbReadJSONsVanilla->setEnabled(false);
    ui->qpbReadJSONsBlazeandcave->setEnabled(false);
}

FRM_Principale::~FRM_Principale() {
    delete ui;
}

void FRM_Principale::choixLauncher(int index) {
    QString qsLanceur = ui->qcbLauncher->itemData(index).toString();
    QString qsFauxCheminLanceur, qsValeurTemp, qsNomVersionTemp, qsNomVersion;
    QStringList qslFormatFichier, qslDossierLanceurTemp, qslNomVersionTemp;

    m_qslListVersionJar.clear();
    ui->qcbVersion->clear();
    ui->qleDossierLanceur->clear();
    qslFormatFichier << "*.jar";
    ui->qpbSelectionDossierLanceur->setEnabled(true);
    m_bUpdateProgres = false;

    ui->qcbVersion->addItem("", QVariant("EMPTY"));

    if (qsLanceur == "Mojang") {
        ui->qpbSelectionDossierLanceur->setEnabled(false);

        qslDossierLanceurTemp = m_qsAppDataPath.split("\\");
        for (int i = 0 ; i < qslDossierLanceurTemp.length() ; i++) {
            if (i != 2) {
                qsFauxCheminLanceur += qslDossierLanceurTemp.at(i);
            } else {
                qsFauxCheminLanceur += "fake_Utilisateur";
            }

            if (i + 1 != qslDossierLanceurTemp.length())
                qsFauxCheminLanceur += "\\";
        }


        ui->qleDossierLanceur->setText(qsFauxCheminLanceur);
        m_qsDossierMinecraft = m_qsAppDataPath + "\\.minecraft";
        m_qsDossierVersion = m_qsAppDataPath + "\\.minecraft\\versions";
        m_qsDossierAssets = m_qsAppDataPath + "\\.minecraft\\assets";
        m_qsDossierObjects = m_qsDossierAssets + "\\objects";
        m_qsDossierIndexes = m_qsDossierAssets + "\\indexes";
        QDirIterator qdiMinecraftVersion(m_qsDossierVersion, qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

        while (qdiMinecraftVersion.hasNext()) {
            qsNomVersion.clear();
            qsValeurTemp = qdiMinecraftVersion.next();
            m_qslListVersionJar << qsValeurTemp;
            qsNomVersionTemp = qsValeurTemp.split("/").last();

            if (!qsNomVersionTemp.contains("fabric") && !qsNomVersionTemp.contains("forge")) {
                qslNomVersionTemp = qsNomVersionTemp.split(".");
                for (int i = 0; i < qslNomVersionTemp.length()-1; i++) {
                    qsNomVersion = qsNomVersion + qslNomVersionTemp.at(i);
                    if (i + 1 != qslNomVersionTemp.length()-1) {
                        qsNomVersion = qsNomVersion + ".";
                    }
                }
                ui->qcbVersion->addItem(qsNomVersion, QVariant(qsValeurTemp));
                qDebug() << "Nom Version" << qsNomVersion << "- qsValeurTemp" << qsValeurTemp;
            }

        }
    }
}

void FRM_Principale::choixVersion(int index) {
    QString qsCheminVersion = ui->qcbVersion->itemData(index).toString();
    QString qsFauxChemin, qsNumeroIndex = "";
    QStringList qslFormatFichier;
    qslFormatFichier << "*.json";
    int iFicherDejaExtrait = 0;

    if (ui->qcbVersion->currentIndex() != 0) {
        m_qsJSONVersion = ui->qcbVersion->currentData().toString().replace(".jar", ".json");
        // Aller chercher id avec la variable m_qsJSONVersion
        qsNumeroIndex = numeroIndex();
        // Renseigner fichier index (m_qsFichierIndex
        m_qsFichierIndex = m_qsDossierIndexes + "\\" + qsNumeroIndex + ".json";
    }
    qDebug() << m_qsFichierIndex;

    m_qsNumeroVersion = ui->qcbVersion->currentText();
    m_qsl7zipArguments.clear();
    m_qsl7zipArgumentsLang.clear();
    //ui->qlAdvancementsExtrait->setVisible(false);
    //ui->qlLangExtraite->setVisible(false);

    if (qsCheminVersion != "EMPTY") {
        ui->qleCheminVersion->setText("C:\\fake_Path\\" + qsCheminVersion.split("/").last());
    } else
        ui->qleCheminVersion->setText("");

    m_qdDossierAdvancedments.setPath("advancements/" + ui->qcbVersion->currentText() + "/");
    m_qsFichierLang = m_qdDossierAdvancedments.absolutePath() + ui->qcbLangue->currentData().toString();
    m_qsCleLang = "minecraft/lang" + ui->qcbLangue->currentData().toString().replace(".lang", ".json");

    if (ui->qcbVersion->currentData() != "EMPTY")
        m_bVersionOK = true;
    else
        m_bVersionOK = false;

    if (m_qdDossierAdvancedments.exists() && QFile(m_qsFichierLang).exists() && m_bVersionOK) {
        ui->qpbExtraireProgres->setText("Update Progrès");
        ui->qpbExtraireProgres->setEnabled(true);
        m_bUpdateProgres = true;
        m_bProgresVanillaOK = true;

        QDirIterator qdiFichierProgresExtrait(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);
        while (qdiFichierProgresExtrait.hasNext()) {
            qdiFichierProgresExtrait.next();
            iFicherDejaExtrait++;
        }

        if (iFicherDejaExtrait > 1) {
            ui->qlAdvancementsExtrait->setText("Progrès extrait !");
            ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: green; }");
            ui->qlAdvancementsExtrait->setVisible(true);
        } else {
            ui->qlAdvancementsExtrait->setText("Progrès non extrait proprement !");
            ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: red; }");
            ui->qlAdvancementsExtrait->setVisible(true);
        }

        ui->qlLangExtraite->setText("Langue extraite !");
        ui->qlLangExtraite->setStyleSheet("QLabel { color: green; }");
        ui->qlLangExtraite->setVisible(true);

    } else if (m_qdDossierAdvancedments.exists() && !QFile(m_qsFichierLang).exists() && m_bVersionOK) {
        m_qdDossierAdvancedments.removeRecursively();
        if (m_qdDossierAdvancedments.mkpath(".")) {
            ui->qpbExtraireProgres->setEnabled(true);
            ui->qpbExtraireProgres->setText("Extraire Progrès");
            m_bUpdateProgres = false;
            m_bProgresVanillaOK = false;

            QDirIterator qdiFichierProgresExtrait(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);
            while (qdiFichierProgresExtrait.hasNext()) {
                qdiFichierProgresExtrait.next();
                iFicherDejaExtrait++;
            }

            if (iFicherDejaExtrait > 1) {
                ui->qlAdvancementsExtrait->setText("Progrès extrait !");
                ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: green; }");
                ui->qlAdvancementsExtrait->setVisible(true);
            } else {
                ui->qlAdvancementsExtrait->setText("Progrès non extrait proprement !");
                ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: red; }");
                ui->qlAdvancementsExtrait->setVisible(true);
            }

            ui->qlLangExtraite->setText("Langue non extraite !");
            ui->qlLangExtraite->setStyleSheet("QLabel { color: red; }");
            ui->qlLangExtraite->setVisible(true);
        }
    } else if (ui->qcbVersion->currentData() == "EMPTY") {
        ui->qpbExtraireProgres->setEnabled(false);
        m_bProgresVanillaOK = false;
    } else {
        if (m_qdDossierAdvancedments.mkpath(".")) {
            ui->qpbExtraireProgres->setEnabled(true);
            ui->qpbExtraireProgres->setText("Extraire Progrès");
            m_bUpdateProgres = false;
            m_bProgresVanillaOK = false;
        }
    }

    if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK) {
        ui->qpbReadJSONsVanilla->setEnabled(true);
    } else {
        ui->qpbReadJSONsVanilla->setEnabled(false);
    }

    if (m_bVersionOK && m_bProgresPersoOK && m_bProgresBlazeandcaveOK) {
        ui->qpbReadAllJSONs->setEnabled(true);
    } else {
        ui->qpbReadAllJSONs->setEnabled(false);
    }

    if (ui->qcbVersion->currentData() != "EMPTY") {
        m_qsl7zipArguments << "x" << qsCheminVersion << "-o"+m_tempDir.path() << "-ir!data\\minecraft\\advancements\\*.json";
        m_qsl7zipArgumentsLang << "x" << qsCheminVersion << "-o"+m_tempDir.path() << "-ir!assets\\minecraft\\lang\\*.json";
    }
}

void FRM_Principale::extraireProgres(bool checked) {
    QStringList qslFormatFichier;
    QString qsTempNom, qsNouveauNom;
    bool bErreurDetecteAdvancement = false, bErreurDetecteLang = false;

    QMessageBox qmbError;
    qmbError.setTextFormat(Qt::RichText);
    qmbError.setWindowIcon(QIcon(":/img/icons8_minecraft_logo_48px.png"));
    qmbError.setStandardButtons(QMessageBox::Ok);
    qmbError.setDefaultButton(QMessageBox::Ok);
    qmbError.setIcon(QMessageBox::Critical);

    qslFormatFichier << "*.json";

    if (m_bUpdateProgres) {
        m_qdDossierAdvancedments.removeRecursively();
        m_qdDossierAdvancedments.mkpath(".");
    }

    m_qp7zProcess->start(m_qs7zBin, m_qsl7zipArguments);
    if (m_qp7zProcess->waitForFinished()) {
        QDirIterator qdiFichierProgres(m_tempDir.path()+"/data/minecraft/advancements/", qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

        while (qdiFichierProgres.hasNext() && !bErreurDetecteAdvancement) {
            qsTempNom = qdiFichierProgres.next();
            QString qsCheminCompletTemp = qdiFichierProgres.filePath();
            QString qsNomDuFichierTemp = qdiFichierProgres.fileName();
            QString qsDossierTemp = qsCheminCompletTemp.replace(qsNomDuFichierTemp, "");
            QString qsDossierFinal = qsDossierTemp.replace(m_tempDir.path()+"/data/minecraft/advancements/", m_qdDossierAdvancedments.absolutePath() + "/");
            qsNouveauNom = qsTempNom;
            qsNouveauNom.replace(m_tempDir.path()+"/data/minecraft/advancements/", m_qdDossierAdvancedments.absolutePath() + "/");
            QFile qfFichierTemporaire(qsTempNom);
            QFile qfFichierFinal(qsNouveauNom);
            QDir qdDossierFinal(qsDossierFinal);

            if (!(qdDossierFinal.exists()))
                qdDossierFinal.mkpath(".");

            if (qsNomDuFichierTemp != "." && qsNomDuFichierTemp != "..") {
                if(!qfFichierTemporaire.open(QIODevice::ReadOnly)){
                    qDebug()<<"Failed to open "<< qfFichierTemporaire;
                    bErreurDetecteAdvancement = true;
                } else {
                    if(!qfFichierFinal.open(QIODevice::ReadWrite)){
                        qDebug()<<"Failed to open "<< qfFichierFinal;
                        bErreurDetecteAdvancement = true;
                    } else {
                        QByteArray qbaContenuFichierTemp = qfFichierTemporaire.readAll();

                        qfFichierFinal.write(qbaContenuFichierTemp);
                    }
                }
            }

            qfFichierFinal.close();
            qfFichierTemporaire.close();
            qfFichierTemporaire.remove();
        }

        ui->qlAdvancementsExtrait->setVisible(true);

        if (!bErreurDetecteAdvancement) {
            ui->qpbExtraireProgres->setText("Update Progrès");
            ui->qlAdvancementsExtrait->setText("Progrès extrait !");
            ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: green; }");
            m_bUpdateProgres = true;
            QMessageBox::information(this, "Extraction terminée", "L'extraction des progrès Vanilla est terminée.");
        } else {
            ui->qlAdvancementsExtrait->setText("Extraction progrès échoué !");
            ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: red; }");
            m_qdDossierAdvancedments.removeRecursively();
            m_qdDossierAdvancedments.mkpath(".");
            QMessageBox::information(this, "Extraction échouée", "L'extraction des progrès Vanilla est en erreur.");
        }
        QDir qdDossierTemporaire(m_tempDir.path()+"/data");
        qdDossierTemporaire.removeRecursively();
    }

//    qDebug () << "ErreurDetectAdvancement" << bErreurDetecteAdvancement;
//    qDebug () << "ErreurDetectLang" << bErreurDetecteLang;
    if (!bErreurDetecteAdvancement && ui->qcbLangue->currentData() == "/en_us.lang") {
//        qDebug() << "Traitement de la lang";
        m_qp7zProcess->start(m_qs7zBin, m_qsl7zipArgumentsLang);
        if (m_qp7zProcess->waitForFinished()) {
            QDirIterator qdiFichierLang(m_tempDir.path()+"/assets/minecraft/lang/", qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

            while (qdiFichierLang.hasNext() && !bErreurDetecteLang) {
                qsTempNom = qdiFichierLang.next();
                QString qsCheminCompletTemp = qdiFichierLang.filePath();
                QString qsNomDuFichierTemp = qdiFichierLang.fileName();
                QString qsDossierTemp = qsCheminCompletTemp.replace(qsNomDuFichierTemp, "");
                QFile qfFichierTemporaire(qsTempNom);
                QFile qfFichierFinal(m_qsFichierLang);
                qDebug() << qsCheminCompletTemp;
                qDebug() << qsNomDuFichierTemp;

                if (qsNomDuFichierTemp != "." && qsNomDuFichierTemp != "..") {
                    if(!qfFichierTemporaire.open(QIODevice::ReadOnly)) {
                        qDebug() << "Failed to open " << qfFichierTemporaire;
                        bErreurDetecteLang = true;
                    } else {
                        qDebug() << "Fichier" << qfFichierTemporaire << "ouvert";
                        if(!qfFichierFinal.open(QIODevice::ReadWrite)){
                            qDebug() << "Failed to open " << qfFichierFinal;
                            bErreurDetecteLang = true;
                        } else {
                            qDebug() << "Fichier" << qfFichierFinal << "ouvert";
                            QByteArray qbaContenuFichierTemp = qfFichierTemporaire.readAll();
                            qDebug() << "qbaContenuFichierTemp" << qbaContenuFichierTemp;
                            if (qfFichierFinal.write(qbaContenuFichierTemp) == -1) {
                                bErreurDetecteLang = true;
                            }
                            qfFichierFinal.close();
                            qfFichierTemporaire.close();
                            qfFichierTemporaire.remove();
                        }
                    }
                }

            }
        }
    } else if (!bErreurDetecteAdvancement && ui->qcbLangue->currentData() != "/en_us.lang") {
        QString qsNomFichierLangue = hashLangue();
        QString qsFichier = "";
        QFile qfFichierTemporaire("");
        QFile qfFichierFinal(m_qsFichierLang);

        QDirIterator qdiFichierLangue(m_qsDossierObjects, QStringList() << qsNomFichierLangue, QDir::Files, QDirIterator::Subdirectories);

        qDebug() << "qsNomFichierLangue" << qsNomFichierLangue;

        while (qdiFichierLangue.hasNext()) {
            qsFichier = qdiFichierLangue.next();
            qDebug() << "#BOUCLE" << qsFichier << "-" << qdiFichierLangue.path();
        }

        qfFichierTemporaire.setFileName(qsFichier);

        if(!qfFichierTemporaire.open(QIODevice::ReadOnly)) {
            qDebug() << "Failed to open " << qsFichier;
            bErreurDetecteLang = true;
        } else {
            qDebug() << "Fichier" << qsFichier << "ouvert";
            if(!qfFichierFinal.open(QIODevice::ReadWrite)){
                qDebug() << "Failed to open " << m_qsFichierLang;
                bErreurDetecteLang = true;
            } else {
                qDebug() << "Fichier" << qfFichierFinal << "ouvert";
                QByteArray qbaContenuFichierTemp = qfFichierTemporaire.readAll();
                //qDebug() << "qbaContenuFichierTemp" << qbaContenuFichierTemp;
                if (qfFichierFinal.write(qbaContenuFichierTemp) == -1) {
                    bErreurDetecteLang = true;
                }
                qfFichierFinal.close();
                qfFichierTemporaire.close();
            }
        }
    }

    ui->qlLangExtraite->setVisible(true);

    if (!bErreurDetecteLang) {
        ui->qlLangExtraite->setText("Langue extraite !");
        ui->qlLangExtraite->setStyleSheet("QLabel { color: green; }");
        m_bUpdateProgres = true;
        QMessageBox::information(this, "Extraction langue terminée", "L'extraction de la langue a réussie.");
    } else {
        ui->qlLangExtraite->setText("Extraction éhcouée !");
        ui->qlLangExtraite->setStyleSheet("QLabel { color: red; }");
        m_bUpdateProgres = true;
        qmbError.setText("Impossible d'extraire la langue <i>" + ui->qcbLangue->currentData().toString().right(ui->qcbLangue->currentData().toString().count()-1) + "<i>.");
        qmbError.setInformativeText("<strong>Lancer le jeux dans la même version, fermer et relancer l'extraction.</strong>");
        //qmbError.setDetailedText(error->errorString().replace(0, 1, error->errorString()[0].toUpper()));
        qmbError.exec();
        //QMessageBox::critical(this, "Extraction échouée", "L'extraction de la langue a échouée.");
    }
    QDir qdDossierTemporaire(m_tempDir.path()+"/assets");
    qdDossierTemporaire.removeRecursively();

    if (bErreurDetecteAdvancement || bErreurDetecteLang) {
        m_bErreurExtraction = true;
    }

    if (!m_bErreurExtraction) {
        m_bProgresVanillaOK = true;
    }

    if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK) {
        ui->qpbReadJSONsVanilla->setEnabled(true);
    } else {
        ui->qpbReadJSONsVanilla->setEnabled(false);
    }

    if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK && m_bProgresBlazeandcaveOK) {
        ui->qpbReadAllJSONs->setEnabled(true);
    } else {
        ui->qpbReadAllJSONs->setEnabled(false);
    }

}

void FRM_Principale::selectionDossierBlazeandcave(bool checked) {
    QString qsDossierBlazeandCave = QFileDialog::getExistingDirectory(this, tr("Dossier Blaze And Cave"),
                                                 m_qsDossierMinecraft,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    m_qdDossierAdvancementsBlazeAndCave.setPath(qsDossierBlazeandCave + "\\data\\blazeandcave\\advancements");

    if (m_qdDossierAdvancementsBlazeAndCave.exists()) {
        QStringList qslFauxDossier = qsDossierBlazeandCave.split("/");
        QString qsFauxDossier = qslFauxDossier.first() + "\\fake_Path\\" + qslFauxDossier.last();
        ui->qleDossierBlazeandcave->setText(qsFauxDossier);

        m_bProgresBlazeandcaveOK = true;
    } else {
        m_bProgresBlazeandcaveOK = false;
    }

    if (m_bProgresBlazeandcaveOK && m_bProgresPersoOK) {
        ui->qpbReadJSONsBlazeandcave->setEnabled(true);
    } else {
        ui->qpbReadJSONsBlazeandcave->setEnabled(false);
    }

    if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK && m_bProgresBlazeandcaveOK) {
        ui->qpbReadAllJSONs->setEnabled(true);
    } else {
        ui->qpbReadAllJSONs->setEnabled(false);
    }
}

void FRM_Principale::choixFichierAdvancements(bool checked) {
    QStringList qslDossierSauvegardeTemp;
    QString qsFauxDossierSauvegarde;
    QStringList qslFormatFichier, qslFauxChemin;
    QString qsTypeFichierProgres;
    QString qsFauxChemin;
    qsTypeFichierProgres = tr("Fichier JSON (*.json)");
    qslFormatFichier << "*.json";
    bool bOuvertureJson = true;

    QString qsDossierSauvegarde = QFileDialog::getOpenFileName(this, tr("Choisir le fichier de vos progrès"),
                                                    m_qsDossierMinecraft,
                                                    qsTypeFichierProgres);

    m_qsFichierAdvancementsSolo = qsDossierSauvegarde;
    qslFauxChemin = m_qsFichierAdvancementsSolo.split("/");
    qsFauxChemin = qslFauxChemin.first() + "\\Fake_Path\\" + qslFauxChemin.last();

    if (QFile::exists(m_qsFichierAdvancementsSolo)) {
        QString qsAdvancementPerso = m_qsFichierAdvancementsSolo;
        QFile qfAdvancementPerso(qsAdvancementPerso);
        if(!qfAdvancementPerso.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<< qsAdvancementPerso;
            bOuvertureJson = false;
        }

        if (bOuvertureJson) {
            QTextStream file_text(&qfAdvancementPerso);
            QString qsJsonStringPerso;
            qsJsonStringPerso = file_text.readAll();
            qfAdvancementPerso.close();
            QByteArray qbaJsonPerso = qsJsonStringPerso.toLocal8Bit();

            QJsonDocument qjdJsonPerso = QJsonDocument::fromJson(qbaJsonPerso);

            if(qjdJsonPerso.isNull()){
                qDebug()<<"Failed to create JSON doc.";
                bOuvertureJson = false;
            } else {
                if(!qjdJsonPerso.isObject()){
                    qDebug()<<"JSON is not an object.";
                    bOuvertureJson = false;
                } else {
                    QJsonObject qjsJsonPerso = qjdJsonPerso.object();

                    if(qjsJsonPerso.isEmpty()){
                        qDebug()<<"JSON object is empty.";
                        bOuvertureJson = false;
                    } else {
                        m_qvmJsonProgresPerso = qjsJsonPerso.toVariantMap();
                    }
                }
            }
        }

        ui->qleFichierProgres->setText(qsFauxChemin);

        if (!m_bErreurExtraction && bOuvertureJson) {
            ui->qlProgresPersoOuvert->setText("Vos progrès ont pu être ouvert !");
            ui->qlProgresPersoOuvert->setStyleSheet("QLabel { color: green; }");
            m_bProgresPersoOK = true;
        } else if (!bOuvertureJson) {
            ui->qlProgresPersoOuvert->setText("Vos progrès n'ont pas pu être ouvert !");
            ui->qlProgresPersoOuvert->setStyleSheet("QLabel { color: red; }");
            m_bProgresPersoOK = false;
        }
        ui->qlProgresPersoOuvert->setVisible(true);

        if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK) {
            ui->qpbReadJSONsVanilla->setEnabled(true);
        } else {
            ui->qpbReadJSONsVanilla->setEnabled(false);
        }

        if (m_bProgresBlazeandcaveOK && m_bProgresPersoOK) {
            ui->qpbReadJSONsBlazeandcave->setEnabled(true);
        } else {
            ui->qpbReadJSONsBlazeandcave->setEnabled(false);
        }

        if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK && m_bProgresBlazeandcaveOK) {
            ui->qpbReadAllJSONs->setEnabled(true);
        } else {
            ui->qpbReadAllJSONs->setEnabled(false);
        }

//        if(m_qdDossierAdvancementsBlazeAndCave.exists() && bOuvertureJson) {
//            ui->qpbReadJSONsBlazeandcave->setEnabled(true);
//        }
    }
}

void FRM_Principale::readJSONsVanilla(bool checked) {
    ui->qcbFiltreOrigine->disconnect();
    ui->qcbFiltreTitre->disconnect();

    proxyModelFiltreConditionFaite->invalidate();
    proxyModelFiltreProgresFinis->invalidate();
    proxyModelFiltreTitre->invalidate();
    proxModelFiltreOrigine->invalidate();
    m_qsimProgresRealisation->clear();

    ui->qcbFiltreOrigine->clear();
    ui->qcbFiltreOrigine->addItem("");
    ui->qcbFiltreTitre->clear();
    ui->qcbFiltreTitre->addItem("");

    ui->qgbFiltres->setEnabled(false);

    QStringList qslFormatFichier;
    QString qsTitrePrecedent = "";
    qslFormatFichier << "*.json";

    ui->qcbFiltreOrigine->addItem("Minecraft Vanilla");
    ui->qcbFiltreTitre->addItem("----- Minecraft Vanilla -----");
    QString qsJsonLang = m_qsFichierLang;
    QFile qfLangUs(qsJsonLang);
    if(!qfLangUs.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<< qsJsonLang;
        exit(1);
    }

    QTextStream qtsLang(&qfLangUs);
    QString qsJsonLangUs;
    qsJsonLangUs = qtsLang.readAll();
    qfLangUs.close();
    QByteArray qbaJsonLang = qsJsonLangUs.toLocal8Bit();

    QJsonDocument qjdJsonLang = QJsonDocument::fromJson(qbaJsonLang);

    if(qjdJsonLang.isNull()){
        qDebug()<<"Failed to create JSON doc.";
        exit(2);
    }
    if(!qjdJsonLang.isObject()){
        qDebug()<<"JSON is not an object.";
        exit(3);
    }

    QJsonObject qjsJsonLang = qjdJsonLang.object();

    if(qjsJsonLang.isEmpty()){
        qDebug()<<"JSON object is empty.";
        exit(4);
    }

    QVariantMap qvmJsonLang = qjsJsonLang.toVariantMap();

    QDirIterator qdiFichierProgres(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

    qDebug() << "Origine;Titre;Progres Fini;Condition;Condition Faite;Date Fait";

    while (qdiFichierProgres.hasNext()) {
        QString qsJsonFile = qdiFichierProgres.next();
        QFile qfJsonFile(qsJsonFile);
        if(!qfJsonFile.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<< qsJsonFile;
            exit(1);
        }

        QTextStream file_text(&qfJsonFile);
        QString json_string;
        json_string = file_text.readAll();
        qfJsonFile.close();
        QByteArray json_bytes = json_string.toLocal8Bit();

        QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

        if(json_doc.isNull()){
            qDebug()<<"Failed to create JSON doc.";
            exit(2);
        }
        if(!json_doc.isObject()){
            qDebug()<<"JSON is not an object.";
            exit(3);
        }

        QJsonObject json_obj = json_doc.object();

        if(json_obj.isEmpty()){
            qDebug()<<"JSON object is empty.";
            exit(4);
        }

        QVariantMap json_map = json_obj.toVariantMap();
        QMap<QString, QVariant> qmDisplay = json_map["display"].toMap();
        QMap<QString, QVariant> qmTitle = qmDisplay["title"].toMap();
        QMap<QString, QVariant> qmDescription = qmDisplay["description"].toMap();
        QMap<QString, QVariant> qmCriteres = json_map["criteria"].toMap();
        QJsonArray qjaConditionsTemp = json_map["requirements"].toJsonArray();
        QString qsIdentifiant = qsJsonFile;
        QString qsTitre = qvmJsonLang[qmTitle["translate"].toString()].toString();
        QString qsTitreAvecDescription = "";
        QString qsDescription = qvmJsonLang[qmDescription["translate"].toString()].toString();
        qsIdentifiant.replace(m_qdDossierAdvancedments.path()+"/", "");
        qsIdentifiant = "minecraft:" + qsIdentifiant.split(".").first();

        if (qsTitre == "") {
            QStringList qslIdentifiant = qsIdentifiant.split("/");
            QString qsValeurDansLang = "minecraft." + qslIdentifiant.last();

            QMapIterator<QString, QVariant> qmiFichierLang(qvmJsonLang);
            while (qmiFichierLang.hasNext()) {
                qmiFichierLang.next();
                QString qsCle = qmiFichierLang.key();
                if (qsCle.contains(qsValeurDansLang)) {
                    qsTitre = qmiFichierLang.value().toString();
                }
            }
            if (qsTitre == "") {
                QStringList qslTitre = qsIdentifiant.split("/").last().split("_");
                for (int a = 0 ; a < qslTitre.count() ; a++) {
                    QString qsTitreTemp = qslTitre.at(a);
                    qsTitreTemp.replace(0, 1, qsTitreTemp.at(0).toUpper());
                    qsTitre += qsTitreTemp + " ";
                }
                qsTitre = qsTitre.trimmed();
            }
        }

        if (qsTitre != qsTitrePrecedent) {
            qsTitrePrecedent = qsTitre;
            ui->qcbFiltreTitre->addItem(qsTitrePrecedent);
        }

        bool bCriteresPersoExiste = m_qvmJsonProgresPerso[qsIdentifiant].isValid();
        bool bProgesFini;
        int iCritereFait = 0;
        QMap<QString, QVariant> qmIdentifiantPerso;
        QMap<QString, QVariant> qmCriteresPerso;
        QString qsDateRealisation;
        if (bCriteresPersoExiste) {
            qmIdentifiantPerso = m_qvmJsonProgresPerso[qsIdentifiant].toMap();
            bProgesFini = qmIdentifiantPerso.value("done").toBool();
            qmCriteresPerso = qmIdentifiantPerso["criteria"].toMap();
            iCritereFait = qmCriteresPerso.count();
        } else {
            bProgesFini = false;

        }
            QString qsProgresFini;
            int iCritereAFaire = qmCriteres.count();

            if (bProgesFini)
                qsProgresFini = "oui";
            else
                qsProgresFini = "non";

            QMapIterator<QString, QVariant> qmiCriteres(qmCriteres);
            while (qmiCriteres.hasNext()) {
                qmiCriteres.next();
                m_qlLigneProgres.clear();
                QString qsCondition = qmiCriteres.key();
                QMap<QString, QVariant> qmCritere = qmCriteres[qsCondition].toMap();
                QString qmTrigger = qmCritere["trigger"].toString();
                QMap<QString, QVariant> qmConditions = qmCritere["conditions"].toMap();
                QList<QString> qlsKeysMap = qmConditions.keys();
                QDateTime qdtDateRealisation = QDateTime();
                if (bCriteresPersoExiste) {
                    qsDateRealisation = qmCriteresPerso[qsCondition].toString();
                    qsDateRealisation = qsDateRealisation.left(qsDateRealisation.length()-6);
                    qdtDateRealisation = QDateTime::fromString(qsDateRealisation, "yyyy-MM-dd hh:mm:ss");
                }

                QStandardItem *qsiOrigine = new QStandardItem("Minecraft Vanilla");
                QStandardItem *qsiTitre = new QStandardItem("");
                if (qsDescription == "") {
                    qsiTitre->setText(qsTitre);
                    qsTitreAvecDescription = qsTitre;
                }
                else {
                    qsiTitre->setText(qsTitre + " (" + qsDescription + ")");
                    qsTitreAvecDescription = qsTitre + " (" + qsDescription + ")";
                }
                QStandardItem *qsiProgreFini = new QStandardItem(qsProgresFini);
                QStandardItem *qsiCondition = new QStandardItem(qsCondition);
                QStandardItem *qsiConditionRemplie = new QStandardItem("");
                QStandardItem *qsiDateRealisation = new QStandardItem("");

                if (bCriteresPersoExiste && (bProgesFini && iCritereFait <= iCritereAFaire)) {
                    if (qsDateRealisation != "") {
                        qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                        qsiConditionRemplie->setText("oui");
                        qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    }
                } else if (bCriteresPersoExiste) {
                    if (qsDateRealisation != "") {
                        qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                        qsiConditionRemplie->setText("oui");
                        qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    } else {
                        qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                        qsiConditionRemplie->setText("non");
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    }
                } else {
                    qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                    qsiConditionRemplie->setText("non");
                    m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                    m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                }
            }
    }

    if (!bTousLesProgres){
        QStringList qslHorizontalLabel;
        qslHorizontalLabel << "Origine" << "Titre" << "Progres Fini" << "Condition" << "Condition Faite" << "Date Fait";
        m_qsimProgresRealisation->setHorizontalHeaderLabels(qslHorizontalLabel);

        proxModelFiltreOrigine->setSourceModel(m_qsimProgresRealisation);
        proxyModelFiltreTitre->setSourceModel(proxModelFiltreOrigine);
        proxyModelFiltreProgresFinis->setSourceModel(proxyModelFiltreTitre);
        proxyModelFiltreConditionFaite->setSourceModel(proxyModelFiltreProgresFinis);

        ui->tableView->setModel(proxyModelFiltreConditionFaite);
        ui->tableView->resizeColumnsToContents();

        connect(ui->qcbFiltreOrigine, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableOrigine(QString)));
        connect(ui->qcbFiltreTitre, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTitre(QString)));

        ui->qgbFiltres->setEnabled(true);
    }
}

void FRM_Principale::readJSONsBlazeandcave(bool checked) {
    if (!bTousLesProgres) {
        ui->qcbFiltreOrigine->disconnect();
        ui->qcbFiltreTitre->disconnect();

        proxyModelFiltreConditionFaite->invalidate();
        proxyModelFiltreProgresFinis->invalidate();
        proxyModelFiltreTitre->invalidate();
        proxModelFiltreOrigine->invalidate();
        m_qsimProgresRealisation->clear();

        ui->qcbFiltreOrigine->clear();
        ui->qcbFiltreOrigine->addItem("");
        ui->qcbFiltreTitre->clear();
        ui->qcbFiltreTitre->addItem("");

        ui->qgbFiltres->setEnabled(false);
    }

    QStringList qslFormatFichier;
    QString qsTitrePrecedent = "";
    bool bOuvertureJSON = true;
    qslFormatFichier << "*.json";
    QMessageBox qmbError;
    qmbError.setTextFormat(Qt::RichText);
    qmbError.setWindowIcon(QIcon(":/img/icons8_minecraft_logo_48px.png"));
    qmbError.setStandardButtons(QMessageBox::Ok);
    qmbError.setDefaultButton(QMessageBox::Ok);
    qmbError.setIcon(QMessageBox::Critical);
    QJsonParseError *error = new QJsonParseError();

    ui->qcbFiltreOrigine->addItem("Blaze and Cave");
    ui->qcbFiltreTitre->addItem("----- Blaze and Cave -----");
    if (bTousLesProgres)
        ui->qcbFiltreTitre->insertSeparator(ui->qcbFiltreTitre->count()-1);

    QString qsJsonLang = "rcs/blazeandcave-fr_fr.json";
    QFile qfLangUs(qsJsonLang);
    if(!qfLangUs.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<< qsJsonLang;
        exit(1);
    }

    QTextStream qtsLang(&qfLangUs);
    QString qsJsonLangUs;
    qsJsonLangUs = qtsLang.readAll();
    qfLangUs.close();
    QByteArray qbaJsonLang = qsJsonLangUs.toLocal8Bit();

    QJsonDocument qjdJsonLang = QJsonDocument::fromJson(qbaJsonLang, error);

    if(qjdJsonLang.isNull()){
        qDebug()<<"Failed to create JSON doc.";
        qmbError.setText("Impossible de récupérer le contenu de <i>" + qsJsonLang + "<i>.");
        qmbError.setInformativeText("<strong>Le fichier ne sera pas traité...</strong>");
        qmbError.setDetailedText(error->errorString().replace(0, 1, error->errorString()[0].toUpper()));
        qmbError.exec();
        exit(2);
    }
    if(!qjdJsonLang.isObject()){
        qDebug()<<"JSON is not an object.";
        exit(3);
    }

    QJsonObject qjsJsonLang = qjdJsonLang.object();

    if(qjsJsonLang.isEmpty()){
        qDebug()<<"JSON object is empty.";
        exit(4);
    }

    QVariantMap qvmJsonLang = qjsJsonLang.toVariantMap();

    QDirIterator qdiFichierProgres(m_qdDossierAdvancementsBlazeAndCave.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

    qDebug() << "Origine;Titre;Progres Fini;Condition;Condition Faite;Date Fait";

    while (qdiFichierProgres.hasNext()) {

        QString qsJsonFile = qdiFichierProgres.next();
        QFile qfJsonFile(qsJsonFile);
        if(!qfJsonFile.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<< qsJsonFile;
            QMessageBox::critical(this, "Ouvrir JSON", "Impossible d'e récupérer le contenu d'ouvrir " + qsJsonFile + ".\n\n<strong>Le fichier ne sera pas traité...</strong>");
            bOuvertureJSON = false;
        }

        QTextStream file_text(&qfJsonFile);
        QString json_string;
        json_string = file_text.readAll();
        qfJsonFile.close();
        QByteArray json_bytes = json_string.toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes, error);

        if(json_doc.isNull() && bOuvertureJSON){
            QStringList qslJsonFile = qsJsonFile.split("/");
            QString qsFauxJsonFile = qslJsonFile.first() + "\\fake_Path\\" + qslJsonFile.last();

            qDebug()<<"Failed to create JSON doc." << qsJsonFile;

            qmbError.setText("Impossible de récupérer le contenu de <i>" + qsFauxJsonFile + "<i>.");
            qmbError.setInformativeText("<strong>Le fichier ne sera pas traité...</strong>");
            qmbError.setDetailedText(error->errorString().replace(0, 1, error->errorString()[0].toUpper()) + "\n\n" + json_string);
            qmbError.exec();
            bOuvertureJSON = false;
        }
        if(!json_doc.isObject() && bOuvertureJSON){
            qDebug()<<"JSON is not an object.";
            QMessageBox::critical(this, "Format JSON", "Le fichier JSON " + qsJsonFile + " n'a pas le bon format.\nLe fichier ne sera pas traité...");
            bOuvertureJSON = false;
        }

        QJsonObject json_obj = json_doc.object();

        if(json_obj.isEmpty() && bOuvertureJSON){
            qDebug()<<"JSON object is empty.";
            QMessageBox::critical(this, "JSON Vide", "Le fichier JSON " + qsJsonFile + " est vide.\nLe fichier ne sera pas traité...");
            bOuvertureJSON = false;
        }

        if (bOuvertureJSON) {
            QVariantMap json_map = json_obj.toVariantMap();
            QMap<QString, QVariant> qmDisplay = json_map["display"].toMap();
            QMap<QString, QVariant> qmTitle = qmDisplay["title"].toMap();
            QMap<QString, QVariant> qmDescription = qmDisplay["description"].toMap();
            QMap<QString, QVariant> qmCriteres = json_map["criteria"].toMap();
            QString qsIdentifiant = qsJsonFile;
//            QString qsTitre = qmTitle["translate"].toString();
//            QString qsTitreAvecDescription = "";
//            QString qsDescription = qmDescription["translate"].toString();
            QString qsTitre = qvmJsonLang[qmTitle["translate"].toString()].toString();
            QString qsTitreAvecDescription = "";
            QString qsDescription = qvmJsonLang[qmDescription["translate"].toString()].toString();
            qsIdentifiant.replace(m_qdDossierAdvancementsBlazeAndCave.path()+"/", "");
            qsIdentifiant = "blazeandcave:" + qsIdentifiant.split(".").first();

            if (qsTitre == "") {
                QStringList qslTitre = qsIdentifiant.split("/").last().split("_");
                for (int a = 0 ; a < qslTitre.count() ; a++) {
                    QString qsTitreTemp = qslTitre.at(a);
                    qsTitreTemp.replace(0, 1, qsTitreTemp.at(0).toUpper());
                    qsTitre += qsTitreTemp + " ";
                }
                qsTitre = qsTitre.trimmed();
            }

            if (qsTitre != qsTitrePrecedent) {
                qsTitrePrecedent = qsTitre;
                ui->qcbFiltreTitre->addItem(qsTitrePrecedent);
            }


            bool bCriteresPersoExiste = m_qvmJsonProgresPerso[qsIdentifiant].isValid();
            bool bProgesFini;
            int iCritereFait = 0;
            QMap<QString, QVariant> qmIdentifiantPerso;
            QMap<QString, QVariant> qmCriteresPerso;
            QString qsDateRealisation;
            if (bCriteresPersoExiste) {
                qmIdentifiantPerso = m_qvmJsonProgresPerso[qsIdentifiant].toMap();
                bProgesFini = qmIdentifiantPerso.value("done").toBool();
                qmCriteresPerso = qmIdentifiantPerso["criteria"].toMap();
                iCritereFait = qmCriteresPerso.count();
            } else {
                bProgesFini = false;

            }

            QString qsProgresFini;
            int iCritereAFaire = qmCriteres.count();

            if (bProgesFini)
                qsProgresFini = "oui";
            else
                qsProgresFini = "non";

            QMapIterator<QString, QVariant> qmiCriteres(qmCriteres);
            while (qmiCriteres.hasNext()) {
                qmiCriteres.next();
                m_qlLigneProgres.clear();
                QString qsCondition = qmiCriteres.key();
                QMap<QString, QVariant> qmCritere = qmCriteres[qsCondition].toMap();
                QString qmTrigger = qmCritere["trigger"].toString();
                QMap<QString, QVariant> qmConditions = qmCritere["conditions"].toMap();
                QList<QString> qlsKeysMap = qmConditions.keys();
                QDateTime qdtDateRealisation = QDateTime();
                if (bCriteresPersoExiste) {
                    qsDateRealisation = qmCriteresPerso[qsCondition].toString();
                    qsDateRealisation = qsDateRealisation.left(qsDateRealisation.length()-6);
                    qdtDateRealisation = QDateTime::fromString(qsDateRealisation, "yyyy-MM-dd hh:mm:ss");
                }

                QStandardItem *qsiOrigine = new QStandardItem("Blaze and Cave");
                QStandardItem *qsiTitre = new QStandardItem("");
                if (qsDescription == "") {
                    qsiTitre->setText(qsTitre);
                    qsTitreAvecDescription = qsTitre;
                }
                else {
                    qsiTitre->setText(qsTitre + " (" + qsDescription + ")");
                    qsTitreAvecDescription = qsTitre + " (" + qsDescription + ")";
                }
                QStandardItem *qsiProgreFini = new QStandardItem(qsProgresFini);
                QStandardItem *qsiCondition = new QStandardItem(qsCondition);
                QStandardItem *qsiConditionRemplie = new QStandardItem("");
                QStandardItem *qsiDateRealisation = new QStandardItem("");

                if (bCriteresPersoExiste && (bProgesFini && iCritereFait <= iCritereAFaire)) {
                    if (qsDateRealisation != "") {
                        qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                        qsiConditionRemplie->setText("oui");
                        qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    }
                } else if (bCriteresPersoExiste) {
                    if (qsDateRealisation != "") {
                        qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                        qsiConditionRemplie->setText("oui");
                        qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    } else {
                        qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                        qsiConditionRemplie->setText("non");
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    }
                } else {
                    qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                    qsiConditionRemplie->setText("non");
                    m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation;
                    m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                }
            }
        }
    }

    if (!bTousLesProgres){
        QStringList qslHorizontalLabel;
        qslHorizontalLabel << "Origine" << "Titre" << "Progres Fini" << "Condition" << "Condition Faite" << "Date Fait";
        m_qsimProgresRealisation->setHorizontalHeaderLabels(qslHorizontalLabel);

        proxModelFiltreOrigine->setSourceModel(m_qsimProgresRealisation);
        proxyModelFiltreTitre->setSourceModel(proxModelFiltreOrigine);
        proxyModelFiltreProgresFinis->setSourceModel(proxyModelFiltreTitre);
        proxyModelFiltreConditionFaite->setSourceModel(proxyModelFiltreProgresFinis);

        ui->tableView->setModel(proxyModelFiltreConditionFaite);
        ui->tableView->resizeColumnsToContents();

        connect(ui->qcbFiltreOrigine, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableOrigine(QString)));
        connect(ui->qcbFiltreTitre, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTitre(QString)));

        ui->qgbFiltres->setEnabled(true);
    }
}

void FRM_Principale::readAllJsons(bool checked) {
    bTousLesProgres = true;

    // Vanilla
    readJSONsVanilla(true);

    //Blaze And Cave
    readJSONsBlazeandcave(true);

    // Connection !
    QStringList qslHorizontalLabel;
    qslHorizontalLabel << "Origine" << "Titre" << "Progres Fini" << "Condition" << "Condition Faite" << "Date Fait";
    m_qsimProgresRealisation->setHorizontalHeaderLabels(qslHorizontalLabel);

    proxModelFiltreOrigine->setSourceModel(m_qsimProgresRealisation);
    proxyModelFiltreTitre->setSourceModel(proxModelFiltreOrigine);
    proxyModelFiltreProgresFinis->setSourceModel(proxyModelFiltreTitre);
    proxyModelFiltreConditionFaite->setSourceModel(proxyModelFiltreProgresFinis);

    ui->tableView->setModel(proxyModelFiltreConditionFaite);
    ui->tableView->resizeColumnsToContents();

    connect(ui->qcbFiltreOrigine, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableOrigine(QString)));
    connect(ui->qcbFiltreTitre, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTitre(QString)));

    ui->qgbFiltres->setEnabled(true);

    bTousLesProgres = false;
}

void FRM_Principale::filtreTableOrigine(QString filtre) {
    proxModelFiltreOrigine->setFilterKeyColumn(0);
    proxModelFiltreOrigine->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));

    if (ui->qcbFiltreTitre->currentText() != "") {
        filtreTableTitre(ui->qcbFiltreTitre->currentText());
    }
    if (ui->qcbFiltreProgresFinis->currentText() != "") {
        filtreTableProgresFinis(ui->qcbFiltreProgresFinis->currentText());
    }
    if (ui->qcbFiltreConditionFait->currentText() != "") {
        filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
    }
}

void FRM_Principale::filtreTableTitre(QString filtre) {
    if (filtre != "----- Minecraft Vanilla -----" && filtre != "----- Blaze and Cave -----") {
        proxyModelFiltreTitre->setFilterKeyColumn(1);
        if (ui->qcbRegExp->isChecked())
            proxyModelFiltreTitre->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::RegExp));
        else
            proxyModelFiltreTitre->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
    }

    if (ui->qcbFiltreProgresFinis->currentText() != "") {
        filtreTableProgresFinis(ui->qcbFiltreProgresFinis->currentText());
    }
    if (ui->qcbFiltreConditionFait->currentText() != "") {
        filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
    }
}

void FRM_Principale::filtreTableProgresFinis(QString filtre) {
    proxyModelFiltreProgresFinis->setFilterKeyColumn(2);
    proxyModelFiltreProgresFinis->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));

    if (filtre == "oui") {
        ui->qcbFiltreConditionFait->setCurrentIndex(1);
        filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
        ui->qcbFiltreConditionFait->setEnabled(false);
    } else {
        if (ui->qcbFiltreConditionFait->isEnabled()) {
            if (ui->qcbFiltreConditionFait->currentText() != "") {
                filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
            }
        } else {
            ui->qcbFiltreConditionFait->setEnabled(true);
            ui->qcbFiltreConditionFait->setCurrentIndex(0);
            filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
        }
    }
}

void FRM_Principale::filtreTableConditionFait(QString filtre) {
    proxyModelFiltreConditionFaite->setFilterKeyColumn(4);
    proxyModelFiltreConditionFaite->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
}

QString FRM_Principale::numeroIndex() {
    bool bOuvertureJson = true;
    QVariantMap qvmIndexes;
    if (QFile::exists(m_qsJSONVersion)) {
        QString qsAdvancementPerso = m_qsJSONVersion;
        QFile qfAdvancementPerso(qsAdvancementPerso);
        if(!qfAdvancementPerso.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<< qsAdvancementPerso;
            bOuvertureJson = false;
        }

        if (bOuvertureJson) {
            QTextStream file_text(&qfAdvancementPerso);
            QString qsJsonStringPerso;
            qsJsonStringPerso = file_text.readAll();
            qfAdvancementPerso.close();
            QByteArray qbaJsonPerso = qsJsonStringPerso.toLocal8Bit();

            QJsonDocument qjdJsonPerso = QJsonDocument::fromJson(qbaJsonPerso);

            if(qjdJsonPerso.isNull()){
                qDebug()<<"Failed to create JSON doc.";
                bOuvertureJson = false;
            } else {
                if(!qjdJsonPerso.isObject()){
                    qDebug()<<"JSON is not an object.";
                    bOuvertureJson = false;
                } else {
                    QJsonObject qjsJsonPerso = qjdJsonPerso.object();

                    if(qjsJsonPerso.isEmpty()){
                        qDebug()<<"JSON object is empty.";
                        bOuvertureJson = false;
                    } else {
                        qvmIndexes = qjsJsonPerso.toVariantMap();
                    }
                }
            }
        }
    }
    QMap<QString, QVariant> qvmAssetIndex = qvmIndexes["assetIndex"].toMap();
    //QMap<QString, QVariant> qvmLang = qvmObjects[m_qsCleLang].toMap();

    //qDebug() << m_qsCleLang;
    return qvmAssetIndex["id"].toString();
}

QString FRM_Principale::hashLangue() {
    bool bOuvertureJson = true;
    //qDebug() << m_qsFichierIndex;
    QVariantMap qvmIndexes;
    if (QFile::exists(m_qsFichierIndex)) {
        QString qsAdvancementPerso = m_qsFichierIndex;
        QFile qfAdvancementPerso(qsAdvancementPerso);
        if(!qfAdvancementPerso.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<< qsAdvancementPerso;
            bOuvertureJson = false;
        }

        if (bOuvertureJson) {
            QTextStream file_text(&qfAdvancementPerso);
            QString qsJsonStringPerso;
            qsJsonStringPerso = file_text.readAll();
            qfAdvancementPerso.close();
            QByteArray qbaJsonPerso = qsJsonStringPerso.toLocal8Bit();

            QJsonDocument qjdJsonPerso = QJsonDocument::fromJson(qbaJsonPerso);

            if(qjdJsonPerso.isNull()){
                qDebug()<<"Failed to create JSON doc.";
                bOuvertureJson = false;
            } else {
                if(!qjdJsonPerso.isObject()){
                    qDebug()<<"JSON is not an object.";
                    bOuvertureJson = false;
                } else {
                    QJsonObject qjsJsonPerso = qjdJsonPerso.object();

                    if(qjsJsonPerso.isEmpty()){
                        qDebug()<<"JSON object is empty.";
                        bOuvertureJson = false;
                    } else {
                        qvmIndexes = qjsJsonPerso.toVariantMap();
                    }
                }
            }
        }
    }
    QMap<QString, QVariant> qvmObjects = qvmIndexes["objects"].toMap();
    QMap<QString, QVariant> qvmLang = qvmObjects[m_qsCleLang].toMap();

    //qDebug() << m_qsCleLang;
    return qvmLang["hash"].toString();
}

void FRM_Principale::imprimerTable(bool checked) {
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView->model()->rowCount();
    const int columnCount = ui->tableView->model()->columnCount();

    out << "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("Minecraft Advancements")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n";

    // Titre
    out << QString("<h1 style=\"text-align: center; margin: auto;\">%1</h1>\n").arg("Minecraft Advancements")
        << "<br />\n";

    // Tableau
    out << "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView->isColumnHidden(column)) {
                QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void FRM_Principale::TEST(bool checked) {
    bool bOuvertureJson = true;
    QVariantMap qvmIndexes;
    if (QFile::exists(m_qsJSONVersion)) {
        QString qsAdvancementPerso = m_qsJSONVersion;
        QFile qfAdvancementPerso(qsAdvancementPerso);
        if(!qfAdvancementPerso.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<< qsAdvancementPerso;
            bOuvertureJson = false;
        }

        if (bOuvertureJson) {
            QTextStream file_text(&qfAdvancementPerso);
            QString qsJsonStringPerso;
            qsJsonStringPerso = file_text.readAll();
            qfAdvancementPerso.close();
            QByteArray qbaJsonPerso = qsJsonStringPerso.toLocal8Bit();

            QJsonDocument qjdJsonPerso = QJsonDocument::fromJson(qbaJsonPerso);

            if(qjdJsonPerso.isNull()){
                qDebug()<<"Failed to create JSON doc.";
                bOuvertureJson = false;
            } else {
                if(!qjdJsonPerso.isObject()){
                    qDebug()<<"JSON is not an object.";
                    bOuvertureJson = false;
                } else {
                    QJsonObject qjsJsonPerso = qjdJsonPerso.object();

                    if(qjsJsonPerso.isEmpty()){
                        qDebug()<<"JSON object is empty.";
                        bOuvertureJson = false;
                    } else {
                        qvmIndexes = qjsJsonPerso.toVariantMap();
                    }
                }
            }
        }
    }
    QMap<QString, QVariant> qvmAssetIndex = qvmIndexes["assetIndex"].toMap();

    qDebug () << qvmAssetIndex["id"].toString();
}
