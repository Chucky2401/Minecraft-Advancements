#include "frm_principale.h"
#include "ui_frm_principale.h"

FRM_Principale::FRM_Principale(QWidget *parent, bool test)
    : QMainWindow(parent)
    , ui(new Ui::FRM_Principale), m_test(test) {

    // Quelques réglages de bases sur la fenêtre
    ui->setupUi(this);
    m_statusBar = this->statusBar();
    m_statusBar->setStyleSheet("QStatusBar { background: #E0E0E0; }");
    this->setStatusBar(m_statusBar);
    m_statusBar->showMessage("Bonjour et bienvenue dans Minecraft Advancements !", 5000);
    m_progressExtractionProgresVanilla = new QProgressBar();
    m_progressExtractionProgresVanilla->setStyleSheet("QProgressBar { border: 2px solid #8BC34A; border-radius: 5px; text-align: center; height: 10px; } QProgressBar::chunk { background-color: #33cc33; }");
    m_labelExtractionProgresVanilla = new QLabel("");
    this->setStyleSheet("QMainWindow { background-image: url(:/img/wallpaper.png); background-position: bottom right; background-repeat: none; }");

    QAction *qaDockOperation = ui->qdwOpe->toggleViewAction();
    qaDockOperation->setIcon(QIcon(":/img/icons8_work_24px.png"));
    qaDockOperation->setShortcut(QKeySequence("Ctrl+O"));
    ui->qmOutils->addSeparator();
    ui->qmOutils->addAction(qaDockOperation);

    ouvertureEnCours = true;

    QString qsWindowTitle = QApplication::applicationName() + " - " + QApplication::applicationVersion();
    if (QApplication::applicationVersion().right(1) == "b") {
        qsWindowTitle += " /!\\ BETA /!\\";
    }

    // Si on est on mode test on masque certaines choses
    if (test == false) {
        ui->qpbReadJSON->setVisible(test);
        //ui->lineInDebug->setVisible(test);
    } else {
        ui->qpbReadJSON->setVisible(test);
        //ui->lineInDebug->setVisible(test);
        qsWindowTitle += " - TEST MODE";
        connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(TEST(bool)));
        //connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(imprimerTable()));
    }

    this->setWindowTitle(qsWindowTitle);
    this->setWindowIcon(QIcon(":/img/icons8_minecraft_logo_48px.png"));


    // On crée le nécessaire pour gérer les paramètres utilisateurs
    param = new Settings();
    param->initialisation(m_test);
    bdd.initialisation(m_test);

    // Variable global à toute la fenêtre
    m_qsAppDataPath = qEnvironmentVariable("APPDATA");
    m_ouvertureJson = false;
    m_qsDossierAExclure = "recipes|technical";
    m_qmbMessage.setTextFormat(Qt::RichText);
    m_qmbMessage.setWindowIcon(QIcon(":/img/icons8_minecraft_logo_48px.png"));
    m_qmbMessage.setStandardButtons(QMessageBox::Ok);
    m_qmbMessage.setDefaultButton(QMessageBox::Ok);

    // On désactive certaines choses
    ui->qgbFiltres->setEnabled(false);
    ui->qgbOperations->setEnabled(false);
    ui->qaImprimerVue->setEnabled(false);
    ui->qpbExtraireProgresBacap->setEnabled(false);

    // Langue disponibles
    ui->qcbLangue->addItem("Français", QVariant("/fr_fr.lang"));
    ui->qcbLangue->addItem("English", QVariant("/en_us.lang"));

    // On initialise certaines variables et champ de la fenêtre
    m_updateBetaVerifiee = false;
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

    //ui->qcbStatistiques->setCheckState(Qt::Checked);
    ui->qcbStatistiques->setToolTip("Progrès liés aux statistiques de jeu.\n"
                                  "Tel que \"Parcourir 100 Km\", \"Reproduire 2500 animaux\" ou \"Atteindre le niveau 30\", etc.");

    //ui->qcbMilestones->setCheckState(Qt::Checked);
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

    bool testBdd = bdd.createConnection(connectionName);
    if(!testBdd){
        QString lastBddError = bdd.getError();
        QMessageBox::critical(this, "Connexion à la BDD", "Echec de la connexion à la Base de Données.\nDétails:\n"+bdd.getError());
    }

    // Gestion de l'autocomplétion pour les titres
    m_sansCompleter = new QCompleter();
    m_defaultCompleter = new QCompleter(this);
    ui->qcbAutoCompletion->setChecked(true);

    // Pour les mises à jour
    m_qnamManager = new QNetworkAccessManager();

    // On connecte tout ce que l'on peut
    // GUI
    connect(ui->qdwOpe, SIGNAL(topLevelChanged(bool)), this, SLOT(dockWidgetOperationFloating(bool)));
//    connect(ui->qdwOpe, SIGNAL(visibilityChanged(bool)), this, SLOT(dockWidgetOperationClosing(bool)));
    // Configuration
    connect(ui->qcbLauncher, SIGNAL(currentIndexChanged(int)), this, SLOT(choixLauncher(int)));
    //connect(ui->qcbVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(choixVersion(int)));
    connect(ui->qcbVersion, SIGNAL(currentIndexChanged(QString)), this, SLOT(choixVersion(QString)));
    connect(ui->qpbSelectionFichierProgres, SIGNAL(clicked(bool)), this, SLOT(choixFichierAdvancements(bool)));
    connect(ui->qpbDossierBlazeandcave, SIGNAL(clicked(bool)), this, SLOT(selectionDossierBlazeandcave(bool)));
    connect(ui->qpbExtraireProgresBacap, SIGNAL(clicked(bool)), this, SLOT(importProgresBlazeandcave(bool)));
    connect(ui->qpbImportProgresJoueur, SIGNAL(clicked(bool)), this, SLOT(importProgresPerso(bool)));
    connect(ui->qcbStatistiques, SIGNAL(stateChanged(int)), this, SLOT(exclureStats(int)));
    connect(ui->qcbMilestones, SIGNAL(stateChanged(int)), this, SLOT(exclureStats(int)));
    // Lecture fichiers
    connect(ui->qpbExtraireProgresVanilla, SIGNAL(clicked(bool)), this, SLOT(extraireProgres(bool)));
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
    connect(ui->qpbResetDates, SIGNAL(clicked(bool)), this, SLOT(effacerFiltresSurLesDates(bool)));
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
        qInfo() << "Dernière Verif : " << param->getDerniereVerificationMiseAJour();
        qInfo() << "Prochaine vérification : " << param->getProchaineVerificationMiseAjour();
        param->setDerniereVerificationMiseAJour(QDate::currentDate());
        verifierMiseAJour();
    } else {
        qInfo() << "On ne vérifie pas les mise à jour";
        qInfo() << "Derniere Verif : " << param->getDerniereVerificationMiseAJour();
        qInfo() << "Prochaine Verif : " << param->getProchaineVerificationMiseAjour();
    }

    // Suite à la connexion on force le launcher et on désactive certains champs pour ne pas avoir de bug
    ui->qcbLauncher->setCurrentIndex(1);
    ui->qpbSelectionDossierLanceur->setVisible(false);
    ui->qpbExtraireProgresVanilla->setEnabled(false);
    ui->qlAdvancementsVanillaExtrait->setVisible(false);
    ui->qlDernierImportVanilla->setVisible(false);
    ui->qlProgresPerso->setVisible(false);
    ui->qpbReadJSONsVanilla->setEnabled(false);
    ui->qpbReadJSONsBlazeandcave->setEnabled(false);
    ui->qpbReadAllJSONs->setEnabled(false);

    // On redimensionne la fenêtre dans son dernier état si l'utilisateur la souhaité
    if (param->getRestoreSizePos()) {
        if(param->getEtat() != "DNE" && param->getGeometrie() != "DNE") {
            this->restoreGeometry(param->getGeometrie());
            this->restoreState(param->getEtat());
        }
        if(param->getDockIsFloating()) {
            ui->qdwOpe->setFloating(param->getDockIsFloating());
            if(param->getGeometrieDock() != "DNE") {
                ui->qdwOpe->restoreGeometry(param->getGeometrieDock());
            }
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

        if (param->getDossierBlazeAndCave() != "DNE") {
            traitementDossierBac(param->getDossierBlazeAndCave());
        }

        ui->qcbMilestones->setChecked(param->getMilestones());
        ui->qcbStatistiques->setChecked(param->getStatistics());
        exclureStats(ui->qcbMilestones->checkState());

        if (param->getFichierAdvancementsPerso() != "DNE") {
            traitementFichierAdvancements(param->getFichierAdvancementsPerso());
        }
    }

    ouvertureEnCours = false;

    // TEST
//    plainModel = new QSqlQueryModel();
//    plainModel->setQuery("SELECT * FROM list_advancements WHERE version = '1.15.2' AND identifiant = 'minecraft:adventure/adventuring_time'", bdd.getBase());
//    ui->tableView->setModel(plainModel);
}

/*
 * Destructeur de la classe
 */
FRM_Principale::~FRM_Principale() {
    if (bdd.isOpen(connectionName))
        bdd.closeConnection(connectionName);
//    if (getEtatFenAjouterRecette())
//        fenAjouterRecette->close();
    delete param;
    delete ui;
}

/*
 * Fonction pour détecter quand la fenêtre est fermé
 */
void FRM_Principale::closeEvent(QCloseEvent *event){
    // Si on est en test ou le paramètre pour confirmation fermeture est désactivé
    // On ferme sans message bloquant
    if (m_test || !param->getMessageConfirmationFermeture()) {

        if (param->getRestoreSizePos()) {
            param->setGeometrieEtat(saveGeometry(), saveState());
            param->setGeometrieDock(ui->qdwOpe->saveGeometry());
        }

        event->accept();
        return;
    }

    // "Sinon", on demande confirmation de fermeture
    if (QMessageBox::question(this, "Fermeture", "Voulez-vous fermer le programme ?") == QMessageBox::Yes){
        if (param->getRestoreSizePos()) {
            param->setGeometrieEtat(saveGeometry(), saveState());
            param->setGeometrieDock(ui->qdwOpe->saveGeometry());
        }

        event->accept();
    } else {
        event->ignore();
    }
}

/*  ~~~~~~~~~
 *  | SLOTS |
 *  ~~~~~~~~~
 */

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
            }

        }
    }
}

/*
 * Slots lorsque l'utilisateur sélectionne la version
 */
void FRM_Principale::choixVersion(QString text) {
    QString qsCheminVersion = ui->qcbVersion->currentData().toString();
    QString qsFauxChemin, qsNumeroIndex = "";
    QStringList qslFormatFichier;
    QSqlQuery qsqCompteProgresVanilla(bdd.getBase()), qsqDernierImporteVanilla(bdd.getBase());
    //int iFicherDejaExtrait = 0;

    qslFormatFichier << "*.json";

    // Ici, on récupère le nom du fichier index pour les assets
    if (ui->qcbVersion->currentIndex() != 0) {
        m_qsJSONVersion = ui->qcbVersion->currentData().toString().replace(".jar", ".json");
        qsNumeroIndex = numeroIndex();
        m_qsFichierIndex = m_qsDossierIndexes + "\\" + qsNumeroIndex + ".json";
    }

    m_qsNumeroVersion = ui->qcbVersion->currentText();
    m_qsl7zipArguments.clear();
    m_qsl7zipArgumentsLang.clear();

    if (qsCheminVersion != "EMPTY") {
        ui->qleCheminVersion->setText("C:\\fake_Path\\" + text + ".jar");
    } else
        ui->qleCheminVersion->clear();//ui->qleCheminVersion->setText("");

    m_qdDossierAdvancedments.setPath(param->getPath() + "advancements/" + ui->qcbVersion->currentText() + "/");
    m_qsFichierLang = m_qdDossierAdvancedments.absolutePath() + ui->qcbLangue->currentData().toString();
    m_qsCleLang = "minecraft/lang" + ui->qcbLangue->currentData().toString().replace(".lang", ".json");

    if (ui->qcbVersion->currentData() != "EMPTY")
        m_bVersionOK = true;
    else
        m_bVersionOK = false;

    if (qsqCompteProgresVanilla.exec("SELECT COUNT(1) progresImporte FROM statistics WHERE nom = \"progres_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
        qsqCompteProgresVanilla.next();
        int iNombreEnregistrement = qsqCompteProgresVanilla.value("progresImporte").toInt();
        if (iNombreEnregistrement > 0) {
            if (qsqDernierImporteVanilla.exec("SELECT valeur FROM statistics WHERE nom = \"progres_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
                qsqDernierImporteVanilla.next();
                QString qsDernierImport = qsqDernierImporteVanilla.value("valeur").toString();
                QDateTime qdtDernierImport = QDateTime::fromString(qsDernierImport, "yyyy-MM-dd hh:mm:ss");
                if (qdtDernierImport.isValid()) {
                    ui->qlDernierImportVanilla->setText("Dernier Import : " + qdtDernierImport.toString("dd/MM/yyyy hh:mm:ss"));
                    ui->qlDernierImportVanilla->setVisible(true);
                    // Modification du bouton
                    ui->qpbExtraireProgresVanilla->setText("Ré-Importer Progrès");
                    ui->qpbExtraireProgresVanilla->setEnabled(true);
                    m_bUpdateProgres = true;
                    m_bProgresVanillaOK = true;
                    // Info utilisateur
                    ui->qlAdvancementsVanillaExtrait->setText("Progrès importé !");
                    ui->qlAdvancementsVanillaExtrait->setStyleSheet("QLabel { color: green; }");
                    ui->qlAdvancementsVanillaExtrait->setVisible(true);
                    m_bProgresVanillaOK = true;
                } else {
                    ui->qlDernierImportVanilla->setVisible(false);
                    // Modification du bouton
                    ui->qpbExtraireProgresVanilla->setText("Ré-Importer Progrès");
                    ui->qpbExtraireProgresVanilla->setEnabled(true);
                    m_bUpdateProgres = true;
                    m_bProgresVanillaOK = true;
                    // Info utilisateur
                    ui->qlAdvancementsVanillaExtrait->setText("Import progrès incomplet !");
                    ui->qlAdvancementsVanillaExtrait->setStyleSheet("QLabel { color: orange; }");
                    ui->qlAdvancementsVanillaExtrait->setVisible(true);
                    m_bProgresVanillaOK = false;
                }
            } else {
                m_bProgresVanillaOK = false;
                afficherMessage(QMessageBox::Warning, "Impossible de récupérer la date de dernier import des progrès Minecraft Vanilla.", \
                                            "Voir les détails pour plus d'informations.", \
                                            qsqDernierImporteVanilla.lastError().text());
                ui->qlDernierImportVanilla->setVisible(false);
            }
        } else {
            ui->qlDernierImportVanilla->setVisible(false);
            // Modification du bouton
            ui->qpbExtraireProgresVanilla->setText("Importer Progrès");
            ui->qpbExtraireProgresVanilla->setEnabled(true);
            m_bUpdateProgres = true;
            m_bProgresVanillaOK = true;
            // Info utilisateur
            ui->qlAdvancementsVanillaExtrait->setText("Progrès non importé !");
            ui->qlAdvancementsVanillaExtrait->setStyleSheet("QLabel { color: red; }");
            ui->qlAdvancementsVanillaExtrait->setVisible(true);
            m_bProgresVanillaOK = false;
        }
    } else {
        m_bProgresVanillaOK = false;
        afficherMessage(QMessageBox::Critical, "Impossible de vérifier si les progrès ont déjà étés importés.", \
                                    "Contacter <a href=\"https://github.com/Chucky2401/Minecraft-Advancements/issues/new?title=Erreur contrôle import progrès&body=" + qsqDernierImporteVanilla.lastError().text() + "\n\nRemarque personnel :\n\">le développeur</a>.", \
                                    qsqDernierImporteVanilla.lastError().text());
        ui->qlDernierImportVanilla->setVisible(false);
    }

    traitementDossierBac(m_qdDossierAdvancementsBlazeAndCave.path().replace("/data/blazeandcave/advancements", ""));
    traitementFichierAdvancements(m_qsFichierAdvancementsSolo);

    activationBoutonExtraction();

    if (qsCheminVersion != "EMPTY") {
        m_qsl7zipArguments << "x" << qsCheminVersion << "-o"+m_tempDir.path() << "-ir!data\\minecraft\\advancements\\*.json";
        m_qsl7zipArgumentsLang << "x" << qsCheminVersion << "-o"+m_tempDir.path() << "-ir!assets\\minecraft\\lang\\*.json";
    }

    // On enregistre la valeur pour une restauration ultérieur au démarrage
    if (ui->qcbVersion->currentData() != "EMPTY") {
        param->setVersion(text);
    }
}

/*
 * Slots pour extraire les fichiers .json sur les advancements
 * Ainsi que le fichier de langue
 * Importe le tout dans la base de données
 */
void FRM_Principale::extraireProgres(bool checked) {
    if (checked) {
    }

    // TEST
    QTime qtDebut(QTime::currentTime());

    QStringList qslFormatFichier;
    QString qsTitrePrecedent = "";
    QString qsTempNom, qsNouveauNom;
    QString qsLastErrorBdd = "", qsDernierImport = "", qsDerniereRequete = "";
    bool bErreurDetecteAdvancement = false, bErreurDetecteLang = false, bErreurDelete = false, bErreurInsertionAdvancement = false;
    QString qsErreurExtractionProgres = "", qsErreurExtractionLang = "";
    int iNombreFichierATraiter = 0, iNombreFichierTraiter = 0;

    qslFormatFichier << "*.json";

    m_progressExtractionProgresVanilla->setMinimum(0);
    m_progressExtractionProgresVanilla->setMaximum(0);
    m_progressExtractionProgresVanilla->setValue(0);
    m_labelExtractionProgresVanilla->setText("(\?\?/\?\?)");
    m_statusBar->clearMessage();
    m_statusBar->addWidget(m_progressExtractionProgresVanilla, 1);
    m_statusBar->insertWidget(99, m_labelExtractionProgresVanilla);
    m_progressExtractionProgresVanilla->show();
    m_labelExtractionProgresVanilla->show();

    ui->qcbLauncher->setEnabled(false);
    ui->qcbLangue->setEnabled(false);
    ui->qcbVersion->setEnabled(false);
    ui->qpbExtraireProgresVanilla->setEnabled(false);
    ui->qpbExtraireProgresBacap->setEnabled(false);
    ui->qpbImportProgresJoueur->setEnabled(false);
    ui->qpbReadJSONsVanilla->setEnabled(false);
    ui->qpbReadJSONsBlazeandcave->setEnabled(false);
    ui->qpbReadAllJSONs->setEnabled(false);

    /*
     * On extrait les progrès du fichier .jar de la version de Minecraft
     */
    m_qp7zProcess->start(m_qs7zBin, m_qsl7zipArguments);
    if (m_qp7zProcess->waitForFinished()) {
        QDirIterator qdiFichierProgres(m_tempDir.path()+"/data/minecraft/advancements/", qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

        while (qdiFichierProgres.hasNext() && !bErreurDetecteAdvancement) {
            qsTempNom = qdiFichierProgres.next();
            qsNouveauNom = qsTempNom;
            qsNouveauNom.replace(m_tempDir.path()+"/data/minecraft/advancements/", m_qdDossierAdvancedments.absolutePath() + "/");

            QString qsCheminCompletTemp = qdiFichierProgres.filePath();
            QStringList qslCheminFichier = qsCheminCompletTemp.split("/");
            QString qsNomDuFichierTemp = qdiFichierProgres.fileName();
            QString qsDossierTemp = qsCheminCompletTemp.replace(qsNomDuFichierTemp, "");
            QString qsDossierFinal = qsDossierTemp.replace(m_tempDir.path()+"/data/minecraft/advancements/", m_qdDossierAdvancedments.absolutePath() + "/");
            QFile qfFichierTemporaire(qsTempNom);
            QFile qfFichierFinal(qsNouveauNom);
            QDir qdDossierFinal(qsDossierFinal);

            iNombreFichierATraiter++;

            if (!(qdDossierFinal.exists()))
                qdDossierFinal.mkpath(".");

            if (qsNomDuFichierTemp != "." && qsNomDuFichierTemp != "..") {
                if(!qfFichierTemporaire.open(QIODevice::ReadOnly)){
                    qDebug()<<"Failed to open "<< qfFichierTemporaire;
                    bErreurDetecteAdvancement = true;
                } else {
                    if(!qfFichierFinal.open(QIODevice::ReadWrite)){
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
            QCoreApplication::processEvents();
        }

        QDir qdDossierTemporaire(m_tempDir.path()+"/data");
        qdDossierTemporaire.removeRecursively();
    }

    /*
     * Si les progrès ont été extrait et que la lang est anglais
     * On extrait le fichier du .jar
     */
    if (!bErreurDetecteAdvancement && ui->qcbLangue->currentData() == "/en_us.lang") {
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
                            QByteArray qbaContenuFichierTemp = qfFichierTemporaire.readAll();
                            if (qfFichierFinal.write(qbaContenuFichierTemp) == -1) {
                                bErreurDetecteLang = true;
                            }
                            qfFichierFinal.close();
                            qfFichierTemporaire.close();
                            qfFichierTemporaire.remove();
                        }
                    }
                }
                QCoreApplication::processEvents();
            }
        }
    /*
     * Si les progrès ont été extrait et que la lang n'est pas l'anglais
     * On va récupérer le bon ficier asset
     */
    } else if (!bErreurDetecteAdvancement && ui->qcbLangue->currentData() != "/en_us.lang") {
        QString qsNomFichierLangue = hashLangue();
        QString qsFichier = "";
        QFile qfFichierTemporaire("");
        QFile qfFichierFinal(m_qsFichierLang);

        QDirIterator qdiFichierLangue(m_qsDossierObjects, QStringList() << qsNomFichierLangue, QDir::Files, QDirIterator::Subdirectories);

        while (qdiFichierLangue.hasNext()) {
            qsFichier = qdiFichierLangue.next();
        }

        qfFichierTemporaire.setFileName(qsFichier);

        if(!qfFichierTemporaire.open(QIODevice::ReadOnly)) {
            bErreurDetecteLang = true;
        } else {
            if(!qfFichierFinal.open(QIODevice::ReadWrite)){
                bErreurDetecteLang = true;
            } else {
                QByteArray qbaContenuFichierTemp = qfFichierTemporaire.readAll();
                if (qfFichierFinal.write(qbaContenuFichierTemp) == -1) {
                    bErreurDetecteLang = true;
                }
                qfFichierFinal.close();
                qfFichierTemporaire.close();
            }
        }
    }

    QDir qdDossierTemporaire(m_tempDir.path()+"/assets");
    qdDossierTemporaire.removeRecursively();

    /*
     * Toute cette partie s'occupe de stocker tous les progrès dans la base de données
     * /!\ Mincraft Vanilla seulement ! /!\
     */

    if (!bErreurDetecteAdvancement && !bErreurDetecteLang) {
        // On les supprimes avant
        QSqlQuery queryDelete(bdd.getBase());
        if (!queryDelete.exec("DELETE FROM list_advancements WHERE origine = \"Minecraft Vanilla\" AND version = \"" + m_qsNumeroVersion + "\"")) {
            bErreurDelete = true;
            afficherMessage(QMessageBox::Critical, "Impossible de purger la base de données avant import.", \
                                        "Voir les détails pour plus d'informations.", \
                                        queryDelete.lastError().text());
        } else {
            QVariantMap qvmJsonLang = ouvrirJson(m_qsFichierLang);
            // Traduction dans une liste
            toutesLesTraductions(qvmJsonLang);
            toutesLesTraductionsListe();

            m_progressExtractionProgresVanilla->setMaximum(iNombreFichierATraiter);
            m_labelExtractionProgresVanilla->setText("(0/" + QString::number(iNombreFichierATraiter) + ")");

            QDirIterator qdiFichierProgres(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

            while (qdiFichierProgres.hasNext() && !bErreurInsertionAdvancement) {
                QString qsJsonFile = qdiFichierProgres.next();
                QStringList qslCheminFichier = qsJsonFile.split("/");
                QString qsCategorie = qslCheminFichier.at(qslCheminFichier.length()-2);
                if (!qslCheminFichier.contains("recipes")) {
                    QVariantMap qvmJsonAdvancementsVanilla = ouvrirJson(qsJsonFile);
                    QMap<QString, QVariant> qmDisplay = qvmJsonAdvancementsVanilla["display"].toMap();
                    QMap<QString, QVariant> qmTitle = qmDisplay["title"].toMap();
                    QMap<QString, QVariant> qmDescription = qmDisplay["description"].toMap();
                    QMap<QString, QVariant> qmCriteres = qvmJsonAdvancementsVanilla["criteria"].toMap();
                    QJsonArray qjaConditionsTemp = qvmJsonAdvancementsVanilla["requirements"].toJsonArray();
                    QJsonArray qjaConditions = qjaConditionsTemp.at(0).toArray();

                    // Si > 1 => OU (||)
                    // Sinon  => ET (&&)
                    int iNombreRequierements = qjaConditions.count();
                    QString qsIdentifiant = qsJsonFile;
//                    QString qsTitre = qvmJsonLang[qmTitle["translate"].toString()].toString();
                    QString qsTitre = qmTitle["translate"].toString();
//                    QString qsDescription = qvmJsonLang[qmDescription["translate"].toString()].toString();
                    QString qsDescription = qmDescription["translate"].toString();
                    QSqlQuery qsqSelectTraductionTitreCompteur(bdd.getBase()), qsqSelectTraductionTitreValeur(bdd.getBase());
                    QSqlQuery qsqSelectTraductionDescriptionCompteur(bdd.getBase()), qsqSelectTraductionDescriptionValeur(bdd.getBase());
                    qsIdentifiant.replace(m_qdDossierAdvancedments.path()+"/", "");
                    qsIdentifiant = "minecraft:" + qsIdentifiant.split(".").first();

                    // Récupération du titre traduit
                    if (qsqSelectTraductionTitreCompteur.exec("SELECT COUNT(1) nbrTraduction FROM traduction_vanilla WHERE version = '" + m_qsNumeroVersion + "' AND key = '" + qsTitre + "'")) {
                        qsqSelectTraductionTitreCompteur.next();
                        if (qsqSelectTraductionTitreCompteur.value("nbrTraduction").toInt() != 0) {
                            if (qsqSelectTraductionTitreValeur.exec("SELECT value FROM traduction_vanilla WHERE version = '" + m_qsNumeroVersion + "' AND key = '" + qsTitre + "'")) {
                                qsqSelectTraductionTitreValeur.next();
                                qsTitre = qsqSelectTraductionTitreValeur.value("value").toString();
                            }
                        } else {
                            QStringList qslIdentifiant = qsIdentifiant.split("/");
                            QString qsValeurDansLang = "minecraft." + qslIdentifiant.last();
                            if (qsqSelectTraductionTitreValeur.exec("SELECT value FROM traduction_vanilla WHERE version = '" + m_qsNumeroVersion + "' AND key LIKE '%" + qsTitre + "%'")) {
                                qsqSelectTraductionTitreValeur.next();
                                qsTitre = qsqSelectTraductionTitreValeur.value("value").toString();
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
                    }

                    // Récupération description traduit
                    if (qsqSelectTraductionDescriptionCompteur.exec("SELECT COUNT(1) nbrTraduction FROM traduction_vanilla WHERE version = '" + m_qsNumeroVersion + "' AND key = '" + qsDescription + "'")) {
                        qsqSelectTraductionDescriptionCompteur.next();
                        if (qsqSelectTraductionDescriptionCompteur.value("nbrTraduction").toInt() != 0) {
                            if (qsqSelectTraductionDescriptionValeur.exec("SELECT value FROM traduction_vanilla WHERE version = '" + m_qsNumeroVersion + "' AND key = '" + qsDescription + "'")) {
                                qsqSelectTraductionDescriptionValeur.next();
                                qsDescription = qsqSelectTraductionDescriptionValeur.value("value").toString();
                            }
                        } else {
                            qsDescription = "";
                        }
                    }

                    qsTitre.replace("’", "'");

                    QMapIterator<QString, QVariant> qmiCriteres(qmCriteres);
                    while (qmiCriteres.hasNext()) {
                        qmiCriteres.next();
                        m_qlLigneProgres.clear();

                        QString qsTypeCondition = "";

                        QString qsCondition = qmiCriteres.key();
                        QString qsConditionSimple = qsCondition;
                        QMap<QString, QVariant> qmCritere = qmCriteres[qsCondition].toMap();
                        QString qmTrigger = qmCritere["trigger"].toString();

                        QMap<QString, QVariant> qmConditions = qmCritere["conditions"].toMap();
                        QList<QString> qlsKeysMap = qmConditions.keys();

                        QDateTime qdtDateRealisation = QDateTime();

                        qsConditionSimple.replace(QRegExp("^.+:"), "");

                        /*
                         * Rechercher la traduction
                         * Si trouvé : on la met
                         * Sinon     : on mets qsConditionSimple
                         */
                        int index = m_qslClesToutesLesTrads.indexOf(QRegExp(".+\\.minecraft(\\..+)?\\." + qsConditionSimple + "$"));
                        if (index != -1) {
                            qsConditionSimple = m_qslToutesLesTrads.at(index);
                        }

                        if (iNombreRequierements > 1) {
                            qsTypeCondition = "OU";
                        } else if (iNombreRequierements == 1 && qjaConditionsTemp.count() > 1) {
                            qsTypeCondition = "ET";
                        } else {
                            qsTypeCondition = "UNE";
                        }

                        /*
                         * Moment de vérité, on insert, mais avant on supprime tout.
                         */
                        QSqlQuery queryInsert(bdd.getBase());
                        queryInsert.prepare("INSERT INTO list_advancements (origine, version, categorie, identifiant, titre, description, condition, condition_texte, type_condition) "
                                      "VALUES (:origine, :version, :categorie, :identifiant, :titre, :description, :condition, :condition_texte, :type_condition)");
                        queryInsert.bindValue(":origine", "Minecraft Vanilla");
                        queryInsert.bindValue(":version", m_qsNumeroVersion);
                        queryInsert.bindValue(":categorie", qsCategorie);
                        queryInsert.bindValue(":identifiant", qsIdentifiant);
                        queryInsert.bindValue(":titre", qsTitre);
                        queryInsert.bindValue(":description", qsDescription);
                        queryInsert.bindValue(":condition", qsCondition);
                        queryInsert.bindValue(":condition_texte", qsConditionSimple);
                        queryInsert.bindValue(":type_condition", qsTypeCondition);
                        if(!bErreurInsertionAdvancement) {
                            if(!queryInsert.exec()) {
                                bErreurInsertionAdvancement = true;
                                qsLastErrorBdd = queryInsert.lastError().text();
                                qsDerniereRequete = queryInsert.executedQuery();
                            }
                        }
                        QCoreApplication::processEvents();
                    }
                }
                iNombreFichierTraiter++;
                m_progressExtractionProgresVanilla->setValue(m_progressExtractionProgresVanilla->value()+1);
                m_labelExtractionProgresVanilla->setText("(" + QString::number(iNombreFichierTraiter) + "/" + QString::number(iNombreFichierATraiter) + ")");
            }
        }
        if (!bErreurDelete && !bErreurInsertionAdvancement) {
            QSqlQuery queryDeleteStats(bdd.getBase());
            if(!queryDeleteStats.exec("DELETE FROM statistics WHERE nom = \"progres_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
                ui->qlDernierImportVanilla->setVisible(false);
                afficherMessage(QMessageBox::Warning, "Impossible de mettre à jour la date d'import des progrès.\nLes progrès pour la version <strong>" + m_qsNumeroVersion + "</strong> ont bien été importés dans la base.", \
                                            "Voir les détails pour plus d'informations.", \
                                            queryDeleteStats.lastError().text());
            } else {
                qsDernierImport = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QDateTime qdtDernierImportFR = QDateTime::fromString(qsDernierImport, "yyyy-MM-dd hh:mm:ss");
                QSqlQuery queryInsertStats(bdd.getBase());
                if(!queryInsertStats.exec("INSERT INTO statistics (nom, valeur, version) VALUES (\"progres_update\", \"" + qsDernierImport + "\", \"" + m_qsNumeroVersion + "\")")) {
                    ui->qlDernierImportVanilla->setVisible(false);
                    afficherMessage(QMessageBox::Warning, "Impossible de mettre à jour la date d'import des progrès.\nLes progrès pour la version <strong>" + m_qsNumeroVersion + "</strong> ont bien été importés dans la base.", \
                                                "Voir les détails pour plus d'informations.", \
                                                queryInsertStats.lastError().text());
                } else {
                    ui->qlDernierImportVanilla->setText("Dernier Import : " + qdtDernierImportFR.toString("dd/MM/yyyy hh:mm:ss"));
                    ui->qlDernierImportVanilla->setVisible(true);
                    afficherMessage(QMessageBox::Information, "Tous les progrès ont été inséré avec succès !", \
                                                "Les progrès de Minecraft Vanilla pour la version <strong>" + m_qsNumeroVersion + "</strong> sont maintenant en base");
                }
            }

            // Modification du bouton
            ui->qpbExtraireProgresVanilla->setText("Ré-Importer Progrès");
            ui->qpbExtraireProgresVanilla->setEnabled(true);
            m_bUpdateProgres = true;
            m_bProgresVanillaOK = true;
            // Info utilisateur
            ui->qlAdvancementsVanillaExtrait->setText("Progrès importé !");
            ui->qlAdvancementsVanillaExtrait->setStyleSheet("QLabel { color: green; }");
            ui->qlAdvancementsVanillaExtrait->setVisible(true);
            m_bProgresVanillaOK = true;
        } else if (!bErreurDelete && bErreurInsertionAdvancement) {
            afficherMessage(QMessageBox::Critical, "Impossible d'insérer tous les progrès.", \
                                        "Voir les détails pour plus d'informations.", \
                                        qsLastErrorBdd + "\nDernières Requêtes :\n" + qsDerniereRequete);
            ui->qlDernierImportVanilla->setVisible(false);
            // Modification du bouton
            ui->qpbExtraireProgresVanilla->setText("Importer Progrès");
            ui->qpbExtraireProgresVanilla->setEnabled(true);
            m_bUpdateProgres = true;
            m_bProgresVanillaOK = true;
            // Info utilisateur
            ui->qlAdvancementsVanillaExtrait->setText("Progrès non importé !");
            ui->qlAdvancementsVanillaExtrait->setStyleSheet("QLabel { color: red; }");
            ui->qlAdvancementsVanillaExtrait->setVisible(true);
            m_bProgresVanillaOK = false;
        }

        // On supprime les dossiers ont en a plus besoin...
        m_qdDossierAdvancedments.removeRecursively();
        // On remet les boutons actifs
        ui->qcbLauncher->setEnabled(true);
        ui->qcbLangue->setEnabled(true);
        ui->qcbVersion->setEnabled(true);
        ui->qpbExtraireProgresVanilla->setEnabled(true);
        ui->qpbExtraireProgresBacap->setEnabled(true);
        ui->qpbImportProgresJoueur->setEnabled(true);
        // On supprime les widgets de la status bar
        m_statusBar->removeWidget(m_progressExtractionProgresVanilla);
        m_statusBar->removeWidget(m_labelExtractionProgresVanilla);
        m_statusBar->clearMessage();

        activationBoutonExtraction();
    } else {
        afficherMessage(QMessageBox::Critical, "Erreur avec les fichiers", "Les fichier progrès ou la langue n'ont pas pu être extrait.");
    }

    QTime qtFin(QTime::currentTime());
    int iDuree = qtDebut.secsTo(qtFin);
    m_statusBar->showMessage("Durée écoulée : " + QString::number(iDuree), 10000);

}

/*
 * Slots pour que l'utilisateur choisisse le dossier des advancements Blaze And Cave
 */
void FRM_Principale::selectionDossierBlazeandcave(bool checked) {
    if (checked) {
    }
    QString qsDossierBlazeandCave = QFileDialog::getExistingDirectory(this, tr("Dossier Blaze And Cave"),
                                                 m_qsDossierMinecraft,
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    traitementDossierBac(qsDossierBlazeandCave);

    param->setDossierBlazeAndCave(qsDossierBlazeandCave);
}

/*
 * Slots pour importer les progrès BACAP
 */
void FRM_Principale::importProgresBlazeandcave(bool checked) {
    if (checked) {
    }

    // TEST
    QTime qtDebut(QTime::currentTime());

    QStringList qslFormatFichier;
    QString qsTitrePrecedent = "";
    int iNombreFichierATraiter = 0, iNombreFichierTraiter = 0;
    QString qsLastErrorBdd = "", qsDernierImport = "", qsDerniereRequete = "";
    bool bErreurDelete = false, bErreurInsertionAdvancement = false;

    qslFormatFichier << "*.json";

    m_progressExtractionProgresVanilla->setMinimum(0);
    m_progressExtractionProgresVanilla->setMaximum(0);
    m_progressExtractionProgresVanilla->setValue(0);
    m_labelExtractionProgresVanilla->setText("(\?\?/\?\?)");
    m_statusBar->clearMessage();
    m_statusBar->addWidget(m_progressExtractionProgresVanilla, 1);
    m_statusBar->insertWidget(99, m_labelExtractionProgresVanilla);
    m_progressExtractionProgresVanilla->show();
    m_labelExtractionProgresVanilla->show();

    ui->qcbLauncher->setEnabled(false);
    ui->qcbLangue->setEnabled(false);
    ui->qcbVersion->setEnabled(false);
    ui->qpbExtraireProgresVanilla->setEnabled(false);
    ui->qpbExtraireProgresBacap->setEnabled(false);
    ui->qpbImportProgresJoueur->setEnabled(false);
    ui->qpbReadJSONsVanilla->setEnabled(false);
    ui->qpbReadJSONsBlazeandcave->setEnabled(false);
    ui->qpbReadAllJSONs->setEnabled(false);

    // On les supprimes avant
    QSqlQuery queryDelete(bdd.getBase());
    if (!queryDelete.exec("DELETE FROM list_advancements WHERE origine = \"BACAP\" AND version = \"" + m_qsNumeroVersion + "\"")) {
        bErreurDelete = true;
        afficherMessage(QMessageBox::Critical, "Impossible de purger la base de données avant import.", \
                                    "Voir les détails pour plus d'informations.", \
                                    queryDelete.lastError().text());
    } else {
        // Pas d'erreur lors de la suppression, on ajoute !
        toutesLesTraductionsListe();

        QString qsJsonLang = "rcs/blazeandcave-fr_fr.json";
        QVariantMap qvmJsonLang = ouvrirJson(qsJsonLang);

        qDebug() << m_qdDossierAdvancementsBlazeAndCave.path();
        //exit(0);

        QDirIterator qdiNombreFichier(m_qdDossierAdvancementsBlazeAndCave.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);
        while (qdiNombreFichier.hasNext()) {
            qdiNombreFichier.next();
            iNombreFichierATraiter++;
            m_labelExtractionProgresVanilla->setText("Nombre Fichier : 0/"+QString::number(iNombreFichierATraiter));
            QCoreApplication::processEvents();
        }
        m_progressExtractionProgresVanilla->setMaximum(iNombreFichierATraiter);
        m_labelExtractionProgresVanilla->setText("(0/" + QString::number(iNombreFichierATraiter) + ")");

        QDirIterator qdiFichierProgres(m_qdDossierAdvancementsBlazeAndCave.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);
        while (qdiFichierProgres.hasNext()) {
            QString qsJsonFile = qdiFichierProgres.next();
            QStringList qslCheminFichier = qsJsonFile.split("/");
            QString qsCategorie = qslCheminFichier.at(qslCheminFichier.length()-2);
            if (!qslCheminFichier.contains("technical") && !qslCheminFichier.contains("recipes")) {
                QVariantMap json_map = ouvrirJson(qsJsonFile);
                if (m_ouvertureJson) {
                    QMap<QString, QVariant> qmDisplay = json_map["display"].toMap();
                    QMap<QString, QVariant> qmTitle = qmDisplay["title"].toMap();
                    QMap<QString, QVariant> qmDescription = qmDisplay["description"].toMap();
                    QMap<QString, QVariant> qmCriteres = json_map["criteria"].toMap();
                    QJsonArray qjaConditionsTemp = json_map["requirements"].toJsonArray();
                    QString qsTypeCondition = "";
                    int iNombreRequierements;

                    int iCritereAFaire = qmCriteres.count();

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

                    qsTitre.replace("’", "'");

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
                        QStandardItem *qsiTitre = new QStandardItem("");

                        if (qsDescription == "") {
                            qsiTitre->setText(qsTitre);
                        } else {
                            qsiTitre->setText(qsTitre + " (" + qsDescription + ")");
                        }
                        qsiTitre->setData(qsJsonFile, Qt::UserRole);

                        /*
                 * Rechercher la traduction
                 * Si trouvé : on la met
                 * Sinon     : on mets qsConditionSimple
                 */
                        int index = m_qslClesToutesLesTrads.indexOf(QRegExp(".+\\.minecraft(\\..+)?\\." + qsConditionSimple + "$"));
                        if (index != -1) {
                            qsConditionSimple = m_qslToutesLesTrads.at(index);
                        }

                        if (iCritereAFaire == 1) {
                            qsTypeCondition = "UNE";
                        } else {
                            if (iNombreRequierements > 1) {
                                qsTypeCondition = "OU";
                            } else if (iNombreRequierements == 1) {
                                qsTypeCondition = "ET";
                            } else {
                                qsTypeCondition = "UNE";
                            }
                        }

                        //QDateTime test(QDateTime::currentDateTime());

                        QSqlQuery queryInsert(bdd.getBase());
                        queryInsert.prepare("INSERT INTO list_advancements (origine, version, categorie, identifiant, titre, description, condition, condition_texte, type_condition) "
                                      "VALUES (:origine, :version, :categorie, :identifiant, :titre, :description, :condition, :condition_texte, :type_condition)");
                        queryInsert.bindValue(":origine", "BACAP");
                        queryInsert.bindValue(":version", m_qsNumeroVersion);
                        queryInsert.bindValue(":categorie", qsCategorie);
                        queryInsert.bindValue(":identifiant", qsIdentifiant);
                        queryInsert.bindValue(":titre", qsTitre);
                        queryInsert.bindValue(":description", qsDescription);
                        queryInsert.bindValue(":condition", qsCondition);
                        queryInsert.bindValue(":condition_texte", qsConditionSimple);
                        queryInsert.bindValue(":type_condition", qsTypeCondition);
                        if(!bErreurInsertionAdvancement) {
                            if(!queryInsert.exec()) {
                                bErreurInsertionAdvancement = true;
                                qsLastErrorBdd = queryInsert.lastError().text();
                                qsDerniereRequete = queryInsert.executedQuery();
                            }
                        }
                        //qDebug() << "BACAP;"+m_qsNumeroVersion+";"+qsCategorie+";"+qsIdentifiant+";"+qsTitre+";"+qsDescription+";"+qsCondition+";"+qsConditionSimple+";"+qsTypeCondition;
                        QCoreApplication::processEvents();
                    }
                }
            }
            iNombreFichierTraiter++;
            m_progressExtractionProgresVanilla->setValue(m_progressExtractionProgresVanilla->value()+1);
            m_labelExtractionProgresVanilla->setText("(" + QString::number(iNombreFichierTraiter) + "/" + QString::number(iNombreFichierATraiter) + ")");
        }
    }

    if (!bErreurDelete && !bErreurInsertionAdvancement) {
        QSqlQuery queryDeleteStats(bdd.getBase());
        if(!queryDeleteStats.exec("DELETE FROM statistics WHERE nom = \"bacap_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
            ui->qlDernierImportBacap->setVisible(false);
            afficherMessage(QMessageBox::Warning, "Impossible de mettre à jour la date d'import des progrès.\nLes progrès pour la version <strong>" + m_qsNumeroVersion + "</strong> ont bien été importés dans la base.", \
                                        "Voir les détails pour plus d'informations.", \
                                        queryDeleteStats.lastError().text());
        } else {
            qsDernierImport = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QDateTime qdtDernierImportFR = QDateTime::fromString(qsDernierImport, "yyyy-MM-dd hh:mm:ss");
            QSqlQuery queryInsertStats(bdd.getBase());
            if(!queryInsertStats.exec("INSERT INTO statistics (nom, valeur, version) VALUES (\"bacap_update\", \"" + qsDernierImport + "\", \"" + m_qsNumeroVersion + "\")")) {
                ui->qlDernierImportBacap->setVisible(false);
                afficherMessage(QMessageBox::Warning, "Impossible de mettre à jour la date d'import des progrès.\nLes progrès pour la version <strong>" + m_qsNumeroVersion + "</strong> ont bien été importés dans la base.", \
                                            "Voir les détails pour plus d'informations.", \
                                            queryInsertStats.lastError().text());
            } else {
                ui->qlDernierImportBacap->setText("Dernier Import : " + qdtDernierImportFR.toString("dd/MM/yyyy hh:mm:ss"));
                ui->qlDernierImportBacap->setVisible(true);
                afficherMessage(QMessageBox::Information, "Tous les progrès ont été inséré avec succès !", \
                                            "Les progrès de BACAP pour la version <strong>" + m_qsNumeroVersion + "</strong> sont maintenant en base");
            }
        }

        // Modification du bouton
        ui->qpbExtraireProgresBacap->setText("Ré-Importer Progrès");
        ui->qpbExtraireProgresBacap->setEnabled(true);
        m_bUpdateProgres = true;
        m_bProgresBlazeandcaveOK = true;
        // Info utilisateur
        ui->qlAdvancementsBacapExtrait->setText("Progrès importé !");
        ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: green; }");
        ui->qlAdvancementsBacapExtrait->setVisible(true);
        m_bProgresBlazeandcaveOK = true;
    } else if (!bErreurDelete && bErreurInsertionAdvancement) {
        afficherMessage(QMessageBox::Critical, "Impossible d'insérer tous les progrès pour la version <strong>" + m_qsNumeroVersion + "</strong>.", \
                                    "Voir les détails pour plus d'informations.", \
                                    qsLastErrorBdd + "\nDernières Requêtes :\n" + qsDerniereRequete);
        ui->qlDernierImportVanilla->setVisible(false);
        // Modification du bouton
        ui->qpbExtraireProgresBacap->setText("Importer Progrès");
        ui->qpbExtraireProgresBacap->setEnabled(true);
        m_bUpdateProgres = true;
        m_bProgresBlazeandcaveOK = true;
        // Info utilisateur
        ui->qlAdvancementsBacapExtrait->setText("Progrès non importé !");
        ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: red; }");
        ui->qlAdvancementsBacapExtrait->setVisible(true);
        m_bProgresBlazeandcaveOK = false;
    }

    // On remet les boutons actifs
    ui->qcbLauncher->setEnabled(true);
    ui->qcbLangue->setEnabled(true);
    ui->qcbVersion->setEnabled(true);
    ui->qpbExtraireProgresBacap->setEnabled(true);
    ui->qpbExtraireProgresBacap->setEnabled(true);
    ui->qpbImportProgresJoueur->setEnabled(true);
    // On supprime les widgets de la status bar
    m_statusBar->removeWidget(m_progressExtractionProgresVanilla);
    m_statusBar->removeWidget(m_labelExtractionProgresVanilla);
    m_statusBar->clearMessage();

    activationBoutonExtraction();

    QTime qtFin(QTime::currentTime());
    int iDuree = qtDebut.secsTo(qtFin);
    m_statusBar->showMessage("Durée écoulée : " + QString::number(iDuree), 10000);
}

/*
 *
 */
void FRM_Principale::importProgresPerso(bool checked) {
    if (checked) {
    }

    // TEST
    QTime qtDebut(QTime::currentTime());

    int iNombreProgresJoueur = 0, iNombreProgresTraite = 0;
    bool bErreurDelete = false, bErreurInsertionAdvancement = false;
    QString qsLastErrorBdd = "", qsDernierImport = "", qsDerniereRequete = "";

    m_progressExtractionProgresVanilla->setMinimum(0);
    m_progressExtractionProgresVanilla->setMaximum(0);
    m_progressExtractionProgresVanilla->setValue(0);
    m_labelExtractionProgresVanilla->setText("(\?\?/\?\?)");
    m_statusBar->clearMessage();
    m_statusBar->addWidget(m_progressExtractionProgresVanilla, 1);
    m_statusBar->insertWidget(99, m_labelExtractionProgresVanilla);
    m_progressExtractionProgresVanilla->show();
    m_labelExtractionProgresVanilla->show();

    ui->qcbLauncher->setEnabled(false);
    ui->qcbLangue->setEnabled(false);
    ui->qcbVersion->setEnabled(false);
    ui->qpbExtraireProgresVanilla->setEnabled(false);
    ui->qpbExtraireProgresBacap->setEnabled(false);
    ui->qpbImportProgresJoueur->setEnabled(false);
    ui->qpbReadJSONsVanilla->setEnabled(false);
    ui->qpbReadJSONsBlazeandcave->setEnabled(false);
    ui->qpbReadAllJSONs->setEnabled(false);

    if (m_bProgresPersoOK) {
        // DELETE
        QSqlQuery queryDelete(bdd.getBase());
        if (!queryDelete.exec("DELETE FROM player_advancements WHERE version = \"" + m_qsNumeroVersion + "\"")) {
            bErreurDelete = true;
            afficherMessage(QMessageBox::Critical, "Impossible de purger la base de données avant import.", \
                                        "Voir les détails pour plus d'informations.", \
                                        queryDelete.lastError().text());
        }
    }

    if (!bErreurDelete) {
        if (QFile::exists(m_qsFichierAdvancementsSolo)) {
            QString qsAdvancementPerso = m_qsFichierAdvancementsSolo;
            QVariantMap qvmProgrePerso = ouvrirJson(m_qsFichierAdvancementsSolo);

            if (m_ouvertureJson) {
                // On compte les progres
                QMapIterator<QString, QVariant> qmiIdentifiant(qvmProgrePerso);
                while (qmiIdentifiant.hasNext()) {
                    qmiIdentifiant.next();
                    QString qsIdentifiant = qmiIdentifiant.key();
                    if (!qsIdentifiant.contains("recipes") && !qsIdentifiant.contains("blazeandcave:technical") && !qsIdentifiant.contains("DataVersion")) {
                        iNombreProgresJoueur++;
                        m_labelExtractionProgresVanilla->setText("(0/" + QString::number(iNombreProgresJoueur) + ")");
                        QCoreApplication::processEvents();
                    }
                }

                m_progressExtractionProgresVanilla->setMaximum(iNombreProgresJoueur);
                m_labelExtractionProgresVanilla->setText("(0/" + QString::number(iNombreProgresJoueur) + ")");
                qmiIdentifiant.toFront();

                // On Import
                while (qmiIdentifiant.hasNext()) {
                    qmiIdentifiant.next();
                    QString qsIdentifiant = qmiIdentifiant.key();
                    if (!qsIdentifiant.contains("recipes") && !qsIdentifiant.contains("blazeandcave:technical") && !qsIdentifiant.contains("DataVersion")) {
                        QMap<QString, QVariant> qmIdentifiantPerso, qmCriteresPerso;
                        qmIdentifiantPerso = qvmProgrePerso[qsIdentifiant].toMap();
                        qmCriteresPerso = qmIdentifiantPerso["criteria"].toMap();
                        QString qsDone = qmIdentifiantPerso.value("done").toString();
                        QMapIterator<QString, QVariant> qmiCriteresPerso(qmCriteresPerso);
                        //qDebug() << "Identifiant :" << qsIdentifiant << "Done :" << qsDone;
                        qDebug() << qsIdentifiant;
                        while (qmiCriteresPerso.hasNext()) {
                            qmiCriteresPerso.next();
                            QString qsNomCriteres = qmiCriteresPerso.key();
                            QDateTime qdtDateCriteres = qmiCriteresPerso.value().toDateTime();

                            QSqlQuery queryInsert(bdd.getBase());
                            queryInsert.prepare("INSERT INTO player_advancements (version, identifiant, done, condition, date_fait) "
                                          "VALUES (:version, :identifiant, :done, :condition, :date_fait)");
                            queryInsert.bindValue(":version", m_qsNumeroVersion);
                            queryInsert.bindValue(":identifiant", qsIdentifiant);
                            queryInsert.bindValue(":done", qsDone);
                            queryInsert.bindValue(":condition", qsNomCriteres);
                            queryInsert.bindValue(":date_fait", qdtDateCriteres.toString("yyyy-MM-dd hh:m:ss"));
                            if(!bErreurInsertionAdvancement) {
                                if(!queryInsert.exec()) {
                                    bErreurInsertionAdvancement = true;
                                    qsLastErrorBdd = queryInsert.lastError().text();
                                    qsDerniereRequete = queryInsert.executedQuery();
                                }
                            }

                            QCoreApplication::processEvents();
                            //qDebug() << "\t" << "Nom :" << qsNomCriteres << "Date :" << qdtDateCriteres;
                        }
                        //qDebug() << "Identifiant :" << qsIdentifiant << "Done :" << qsDone << "Criteres :" << qmCriteresPerso;
                        iNombreProgresTraite++;
                        m_labelExtractionProgresVanilla->setText("(" + QString::number(iNombreProgresTraite) + "/" + QString::number(iNombreProgresJoueur) + ")");
                        m_progressExtractionProgresVanilla->setValue(m_progressExtractionProgresVanilla->value()+1);
                    }
                }
            }
        } else {
            afficherMessage(QMessageBox::Critical, "Fichier progrès perso n'existe pas.", "Assurez-vous que le fichier existe. L'avez-vous renommer ou supprimer entre temps ?");
            m_bProgresPersoOK = false;
        }

        if (!bErreurInsertionAdvancement) {
            QSqlQuery queryDeleteStats(bdd.getBase());
            if(!queryDeleteStats.exec("DELETE FROM statistics WHERE nom = \"player_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
                ui->qlDernierImportPerso->setVisible(false);
                afficherMessage(QMessageBox::Warning, "Impossible de mettre à jour la date d'import des progrès.\nLes progrès pour la version <strong>" + m_qsNumeroVersion + "</strong> ont bien été importés dans la base.", \
                                            "Voir les détails pour plus d'informations.", \
                                            queryDeleteStats.lastError().text());
            } else {
                qsDernierImport = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QDateTime qdtDernierImportFR = QDateTime::fromString(qsDernierImport, "yyyy-MM-dd hh:mm:ss");
                QSqlQuery queryInsertStats(bdd.getBase());
                if(!queryInsertStats.exec("INSERT INTO statistics (nom, valeur, version) VALUES (\"player_update\", \"" + qsDernierImport + "\", \"" + m_qsNumeroVersion + "\")")) {
                    ui->qlDernierImportPerso->setVisible(false);
                    afficherMessage(QMessageBox::Warning, "Impossible de mettre à jour la date d'import des progrès.\nLes progrès pour la version <strong>" + m_qsNumeroVersion + "</strong> ont bien été importés dans la base.", \
                                                "Voir les détails pour plus d'informations.", \
                                                queryInsertStats.lastError().text());
                } else {
                    ui->qlDernierImportPerso->setText("Dernier Import : " + qdtDernierImportFR.toString("dd/MM/yyyy hh:mm:ss"));
                    ui->qlDernierImportPerso->setVisible(true);
                    afficherMessage(QMessageBox::Information, "Tous les progrès ont été inséré avec succès !", \
                                                "Vos progrès Perso pour la version <strong>" + m_qsNumeroVersion + "</strong> sont maintenant en base");
                }
            }

            // Modification du bouton
            ui->qpbExtraireProgresBacap->setText("Ré-Importer Progrès");
            ui->qpbExtraireProgresBacap->setEnabled(true);
            // Info utilisateur
            ui->qlProgresPerso->setText("Progrès importé !");
            ui->qlProgresPerso->setStyleSheet("QLabel { color: green; }");
            ui->qlProgresPerso->setVisible(true);
            m_bProgresPersoOK = true;
        } else {
            afficherMessage(QMessageBox::Critical, "Impossible d'insérer tous vos progrès pour la version <strong>" + m_qsNumeroVersion + "</strong>.", \
                                        "Voir les détails pour plus d'informations.", \
                                        qsLastErrorBdd + "\nDernières Requêtes :\n" + qsDerniereRequete);
            ui->qlDernierImportVanilla->setVisible(false);
            // Modification du bouton
            ui->qpbExtraireProgresBacap->setText("Importer Progrès");
            ui->qpbExtraireProgresBacap->setEnabled(true);
            // Info utilisateur
            ui->qlProgresPerso->setText("Progrès non importé !");
            ui->qlProgresPerso->setStyleSheet("QLabel { color: red; }");
            ui->qlProgresPerso->setVisible(true);
            m_bProgresPersoOK = false;
        }
    }

    // On remet les boutons actifs
    ui->qcbLauncher->setEnabled(true);
    ui->qcbLangue->setEnabled(true);
    ui->qcbVersion->setEnabled(true);
    ui->qpbExtraireProgresVanilla->setEnabled(true);
    ui->qpbExtraireProgresBacap->setEnabled(true);
    ui->qpbImportProgresJoueur->setEnabled(true);
    // On supprime les widgets de la status bar
    m_statusBar->removeWidget(m_progressExtractionProgresVanilla);
    m_statusBar->removeWidget(m_labelExtractionProgresVanilla);
    m_statusBar->clearMessage();
    traitementFichierAdvancements(m_qsFichierAdvancementsSolo);

    QTime qtFin(QTime::currentTime());
    int iDuree = qtDebut.secsTo(qtFin);
    m_statusBar->showMessage("Durée écoulée : " + QString::number(iDuree), 10000);
}
/*
 * Slots lors du choix pour les milestones et statistics pour BACAP
 */
void FRM_Principale::exclureStats(int statut) {
    if (statut) {
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

    param->setMilestones(ui->qcbMilestones->isChecked());
    param->setStatistics(ui->qcbStatistiques->isChecked());
}

/*
 * Slots lors du choix du fichier des progrès perso
 */
void FRM_Principale::choixFichierAdvancements(bool checked) {
    if (checked) {
    }
    QString qsTypeFichierProgres;
    qsTypeFichierProgres = tr("Fichier JSON (*.json)");

    QString qsFichierAdvancementsPerso = QFileDialog::getOpenFileName(this, tr("Choisir le fichier de vos progrès"),
                                                    m_qsDossierMinecraft,
                                                    qsTypeFichierProgres);

    traitementFichierAdvancements(qsFichierAdvancementsPerso);

    param->setFichierAdvancementsPerso(qsFichierAdvancementsPerso);

}

/*
 * Slots pour comparer tous les progrès Vanilla
 */
void FRM_Principale::readJSONsVanilla(bool checked) {
    if (checked) {
    }

    afficherMessage(QMessageBox::Information, "Ce bouton est désactivé !", "Réécriture à faire !");

    /*ui->qcbFiltreOrigine->disconnect();
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
    QVariantMap qvmJsonLang = ouvrirJson(m_qsFichierLang);

     * Tout stocké dans un QStringList

    toutesLesTraductions(qvmJsonLang);

    QDirIterator qdiFichierProgres(m_qdDossierAdvancedments.path(), qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

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
            qsTitre.replace("’", "'");

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

                    if (qsConditionSimple.contains("/")) {
                        QStringList qslConditionSansChemin = qsConditionSimple.split("/");
                        qsiCondition->setText(qslConditionSansChemin.last().split(".").first());
                        qsiCondition->setIcon(QIcon(qsConditionSimple));
                        qsiCondition->setToolTip("<img src=\"" + qsConditionSimple + "\" width=\"167\" height=\"100\">");
                    } else {
                        qsiCondition->setText(qsConditionSimple);
                    }


                     * Rechercher la traduction
                     * Si trouvé : on la met
                     * Sinon     : on mets qsConditionSimple

                    int index = m_qslClesToutesLesTrads.indexOf(QRegExp(".+\\.minecraft(\\..+)?\\." + qsConditionSimple + "$"));
                    if (index != -1) {
                        qsiCondition->setText(m_qslToutesLesTrads.at(index));
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
                            //qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                            qsiConditionRemplie->setText("oui");
                            //qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                            qsiDateRealisation->setData(qdtDateRealisation, Qt::DisplayRole);
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        }
                    } else if (bCriteresPersoExiste) {
                        if (qsDateRealisation != "") {
                            //qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";oui;" + qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss");
                            qsiConditionRemplie->setText("oui");
                            //qsiDateRealisation->setText(qdtDateRealisation.toString("dd/MM/yyyy à hh:mm:ss"));
                            qsiDateRealisation->setData(qdtDateRealisation, Qt::DisplayRole);
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        } else {
                            //qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
                            qsiConditionRemplie->setText("non");
                            m_qlLigneProgres << qsiOrigine << qsiTitre << qsiProgreFini << qsiCondition << qsiConditionRemplie << qsiDateRealisation << qsiTypeCondition;
                            m_qsimProgresRealisation->appendRow(m_qlLigneProgres);
                        }
                    } else {
                        //qDebug() << "Minecraft Vanilla;" + qsTitreAvecDescription + ";" + qsProgresFini + ";" + qsCondition + ";non;";
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
    }*/
}

/*
 * Slots pour comparer tous les progrès BACAP
 */
void FRM_Principale::readJSONsBlazeandcave(bool checked) {
    if (checked) {
    }

    afficherMessage(QMessageBox::Information, "Ce bouton est désactivé !", "Réécriture à faire !");

    /*if (!bTousLesProgres) {
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

    QVariantMap qvmJsonLangVanilla = ouvrirJson(m_qsFichierLang);

     * Tout stocké dans un QStringList

    toutesLesTraductions(qvmJsonLangVanilla);

    QString qsJsonLang = "rcs/blazeandcave-fr_fr.json";
    QFile qfLangUs(qsJsonLang);
    if(!qfLangUs.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<< qsJsonLang;
        exit(1);
    }

    QTextStream qtsLang(&qfLangUs);
    QString qsJsonLangUs;
    qsJsonLangUs = qtsLang.readAll();
    qsJsonLangUs = qsJsonLangUs.replace(QRegularExpression("#.+?\r\n"), "");
    qDebug() << qsJsonLangUs;
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

                qsTitre.replace("’", "'");

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


                     * Rechercher la traduction
                     * Si trouvé : on la met
                     * Sinon     : on mets qsConditionSimple

                    int index = m_qslClesToutesLesTrads.indexOf(QRegExp(".+\\.minecraft(\\..+)?\\." + qsConditionSimple + "$"));
                    if (index != -1) {
                        //qDebug() << "Trad" << qslClesToutesLesTrads.at(index) << "=>" << qslToutesLesTrads.at(index) << "(" + qsConditionSimple + ")";
                        qsiCondition->setText(m_qslToutesLesTrads.at(index));
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
    }*/
}

/*
 * Slots pour comparer tous les progrès (Vanilla + BCAP)
 */
void FRM_Principale::readAllJsons(bool checked) {
    if (checked) {
    }

    afficherMessage(QMessageBox::Information, "Ce bouton est désactivé !", "Réécriture à faire !");

    /*bTousLesProgres = true;

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

    bTousLesProgres = false;*/
}

/*
 * Slots lors de la modification du filtre sur l'origine (Vanilla ou BCAP)
 */
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

/*
 * Slots lors du filtre sur le titre
 */
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

/*
 * Slots lors du filtre si progrès finis (oui/non)
 */
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

/*
 * Slots lors du filtre si condition faite (oui/non)
 */
void FRM_Principale::filtreTableConditionFait(QString filtre) {
    proxyModelFiltreConditionFaite->setFilterKeyColumn(4);
    proxyModelFiltreConditionFaite->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
    if (ui->qcbFiltreType->currentText() != "") {
        filtreTableTypeCondition(ui->qcbFiltreType->currentText());
    }
}

/*
 * Slots lors du filtre sur le type de condition (ET/OU/UN)
 */
void FRM_Principale::filtreTableTypeCondition(QString filtre) {
    proxyModelFiltreTypeCondition->setFilterKeyColumn(6);
    proxyModelFiltreTypeCondition->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
}

/*
 * Slots lors du filtre sur les dates
 */
void FRM_Principale::dateFilterChanged()
{
    proxyModelFiltreDate->setFilterMinimumDate(ui->qdteFrom->dateTime());
    proxyModelFiltreDate->setFilterMaximumDate(ui->qdteTo->dateTime());
}

/*
 * Slots lors du clique sur le bouton "Effacer les filtres"
 */
void FRM_Principale::effacerLesFiltres(bool checked) {
    if (checked) {
    }

    ui->qcbFiltreOrigine->setCurrentIndex(0);
    ui->qcbFiltreTitre->setCurrentText(0);
    ui->qcbFiltreProgresFinis->setCurrentIndex(0);
    ui->qcbFiltreConditionFait->setCurrentIndex(0);
    ui->qcbFiltreType->setCurrentIndex(0);
    effacerFiltreDate();
}

/*
 * Slots lors du clique sur le bouton "Reset dates"
 */
void FRM_Principale::effacerFiltresSurLesDates(bool checked) {
    if (checked) {
    }

    effacerFiltreDate();
}

void FRM_Principale::etatAutoCompletion(int etat) {
    if (etat == 0) {
        // Unchecked - Désactivation
        ui->qcbFiltreTitre->setCompleter(m_sansCompleter);
    } else {
        QStringList qslListCompleter;
        // Checked - Activation
        m_defaultCompleter->setModel(ui->qcbFiltreTitre->model());
        m_defaultCompleter->setCompletionMode(QCompleter::PopupCompletion);
        m_defaultCompleter->setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
        ui->qcbFiltreTitre->setCompleter(m_defaultCompleter);
    }
}

void FRM_Principale::dataSelectionnee(const QModelIndex index) {
    QModelIndex qmiTitre = proxyModelFiltreDate->index(index.row(), 1);
    QString qsTitreDisplay = proxyModelFiltreDate->data(qmiTitre, Qt::DisplayRole).toString();
    QString qsTitreData = proxyModelFiltreDate->data(qmiTitre, Qt::UserRole).toString();

    qsTitreDisplay.replace(QRegularExpression(" \\(.+\\)"), "");
}

void FRM_Principale::imprimerTable(bool checked) {
    if (checked) {
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
    if (param->getMiseAJourBeta() && !m_updateBetaVerifiee) {
        url.setUrl("https://advancements.blackwizard.fr/repository/beta/Updates.xml");
        m_updateBetaVerifiee = true;
    } else {
        url.setUrl("https://advancements.blackwizard.fr/repository/release/Updates.xml");
        m_updateBetaVerifiee = false;
    }
    QNetworkRequest request;

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
            QMessageBox::critical(this, "Mise à jour", "Erreur lors de la vérification des mises à jour.");
            return;
        } else {
            qfUpdateXml.write(m_qbaDonneesTelechargees);
            qfUpdateXml.close();
        }
    }

    if(qfUpdateXml.open(QIODevice::ReadOnly)){
        qddXmlBOM.setContent(m_qbaDonneesTelechargees);
    } else {
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
    //TEST
    //qsVersionLocal = "0.2.4.1";
    //qsVersionOnline = "0.2.4.1";
    qslVersionOnline = qsVersionOnline.split(".");
    qslVersionLocal = qsVersionLocal.split(".");

    if (qsVersionOnline.count() > qsVersionLocal.count()) {
        int diff = qsVersionOnline.count() - qsVersionLocal.count();
        for (int ite = 0 ; ite < diff ; ite++) {
            qslVersionLocal << "0";
        }
    }

    for(int i = 0; i < qslVersionOnline.size(); i++) {
        if(!bMiseAJourNecessaire) {
            if(qslVersionOnline.at(i).toInt() > qslVersionLocal.at(i).toInt()) {
                bMiseAJourNecessaire = true;
            }
        }
    }

    // On définis la dernière vérification des mises à jour, même si c'est une vérification manuelle
    param->setDerniereVerificationMiseAJour(QDate::currentDate());

    if(bMiseAJourNecessaire){
        if(QMessageBox::question(this, "Mise à jour disponible", "La version " + qsVersionOnline + " est disponible.\n Voulez-vous mettre à jour ?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
            QMessageBox::information(this, "Mise à jour", "L'outils de maintenance va s'ouvrir pour vous guider dans la mise à jour.");
            QProcess *qpOutilDeMaintenance = new QProcess();
            QStringList arguments;
            arguments << "--updater";
            if (param->getMiseAJourBeta()) {
                arguments << "--addTempRepository";
                arguments << "https://advancements.blackwizard.fr/repository/beta";
            }
            qpOutilDeMaintenance->setProgram("maintenancetool.exe");
            qpOutilDeMaintenance->setArguments(arguments);
            qpOutilDeMaintenance->startDetached();

            // Fermer la fenêtre
            emit fermeture();
            if(ouvertureEnCours)
                exit(1);
        }
    } else {
        if(!ouvertureEnCours && !m_updateBetaVerifiee)
            QMessageBox::information(this, "Pas de nouvelle version", "La version <strong>" + qsVersionLocal + "</strong> est la plus récente.");

        if (m_updateBetaVerifiee) {
            verifierMiseAJour();
        }
    }
}

/*
 *
 */
void FRM_Principale::dockWidgetOperationFloating(bool floating) {
    if (floating) {
        ui->qdwOpe->resize(0, ui->qdwOpe->height());
    }
    param->setDockIsFloating(floating);
}

/*
 *
 */
//void FRM_Principale::dockWidgetOperationClosing(bool closing) {
//    qDebug() << closing;
//}

/*  ~~~~~~~~~~~~~
 *  | FONCTIONS |
 *  ~~~~~~~~~~~~~
 */

QVariantMap FRM_Principale::ouvrirJson(QString fichier) {
    QFile qfFichierJson(fichier);
    QJsonParseError *error = new QJsonParseError();
    m_ouvertureJson = false;
    if(!qfFichierJson.open(QIODevice::ReadOnly)){
        //qDebug()<<"Failed to open "<< fichier;
        afficherMessage(QMessageBox::Critical, "Ouverture fichier JSON en échec", "Impossible d'ouvrir le fichier");
        return QVariantMap();
        //exit(1);
    } else {
        QTextStream qtsFichier(&qfFichierJson);
        QString qsFichierJson;
        qsFichierJson = qtsFichier.readAll();
        qfFichierJson.close();
        QByteArray qbaFichierJson = qsFichierJson.toLocal8Bit();

        QJsonDocument qjdFichierJson = QJsonDocument::fromJson(qbaFichierJson, error);

        if(qjdFichierJson.isNull()){
            //qDebug()<<"Failed to create JSON doc. Fichier :" << fichier;
            //qDebug() << error->errorString();
            afficherMessage(QMessageBox::Critical, "Ouverture fichier JSON en échec", "Impossible de créer le document JSON", error->errorString());
            return QVariantMap();
            //exit(2);
        } else {
            if(!qjdFichierJson.isObject()){
                qDebug()<<"JSON is not an object.";
                return QVariantMap();
            } else {
                QJsonObject qjsFichierJson = qjdFichierJson.object();

                if(qjsFichierJson.isEmpty()){
                    qDebug()<<"JSON object is empty.";
                    return QVariantMap();
                } else {
                    m_ouvertureJson = true;
                    return qjsFichierJson.toVariantMap();
                }
            }
        }
    }
}

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
                bOuvertureJson = false;
            } else {
                if(!qjdJsonPerso.isObject()){
                    bOuvertureJson = false;
                } else {
                    QJsonObject qjsJsonPerso = qjdJsonPerso.object();

                    if(qjsJsonPerso.isEmpty()){
                        bOuvertureJson = false;
                    } else {
                        qvmIndexes = qjsJsonPerso.toVariantMap();
                    }
                }
            }
        }
    }
    QMap<QString, QVariant> qvmAssetIndex = qvmIndexes["assetIndex"].toMap();

    return qvmAssetIndex["id"].toString();
}

/*
 * Fonction pour récupérer le hash du fichier de langue
 */
QString FRM_Principale::hashLangue() {
    bool bOuvertureJson = true;
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

    return qvmLang["hash"].toString();
}

/*
 * Fonction qui traite le dossier choisis par l'utilisateur du BAC
 */
void FRM_Principale::traitementDossierBac(QString folder) {
    m_qdDossierAdvancementsBlazeAndCave.setPath(folder + "\\data\\blazeandcave\\advancements");

    if (m_qdDossierAdvancementsBlazeAndCave.exists()) {
        ui->qpbExtraireProgresBacap->setEnabled(true);
        QSqlQuery qsqCompteProgresBacap(bdd.getBase()), qsqDernierImportBacap(bdd.getBase());
        QStringList qslFauxDossier = folder.split("/");
        QString qsFauxDossier = qslFauxDossier.first() + "\\fake_Path\\" + qslFauxDossier.last();
        ui->qleDossierBlazeandcave->setText(qsFauxDossier);

        if (qsqCompteProgresBacap.exec("SELECT COUNT(1) progresImporte FROM statistics WHERE nom = \"bacap_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
            qsqCompteProgresBacap.next();
            int iNombreEnregistrement = qsqCompteProgresBacap.value("progresImporte").toInt();
            if (iNombreEnregistrement > 0) {
                QSqlQuery qsqLangueImporte(bdd.getBase());
                if (qsqLangueImporte.exec("SELECT COUNT(1) nbrTraduction FROM traduction_vanilla WHERE version = '" + m_qsNumeroVersion + "'")) {
                    qsqLangueImporte.next();
                    if (qsqLangueImporte.value("nbrTraduction").toInt() <= 0) {
                        ui->qpbExtraireProgresBacap->setText("Importer Progrès");
                        ui->qpbExtraireProgresBacap->setEnabled(false);
                        // Info utilisateur
                        ui->qlAdvancementsBacapExtrait->setText("La langue de Minecraft n'est pas en base ! Relancer l'import Minecraft Vanilla");
                        ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: orange; }");
                        ui->qlAdvancementsBacapExtrait->setVisible(true);
                        m_bProgresBlazeandcaveOK = false;
                    } else {
                        if (qsqDernierImportBacap.exec("SELECT valeur FROM statistics WHERE nom = \"bacap_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
                            qsqDernierImportBacap.next();
                            QString qsDernierImport = qsqDernierImportBacap.value("valeur").toString();
                            QDateTime qdtDernierImport = QDateTime::fromString(qsDernierImport, "yyyy-MM-dd hh:mm:ss");
                            if (qdtDernierImport.isValid()) {
                                ui->qlDernierImportBacap->setText("Dernier Import : " + qdtDernierImport.toString("dd/MM/yyyy hh:mm:ss"));
                                ui->qlDernierImportBacap->setVisible(true);
                                // Modification du bouton
                                ui->qpbExtraireProgresBacap->setText("Ré-Importer Progrès");
                                ui->qpbExtraireProgresBacap->setEnabled(true);
                                m_bUpdateProgres = true;
                                m_bProgresBlazeandcaveOK = true;
                                // Info utilisateur
                                ui->qlAdvancementsBacapExtrait->setText("Progrès importé !");
                                ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: green; }");
                                ui->qlAdvancementsBacapExtrait->setVisible(true);
                                m_bProgresBlazeandcaveOK = true;
                            } else {
                                ui->qlDernierImportBacap->setVisible(false);
                                // Modification du bouton
                                ui->qpbExtraireProgresBacap->setText("Ré-Importer Progrès");
                                ui->qpbExtraireProgresBacap->setEnabled(true);
                                m_bUpdateProgres = true;
                                m_bProgresBlazeandcaveOK = true;
                                // Info utilisateur
                                ui->qlAdvancementsBacapExtrait->setText("Import progrès incomplet !");
                                ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: orange; }");
                                ui->qlAdvancementsBacapExtrait->setVisible(true);
                                m_bProgresBlazeandcaveOK = false;
                            }
                        } else {
                            m_bProgresBlazeandcaveOK = false;
                            afficherMessage(QMessageBox::Warning, "Impossible de récupérer la date de dernier import des progrès Minecraft Vanilla.", \
                                                        "Voir les détails pour plus d'informations.", \
                                                        qsqDernierImportBacap.lastError().text());
                            ui->qlDernierImportBacap->setVisible(false);
                        }
                    }
                } else {
                    m_bProgresBlazeandcaveOK = false;
                    afficherMessage(QMessageBox::Warning, "Impossible de récupérer la date de dernier import des progrès Minecraft Vanilla.", \
                                                "Voir les détails pour plus d'informations.", \
                                                qsqDernierImportBacap.lastError().text());
                    ui->qlDernierImportBacap->setVisible(false);
                }
            } else {
                ui->qlDernierImportBacap->setVisible(false);
                // Modification du bouton
                ui->qpbExtraireProgresBacap->setText("Importer Progrès");
                ui->qpbExtraireProgresBacap->setEnabled(true);
                m_bUpdateProgres = true;
                m_bProgresBlazeandcaveOK = true;
                // Info utilisateur
                ui->qlAdvancementsBacapExtrait->setText("Progrès non importé !");
                ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: red; }");
                ui->qlAdvancementsBacapExtrait->setVisible(true);
                m_bProgresBlazeandcaveOK = false;
            }
        } else {
            m_bProgresBlazeandcaveOK = false;
            afficherMessage(QMessageBox::Critical, "Impossible de vérifier si les progrès ont déjà étés importés.", \
                                        "Contacter <a href=\"https://github.com/Chucky2401/Minecraft-Advancements/issues/new?title=Erreur contrôle import progrès&body=" + qsqDernierImportBacap.lastError().text() + "\n\nRemarque personnel :\n\">le développeur</a>.", \
                                        qsqDernierImportBacap.lastError().text());
            ui->qlDernierImportBacap->setVisible(false);
        }
    } else {
        ui->qlDernierImportBacap->setVisible(false);
        // Modification du bouton
        ui->qpbExtraireProgresBacap->setText("Importer Progrès");
        ui->qpbExtraireProgresBacap->setEnabled(true);
        m_bUpdateProgres = true;
        m_bProgresBlazeandcaveOK = true;
        // Info utilisateur
        ui->qlAdvancementsBacapExtrait->setText("Progrès non importé !");
        ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: red; }");
        ui->qlAdvancementsBacapExtrait->setVisible(true);
        m_bProgresBlazeandcaveOK = false;
    }

    activationBoutonExtraction();
}

/*
 * Fonction qui traite le choix de l'utilisateur sur son fichier d'advancements
 */
void FRM_Principale::traitementFichierAdvancements(QString fichier) {
    QStringList qslDossierSauvegardeTemp;
    QString qsFauxDossierSauvegarde;
    QStringList qslFormatFichier, qslFauxChemin;
    QString qsFauxChemin;
    QSqlQuery qsqCompteProgresPerso(bdd.getBase()), qsqDernierImportPerso(bdd.getBase());

    qslFormatFichier << "*.json";

    m_qsFichierAdvancementsSolo = fichier;
    qslFauxChemin = m_qsFichierAdvancementsSolo.split("/");
    qsFauxChemin = qslFauxChemin.first() + "\\Fake_Path\\" + qslFauxChemin.last();
    ui->qleFichierProgres->setText(qsFauxChemin);

    // On vérifie d'abord si déjà importé
    if (qsqCompteProgresPerso.exec("SELECT COUNT(1) progresImporte FROM statistics WHERE nom = \"player_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
        qsqCompteProgresPerso.next();
        int iNombreEnregistrement = qsqCompteProgresPerso.value("progresImporte").toInt();
        if (iNombreEnregistrement > 0) {
            if (qsqDernierImportPerso.exec("SELECT valeur FROM statistics WHERE nom = \"player_update\" AND version = \"" + m_qsNumeroVersion + "\"")) {
                qsqDernierImportPerso.next();
                QString qsDernierImport = qsqDernierImportPerso.value("valeur").toString();
                QDateTime qdtDernierImport = QDateTime::fromString(qsDernierImport, "yyyy-MM-dd hh:mm:ss");
                if (qdtDernierImport.isValid()) {
                    ui->qlDernierImportPerso->setText("Dernier Import : " + qdtDernierImport.toString("dd/MM/yyyy hh:mm:ss"));
                    ui->qlDernierImportPerso->setVisible(true);
                    // Modification du bouton
                    ui->qpbImportProgresJoueur->setText("Ré-Importer Progrès");
                    ui->qpbImportProgresJoueur->setEnabled(true);
                    m_bUpdateProgres = true;
                    // Info utilisateur
                    ui->qlProgresPerso->setText("Progrès importé !");
                    ui->qlProgresPerso->setStyleSheet("QLabel { color: green; }");
                    ui->qlProgresPerso->setVisible(true);
                    m_bProgresPersoOK = true;
                } else {
                    ui->qlDernierImportPerso->setVisible(false);
                    // Modification du bouton
                    ui->qpbImportProgresJoueur->setText("Ré-Importer Progrès");
                    ui->qpbImportProgresJoueur->setEnabled(true);
                    m_bUpdateProgres = true;
                    // Info utilisateur
                    ui->qlProgresPerso->setText("Import progrès incomplet !");
                    ui->qlProgresPerso->setStyleSheet("QLabel { color: orange; }");
                    ui->qlProgresPerso->setVisible(true);
                    m_bProgresPersoOK = false;
                }
            } else {
                m_bProgresPersoOK = false;
                afficherMessage(QMessageBox::Warning, "Impossible de récupérer la date de dernier import des progrès Minecraft Vanilla.", \
                                            "Voir les détails pour plus d'informations.", \
                                            qsqDernierImportPerso.lastError().text());
                ui->qlDernierImportPerso->setVisible(false);
            }
        } else {
            // Modification du bouton
            ui->qpbImportProgresJoueur->setText("Importer Progrès");
            ui->qpbImportProgresJoueur->setEnabled(true);
            m_bUpdateProgres = true;
            // Info utilisateur
            ui->qlProgresPerso->setText("Progrès non importé !");
            ui->qlProgresPerso->setStyleSheet("QLabel { color: red; }");
            ui->qlProgresPerso->setVisible(true);
            ui->qlDernierImportPerso->setVisible(false);
            m_bProgresPersoOK = false;
        }
    }

    activationBoutonExtraction();
}

/*
 * Fonction pour activer les boutons d'extraction suivant des booléens
 */
void FRM_Principale::activationBoutonExtraction() {
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

/*
 * Fonction pour récupérer toutes les traductions de Minecraft dans deux QStringList
 */
void FRM_Principale::toutesLesTraductions(QVariantMap jsonLang) {
    //m_qslClesToutesLesTrads.clear();
    //m_qslToutesLesTrads.clear();
    QSqlQuery qsqInsertTraduction(bdd.getBase()), qsqDeleteTraduction(bdd.getBase());
    QString qsLastQueryError = "";
    bool bQueryInsertKO = false;
    int iLangueImporte = 0;

    if (qsqDeleteTraduction.exec("DELETE FROM traduction_vanilla WHERE version = \"" + m_qsNumeroVersion + "\"")) {
        QMapIterator<QString, QVariant> i(jsonLang);
        while (i.hasNext()) {
            i.next();
            QString qsKey = i.key(), qsValue = i.value().toString();
            qsValue.replace(QRegExp("\\\"(@|%)?.+\\\""), "");

            if (!qsqInsertTraduction.exec("INSERT INTO traduction_vanilla (version, key, value) VALUES (\"" + m_qsNumeroVersion + "\", \"" + qsKey + "\", \"" + qsValue + "\")")) {
                bQueryInsertKO = true;
                qsLastQueryError = qsqInsertTraduction.lastError().text();
                qDebug() << "Traduction valeur en échec : " << qsValue;
            }
            iLangueImporte++;
            m_labelExtractionProgresVanilla->setText("Langue importé : " + QString::number(iLangueImporte) + "/\?\?");
            QCoreApplication::processEvents();
        }
    } else {
        afficherMessage(QMessageBox::Critical, "Erreur suppression langue", "Voir les détails", qsqDeleteTraduction.lastError().text());
    }

    if (bQueryInsertKO) {
        afficherMessage(QMessageBox::Critical, "Erreur insertion traduction langue", "Voir les détails", qsLastQueryError);
    } else {
        ui->qpbExtraireProgresBacap->setEnabled(false);
        traitementDossierBac(m_qdDossierAdvancementsBlazeAndCave.path().replace("/data/blazeandcave/advancements", ""));
    }
}

/*
 * Mettre toutes les traductions dans des listes
 * Obligatoire pour pouvoir utiliser des Regex
 */
void FRM_Principale::toutesLesTraductionsListe() {
    m_qslClesToutesLesTrads.clear();
    m_qslToutesLesTrads.clear();

    QSqlQuery qsqTraduction(bdd.getBase());
    int iLangueImporte = 0;

    if (qsqTraduction.exec("SELECT key, value FROM traduction_vanilla WHERE version = '" + m_qsNumeroVersion + "'")) {
        while (qsqTraduction.next()) {
            m_qslClesToutesLesTrads << qsqTraduction.value("key").toString();
            m_qslToutesLesTrads << qsqTraduction.value("value").toString();

            iLangueImporte++;
            m_labelExtractionProgresVanilla->setText("Remplissage liste Langue : " + QString::number(iLangueImporte) + "/\?\?");
            QCoreApplication::processEvents();
        }
    }
}

/*
 * Fonctions pour effecer le filtre sur les dates
 */
void FRM_Principale::effacerFiltreDate() {
    ui->qdteFrom->setDateTime(QDateTime(QDate(1970, 01, 01), QTime(0, 0, 0)));
    ui->qdteTo->setDateTime(QDateTime(QDate(2099, 12, 31), QTime(23, 59, 59)));
    proxyModelFiltreDate->effacerFiltreDate();
}

/*
 * Afficher une QMessageBox
 */
void FRM_Principale::afficherMessage(int type, QString text, QString information, QString detail) {
    switch (type) {
        case 1 :
            m_qmbMessage.setIcon(QMessageBox::Information);
            break;
        case 2 :
            m_qmbMessage.setIcon(QMessageBox::Warning);
            break;
        case 3 :
            m_qmbMessage.setIcon(QMessageBox::Critical);
            break;
        case 4 :
            m_qmbMessage.setIcon(QMessageBox::Question);
            break;
        default :
            m_qmbMessage.setIcon(QMessageBox::NoIcon);
    }
    m_qmbMessage.setText("<strong>"+ text + "</strong>");
    m_qmbMessage.setInformativeText(information);
    m_qmbMessage.setDetailedText(detail);
    m_qmbMessage.exec();
}

/*
 * Utiliser dans le bouton de test
 */
void FRM_Principale::TEST(bool checked) {
    if (checked) {
    }

    qDebug() << "Is Floating:" << ui->qdwOpe->isFloating() << "Geometry:" << ui->qdwOpe->geometry();

    //plainModel->setQuery("SELECT * FROM Test WHERE condition = 'minecraft:badlands'", bdd.getBase());

    //qDebug() << param->getPath();
    //QString detailSQLTest = "Je suis une erreur SQL";
    QStringList qslLignesValide;
    QFile inputFile("rcs/blazeandcave-fr_fr.json");
    bool bEcrireFichier = false;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          //qDebug() << line;
          if (!line.contains(QRegExp("^( +#.+| +$|\n$|$)"))) {
              qslLignesValide << line;
          } else {
              bEcrireFichier = true;
          }
       }
       inputFile.close();

       if (bEcrireFichier) {
           if (inputFile.open(QIODevice::WriteOnly)) {
               QTextStream out(&inputFile);
               for (int i = 0; i < qslLignesValide.count(); i++) {
                   out << qslLignesValide.at(i) << "\n";
               }
           }
       } else {
           qDebug() << "Pas besoin, clear !";
       }
       inputFile.close();
    }

//    QSqlQuery queryTest(bdd.getBase());
//    qDebug() << bdd.getDriver()->hasFeature(QSqlDriver::QuerySize);

//    if (!queryTest.exec("DROP VIEW main.Test")) {
//    }

//    if (!queryTest.exec("CREATE VIEW Test AS SELECT * FROM list_advancements WHERE identifiant = \"minecraft:adventure/adventuring_time\"")) {
//    }


//    qDebug() << queryTest.size();

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
