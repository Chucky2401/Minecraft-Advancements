#include "frm_principale.h"
#include "ui_frm_principale.h"

FRM_Principale::FRM_Principale(QWidget *parent, bool test)
    : QMainWindow(parent)
    , ui(new Ui::FRM_Principale), m_test(test) {

    // Quelques réglages de bases sur la fenêtre
    ui->setupUi(this);
    ouvertureEnCours = true;

    QString qsWindowTitle = QApplication::applicationName() + " - " + QApplication::applicationVersion();
    if (QApplication::applicationVersion().right(1) == "b") {
        qsWindowTitle += " /!\\ BETA /!\\";
    }
    this->setWindowTitle(qsWindowTitle);
    this->setWindowIcon(QIcon(":/img/icons8_minecraft_logo_48px.png"));

    // Si on est on mode test on masque certaines choses
    if (test == false) {
        ui->qpbReadJSON->setVisible(test);
        ui->lineInDebug->setVisible(test);
    } else {
        ui->qpbReadJSON->setVisible(test);
        ui->lineInDebug->setVisible(test);
        connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(TEST(bool)));
        //connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(imprimerTable()));
    }

    // On crée le nécessaire pour gérer les paramètres utilisateurs
    param = new Settings();
    param->initialisation(m_test);

    // Variable global à toute la fenêtre
    m_qsAppDataPath = qEnvironmentVariable("APPDATA");
    m_qsDossierAExclure = "recipes|technical";

    // On désactive certaines choses
    ui->qgbFiltres->setEnabled(false);
    ui->qgbOperations->setEnabled(false);
    ui->qaImprimerVue->setEnabled(false);

    // Langue disponibles
    ui->qcbLangue->addItem("Français", QVariant("/fr_fr.lang"));
    ui->qcbLangue->addItem("English", QVariant("/en_us.lang"));

    // On initialise certaines variables et champ de la fenêtre
    m_bVersionOK = false;
    m_bProgresVanillaOK = false;
    m_bProgresBlazeandcaveOK = false;
    m_bProgresPersoOK = false;

    m_qs7zBin = "bin/7z.exe";
    m_qp7zProcess = new QProcess(this);
    m_bErreurExtraction = false;
    m_qsimProgresRealisation = new QStandardItemModel(0,6);

    // Modèles pour la vue
    proxModelFiltreOrigine = new QSortFilterProxyModel(this);
    proxyModelFiltreTitre = new QSortFilterProxyModel(this);
    proxyModelFiltreProgresFinis = new QSortFilterProxyModel(this);
    proxyModelFiltreConditionFaite = new QSortFilterProxyModel(this);
    proxyModelFiltreTypeCondition = new QSortFilterProxyModel(this);
    proxyModelFiltreDate = new DateEtHeureFilterProxyModel(this);

    // Variable si on prends Vanilla + BAC ou pas
    bTousLesProgres = false;

    // Préparation de tous les champs
    ui->qcbLauncher->addItem("", QVariant("EMPTY"));
    ui->qcbLauncher->addItem("Minecraft Launcher (Officiel Mojang)", QVariant("Mojang"));
    //ui->qcbLauncher->addItem("MultiMC", QVariant("MultiMC"));
    //ui->qcbLauncher->addItem("ATLauncher", QVariant("ATLauncher"));

    ui->qcbStatistiques->setCheckState(Qt::Checked);
    ui->qcbStatistiques->setToolTip("Progrès liés aux statistiques de jeu.\n"
                                  "Tel que \"Parcourir 100 Km\", \"Reproduire 2500 animaux\" ou \"Atteindre le niveau 30\", etc.");

    ui->qcbMilestones->setCheckState(Qt::Checked);
    ui->qcbMilestones->setToolTip("Progrès liés aux étapes de l'Advancement Pack de Blaze and Cave.\n"
                                  "Tel que \"Compléter tous les progrès de l'onglet Animal\" ou \"Compléter tous les progrès de l'onglet Super Challenge. Bon courage avec celui-ci ;).\", etc.");


    ui->qcbFiltreOrigine->addItem("");
    ui->qcbFiltreConditionFait->addItem("");
    ui->qcbFiltreConditionFait->addItem("oui");
    ui->qcbFiltreConditionFait->addItem("non");
    ui->qcbFiltreTitre->addItem("");
    ui->qcbFiltreProgresFinis->addItem("");
    ui->qcbFiltreProgresFinis->addItem("oui");
    ui->qcbFiltreProgresFinis->addItem("non");
    ui->qcbFiltreType->addItem("");
    ui->qcbFiltreType->addItem("ET");
    ui->qcbFiltreType->addItem("OU");
    ui->qcbFiltreType->addItem("UNE");
    ui->qcbFiltreType->setToolTip("Filtrer sur le type de condition.\n"
                                  "ET : toutes les conditions doivent être remplies.\n"
                                  "OU : une conditions doit être remplie.");

    ui->qcbFiltreTitre->setToolTip("Filtre sur le tire.\n\n"
                                   "Exemple Expression Régulière :\n"
                                   " - 'par' : recherche 'par' partout dans le texte\n"
                                   "    Trouvera 'Partons à l'aventure' et 'Deux par deux'\n\n"
                                   " - '^par' : recherche 'par' seulement au début du texte.\n"
                                   "    Trouvera 'Partons à l'aventure' mais pas 'Deux par deux'\n\n"
                                   " - 'par|monstre' : recherche 'par' OU 'monstre'\n\n"
                                   "Vous pouvez aussi combiner !\n"
                                   " - '^par|^monstre' : recherche 'par' OU 'monstre' au début du texte.\n"
                                   "    Trouvera 'Partons à l'aventure' et 'Monstres chassés'");
    ui->qcbFiltreTitre->setToolTipDuration(30000);

    ui->qdteFrom->setDateTime(QDateTime(QDate(1970, 01, 01), QTime(0, 0, 0)));
    ui->qdteTo->setDateTime(QDateTime(QDate(2099, 12, 31), QTime(23, 59, 59)));

    // On masque la barre de progression, c'était pour un test
    // A voir si on la garde
    ui->qpbTraitementProgres->setVisible(false);
    ui->qpbTraitementProgres->setValue(0);

    // Gestion de l'autocomplétion pour les titres
    m_sansCompleter = new QCompleter();
    m_defaultCompleter = new QCompleter(this);
    ui->qcbAutoCompletion->setChecked(true);

    // Pour les mises à jour
    m_qnamManager = new QNetworkAccessManager();

    // On connecte tout ce que l'on peut
    // Configuration
    connect(ui->qcbLauncher, SIGNAL(currentIndexChanged(int)), this, SLOT(choixLauncher(int)));
    //connect(ui->qcbVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(choixVersion(int)));
    connect(ui->qcbVersion, SIGNAL(currentIndexChanged(QString)), this, SLOT(choixVersion(QString)));
    connect(ui->qpbSelectionFichierProgres, SIGNAL(clicked(bool)), this, SLOT(choixFichierAdvancements(bool)));
    connect(ui->qpbDossierBlazeandcave, SIGNAL(clicked(bool)), this, SLOT(selectionDossierBlazeandcave(bool)));
    connect(ui->qcbStatistiques, SIGNAL(stateChanged(int)), this, SLOT(exclureStats(int)));
    connect(ui->qcbMilestones, SIGNAL(stateChanged(int)), this, SLOT(exclureStats(int)));
    // Lecture fichiers
    connect(ui->qpbExtraireProgres, SIGNAL(clicked(bool)), this, SLOT(extraireProgres(bool)));
    connect(ui->qpbReadJSONsVanilla, SIGNAL(clicked(bool)), this, SLOT(readJSONsVanilla(bool)));
    connect(ui->qpbReadJSONsBlazeandcave, SIGNAL(clicked(bool)), this, SLOT(readJSONsBlazeandcave(bool)));
    connect(ui->qpbReadAllJSONs, SIGNAL(clicked(bool)), this, SLOT(readAllJsons(bool)));
    // Filtres
    connect(ui->qcbFiltreProgresFinis, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableProgresFinis(QString)));
    connect(ui->qcbFiltreConditionFait, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableConditionFait(QString)));
    connect(ui->qcbFiltreType, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTypeCondition(QString)));
    connect(ui->qdteFrom, &QDateTimeEdit::dateChanged, this, &FRM_Principale::dateFilterChanged);
    connect(ui->qdteTo, &QDateTimeEdit::dateChanged, this, &FRM_Principale::dateFilterChanged);
    connect(ui->qcbAutoCompletion, SIGNAL(stateChanged(int)), this, SLOT(etatAutoCompletion(int)));
    // Action sur la vue
    connect(ui->tableView, SIGNAL(pressed(const QModelIndex)), this, SLOT(dataSelectionnee(const QModelIndex)));
    // Outils
    connect(ui->pbImprimer, SIGNAL(clicked(bool)), this, SLOT(imprimerTable(bool)));
    connect(ui->qpbClearFilter, SIGNAL(clicked(bool)), this, SLOT(effacerLesFiltres(bool)));
    // Menu
    connect(ui->qaAbout, SIGNAL(triggered()), this, SLOT(ouvrirAPropos()));
    connect(ui->qaImprimerVue, SIGNAL(triggered(bool)), this, SLOT(imprimerTable(bool)));
    connect(ui->qaSettings, SIGNAL(triggered()), this, SLOT(ouvrirParametres()));
    connect(ui->qaQuitter, SIGNAL(triggered()), this, SLOT(close()));
    // Mise à jour
    connect(ui->qaUpdate, SIGNAL(triggered()), this, SLOT(verifierMiseAJour()));
    connect(m_qnamManager, SIGNAL (finished(QNetworkReply*)), this, SLOT(fichierTelecharge(QNetworkReply*)));
    connect(this, SIGNAL(downloaded(bool)), this, SLOT(comparaisonVersion(bool)));
    // Fermeture
    connect(this, SIGNAL(fermeture()), this, SLOT(close()));

    // Avant de finaliser les champs de la fenêtre, on vérifie les mises à jours
    // On le mets ici, car on besoin de connexion
    if(param->getVerificationAutoMiseAJour() && QDate::currentDate() == param->getProchaineVerificationMiseAjour()) {
        qInfo() << "On vérifie les mises à jour.";
        qDebug() << "Aujourd'hui : " << QDate::currentDate().toString("dd/MM/yyyy");
        qInfo() << "Dernière Verif : " << param->getDerniereVerificationMiseAJour();
        qInfo() << "Prochaine vérification : " << param->getProchaineVerificationMiseAjour();
        param->setDerniereVerificationMiseAJour(QDate::currentDate());
        verifierMiseAJour();
    } else {
        qInfo() << "On ne vérifie pas les mise à jour";
        qDebug() << "Aujourd'hui : " << QDate::currentDate().toString("dd/MM/yyyy");
        qInfo() << "Derniere Verif : " << param->getDerniereVerificationMiseAJour();
        qInfo() << "Prochaine Verif : " << param->getProchaineVerificationMiseAjour();
    }

    // Suite à la connexion on force le launcher et on désactive certains champs pour ne pas avoir de bug
    ui->qcbLauncher->setCurrentIndex(1);
    ui->qpbSelectionDossierLanceur->setVisible(false);
    ui->qpbExtraireProgres->setEnabled(false);
    ui->qlAdvancementsExtrait->setVisible(false);
    ui->qlLangExtraite->setVisible(false);
    ui->qlProgresPersoOuvert->setVisible(false);
    ui->qpbReadJSONsVanilla->setEnabled(false);
    ui->qpbReadJSONsBlazeandcave->setEnabled(false);

    // On redimensionne la fenêtre dans son dernier état si l'utilisateur la souhaité
    if (param->getRestoreSizePos()) {
        if(param->getEtat() != "DNE" && param->getGeometrie() != "DNE") {
            this->restoreGeometry(param->getGeometrie());
            this->restoreState(param->getEtat());
        }
    }

    // Ici on va traiter si l'utilisateur souhaite une restauration de ses dernières saisis
    if (param->getRestoreData()) {
        if (param->getVersion() != "DNE") {
            int index = ui->qcbVersion->findText(param->getVersion());
            if (index != -1) {
                ui->qcbVersion->setCurrentIndex(index);
            }
        }
    }

    ouvertureEnCours = false;
}

/*
 * Destructeur de la classe
 */
FRM_Principale::~FRM_Principale() {
    delete ui;
}

/*
 * Fonction pour détecter quand la fenêtre est fermé
 */
void FRM_Principale::closeEvent(QCloseEvent *event){
    // Si on est en test ou le paramètre pour confirmation fermeture est désactivé
    // On ferme sans message bloquant
    if (m_test || !param->getMessageConfirmationFermeture()) {

        if (param->getRestoreSizePos())
            param->setGeometrieEtat(saveGeometry(), saveState());

        event->accept();
        return;
    }

    // "Sinon", on demande confirmation de fermeture
    if (QMessageBox::question(this, "Fermeture", "Voulez-vous fermer le programme ?") == QMessageBox::Yes){
        if (param->getRestoreSizePos())
            param->setGeometrieEtat(saveGeometry(), saveState());

        event->accept();
    } else {
        event->ignore();
    }
}

/*
 * Slots sur le choix du launcher
 */
void FRM_Principale::choixLauncher(int index) {
    QString qsLanceur = ui->qcbLauncher->itemData(index).toString();
    QString qsFauxCheminLanceur, qsValeurTemp, qsNomVersionTemp, qsNomVersion;
    QStringList qslFormatFichier, qslDossierLanceurTemp, qslNomVersionTemp;

    //m_qslListVersionJar.clear();
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
            //m_qslListVersionJar << qsValeurTemp;
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
               //qDebug() << "Nom Version" << qsNomVersion << "- qsValeurTemp" << qsValeurTemp;
            }

        }
    }
}

//void FRM_Principale::choixVersion(int index) {
//    QString qsCheminVersion = ui->qcbVersion->itemData(index).toString();
//    QString qsFauxChemin, qsNumeroIndex = "";
//    QStringList qslFormatFichier;
//    qslFormatFichier << "*.json";
//    int iFicherDejaExtrait = 0;

//    if (ui->qcbVersion->currentIndex() != 0) {
//        m_qsJSONVersion = ui->qcbVersion->currentData().toString().replace(".jar", ".json");
//        // Aller chercher id avec la variable m_qsJSONVersion
//        qsNumeroIndex = numeroIndex();
//        // Renseigner fichier index (m_qsFichierIndex
//        m_qsFichierIndex = m_qsDossierIndexes + "\\" + qsNumeroIndex + ".json";
//    }
//    qDebug() << m_qsFichierIndex;

//    m_qsNumeroVersion = ui->qcbVersion->currentText();
//    m_qsl7zipArguments.clear();
//    m_qsl7zipArgumentsLang.clear();
//    //ui->qlAdvancementsExtrait->setVisible(false);
//    //ui->qlLangExtraite->setVisible(false);

//    if (qsCheminVersion != "EMPTY") {
//        ui->qleCheminVersion->setText("C:\\fake_Path\\" + qsCheminVersion.split("/").last());
//    } else
//        ui->qleCheminVersion->setText("");

//    m_qdDossierAdvancedments.setPath("advancements/" + ui->qcbVersion->currentText() + "/");
//    m_qsFichierLang = m_qdDossierAdvancedments.absolutePath() + ui->qcbLangue->currentData().toString();
//    m_qsCleLang = "minecraft/lang" + ui->qcbLangue->currentData().toString().replace(".lang", ".json");

//    if (ui->qcbVersion->currentData() != "EMPTY")
//        m_bVersionOK = true;
//    else
//        m_bVersionOK = false;

//    if (m_qdDossierAdvancedments.exists() && QFile(m_qsFichierLang).exists() && m_bVersionOK) {
//        ui->qpbExtraireProgres->setText("Update Progrès");
//        ui->qpbExtraireProgres->setEnabled(true);
//        m_bUpdateProgres = true;
//        m_bProgresVanillaOK = true;

//        QDirIterator qdiFichierProgresExtrait(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);
//        while (qdiFichierProgresExtrait.hasNext()) {
//            qdiFichierProgresExtrait.next();
//            iFicherDejaExtrait++;
//        }

//        if (iFicherDejaExtrait > 1) {
//            ui->qlAdvancementsExtrait->setText("Progrès extrait !");
//            ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: green; }");
//            ui->qlAdvancementsExtrait->setVisible(true);
//        } else {
//            ui->qlAdvancementsExtrait->setText("Progrès non extrait proprement !");
//            ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: red; }");
//            ui->qlAdvancementsExtrait->setVisible(true);
//        }

//        ui->qlLangExtraite->setText("Langue extraite !");
//        ui->qlLangExtraite->setStyleSheet("QLabel { color: green; }");
//        ui->qlLangExtraite->setVisible(true);

//    } else if (m_qdDossierAdvancedments.exists() && !QFile(m_qsFichierLang).exists() && m_bVersionOK) {
//        m_qdDossierAdvancedments.removeRecursively();
//        if (m_qdDossierAdvancedments.mkpath(".")) {
//            ui->qpbExtraireProgres->setEnabled(true);
//            ui->qpbExtraireProgres->setText("Extraire Progrès");
//            m_bUpdateProgres = false;
//            m_bProgresVanillaOK = false;

//            QDirIterator qdiFichierProgresExtrait(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);
//            while (qdiFichierProgresExtrait.hasNext()) {
//                qdiFichierProgresExtrait.next();
//                iFicherDejaExtrait++;
//            }

//            if (iFicherDejaExtrait > 1) {
//                ui->qlAdvancementsExtrait->setText("Progrès extrait !");
//                ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: green; }");
//                ui->qlAdvancementsExtrait->setVisible(true);
//            } else {
//                ui->qlAdvancementsExtrait->setText("Progrès non extrait proprement !");
//                ui->qlAdvancementsExtrait->setStyleSheet("QLabel { color: red; }");
//                ui->qlAdvancementsExtrait->setVisible(true);
//            }

//            ui->qlLangExtraite->setText("Langue non extraite !");
//            ui->qlLangExtraite->setStyleSheet("QLabel { color: red; }");
//            ui->qlLangExtraite->setVisible(true);
//        }
//    } else if (ui->qcbVersion->currentData() == "EMPTY") {
//        ui->qpbExtraireProgres->setEnabled(false);
//        m_bProgresVanillaOK = false;
//    } else {
//        if (m_qdDossierAdvancedments.mkpath(".")) {
//            ui->qpbExtraireProgres->setEnabled(true);
//            ui->qpbExtraireProgres->setText("Extraire Progrès");
//            m_bUpdateProgres = false;
//            m_bProgresVanillaOK = false;
//        }
//    }

//    if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK) {
//        ui->qpbReadJSONsVanilla->setEnabled(true);
//    } else {
//        ui->qpbReadJSONsVanilla->setEnabled(false);
//    }

//    if (m_bVersionOK && m_bProgresPersoOK && m_bProgresBlazeandcaveOK) {
//        ui->qpbReadAllJSONs->setEnabled(true);
//    } else {
//        ui->qpbReadAllJSONs->setEnabled(false);
//    }

//    if (ui->qcbVersion->currentData() != "EMPTY") {
//        m_qsl7zipArguments << "x" << qsCheminVersion << "-o"+m_tempDir.path() << "-ir!data\\minecraft\\advancements\\*.json";
//        m_qsl7zipArgumentsLang << "x" << qsCheminVersion << "-o"+m_tempDir.path() << "-ir!assets\\minecraft\\lang\\*.json";
//    }
//}

void FRM_Principale::choixVersion(QString text) {
    QString qsCheminVersion = ui->qcbVersion->currentData().toString();
    QString qsFauxChemin, qsNumeroIndex = "";
    QStringList qslFormatFichier;
    qslFormatFichier << "*.json";
    int iFicherDejaExtrait = 0;

    if (ui->qcbVersion->currentIndex() != 0) {
        m_qsJSONVersion = ui->qcbVersion->currentData().toString().replace(".jar", ".json");
        qsNumeroIndex = numeroIndex();
        m_qsFichierIndex = m_qsDossierIndexes + "\\" + qsNumeroIndex + ".json";
    }
    qDebug() << m_qsFichierIndex;

    m_qsNumeroVersion = ui->qcbVersion->currentText();
    m_qsl7zipArguments.clear();
    m_qsl7zipArgumentsLang.clear();

    qDebug() << "qsCheminVersion" << qsCheminVersion;

    if (qsCheminVersion != "EMPTY") {
        ui->qleCheminVersion->setText("C:\\fake_Path\\" + text + ".jar");
    } else
        ui->qleCheminVersion->clear();//ui->qleCheminVersion->setText("");

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

    if (param->getRestoreData() && ui->qcbVersion->currentData() != "EMPTY") {
        param->setVersion(text);
    }
}

void FRM_Principale::extraireProgres(bool checked) {
    if (checked) {
        qDebug() << checked;
    }
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
    if (checked) {
        qDebug() << checked;
    }
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

void FRM_Principale::exclureStats(int statut) {
    if (statut) {
        qDebug() << statut;
    }

    if (ui->qcbStatistiques->checkState() == Qt::Checked && ui->qcbMilestones->checkState() == Qt::Checked) {
        // Tout est activé
        m_qsDossierAExclure = "recipes|technical";
    } else if (ui->qcbStatistiques->checkState() == Qt::Checked && ui->qcbMilestones->checkState() == Qt::Unchecked) {
        // Seulement les statistiques
        // Pas les milestones
        m_qsDossierAExclure = "recipes|technical|bacap";
    } else if (ui->qcbStatistiques->checkState() == Qt::Unchecked && ui->qcbMilestones->checkState() == Qt::Checked) {
        // Seulement les milestones
        // Pas les statistiques
        m_qsDossierAExclure = "recipes|technical|statistics";
    } else {
        // Aucun des deux...
        m_qsDossierAExclure = "recipes|technical|statistics|bacap";
    }
}

void FRM_Principale::choixFichierAdvancements(bool checked) {
    if (checked) {
        qDebug() << checked;
    }
    QString qsTypeFichierProgres;
    qsTypeFichierProgres = tr("Fichier JSON (*.json)");

    QString qsDossierSauvegarde = QFileDialog::getOpenFileName(this, tr("Choisir le fichier de vos progrès"),
                                                    m_qsDossierMinecraft,
                                                    qsTypeFichierProgres);

    traitementFichierAdvancements(qsDossierSauvegarde);

}

void FRM_Principale::readJSONsVanilla(bool checked) {
    if (checked) {
        qDebug() << checked;
    }
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
    ui->qgbOperations->setEnabled(false);
    ui->qaImprimerVue->setEnabled(false);

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
    /*
     * Tout stocké dans un QStringList
     */

    QDirIterator qdiFichierProgres(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

    qDebug() << "Origine;Titre;Progres Fini;Condition;Condition Faite;Date Fait";

    while (qdiFichierProgres.hasNext()) {
        QString qsJsonFile = qdiFichierProgres.next();
        QStringList qslCheminFichier = qsJsonFile.split("/");
        if (qslCheminFichier.at(2) != "recipes") {

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
            QJsonArray qjaConditions = qjaConditionsTemp.at(0).toArray();
            // Si > 1 => OU (||)
            // Sinon  => ET (&&)
            int iNombreRequierements = qjaConditions.count();
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
                    QString qsConditionSimple = qsCondition;
                    qsConditionSimple.replace(QRegExp("^.+:"), "");
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
                    } else {
                        qsiTitre->setText(qsTitre + " (" + qsDescription + ")");
                        qsTitreAvecDescription = qsTitre + " (" + qsDescription + ")";
                    }
                    qsiTitre->setData(qsJsonFile, Qt::UserRole);

                    QStandardItem *qsiProgreFini = new QStandardItem(qsProgresFini);
                    if (qsProgresFini == "oui") {
                        qsiTitre->setForeground(QBrush(Qt::darkGreen));
                    }
                    QStandardItem *qsiCondition = new QStandardItem("");
                    /*
                     * Rechercher la traduction
                     * Si trouvé : on la met
                     * Sinon     : on mets qsConditionSimple
                     */
                    if (qsConditionSimple.contains("/")) {
                        QStringList qslConditionSansChemin = qsConditionSimple.split("/");
                        qsiCondition->setText(qslConditionSansChemin.last().split(".").first());
                        qsiCondition->setIcon(QIcon(qsConditionSimple));
                        qsiCondition->setToolTip("<img src=\"" + qsConditionSimple + "\" width=\"167\" height=\"100\">");
                    } else {
                        qsiCondition->setText(qsConditionSimple);
                    }

                    // Si le progres n'est pas fait, on mets une couleur sur la condition
                    // on fonction si une suffit ou toutes
                    if (qsProgresFini == "non" && iNombreRequierements > 1) {
                        qsiCondition->setForeground(QBrush(Qt::blue));
                    } else if (qsProgresFini == "non" && iNombreRequierements == 1 && qjaConditionsTemp.count() > 1) {
                        qsiCondition->setForeground(QBrush(Qt::darkRed));
                    } else if (qsProgresFini == "non") {
                        qsiCondition->setForeground(QBrush(Qt::darkYellow));
                    }

                    QStandardItem *qsiConditionRemplie = new QStandardItem("");
                    QStandardItem *qsiDateRealisation = new QStandardItem("");

                    // On ajoute la colonne type (ET / OU) que l'on masquera pour filtrer
                    QStandardItem *qsiTypeCondition = new QStandardItem("");
                    if (iNombreRequierements > 1) {
                        qsiTypeCondition->setText("OU");
                    } else if (iNombreRequierements == 1 && qjaConditionsTemp.count() > 1) {
                        qsiTypeCondition->setText("ET");
                    } else {
                        qsiTypeCondition->setText("UNE");
                    }

                    if (bCriteresPersoExiste && (bProgesFini && iCritereFait <= iCritereAFaire)) {
                        if (qsDateRealisation != "") {
                            qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                            qsiConditionRemplie->setText("oui");
                            //qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                            qsiDateRealisation->setData(qdtDateRealisation, Qt::DisplayRole);
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        }
                    } else if (bCriteresPersoExiste) {
                        if (qsDateRealisation != "") {
                            qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                            qsiConditionRemplie->setText("oui");
                            //qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                            qsiDateRealisation->setData(qdtDateRealisation, Qt::DisplayRole);
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        } else {
                            qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                            qsiConditionRemplie->setText("non");
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        }
                    } else {
                        qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                        qsiConditionRemplie->setText("non");
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    }
                }
        }
    }

    if (!bTousLesProgres){
        QStringList qslHorizontalLabel;
        qslHorizontalLabel << "Origine" << "Titre" << "Progres Fini" << "Condition" << "Condition Faite" << "Date Fait" << "Type Condition";
        m_qsimProgresRealisation->setHorizontalHeaderLabels(qslHorizontalLabel);

        proxModelFiltreOrigine->setSourceModel(m_qsimProgresRealisation);
        proxyModelFiltreTitre->setSourceModel(proxModelFiltreOrigine);
        proxyModelFiltreProgresFinis->setSourceModel(proxyModelFiltreTitre);
        proxyModelFiltreConditionFaite->setSourceModel(proxyModelFiltreProgresFinis);
        proxyModelFiltreTypeCondition->setSourceModel(proxyModelFiltreConditionFaite);
        proxyModelFiltreDate->setSourceModel(proxyModelFiltreTypeCondition);

        ui->tableView->setModel(proxyModelFiltreDate);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->hideColumn(6);

        connect(ui->qcbFiltreOrigine, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableOrigine(QString)));
        connect(ui->qcbFiltreTitre, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTitre(QString)));

        ui->qgbFiltres->setEnabled(true);
        ui->qgbOperations->setEnabled(true);
        ui->qaImprimerVue->setEnabled(true);

        m_defaultCompleter->setModel(ui->qcbFiltreTitre->model());
        m_defaultCompleter->setCompletionMode(QCompleter::PopupCompletion);
        m_defaultCompleter->setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
        ui->qcbFiltreTitre->setCompleter(m_defaultCompleter);
    }
}

void FRM_Principale::readJSONsBlazeandcave(bool checked) {
    if (checked) {
        qDebug() << checked;
    }
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
        ui->qgbOperations->setEnabled(false);
        ui->qaImprimerVue->setEnabled(false);
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
        qDebug() << qsJsonFile;
        QStringList qslCheminFichier = qsJsonFile.split("/");
        if (qslCheminFichier.indexOf(QRegExp(m_qsDossierAExclure)) == -1) {
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
                QJsonArray qjaConditionsTemp = json_map["requirements"].toJsonArray();
                int iNombreRequierements;
                if (!qjaConditionsTemp.isEmpty()) {
                    QJsonArray qjaConditions = qjaConditionsTemp.at(0).toArray();
                    qjaConditionsTemp.at(1).isArray();
                    // Si > 1 => OU (||)
                    // Sinon  => ET (&&)
                    if (qjaConditionsTemp.at(1).isArray()) {
                        iNombreRequierements = 1;
                    } else {
                        iNombreRequierements = qjaConditions.count();
                    }
                } else {
                    iNombreRequierements = 1;
                }
                QString qsIdentifiant = qsJsonFile;
                QString qsTitre = qvmJsonLang[qmTitle["translate"].toString()].toString();
                // Parfois il n'y a pas de traduction...
                if (qsTitre == "") {
                    qsTitre = qmTitle["translate"].toString();
                }
                QString qsTitreAvecDescription = "";
                QString qsDescription = qvmJsonLang[qmDescription["translate"].toString()].toString();
                // Parfois il n'y a pas de traduction...
                if (qsDescription == "") {
                    qsDescription = qmDescription["translate"].toString();
                }
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
                qDebug() << "Nbr Criteres : " << iCritereAFaire;

                if (bProgesFini)
                    qsProgresFini = "oui";
                else
                    qsProgresFini = "non";

                QMapIterator<QString, QVariant> qmiCriteres(qmCriteres);
                while (qmiCriteres.hasNext()) {
                    qmiCriteres.next();
                    m_qlLigneProgres.clear();
                    QString qsCondition = qmiCriteres.key();
                    QString qsConditionSimple = qsCondition;
                    qsConditionSimple.replace(QRegExp("^.+:"), "");
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
                    } else {
                        qsiTitre->setText(qsTitre + " (" + qsDescription + ")");
                        qsTitreAvecDescription = qsTitre + " (" + qsDescription + ")";
                    }
                    qsiTitre->setData(qsJsonFile, Qt::UserRole);

                    if (qsProgresFini == "oui") {
                        qsiTitre->setForeground(QBrush(Qt::darkGreen));
                    }

                    QStandardItem *qsiProgreFini = new QStandardItem(qsProgresFini);
                    QStandardItem *qsiCondition = new QStandardItem(qsConditionSimple);
                    // Si le progres n'est pas fait, on mets une couleur sur la condition
                    // on fonction si une suffit ou toutes
                    if (iCritereAFaire == 1) {
                        qsiCondition->setForeground(QBrush(Qt::darkYellow));
                    } else {
                        if (qsProgresFini == "non" && iNombreRequierements > 1) {
                           qsiCondition->setForeground(QBrush(Qt::blue));
                        } else if (qsProgresFini == "non" && iNombreRequierements == 1) {
                           qsiCondition->setForeground(QBrush(Qt::darkRed));
                        } else {
                            qsiCondition->setForeground(QBrush(Qt::darkYellow));
                        }
                    }

                    QStandardItem *qsiConditionRemplie = new QStandardItem("");
                    QStandardItem *qsiDateRealisation = new QStandardItem("");
                    // On ajoute la colonne type (ET / OU) que l'on masquera pour filtrer
                    QStandardItem *qsiTypeCondition = new QStandardItem("");
                    if (iCritereAFaire == 1) {
                        qsiTypeCondition->setText("UNE");
                    } else {
                        if (iNombreRequierements > 1) {
                            qsiTypeCondition->setText("OU");
                        } else if (iNombreRequierements == 1) {
                            qsiTypeCondition->setText("ET");
                        } else {
                            qsiTypeCondition->setText("UNE");
                        }
                    }

                    QDateTime test(QDateTime::currentDateTime());

                    if (bCriteresPersoExiste && (bProgesFini && iCritereFait <= iCritereAFaire)) {
                        if (qsDateRealisation != "") {
                            qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                            qsiConditionRemplie->setText("oui");
                            //qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                            qsiDateRealisation->setData(qdtDateRealisation, Qt::DisplayRole);
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        }
                    } else if (bCriteresPersoExiste) {
                        if (qsDateRealisation != "") {
                            qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                            qsiConditionRemplie->setText("oui");
                            //qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                            qsiDateRealisation->setData(qdtDateRealisation, Qt::DisplayRole);
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        } else {
                            qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                            qsiConditionRemplie->setText("non");
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        }
                    } else {
                        qDebug() << "Blaze and Cave;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                        qsiConditionRemplie->setText("non");
                        m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                        m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                    }
                }
            }

        }
    }

    if (!bTousLesProgres){
        QStringList qslHorizontalLabel;
        qslHorizontalLabel << "Origine" << "Titre" << "Progres Fini" << "Condition" << "Condition Faite" << "Date Fait" << "Type Condition";
        m_qsimProgresRealisation->setHorizontalHeaderLabels(qslHorizontalLabel);

        proxModelFiltreOrigine->setSourceModel(m_qsimProgresRealisation);
        proxyModelFiltreTitre->setSourceModel(proxModelFiltreOrigine);
        proxyModelFiltreProgresFinis->setSourceModel(proxyModelFiltreTitre);
        proxyModelFiltreConditionFaite->setSourceModel(proxyModelFiltreProgresFinis);
        proxyModelFiltreTypeCondition->setSourceModel(proxyModelFiltreConditionFaite);
        proxyModelFiltreDate->setSourceModel(proxyModelFiltreTypeCondition);

        ui->tableView->setModel(proxyModelFiltreDate);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->hideColumn(6);

        connect(ui->qcbFiltreOrigine, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableOrigine(QString)));
        connect(ui->qcbFiltreTitre, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTitre(QString)));

        ui->qgbFiltres->setEnabled(true);
        ui->qgbOperations->setEnabled(true);
        ui->qaImprimerVue->setEnabled(true);

        m_defaultCompleter->setModel(ui->qcbFiltreTitre->model());
        m_defaultCompleter->setCompletionMode(QCompleter::PopupCompletion);
        m_defaultCompleter->setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
        ui->qcbFiltreTitre->setCompleter(m_defaultCompleter);
    }
}

void FRM_Principale::readAllJsons(bool checked) {
    if (checked) {
        qDebug() << checked;
    }
    bTousLesProgres = true;

    // Vanilla
    readJSONsVanilla(true);

    //Blaze And Cave
    readJSONsBlazeandcave(true);

    // Connection !
    QStringList qslHorizontalLabel;
    qslHorizontalLabel << "Origine" << "Titre" << "Progres Fini" << "Condition" << "Condition Faite" << "Date Fait" << "Type Condition";
    m_qsimProgresRealisation->setHorizontalHeaderLabels(qslHorizontalLabel);

    proxModelFiltreOrigine->setSourceModel(m_qsimProgresRealisation);
    proxyModelFiltreTitre->setSourceModel(proxModelFiltreOrigine);
    proxyModelFiltreProgresFinis->setSourceModel(proxyModelFiltreTitre);
    proxyModelFiltreConditionFaite->setSourceModel(proxyModelFiltreProgresFinis);
    proxyModelFiltreTypeCondition->setSourceModel(proxyModelFiltreConditionFaite);
    proxyModelFiltreDate->setSourceModel(proxyModelFiltreTypeCondition);

    ui->tableView->setModel(proxyModelFiltreDate);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->hideColumn(6);

    connect(ui->qcbFiltreOrigine, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableOrigine(QString)));
    connect(ui->qcbFiltreTitre, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTitre(QString)));

    ui->qgbFiltres->setEnabled(true);
    ui->qgbOperations->setEnabled(true);
    ui->qaImprimerVue->setEnabled(true);

    m_defaultCompleter->setModel(ui->qcbFiltreTitre->model());
    m_defaultCompleter->setCompletionMode(QCompleter::PopupCompletion);
    m_defaultCompleter->setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    ui->qcbFiltreTitre->setCompleter(m_defaultCompleter);

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
    if (ui->qcbFiltreType->currentText() != "") {
        filtreTableTypeCondition(ui->qcbFiltreType->currentText());
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
    if (ui->qcbFiltreType->currentText() != "") {
        filtreTableTypeCondition(ui->qcbFiltreType->currentText());
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
    if (ui->qcbFiltreType->currentText() != "") {
        filtreTableTypeCondition(ui->qcbFiltreType->currentText());
    }
}

void FRM_Principale::filtreTableConditionFait(QString filtre) {
    proxyModelFiltreConditionFaite->setFilterKeyColumn(4);
    proxyModelFiltreConditionFaite->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
    if (ui->qcbFiltreType->currentText() != "") {
        filtreTableTypeCondition(ui->qcbFiltreType->currentText());
    }
}

void FRM_Principale::filtreTableTypeCondition(QString filtre) {
    proxyModelFiltreTypeCondition->setFilterKeyColumn(6);
    proxyModelFiltreTypeCondition->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
}

void FRM_Principale::dateFilterChanged()
{
    proxyModelFiltreDate->setFilterMinimumDate(ui->qdteFrom->dateTime());
    proxyModelFiltreDate->setFilterMaximumDate(ui->qdteTo->dateTime());
}

void FRM_Principale::effacerLesFiltres(bool checked) {
    if (checked) {
        qDebug() << checked;
    }

    ui->qcbFiltreOrigine->setCurrentIndex(0);
    ui->qcbFiltreTitre->setCurrentText(0);
    ui->qcbFiltreProgresFinis->setCurrentIndex(0);
    ui->qcbFiltreConditionFait->setCurrentIndex(0);
    ui->qcbFiltreType->setCurrentIndex(0);
}

void FRM_Principale::etatAutoCompletion(int etat) {
    if (etat == 0) {
        // Unchecked
        qDebug() << "Unchecked !";
        ui->qcbFiltreTitre->setCompleter(m_sansCompleter);
        qDebug() << "Désactivation AutoComplétion";
    } else {
        QStringList qslListCompleter;
        // Checked
        qDebug() << "Checked !";
        //m_defaultCompleter = new QCompleter(ui->qcbFiltreTitre->model(), this);
        m_defaultCompleter->setModel(ui->qcbFiltreTitre->model());
        m_defaultCompleter->setCompletionMode(QCompleter::PopupCompletion);
        m_defaultCompleter->setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
        ui->qcbFiltreTitre->setCompleter(m_defaultCompleter);
        qDebug() << "Activation AutoComplétion";
    }
}

void FRM_Principale::dataSelectionnee(const QModelIndex index) {
    qDebug() << index;
    qDebug() << proxyModelFiltreTypeCondition->data(index, Qt::UserRole);
}

void FRM_Principale::imprimerTable(bool checked) {
    if (checked) {
        qDebug() << checked;
    }
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

/*
 * Ouvrir la fenêtre a propos
 */
void FRM_Principale::ouvrirAPropos(){
    diaAPropos = new DIA_apropos(this);
    diaAPropos->setStyleSheet("QDialog { border: 1px solid gray }");
    diaAPropos->exec();
    delete diaAPropos;
}

/*
 * Ouvrir la fenêtre des paramètres
 */
void FRM_Principale::ouvrirParametres(){
    diaParametres = new DIA_Parametres(param, this, m_test);
    diaParametres->exec();
    delete diaParametres;
}

/*
 * Slot de vérification des mises à jour.
 * Télécharge le fichier Updates.xml du repository pour lecture.
 */
void FRM_Principale::verifierMiseAJour(){
    QUrl url;
    if (param->getMiseAJourBeta()) {
        url.setUrl("https://blackwizard.yj.fr/repository/b-advancements/Updates.xml");
    } else {
        url.setUrl("https://blackwizard.yj.fr/repository/advancements/Updates.xml");
    }
    QNetworkRequest request;

    qDebug() << "On récupère les données du fichier depuis le repository Online";
    request.setUrl(url);
    m_qnamManager->get(request);

}

/*
 * Quand le QNetworkManager (m_qnamManager) émet le signal que le téléchargement est finis,
 * ce slot est appelé.
 * Dans ce slot, on lit les données récupéré dans un QByteArray, on marque le QNetworkReply (pReply) à supprimer
 * et on émet le signal downloaded() pour indiquer que l'on a tout télécharger correctement.
 */
void FRM_Principale::fichierTelecharge(QNetworkReply* pReply){
    qDebug() << "On lit les données téléchargées";
    m_qbaDonneesTelechargees = pReply->readAll();
    pReply->deleteLater();
    emit downloaded(true);
}

/*
 * Ce slot est appelé lors de l'émission du signal downloaded().
 * Ici, on écrit le fichier Updates.xml en local (inutile) et on lis les données XML récupérées
 * pour récupérer la version du repository.
 * On compare numéro après numéro pour voir s'il y a une mise à jour.
 */
void FRM_Principale::comparaisonVersion(bool ecrireFichier){
    QString qsCheminUpdate = param->getPath();
    QString qsFichierUpdate = qsCheminUpdate + "Updates-Minecraft_Advancements.xml";
    QFile qfUpdateXml(qsFichierUpdate);
    QDomDocument qddXmlBOM;
    QString qsVersionOnline;
    QString qsVersionLocal = QApplication::applicationVersion();
    QStringList qslVersionOnline, qslVersionLocal;
    bool bMiseAJourNecessaire = false;

    qsVersionLocal.replace(QRegExp("[a-z]"), "");

    if(ecrireFichier){
        if(!qfUpdateXml.open(QIODevice::ReadWrite)){
            qDebug() << "Fichier Updates.xml non ouvert en lecture/écriture";
            QMessageBox::critical(this, "Mise à jour", "Erreur lors de la vérification des mises à jour.");
            return;
        } else {
            qDebug() << "Fichier Updates.xml écrit";
            qfUpdateXml.write(m_qbaDonneesTelechargees);
            qfUpdateXml.close();
        }
    }

    if(qfUpdateXml.open(QIODevice::ReadOnly)){
        qDebug() << "Contenu de l'object QDomDocument définis";
        qddXmlBOM.setContent(m_qbaDonneesTelechargees);
    } else {
        qDebug() << "Fichier Updates.xml non ouvert en lecture seule";
        QMessageBox::critical(this, "Mise à jour", "Erreur lors de la vérification des mises à jour.");
        return;
    }
    qfUpdateXml.close();

    // Extract the root markup
    QDomElement root = qddXmlBOM.documentElement();

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Component = root.firstChild().toElement();

    while(!Component.isNull()) {
        if (Component.tagName() == "PackageUpdate") {
            QDomElement Child = Component.firstChild().toElement();

            while (!Child.isNull()) {
                if (Child.tagName() == "Version") {
                    qsVersionOnline = Child.firstChild().toText().data();
                }
                Child = Child.nextSibling().toElement();
            }
        }
        Component = Component.nextSibling().toElement();
    }
    //qsVersionOnline = "0.2.4.1";
    qslVersionOnline = qsVersionOnline.split(".");
    qslVersionLocal = qsVersionLocal.split(".");

    //TEST
    //qslVersionOnline << "0" << "2" << "4" << "1";

    qDebug() << qsVersionOnline << qsVersionLocal;

    if (qslVersionOnline > qslVersionLocal) {
        qDebug() << "Test sans for fonctionne aussi !";
    }

    for(int i = 0; i < qslVersionOnline.size(); i++) {
        if(!bMiseAJourNecessaire) {
            if(qslVersionOnline > qslVersionLocal)
                bMiseAJourNecessaire = true;
        }
    }

    // On définis la dernière vérification des mises à jour, même si c'est une vérification manuelle
    param->setDerniereVerificationMiseAJour(QDate::currentDate());

    if(bMiseAJourNecessaire){
        if(QMessageBox::question(this, "Mise à jour disponible", "La version " + qsVersionOnline + " est disponible.\n Voulez-vous mettre à jour ?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
            qDebug() << "On lance la mise à jour";
            QProcess *qpOutilDeMaintenance = new QProcess();
            QStringList arguments;
            arguments << "--updater";
            if (param->getMiseAJourBeta()) {
                arguments << "--addTempRepository https://blackwizard.yj.fr/repository/b-advancements";
            }
            qpOutilDeMaintenance->setProgram("maintenancetool.exe");
            qpOutilDeMaintenance->setArguments(arguments);
            qpOutilDeMaintenance->startDetached();

            // Fermer la fenêtre
            qDebug() << "On ferme la fenêtre";
            emit fermeture();
            if(ouvertureEnCours)
                exit(1);
        } else {
            qDebug() << "L'utilisateur ne veut pas mettre à jour";
        }
    } else {
        qDebug() << "Pas de mise à jour";
        if(!ouvertureEnCours)
            QMessageBox::information(this, "Pas de nouvelle version", "La version <strong>" + qsVersionLocal + "</strong> est la plus récente.");
    }
}

/*
 * FONCTIONS
 */

/*
 * Fonction pour récupérer le numéro pour aller chercher le fichier index
 */
QString FRM_Principale::numeroIndex() {
    bool bOuvertureJson = true;
    QVariantMap qvmIndexes;
    if (QFile::exists(m_qsJSONVersion)) {
        QString qsFichierJsonVersion = m_qsJSONVersion;
        QFile qfFichierJsonVersion(qsFichierJsonVersion);
        if(!qfFichierJsonVersion.open(QIODevice::ReadOnly)){
            qDebug()<<"Failed to open "<< qsFichierJsonVersion;
            bOuvertureJson = false;
        }

        if (bOuvertureJson) {
            QTextStream file_text(&qfFichierJsonVersion);
            QString qsJsonStringPerso;
            qsJsonStringPerso = file_text.readAll();
            qfFichierJsonVersion.close();
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

/*
 * Fonction pour récupérer le hash du fichier de langue
 */
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

void FRM_Principale::traitementFichierAdvancements(QString fichier) {
    qDebug() << "traitementFichierAdvancements" << fichier;
    QStringList qslDossierSauvegardeTemp;
    QString qsFauxDossierSauvegarde;
    QStringList qslFormatFichier, qslFauxChemin;
    QString qsFauxChemin;
    qslFormatFichier << "*.json";
    bool bOuvertureJson = true;

    m_qsFichierAdvancementsSolo = fichier;
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
    }
}

/*
 * Utiliser dans le bouton de test
 */
void FRM_Principale::TEST(bool checked) {
    if (checked) {
        qDebug() << checked;
    }

    //QString qsJsonFile = "advancements/20w18a/adventure/kill_a_mob.json";
//    QString qsJsonFile = "advancements/20w18a/nether/fast_travel.json";
//    QStringList qslCheminFichier = qsJsonFile.split("/");

//    QFile qfJsonFile(qsJsonFile);
//    if(!qfJsonFile.open(QIODevice::ReadOnly)){
//        qDebug()<<"Failed to open "<< qsJsonFile;
//        exit(1);
//    }

//    QTextStream file_text(&qfJsonFile);
//    QString json_string;
//    json_string = file_text.readAll();
//    qfJsonFile.close();
//    QByteArray json_bytes = json_string.toLocal8Bit();

//    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

//    if(json_doc.isNull()){
//        qDebug()<<"Failed to create JSON doc.";
//        exit(2);
//    }
//    if(!json_doc.isObject()){
//        qDebug()<<"JSON is not an object.";
//        exit(3);
//    }

//    QJsonObject json_obj = json_doc.object();

//    if(json_obj.isEmpty()){
//        qDebug()<<"JSON object is empty.";
//        exit(4);
//    }

//    QVariantMap json_map = json_obj.toVariantMap();
//    QJsonArray qjaConditionsTemp = json_map["requirements"].toJsonArray();
//    QJsonArray qjaConditions = qjaConditionsTemp.at(0).toArray();

//    qDebug() << "Fichier  :" << qsJsonFile;
//    qDebug() << "Niveau 0 :" << qjaConditionsTemp.count();
//    // Si > 1 => OU (||)
//    // Sinon  => ET (&&)
//    qDebug() << "Niveau 1 :" << qjaConditions.count();

}
