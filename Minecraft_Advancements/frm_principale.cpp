#include "frm_principale.h"
#include "ui_frm_principale.h"

FRM_Principale::FRM_Principale(QWidget *parent, bool test)
    : QMainWindow(parent)
    , ui(new Ui::FRM_Principale), m_test(test) {

    ouvertureEnCours = true;

    // Quelques réglages de bases sur la fenêtre
    ui->setupUi(this);
    m_qsArchitecture = QSysInfo::buildCpuArchitecture();
    m_statusBar = this->statusBar();
    m_statusBar->setStyleSheet("QStatusBar { background: #E0E0E0; }");
    this->setStatusBar(m_statusBar);
    m_statusBar->showMessage("Bonjour et bienvenue dans Minecraft Advancements !", 5000);
    m_progressExtractionProgresVanilla = new QProgressBar();
    m_progressExtractionProgresVanilla->setStyleSheet("QProgressBar { border: 2px solid #8BC34A; border-radius: 5px; text-align: center; height: 10px; } QProgressBar::chunk { background-color: #33cc33; }");
    m_labelExtractionProgresVanilla = new QLabel("");
    this->setStyleSheet("QMainWindow { background-image: url(:/img/wallpaper.png); background-position: bottom right; background-repeat: none; }");

    QAction *qaDockOperation = ui->qdwOpe->toggleViewAction();
    qaDockOperation->setText("Afficher/Masquer Opérations");
    qaDockOperation->setIcon(QIcon(":/img/icons8_work_24px.png"));
    qaDockOperation->setShortcut(QKeySequence("Ctrl+O"));
    ui->qmOutils->addSeparator();
    ui->qmOutils->addAction(qaDockOperation);


    QString qsWindowTitle = QApplication::applicationName() + " - " + QApplication::applicationVersion();
    if (m_qsArchitecture == "x86_64") {
        qsWindowTitle += " (64 bits)";
    } else {
        qsWindowTitle += " (32 bits)";
    }

    if (QApplication::applicationVersion().right(1) == "b") {
        qsWindowTitle += " - /!\\ BETA /!\\";
    }

    // Si on est on mode test on masque certaines choses
    if (test == false) {
        ui->qpbReadJSON->setVisible(test);
    } else {
        ui->qpbReadJSON->setVisible(test);
        qsWindowTitle += " - TEST MODE";
        connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(TEST(bool)));
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
    m_qsTypeGraphique = "Ligne";

    m_qs7zBin = "bin/7z.exe";
    m_qp7zProcess = new QProcess(this);
    m_bErreurExtraction = false;

    // Modèles pour la vue
    m_smProgresRealisation = new SqlModel(this);
    proxyModelFiltreTitre = new QSortFilterProxyModel(this);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    m_qmiDataSelectionne = QModelIndex();
    m_qmPopup = new QMenu(this);
    m_qaPopupDeleteAction = new QAction(QIcon(":/img/icons8_delete_24px.png"), "Masquer ...", this);
    m_qaPopupRestoreAction = new QAction(QIcon(":/img/icons8_restart_24px.png"), "Restaurer tous les progrès masqués", this);

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
    ui->qcbFiltreOrigine->addItem("Minecraft Vanilla");
    ui->qcbFiltreOrigine->addItem("BACAP");
    ui->qcbFiltreProgresFinis->addItem("");
    ui->qcbFiltreProgresFinis->addItem("oui", "true");
    ui->qcbFiltreProgresFinis->addItem("non", "false");
    ui->qcbFiltreTitre->addItem("");
    ui->qcbFiltreConditionFait->addItem("");
    ui->qcbFiltreConditionFait->addItem("oui");
    ui->qcbFiltreConditionFait->addItem("non");
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

    // Police spéciale
    int iFontId = QFontDatabase::addApplicationFont(":/files/MINECRAFTER.REG.TTF");
    if (iFontId != -1) {
        QFont qfMinecrafter("Minecrafter");
        ui->qlVosProgres->setFont(qfMinecrafter);
    }

    ui->qdteFrom->setDateTime(QDateTime(QDate(1970, 01, 01), QTime(0, 0, 0)));
    ui->qdteTo->setDateTime(QDateTime(QDate(2099, 12, 31), QTime(23, 59, 59)));

    ui->qgbStats->setEnabled(false);

    restoreTypeGraphique(param->getTypeGraphique());

    fenGraphiqueStatsOuverte = false;

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
    // Configuration
    connect(ui->qcbLauncher, SIGNAL(currentIndexChanged(int)), this, SLOT(choixLauncher(int)));
    connect(ui->qpbSelectionFichierProgres, SIGNAL(clicked(bool)), this, SLOT(choixFichierAdvancements(bool)));
    connect(ui->qpbDossierBlazeandcave, SIGNAL(clicked(bool)), this, SLOT(selectionDossierBlazeandcave(bool)));
    connect(ui->qpbExtraireProgresBacap, SIGNAL(clicked(bool)), this, SLOT(importProgresBlazeandcave(bool)));
    connect(ui->qpbImportProgresJoueur, SIGNAL(clicked(bool)), this, SLOT(importProgresPerso(bool)));
    // Lecture fichiers
    connect(ui->qpbExtraireProgresVanilla, SIGNAL(clicked(bool)), this, SLOT(extraireProgres(bool)));
    connect(ui->qpbReadAllJSONs, SIGNAL(clicked(bool)), this, SLOT(comparerLesProgres(bool)));
    // Filtres
    connect(ui->qcbFiltreOrigine, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableOrigine(QString)));
    connect(ui->qcbFiltreCategorie, &QComboBox::currentTextChanged, this, &FRM_Principale::filtreTableCategorie);
    connect(ui->qcbFiltreProgresFinis, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableProgresFinis(QString)));
    connect(ui->qcbFiltreConditionFait, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableConditionFait(QString)));
    connect(ui->qcbFiltreType, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTypeCondition(QString)));
    connect(ui->qdteFrom, &QDateTimeEdit::dateChanged, this, &FRM_Principale::dateFilterChanged);
    connect(ui->qdteTo, &QDateTimeEdit::dateChanged, this, &FRM_Principale::dateFilterChanged);
    connect(ui->qcbAutoCompletion, SIGNAL(stateChanged(int)), this, SLOT(etatAutoCompletion(int)));
    // Action sur la vue
    connect(ui->tableView, SIGNAL(pressed(const QModelIndex)), this, SLOT(dataSelectionnee(const QModelIndex)));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));
    connect(m_qaPopupDeleteAction, SIGNAL(triggered(bool)), this, SLOT(masquerProgres(bool)));
    connect(m_qaPopupRestoreAction, SIGNAL(triggered(bool)), this, SLOT(restaurerProgres(bool)));
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
    // Autre fenêtres
    connect(ui->qrbLigne, SIGNAL(clicked(bool)), this, SLOT(graphiqueLigne(bool)));
    connect(ui->qrbCerce, SIGNAL(clicked(bool)), this, SLOT(graphiqueSpline(bool)));
    connect(ui->qpbAfficherGraphique, SIGNAL(clicked(bool)), this, SLOT(ouvrirFenGraphiqueStats(bool)));
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
    ui->qpbImportProgresJoueur->setEnabled(false);
    ui->qlAdvancementsVanillaExtrait->setVisible(false);
    ui->qlDernierImportVanilla->setVisible(false);
    ui->qlAdvancementsBacapExtrait->setVisible(false);
    ui->qlProgresPerso->setVisible(false);
    ui->qpbDossierBlazeandcave->setEnabled(false);
    ui->qpbSelectionFichierProgres->setEnabled(false);
    ui->qpbReadAllJSONs->setEnabled(false);
    ui->line_5->setVisible(false);

    // On peut connecter la version
    connect(ui->qcbVersion, SIGNAL(currentIndexChanged(QString)), this, SLOT(choixVersion(QString)));

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
        ui->qcbMilestones->setChecked(param->getMilestones());
        ui->qcbStatistiques->setChecked(param->getStatistics());
        if (param->getVersion() != "DNE") {
            int index = ui->qcbVersion->findText(param->getVersion());
            if (index != -1) {
                ui->qcbVersion->setCurrentIndex(index);
            }
        }

        if (param->getDossierBlazeAndCave() != "DNE") {
            traitementDossierBac(param->getDossierBlazeAndCave());
        }

        // Restaurer progrès masqué
        m_qslProgresMasques = param->getProgresMasque();
        exclureStats(ui->qcbMilestones->checkState());

        if (param->getFichierAdvancementsPerso() != "DNE") {
            traitementFichierAdvancements(param->getFichierAdvancementsPerso());
        }
    }

    // A connecter après restauration
    connect(ui->qcbStatistiques, SIGNAL(stateChanged(int)), this, SLOT(exclureStats(int)));
    connect(ui->qcbMilestones, SIGNAL(stateChanged(int)), this, SLOT(exclureStats(int)));

    ouvertureEnCours = false;
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
        if (getEtatFenGraphiqueStats())
            graphiqueStatistiques->close();

        if (param->getRestoreSizePos()) {
            param->setGeometrieEtat(saveGeometry(), saveState());
            param->setGeometrieDock(ui->qdwOpe->saveGeometry());
        }

        event->accept();
        return;
    }

    // "Sinon", on demande confirmation de fermeture
    if (QMessageBox::question(this, "Fermeture", "Voulez-vous fermer le programme ?") == QMessageBox::Yes){
        if (getEtatFenGraphiqueStats())
            graphiqueStatistiques->close();

        if (param->getRestoreSizePos()) {
            param->setGeometrieEtat(saveGeometry(), saveState());
            param->setGeometrieDock(ui->qdwOpe->saveGeometry());
        }

        event->accept();
    } else {
        event->ignore();
    }
}

/*
 *  ~~~~~~~~~
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

    ui->qpbDossierBlazeandcave->setEnabled(true);
    ui->qpbSelectionFichierProgres->setEnabled(true);

    traitementDossierBac(m_qdDossierAdvancementsBlazeAndCave.path().replace("/data/blazeandcave/advancements", ""));
    traitementFichierAdvancements(m_qsFichierAdvancementsSolo);

    resetVue();
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

    QTime qtDebut(QTime::currentTime());
    QTime qtFin;
    QStringList qslFormatFichier;
    QString qsTitrePrecedent = "";
    QString qsTempNom, qsNouveauNom;
    QString qsLastErrorBdd = "", qsDernierImport = "", qsDerniereRequete = "";
    bool bErreurDetecteAdvancement = false, bErreurDetecteLang = false, bErreurDelete = false, bErreurInsertionAdvancement = false;
    QString qsErreurExtractionProgres = "", qsErreurExtractionLang = "";
    int iNombreFichierATraiter = 0, iNombreFichierTraiter = 0;

    qslFormatFichier << "*.json";
    resetVue();

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
                    QString qsTitre = qmTitle["translate"].toString();
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
        qtFin = QTime::currentTime();
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
        if (m_qdDossierAdvancementsBlazeAndCave.exists())
            ui->qpbExtraireProgresBacap->setEnabled(true);
        if (QFile::exists(m_qsFichierAdvancementsSolo))
            ui->qpbImportProgresJoueur->setEnabled(true);
        // On supprime les widgets de la status bar
        m_statusBar->removeWidget(m_progressExtractionProgresVanilla);
        m_statusBar->removeWidget(m_labelExtractionProgresVanilla);
        m_statusBar->clearMessage();

        activationBoutonExtraction();

        traitementDossierBac(m_qdDossierAdvancementsBlazeAndCave.path().replace("/data/blazeandcave/advancements", ""));
        traitementFichierAdvancements(m_qsFichierAdvancementsSolo);
    } else {
        afficherMessage(QMessageBox::Critical, "Erreur avec les fichiers", "Les fichier progrès ou la langue n'ont pas pu être extrait.");
    }

    //QTime qtFin(QTime::currentTime());
    int iDuree = qtDebut.secsTo(qtFin);
    QTime qtDuree(0,0,0);
    qtDuree = qtDuree.addSecs(iDuree);
    if (iDuree > 60) {
        m_statusBar->showMessage("Durée écoulée : " + qtDuree.toString("m") + " min. " + qtDuree.toString("ss") + " sec(s).", 10000);
    } else {
        m_statusBar->showMessage("Durée écoulée : " + qtDuree.toString("ss") + " sec(s).", 10000);
    }

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

    QTime qtDebut(QTime::currentTime()), qtFin;
    QStringList qslFormatFichier;
    QString qsTitrePrecedent = "";
    int iNombreFichierATraiter = 0, iNombreFichierTraiter = 0;
    QString qsLastErrorBdd = "", qsDernierImport = "", qsDerniereRequete = "";
    bool bErreurDelete = false, bErreurInsertionAdvancement = false;

    qslFormatFichier << "*.json";
    resetVue();

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

    qtFin = QTime::currentTime();
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
    ui->qpbExtraireProgresVanilla->setEnabled(true);
    ui->qpbExtraireProgresBacap->setEnabled(true);
    if (QFile::exists(m_qsFichierAdvancementsSolo))
        ui->qpbImportProgresJoueur->setEnabled(true);
    // On supprime les widgets de la status bar
    m_statusBar->removeWidget(m_progressExtractionProgresVanilla);
    m_statusBar->removeWidget(m_labelExtractionProgresVanilla);
    m_statusBar->clearMessage();

    activationBoutonExtraction();

    //QTime qtFin(QTime::currentTime());
    int iDuree = qtDebut.secsTo(qtFin);
    QTime qtDuree(0,0,0);
    qtDuree = qtDuree.addSecs(iDuree);
    if (iDuree > 60) {
        m_statusBar->showMessage("Durée écoulée : " + qtDuree.toString("m") + " min. " + qtDuree.toString("ss") + " sec(s).", 10000);
    } else {
        m_statusBar->showMessage("Durée écoulée : " + qtDuree.toString("ss") + " sec(s).", 10000);
    }
}

/*
 *
 */
void FRM_Principale::importProgresPerso(bool checked) {
    if (checked) {
    }

    QTime qtDebut(QTime::currentTime()), qtFin(QTime::currentTime());
    int iNombreProgresJoueur = 0, iNombreProgresTraite = 0;
    bool bErreurDelete = false, bErreurInsertionAdvancement = false;
    QString qsLastErrorBdd = "", qsDernierImport = "", qsDerniereRequete = "";
    resetVue();

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
                        //qDebug() << qsIdentifiant;
                        while (qmiCriteresPerso.hasNext()) {
                            qmiCriteresPerso.next();
                            QString qsNomCriteres = qmiCriteresPerso.key();
                            QDateTime qdtDateCriteres = qmiCriteresPerso.value().toDateTime();
                            //qDebug() << qsNomCriteres;

                            QSqlQuery queryInsert(bdd.getBase());
                            queryInsert.prepare("INSERT INTO player_advancements (version, identifiant, done, condition, date_fait) "
                                          "VALUES (:version, :identifiant, :done, :condition, :date_fait)");
                            queryInsert.bindValue(":version", m_qsNumeroVersion);
                            queryInsert.bindValue(":identifiant", qsIdentifiant);
                            queryInsert.bindValue(":done", qsDone);
                            queryInsert.bindValue(":condition", qsNomCriteres);
                            queryInsert.bindValue(":date_fait", qdtDateCriteres.toString("yyyy-MM-dd hh:mm:ss"));
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

        qtFin = QTime::currentTime();
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
            ui->qpbImportProgresJoueur->setText("Ré-Importer Progrès");
            ui->qpbImportProgresJoueur->setEnabled(true);
            // Info utilisateur
            ui->qlProgresPerso->setText("Progrès importé !");
            ui->qlProgresPerso->setStyleSheet("QLabel { color: green; }");
            ui->qlProgresPerso->setVisible(true);
            m_bProgresPersoOK = true;
        } else {
            afficherMessage(QMessageBox::Critical, "Impossible d'insérer tous vos progrès pour la version <strong>" + m_qsNumeroVersion + "</strong>.", \
                                        "Voir les détails pour plus d'informations.", \
                                        qsLastErrorBdd + "\nDernières Requêtes :\n" + qsDerniereRequete);
            ui->qlDernierImportPerso->setVisible(false);
            // Modification du bouton
            ui->qpbImportProgresJoueur->setText("Importer Progrès");
            ui->qpbImportProgresJoueur->setEnabled(true);
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
    if (m_qdDossierAdvancementsBlazeAndCave.exists())
        ui->qpbExtraireProgresBacap->setEnabled(true);
    ui->qpbImportProgresJoueur->setEnabled(true);
    // On supprime les widgets de la status bar
    m_statusBar->removeWidget(m_progressExtractionProgresVanilla);
    m_statusBar->removeWidget(m_labelExtractionProgresVanilla);
    m_statusBar->clearMessage();

    activationBoutonExtraction();

    //QTime qtFin(QTime::currentTime());
    int iDuree = qtDebut.secsTo(qtFin);
    QTime qtDuree(0,0,0);
    qtDuree = qtDuree.addSecs(iDuree);
    if (iDuree > 60) {
        m_statusBar->showMessage("Durée écoulée : " + qtDuree.toString("m") + " min. " + qtDuree.toString("ss") + " sec(s).", 10000);
    } else {
        m_statusBar->showMessage("Durée écoulée : " + qtDuree.toString("ss") + " sec(s).", 10000);
    }
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
 *
 */
void FRM_Principale::comparerLesProgres(bool checked) {
    if(checked){
    }

    ui->qcbFiltreTitre->clear();
    ui->qcbFiltreTitre->addItem("");
    ui->qcbFiltreCategorie->clear();
    ui->qcbFiltreCategorie->addItem("");

    QString qsDeleteVue = "DROP VIEW compare_advancements";
    QString qsRequeteVue = "CREATE VIEW 'compare_advancements' AS SELECT "
                  "la.origine"
                ", la.categorie"
                ", la.titre"
                ", pa.done progres_fait"
                ", la.description"
                ", la.condition_texte"
                ", CASE WHEN pa.condition IS NULL "
                       "THEN 'non' "
                       "ELSE 'oui' "
                       "END condition_fait"
                ", pa.date_fait"
                ", la.type_condition"
            " FROM "
                "list_advancements la "
            "INNER JOIN player_advancements pa ON pa.version = la.version AND pa.identifiant = la.identifiant AND pa.condition = la.condition"
            " WHERE "
                "la.version = '" + m_qsNumeroVersion + "' "
            "AND la.type_condition IN ('OU')"
           "UNION "
           "SELECT"
           "    la.origine"
           "    , la.categorie"
           "    , la.titre"
           "    , CASE WHEN pa.done IS NULL"
           "           THEN 'false'"
           "           ELSE 'true'"
           "           END progres_fait"
           "    , la.description"
           "    , la.condition_texte"
           "    , CASE WHEN pa.condition IS NULL"
           "        THEN 'non'"
           "        ELSE 'oui'"
           "        END condition_fait"
           "    , pa.date_fait"
           "    , la.type_condition"
           " FROM"
           "    list_advancements la"
           " LEFT JOIN player_advancements pa ON pa.version = la.version AND pa.identifiant = la.identifiant AND pa.condition = la.condition AND progres_fait IS NULL AND condition_fait IS NULL"
           " WHERE"
           "    la.version = '1.16.2'"
           " AND la.type_condition IN ('OU')"
           " AND la.titre NOT IN ("
           "    SELECT"
           "        la.titre"
           "    FROM"
           "        list_advancements la"
           "    INNER JOIN player_advancements pa ON pa.version = la.version AND pa.identifiant = la.identifiant AND pa.condition = la.condition"
           "    WHERE"
           "        la.version = '1.16.2'"
           "    AND la.type_condition IN ('OU')"
           ")"
            " UNION "
            "SELECT "
                  "la.origine"
                ", la.categorie"
                ", la.titre"
                ", CASE WHEN pa.done IS NULL "
                    "THEN 'false' "
                    "ELSE pa.done "
                    "END progres_fait"
                ", la.description"
                ", la.condition_texte"
                ", CASE WHEN pa.condition IS NULL "
                        "THEN 'non' "
                        "ELSE 'oui' "
                        "END condition_fait"
                ", pa.date_fait"
                ", la.type_condition"
            " FROM "
                "list_advancements la "
            "LEFT JOIN player_advancements pa ON pa.version = la.version AND pa.identifiant = la.identifiant AND pa.condition = la.condition"
            " WHERE "
                "la.version = '" + m_qsNumeroVersion + "' "
            "AND la.type_condition in ('ET', 'UNE')"
            " ORDER BY "
                  "la.origine DESC"
                ", la.categorie ASC"
                ", la.titre ASC"
                ", la.condition_texte ASC"
                ", progres_fait ASC";

    QSqlQuery qsqDeleteVue(bdd.getBase());
    QSqlQuery qsqCreateVue(bdd.getBase());
    QString qsLastErreurDelete = "", qsLastErreurCreation = "";
    bool bErreurDelete = false, bErreurCreation = false;

    if (!qsqDeleteVue.exec(qsDeleteVue)) {
        qsLastErreurDelete = qsqDeleteVue.lastError().text();
        if (qsLastErreurDelete != "no such view: compare_advancements Unable to execute statement") {
            bErreurDelete = true;
            afficherMessage(QMessageBox::Critical, "Impossible de supprimer l'ancienne comparaison", "Voir les détails pour plus d'informations", qsLastErreurDelete);
        }
    }

    if (!bErreurDelete) {
        if (!qsqCreateVue.exec(qsRequeteVue)) {
            bErreurCreation = true;
            qsLastErreurCreation = qsqCreateVue.lastError().text();
            afficherMessage(QMessageBox::Critical, "Impossible de comparer vos progrès", "Voir les détails pour plus d'informations", qsLastErreurCreation);
        }
    }

    if (!bErreurDelete && !bErreurCreation) {
        // On récupére les titres au complet pour mettre dans la QComboBox
        QString qsLastOrigine = "";
        QSqlQuery qsqListeTitre(bdd.getBase());
        bool bSeparateurFait = false;

        // On ajoute les titres dans la combobox
        if (qsqListeTitre.exec("SELECT DISTINCT origine, titre FROM compare_advancements ORDER BY origine DESC, titre ASC")) {
            while (qsqListeTitre.next()) {
                QString qsOrigine = qsqListeTitre.value("origine").toString();
                QString qsTitre = qsqListeTitre.value("titre").toString();

                if (qsLastOrigine != qsOrigine) {
                    ui->qcbFiltreTitre->addItem("----- " + qsOrigine + " -----");
                    qsLastOrigine = qsOrigine;
                }

                if (qsOrigine == "BACAP" && !bSeparateurFait) {
                    ui->qcbFiltreTitre->insertSeparator(ui->qcbFiltreTitre->count()-1);
                    bSeparateurFait = true;
                }

                ui->qcbFiltreTitre->addItem(qsTitre);
                QCoreApplication::processEvents();
            }

            // On ajoute les catégories dans la combobox
            QString qsLastOrigine = "";
            QSqlQuery qsqListeCategorie(bdd.getBase());
            //bool bSeparateurFait = false;

            // On ajoute les titres dans la combobox
            if (qsqListeCategorie.exec("SELECT DISTINCT categorie FROM compare_advancements ORDER BY categorie ASC")) {
                while (qsqListeCategorie.next()) {
                    //QString qsOrigine = qsqListeCategorie.value("origine").toString();
                    QString qsCategorie = qsqListeCategorie.value("categorie").toString();

//                    if (qsLastOrigine != qsOrigine) {
//                        ui->qcbFiltreCategorie->addItem("----- " + qsOrigine + " -----");
//                        qsLastOrigine = qsOrigine;
//                    }

//                    if (qsOrigine == "BACAP" && !bSeparateurFait) {
//                        ui->qcbFiltreCategorie->insertSeparator(ui->qcbFiltreCategorie->count()-1);
//                        bSeparateurFait = true;
//                    }

                    ui->qcbFiltreCategorie->addItem(qsCategorie);
                    QCoreApplication::processEvents();
                }
            }

            // On cré le modèle et on le mets dans la vue
            definirModele();

            connect(ui->qcbFiltreTitre, SIGNAL(currentTextChanged(QString)), this, SLOT(filtreTableTitre(QString)));

            ui->qgbFiltres->setEnabled(true);
            ui->qgbOperations->setEnabled(true);

            m_defaultCompleter->setModel(ui->qcbFiltreTitre->model());
            m_defaultCompleter->setCompletionMode(QCompleter::PopupCompletion);
            m_defaultCompleter->setCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
            ui->qcbFiltreTitre->setCompleter(m_defaultCompleter);

        } else {
            afficherMessage(QMessageBox::Critical, "Erreur lors de la récupération des titres", "Voir les détails pour plus d'informations", \
                            qsqListeTitre.lastError().text());
        }

//        // On compte pour affichage
//        QString qsSqlCompteTout = "SELECT"
//                                  "	COUNT(DISTINCT titre) 'nbr_progres'"
//                                  " , (SELECT COUNT(DISTINCT titre) FROM compare_advancements WHERE progres_fait = 'true') 'nbr_progres_fait'"
//                                  "FROM"
//                                  "	compare_advancements";
//        QString qsSqlCompteVanilla = "SELECT"
//                                     "   COUNT(DISTINCT titre) 'nbr_progres'"
//                                     " , (SELECT COUNT(DISTINCT titre) FROM compare_advancements WHERE origine = 'Minecraft Vanilla' AND progres_fait = 'true') 'nbr_progres_fait'"
//                                     " FROM"
//                                     " compare_advancements"
//                                     " WHERE"
//                                     " origine = 'Minecraft Vanilla'";
//        QString qsSqlCompteBacap = "SELECT"
//                                   "   COUNT(DISTINCT titre) 'nbr_progres'"
//                                   " , (SELECT COUNT(DISTINCT titre) FROM compare_advancements WHERE origine = 'BACAP' AND progres_fait = 'true') 'nbr_progres_fait'"
//                                   " FROM"
//                                   " compare_advancements"
//                                   " WHERE"
//                                   " origine = 'BACAP'";
//        QSqlQuery qsqCompteTout(qsSqlCompteTout, bdd.getBase()), qsqCompteVanilla(qsSqlCompteVanilla, bdd.getBase()), qsqCompteBacap(qsSqlCompteBacap, bdd.getBase());

//        if (qsqCompteVanilla.exec()) {
//            qsqCompteVanilla.next();
//            int iTotal = qsqCompteVanilla.value("nbr_progres").toInt();
//            int iFait = qsqCompteVanilla.value("nbr_progres_fait").toInt();

//            if (iTotal != 0) {
//                ui->qlVanilla->setText(QString::number(iFait) + " / " + QString::number(iTotal));
//            } else {
//                ui->qlVanilla->setText("x / x");
//            }
//        } else {
//            ui->qlVanilla->setText("\?\? / \?\?");
//            qDebug() << qsqCompteVanilla.lastError();
//            qDebug() << qsSqlCompteVanilla;
//        }

//        if (qsqCompteBacap.exec()) {
//            qsqCompteBacap.next();
//            int iTotal = qsqCompteBacap.value("nbr_progres").toInt();
//            int iFait = qsqCompteBacap.value("nbr_progres_fait").toInt();

//            if (iTotal != 0) {
//                ui->qlBacap->setText(QString::number(iFait) + " / " + QString::number(iTotal));
//            } else {
//                ui->qlBacap->setText("x / x");
//            }
//        } else {
//            ui->qlBacap->setText("\?\? / \?\?");
//        }

//        if (qsqCompteTout.exec()) {
//            qsqCompteTout.next();
//            int iTotal = qsqCompteTout.value("nbr_progres").toInt();
//            int iFait = qsqCompteTout.value("nbr_progres_fait").toInt();

//            if (iTotal != 0) {
//                ui->qlTotal->setText(QString::number(iFait) + " / " + QString::number(iTotal));
//            } else {
//                ui->qlTotal->setText("x / x");
//            }
//        } else {
//            ui->qlTotal->setText("\?\? / \?\?");
//        }

        // On compact la base de données, car le drop la fait gonfler vite
        QSqlQuery qsqCompactage(bdd.getBase());
        qsqCompactage.exec("VACUUM main");
    }
}

/*
 * Slots lors de la modification du filtre sur l'origine (Vanilla ou BCAP)
 */
void FRM_Principale::filtreTableOrigine(QString filtre) {
    int iIndexOfWhere = m_qslRequeteComparaison.indexOf(QRegExp(".*origine = .+"));
    int iTailleListeRequete = m_qslRequeteComparaison.size();
    if(iIndexOfWhere != -1) {
        m_qslRequeteComparaison.removeAt(iIndexOfWhere);
        iTailleListeRequete--;
    }

    if (filtre != "") {
        m_qslRequeteComparaison << "origine = '" + filtre + "'";
    }

    definirModele();
}

/*
 * Slots lors du filtre sur le titre
 */
void FRM_Principale::filtreTableTitre(QString filtre) {
    proxyModelFiltreTitre->invalidate();
    proxyModelFiltreTitre->setFilterKeyColumn(2);

    if (filtre != "----- Minecraft Vanilla -----" && filtre != "----- Blaze and Cave -----") {
        if (ui->qcbRegExp->isChecked())
            proxyModelFiltreTitre->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::RegExp));
        else
            proxyModelFiltreTitre->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
    } else {
        if (ui->qcbRegExp->isChecked())
            proxyModelFiltreTitre->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::RegExp));
        else
            proxyModelFiltreTitre->setFilterRegExp(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString));
    }
    qDebug() << filtre;
}

/*
 * Slots pour filtre sur la catégorie
 */
void FRM_Principale::filtreTableCategorie(QString filtre){
    QString qsDataFiltre = ui->qcbFiltreCategorie->currentText();
    int iIndexOfWhere = m_qslRequeteComparaison.indexOf(QRegExp(".*categorie = .+"));
    int iTailleListeRequete = m_qslRequeteComparaison.size();

    if(iIndexOfWhere != -1) {
        m_qslRequeteComparaison.removeAt(iIndexOfWhere);
        iTailleListeRequete--;
    }

    if (filtre != "") {
        m_qslRequeteComparaison << "categorie = '" + qsDataFiltre + "'";
    }

    definirModele();
}

/*
 * Slots lors du filtre si progrès finis (oui/non)
 */
void FRM_Principale::filtreTableProgresFinis(QString filtre) {
    //int iIndexOfFiltre = ui->qcbFiltreProgresFinis->findData(filtre, Qt::DisplayRole);
    QString qsDataFiltre = ui->qcbFiltreProgresFinis->currentData().toString();
    int iIndexOfWhere = m_qslRequeteComparaison.indexOf(QRegExp(".*progres_fait = .+"));
    int iTailleListeRequete = m_qslRequeteComparaison.size();
    if(iIndexOfWhere != -1) {
        m_qslRequeteComparaison.removeAt(iIndexOfWhere);
        iTailleListeRequete--;
    }

    if (filtre != "") {
        m_qslRequeteComparaison << "progres_fait = '" + qsDataFiltre + "'";
    }

    if (filtre == "oui") {
        ui->qcbFiltreConditionFait->setCurrentIndex(0);
        //filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
        ui->qcbFiltreConditionFait->setEnabled(false);
    } else {
        ui->qcbFiltreConditionFait->setEnabled(true);
//        filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
    }

    definirModele();

//    proxyModelFiltreProgresFinis->setFilterKeyColumn(2);
//    proxyModelFiltreProgresFinis->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));

//    if (filtre == "oui") {
//        ui->qcbFiltreConditionFait->setCurrentIndex(1);
//        filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
//        ui->qcbFiltreConditionFait->setEnabled(false);
//    } else {
//        if (ui->qcbFiltreConditionFait->isEnabled()) {
//            if (ui->qcbFiltreConditionFait->currentText() != "") {
//                filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
//            }
//        } else {
//            ui->qcbFiltreConditionFait->setEnabled(true);
//            ui->qcbFiltreConditionFait->setCurrentIndex(0);
//            filtreTableConditionFait(ui->qcbFiltreConditionFait->currentText());
//        }
//    }
//    if (ui->qcbFiltreType->currentText() != "") {
//        filtreTableTypeCondition(ui->qcbFiltreType->currentText());
//    }
}

/*
 * Slots lors du filtre si condition faite (oui/non)
 */
void FRM_Principale::filtreTableConditionFait(QString filtre) {
    int iIndexOfWhere = m_qslRequeteComparaison.indexOf(QRegExp(".*condition_fait = .+"));
    int iTailleListeRequete = m_qslRequeteComparaison.size();
    if(iIndexOfWhere != -1) {
        m_qslRequeteComparaison.removeAt(iIndexOfWhere);
        iTailleListeRequete--;
    }

    if (filtre != "") {
        m_qslRequeteComparaison << "condition_fait = '" + filtre + "'";
    }

    definirModele();

//    proxyModelFiltreConditionFaite->setFilterKeyColumn(4);
//    proxyModelFiltreConditionFaite->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
//    if (ui->qcbFiltreType->currentText() != "") {
//        filtreTableTypeCondition(ui->qcbFiltreType->currentText());
//    }
}

/*
 * Slots lors du filtre sur le type de condition (ET/OU/UN)
 */
void FRM_Principale::filtreTableTypeCondition(QString filtre) {
    int iIndexOfWhere = m_qslRequeteComparaison.indexOf(QRegExp(".*type_condition = .+"));
    int iTailleListeRequete = m_qslRequeteComparaison.size();
    if(iIndexOfWhere != -1) {
        m_qslRequeteComparaison.removeAt(iIndexOfWhere);
        iTailleListeRequete--;
    }

    if (filtre != "") {
        m_qslRequeteComparaison << "type_condition = '" + filtre + "'";
    }

    definirModele();
//    proxyModelFiltreTypeCondition->setFilterKeyColumn(6);
//    proxyModelFiltreTypeCondition->setFilterRegExp(QRegExp(filtre, Qt::CaseInsensitive, QRegExp::FixedString));
}

/*
 * Slots lors du choix pour les milestones et statistics pour BACAP
 */
void FRM_Principale::exclureStats(int statut) {
    if (statut) {
    }

    int iIndexOfWhere = m_qslRequeteComparaison.indexOf(QRegExp(".*categorie NOT IN.+"));
    int iTailleListeRequete = m_qslRequeteComparaison.size();
    if(iIndexOfWhere != -1) {
        m_qslRequeteComparaison.removeAt(iIndexOfWhere);
        iTailleListeRequete--;
    }

    if (ui->qcbStatistiques->checkState() == Qt::Checked && ui->qcbMilestones->checkState() == Qt::Checked) {
        // Aucun des deux...
        m_qslRequeteComparaison << "categorie NOT IN ('bacap', 'statistics')";
    } else if (ui->qcbStatistiques->checkState() == Qt::Checked && ui->qcbMilestones->checkState() == Qt::Unchecked) {
        // Seulement les milestones
        // Pas les statistiques
        m_qslRequeteComparaison << "categorie NOT IN ('statistics')";
        //m_qsDossierAExclure = "recipes|technical|bacap";
    } else if (ui->qcbStatistiques->checkState() == Qt::Unchecked && ui->qcbMilestones->checkState() == Qt::Checked) {
        // Seulement les statistiques
        // Pas les milestones
        m_qslRequeteComparaison << "categorie NOT IN ('bacap')";
        //m_qsDossierAExclure = "recipes|technical|statistics";
    } else {
        //m_qsDossierAExclure = "recipes|technical|statistics|bacap";
    }



    definirModele();

    param->setMilestones(ui->qcbMilestones->isChecked());
    param->setStatistics(ui->qcbStatistiques->isChecked());
}

/*
 * Slots lors du filtre sur les dates
 */
void FRM_Principale::dateFilterChanged() {
    int iIndexOfWhere = m_qslRequeteComparaison.indexOf(QRegExp(".*date_fait BETWEEN .+"));
    int iTailleListeRequete = m_qslRequeteComparaison.size();
    QDateTime qdtDebutDefaut = QDateTime(QDate(1970, 01, 01), QTime(0, 0, 0));
    QDateTime qdtFinDefaut = QDateTime(QDate(2099, 12, 31), QTime(23, 59, 59));
    QDateTime qdtDebut = ui->qdteFrom->dateTime(), qdtFin = ui->qdteTo->dateTime();

    if(iIndexOfWhere != -1) {
        m_qslRequeteComparaison.removeAt(iIndexOfWhere);
        iTailleListeRequete--;
    }

    if (qdtDebut != qdtDebutDefaut && qdtFin != qdtFinDefaut) {
        m_qslRequeteComparaison << "date_fait BETWEEN '" + qdtDebut.toString("yyyy-MM-dd hh:mm:ss") + "' "
                                   "AND '" + qdtFin.toString("yyyy-MM-dd hh:mm:ss") + "'";
    }

    definirModele();
}

/*
 * Slots lors du clique sur le bouton "Effacer les filtres"
 */
void FRM_Principale::effacerLesFiltres(bool checked) {
    if (checked) {
    }

    ui->qcbFiltreOrigine->setCurrentIndex(0);
    ui->qcbFiltreCategorie->setCurrentText(0);
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

/*
 * Définir l'autocomplétion sur la combobox pour les titres
 */
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

/*
 * Lorsqu'un clique est fait dans la table
 */
void FRM_Principale::dataSelectionnee(const QModelIndex index) {
    // TODO A REFAIRE !
    m_qmiDataSelectionne = index;
    QModelIndex qmiTitre = proxyModelFiltreTitre->index(index.row(), 2);
    QString qsTitreDisplay = proxyModelFiltreTitre->data(qmiTitre, Qt::DisplayRole).toString();
    QString qsTitreData = proxyModelFiltreTitre->data(qmiTitre, Qt::UserRole).toString();

    qsTitreDisplay.replace(QRegularExpression(" \\(.+\\)"), "");
    //qDebug() << qsTitreDisplay;
}

/*
 * Afficher le menu Pop-Up de la table
 */
void FRM_Principale::customMenuRequested(QPoint pos){
    QModelIndex index = m_qmiDataSelectionne;
    QModelIndex qmiTitre = proxyModelFiltreTitre->index(index.row(), 2);
    QString qsTitreDisplay = proxyModelFiltreTitre->data(qmiTitre, Qt::DisplayRole).toString();
    qDebug() << qsTitreDisplay;

    m_qmPopup->clear();
    m_qaPopupDeleteAction->setText("Masquer '"+ qsTitreDisplay + "'");
    m_qmPopup->addAction(m_qaPopupDeleteAction);
    m_qmPopup->addAction(m_qaPopupRestoreAction);
    m_qmPopup->popup(ui->tableView->viewport()->mapToGlobal(pos));
}
/*
 *  Masquer le progres sélectionner lors du clique droit avec le menu pop-up
 */
void FRM_Principale::masquerProgres(bool booleen) {
    if (booleen) {
    }

    QModelIndex index = m_qmiDataSelectionne;
    QModelIndex qmiTitre = proxyModelFiltreTitre->index(index.row(), 2);
    QString qsTitreDisplay = proxyModelFiltreTitre->data(qmiTitre, Qt::DisplayRole).toString();

    m_qslProgresMasques << qsTitreDisplay;
    param->setProgresMasque(m_qslProgresMasques);

    definirModele();
}

/*
 * Restaurer les progres
 */
void FRM_Principale::restaurerProgres(bool booleen) {
    if (booleen) {
    }

    m_qslProgresMasques.clear();
    param->setProgresMasque(m_qslProgresMasques);

    definirModele();
}

/*
 * Imprimer tous les progres dépendant des filtres
 */
void FRM_Principale::imprimerTable(bool checked) {
    if (checked) {
    }

    QString strStream;
    QTextStream out(&strStream);
    QString qsRequeteFinal = "";
    QSqlQuery qsqDataAImprimer(bdd.getBase());

    for (int i = 0; i < m_qslRequeteComparaison.size(); i++) {
        if (i == 1) {
            qsRequeteFinal += " WHERE ";
        } else if (i > 1) {
            qsRequeteFinal += " AND ";
        }
        qsRequeteFinal += m_qslRequeteComparaison.at(i);
    }

    //const int rowCount = ui->tableView->model()->rowCount();
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
    if(qsqDataAImprimer.exec(qsRequeteFinal)) {
        while(qsqDataAImprimer.next()) {
            QString qsOrigine = qsqDataAImprimer.value("origine").toString();
            QString qsCategorie = qsqDataAImprimer.value("categorie").toString();
            QString qsTitre = qsqDataAImprimer.value("titre").toString();
            QString qsProgresFait = (qsqDataAImprimer.value("progres_fait").toString() == "true") ? "oui" : "non";
            QString qsDescription = qsqDataAImprimer.value("description").toString();
            QString qsConditionTexte = qsqDataAImprimer.value("condition_texte").toString();
            QString qsConditionFait = qsqDataAImprimer.value("condition_fait").toString();
            QDateTime qdtDateFait = qsqDataAImprimer.value("date_fait").toDateTime();
            QString qsDateFait = qdtDateFait.toString("dd/MM/yyyy hh:mm:ss");
            out << "<tr>"
                   "<td bkcolor=0>"+qsOrigine+"</td>"
                    "<td bkcolor=0>"+qsCategorie+"</td>"
                    "<td bkcolor=0>"+qsTitre+"</td>"
                    "<td bkcolor=0>"+qsProgresFait+"</td>"
                    "<td bkcolor=0>"+qsDescription+"</td>"
                    "<td bkcolor=0>"+qsConditionTexte+"</td>"
                    "<td bkcolor=0>"+qsConditionFait+"</td>"
                    "<td bkcolor=0>"+qsDateFait+"</td>"
                    "</tr>\n";
        }
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

void FRM_Principale::graphiqueLigne(bool checked) {
    if(checked) {
        m_qsTypeGraphique = "Ligne";
        param->setTypeGraphique(m_qsTypeGraphique);
    }
}

void FRM_Principale::graphiqueSpline(bool checked) {
    if(checked) {
        m_qsTypeGraphique = "Spline";
        param->setTypeGraphique(m_qsTypeGraphique);
    }
}

/*
 * Ouvrir la fenêtre des statistiques
 */
void FRM_Principale::ouvrirFenGraphiqueStats(bool clicked) {
    if (clicked){
    }

    if (!getEtatFenGraphiqueStats()){
        // La fenêtre n'est pas déjà ouverte, on cré l'objet, l'affiche et on lie la femeture de la fenêtre à la fonction
        graphiqueStatistiques = new Statistiques(this, m_qsTypeGraphique,this->m_test);
        setEtatFenGraphiqueStats(true);
        connect(graphiqueStatistiques, SIGNAL(finished(int)), this, SLOT(fenGraphiqueStatsClose(int)));
        graphiqueStatistiques->show();
    } else {
        // La fenêtre est déjà ouverte, on informe, et on la met au premier plan
        QMessageBox::information(this, "Ajouter une recette", "La fenêtre pour ajouter une recette est déjà ouverte.");
        graphiqueStatistiques->raise();
    }
}

/*
 * Quand la fenêtre des stats ce ferme
 */
void FRM_Principale::fenGraphiqueStatsClose(int result) {
    result += 0; // Pour supprimer un warning lors de la compilation

    // On définis l'état de la fenêtre à fermer
    setEtatFenGraphiqueStats(false);
    // On bloque le signal du ComboBox, sinon ça plante !
    //ui->qcbListeRecettes->blockSignals(true);
    // On efface le modèle et listes toutes les recettes pour prendre la nouvelle
    //modele->clear();
    //listeRecettes();
    // On débloque le signal pour pouvoir restaurer la dernière recette sélectionné si l'utilisateur l'a activé.
    //ui->qcbListeRecettes->blockSignals(false);
    //restaurerDerniereRecette();
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
        if (m_qsArchitecture == "i386")
            url.setUrl("https://advancements.blackwizard.fr/repository/beta/Updates.xml");
        else if (m_qsArchitecture == "x86_64")
            url.setUrl("https://advancements.blackwizard.fr/repository-64/beta/Updates.xml");
        m_updateBetaVerifiee = true;
    } else {
        if (m_qsArchitecture == "i386")
            url.setUrl("https://advancements.blackwizard.fr/repository/release/Updates.xml");
        else if (m_qsArchitecture == "x86_64")
            url.setUrl("https://advancements.blackwizard.fr/repository-64/release/Updates.xml");
        m_updateBetaVerifiee = false;
    }
    QNetworkRequest request;

    qDebug() << url;
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
    qDebug() << m_qnamManager;
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
    bool bMiseAJourNecessaire = false, bLocalPlusRecente = false;

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
    //qsVersionOnline = "2.0.2";
    qslVersionOnline = qsVersionOnline.split(".");
    qslVersionLocal = qsVersionLocal.split(".");

//    qDebug() << "Version local" << qslVersionLocal;
//    qDebug() << "Version Online" << qslVersionOnline;

    if (qsVersionOnline.count() > qsVersionLocal.count()) {
        int diff = qsVersionOnline.count() - qsVersionLocal.count();
        for (int ite = 0 ; ite < diff ; ite++) {
            qslVersionLocal << "0";
        }
    }

    for(int i = 0; i < qslVersionOnline.size(); i++) {
//        qDebug() << "i" << i << "Numéro Local" << qslVersionLocal.at(i);
//        qDebug() << "i" << i << "Numéro Online" << qslVersionOnline.at(i);
        if(!bMiseAJourNecessaire && !bLocalPlusRecente) {
            if(qslVersionOnline.at(i).toInt() > qslVersionLocal.at(i).toInt()) {
                bMiseAJourNecessaire = true;
            } else if (qslVersionLocal.at(i).toInt() > qslVersionOnline.at(i).toInt()) {
                bLocalPlusRecente = true;
            }
        }
    }

    // On définis la dernière vérification des mises à jour, même si c'est une vérification manuelle
    param->setDerniereVerificationMiseAJour(QDate::currentDate());

    if(bMiseAJourNecessaire) {
        if(QMessageBox::question(this, "Mise à jour disponible", "La version " + qsVersionOnline + " est disponible.\n Voulez-vous mettre à jour ?", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes){
            QMessageBox::information(this, "Mise à jour", "L'outils de maintenance va s'ouvrir pour vous guider dans la mise à jour.");
            QProcess *qpOutilDeMaintenance = new QProcess();
            QStringList arguments;
            arguments << "--updater";
            if (param->getMiseAJourBeta()) {
                arguments << "--addTempRepository";
                if (m_qsArchitecture == "i386")
                    arguments << "https://advancements.blackwizard.fr/repository/beta";
                else if (m_qsArchitecture == "x86_64")
                    arguments << "https://advancements.blackwizard.fr/repository-64/beta";
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
 *  ~~~~~~~~~~~~~
 *  | FONCTIONS |
 *  ~~~~~~~~~~~~~
 */

QVariantMap FRM_Principale::ouvrirJson(QString fichier) {
    QFile qfFichierJson(fichier);
    QJsonParseError *error = new QJsonParseError();
    m_ouvertureJson = false;
    if(!qfFichierJson.open(QIODevice::ReadOnly)){
        //qDebug()<<"Failed to open "<< fichier;
        afficherMessage(QMessageBox::Critical, "Ouverture fichier JSON en échec", "Impossible d'ouvrir le fichier", "Détail :\n" + qfFichierJson.errorString() + "\n\nFichier bloquant :\n" + qfFichierJson.fileName());
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
            afficherMessage(QMessageBox::Critical, "Ouverture fichier JSON en échec", "Impossible de créer le document JSON", "Détail :\n" + error->errorString() + "\n\nFichier :\n" + qfFichierJson.fileName());
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

    if (m_qdDossierAdvancementsBlazeAndCave.exists() && m_qsNumeroVersion != "") {
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
    } else if (QFile::exists(m_qsFichierAdvancementsSolo) && m_qsNumeroVersion == "") {
        ui->qlDernierImportBacap->setVisible(false);
        // Modification du bouton
        ui->qpbExtraireProgresBacap->setText("Importer Progrès");
        ui->qpbExtraireProgresBacap->setEnabled(false);
        // Info utilisateur
        // Info utilisateur
        ui->qlAdvancementsBacapExtrait->setText("Sélectionnez la version d'abord !");
        ui->qlAdvancementsBacapExtrait->setStyleSheet("QLabel { color: orange; }");
        ui->qlAdvancementsBacapExtrait->setVisible(true);
        m_bProgresBlazeandcaveOK = false;
    } else {
        ui->qlDernierImportBacap->setVisible(false);
        // Modification du bouton
        ui->qpbExtraireProgresBacap->setText("Importer Progrès");
        ui->qpbExtraireProgresBacap->setEnabled(false);
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

    if (QFile::exists(m_qsFichierAdvancementsSolo) && m_qsNumeroVersion != "") {
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
        } else {
            afficherMessage(QMessageBox::Critical, "Impossible de vérifier si les progrès ont déjà étés importés.", \
                            "Contacter <a href=\"https://github.com/Chucky2401/Minecraft-Advancements/issues/new?title=Erreur contrôle import progrès&body=" + qsqCompteProgresPerso.lastError().text() + "\n\nRemarque personnel :\n\">le développeur</a>.", \
                            qsqCompteProgresPerso.lastError().text());
            m_bProgresPersoOK = false;
        }
    } else if (QFile::exists(m_qsFichierAdvancementsSolo) && m_qsNumeroVersion == "") {
        ui->qlDernierImportPerso->setVisible(false);
        // Modification du bouton
        ui->qpbImportProgresJoueur->setText("Importer Progrès");
        ui->qpbImportProgresJoueur->setEnabled(false);
        // Info utilisateur
        ui->qlProgresPerso->setText("Sélectionnez la version d'abord !");
        ui->qlProgresPerso->setStyleSheet("QLabel { color: orange; }");
        ui->qlProgresPerso->setVisible(true);
        m_bProgresPersoOK = false;
    } else {
        ui->qlDernierImportPerso->setVisible(false);
        // Modification du bouton
        ui->qpbImportProgresJoueur->setText("Importer Progrès");
        ui->qpbImportProgresJoueur->setEnabled(false);
        // Info utilisateur
        ui->qlProgresPerso->setText("Progrès non importé !");
        ui->qlProgresPerso->setStyleSheet("QLabel { color: red; }");
        ui->qlProgresPerso->setVisible(true);
        m_bProgresPersoOK = false;
    }

    activationBoutonExtraction();
}

/*
 * Fonction pour activer les boutons d'extraction suivant des booléens
 */
void FRM_Principale::activationBoutonExtraction() {
    if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK) {
        ui->qpbReadAllJSONs->setEnabled(true);
        ui->qgbStats->setEnabled(true);
    } else if (m_bVersionOK && m_bProgresBlazeandcaveOK && m_bProgresPersoOK) {
        ui->qpbReadAllJSONs->setEnabled(true);
        ui->qgbStats->setEnabled(true);
    } else if (m_bVersionOK && m_bProgresVanillaOK && m_bProgresPersoOK && m_bProgresBlazeandcaveOK) {
        ui->qpbReadAllJSONs->setEnabled(true);
        ui->qgbStats->setEnabled(true);
    } else {
        ui->qpbReadAllJSONs->setEnabled(false);
        ui->qgbStats->setEnabled(false);
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

    ui->qpbExtraireProgresBacap->setEnabled(false);

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
 * Definis le modèle à utiliser dans la QTableView
 * S'occupe de compter les progrès pour les compteurs
 */
void FRM_Principale::definirModele() {
    if (!ouvertureEnCours) {
        QString qsRequeteFinal = "";
        QString qsConditionCompteFinal = "";
        QString qsSqlCompteTout = "SELECT"
                                  "	COUNT(DISTINCT titre) 'nbr_progres'"
                                  " , (SELECT COUNT(DISTINCT titre) FROM compare_advancements WHERE progres_fait = 'true' CONDITION_MANQUANTE) 'nbr_progres_fait'"
                                  "FROM"
                                  "	compare_advancements";
        QString qsSqlCompteVanilla = "SELECT"
                                     "   COUNT(DISTINCT titre) 'nbr_progres'"
                                     " , (SELECT COUNT(DISTINCT titre) FROM compare_advancements WHERE origine = 'Minecraft Vanilla' AND progres_fait = 'true' CONDITION_MANQUANTE) 'nbr_progres_fait'"
                                     " FROM"
                                     " compare_advancements"
                                     " WHERE"
                                     " origine = 'Minecraft Vanilla'";
        QString qsSqlCompteBacap = "SELECT"
                                   "   COUNT(DISTINCT titre) 'nbr_progres'"
                                   " , (SELECT COUNT(DISTINCT titre) FROM compare_advancements WHERE origine = 'BACAP' AND progres_fait = 'true' CONDITION_MANQUANTE) 'nbr_progres_fait'"
                                   " FROM"
                                   " compare_advancements"
                                   " WHERE"
                                   " origine = 'BACAP'";
        QString qsFiltreTitreMasque = "";

        for (int i = 0; i < m_qslRequeteComparaison.size(); i++) {
            if (i == 1) {
                qsRequeteFinal += " WHERE ";
                qsSqlCompteTout += " WHERE " + m_qslRequeteComparaison.at(i);
                qsSqlCompteBacap += " AND " + m_qslRequeteComparaison.at(i);
                qsSqlCompteVanilla += " AND " + m_qslRequeteComparaison.at(i);
                qsConditionCompteFinal += "AND " + m_qslRequeteComparaison.at(i);
            } else if (i > 1) {
                qsRequeteFinal += " AND ";
                qsSqlCompteTout += " AND " + m_qslRequeteComparaison.at(i);
                qsSqlCompteBacap += " AND " + m_qslRequeteComparaison.at(i);
                qsSqlCompteVanilla += " AND " + m_qslRequeteComparaison.at(i);
                qsConditionCompteFinal += " AND " + m_qslRequeteComparaison.at(i);
            }
            qsRequeteFinal += m_qslRequeteComparaison.at(i);
        }

        // Filtre titre
        if (m_qslProgresMasques.size() > 0) {
            qsFiltreTitreMasque += "titre NOT IN (";
            for (int i = 0; i < m_qslProgresMasques.size(); i++) {
                QString qsTitreDisplay = m_qslProgresMasques.at(i);
                if (m_qslProgresMasques.size() == 1) {
                    qsFiltreTitreMasque += "'" + qsTitreDisplay + "'";
                } else {
                    if (i != m_qslProgresMasques.size()-1){
                        qsFiltreTitreMasque += "'" + qsTitreDisplay + "',";
                    } else {
                        qsFiltreTitreMasque += "'" + qsTitreDisplay + "'";
                    }
                }
            }
            qsFiltreTitreMasque += ")";
            qsRequeteFinal += " AND " + qsFiltreTitreMasque;
            qsSqlCompteTout += " AND " + qsFiltreTitreMasque;
            qsSqlCompteBacap += " AND " + qsFiltreTitreMasque;
            qsSqlCompteVanilla += " AND " + qsFiltreTitreMasque;
            qsConditionCompteFinal += " AND " + qsFiltreTitreMasque;
        }

        qsSqlCompteVanilla = qsSqlCompteVanilla.replace("CONDITION_MANQUANTE", qsConditionCompteFinal);
        qsSqlCompteBacap = qsSqlCompteBacap.replace("CONDITION_MANQUANTE", qsConditionCompteFinal);
        qsSqlCompteTout = qsSqlCompteTout.replace("CONDITION_MANQUANTE", qsConditionCompteFinal);
        QSqlQuery qsqCompteTout(qsSqlCompteTout, bdd.getBase()), qsqCompteVanilla(qsSqlCompteVanilla, bdd.getBase()), qsqCompteBacap(qsSqlCompteBacap, bdd.getBase());

        // On configure le modèle pour l'afficher
        m_smProgresRealisation->setQuery(qsRequeteFinal, bdd.getBase());

        while (m_smProgresRealisation->canFetchMore())
            m_smProgresRealisation->fetchMore();

        m_smProgresRealisation->setHeaderData(0, Qt::Horizontal, tr("Origine"));
        m_smProgresRealisation->setHeaderData(1, Qt::Horizontal, tr("Catégorie"));
        m_smProgresRealisation->setHeaderData(2, Qt::Horizontal, tr("Progrès"));
        m_smProgresRealisation->setHeaderData(3, Qt::Horizontal, tr("Progrès Fait"));
        m_smProgresRealisation->setHeaderData(4, Qt::Horizontal, tr("Description"));
        m_smProgresRealisation->setHeaderData(5, Qt::Horizontal, tr("Critère"));
        m_smProgresRealisation->setHeaderData(6, Qt::Horizontal, tr("Critère Fait"));
        m_smProgresRealisation->setHeaderData(7, Qt::Horizontal, tr("Date Fait"));
        m_smProgresRealisation->setHeaderData(8, Qt::Horizontal, tr("Type Critère"));

        proxyModelFiltreTitre->setSourceModel(m_smProgresRealisation);

        ui->tableView->setModel(proxyModelFiltreTitre);
        ui->tableView->setColumnWidth(0, 95);
        ui->tableView->setColumnWidth(1, 67);
        ui->tableView->setColumnWidth(2, 250);
        ui->tableView->setColumnWidth(3, 75);
        ui->tableView->setColumnWidth(5, 146);
        ui->tableView->setColumnWidth(6, 84);
        ui->tableView->setColumnWidth(7, 110);
        ui->tableView->hideColumn(8);

        // On compte pour affichage
        if (qsqCompteVanilla.exec()) {
            qsqCompteVanilla.next();
            int iTotal = qsqCompteVanilla.value("nbr_progres").toInt();
            int iFait = qsqCompteVanilla.value("nbr_progres_fait").toInt();

            if (iTotal != 0) {
                ui->qlVanilla->setText(QString::number(iFait) + " / " + QString::number(iTotal));
            } else {
                ui->qlVanilla->setText("x / x");
            }
        } else {
            ui->qlVanilla->setText("\?\? / \?\?");
            qDebug() << qsqCompteVanilla.lastError();
            qDebug() << qsSqlCompteVanilla;
        }

        if (qsqCompteBacap.exec()) {
            qsqCompteBacap.next();
            int iTotal = qsqCompteBacap.value("nbr_progres").toInt();
            int iFait = qsqCompteBacap.value("nbr_progres_fait").toInt();

            if (iTotal != 0) {
                ui->qlBacap->setText(QString::number(iFait) + " / " + QString::number(iTotal));
            } else {
                ui->qlBacap->setText("x / x");
            }
        } else {
            ui->qlBacap->setText("\?\? / \?\?");
        }

        if (qsqCompteTout.exec()) {
            qsqCompteTout.next();
            int iTotal = qsqCompteTout.value("nbr_progres").toInt();
            int iFait = qsqCompteTout.value("nbr_progres_fait").toInt();

            if (iTotal != 0) {
                ui->qlTotal->setText(QString::number(iFait) + " / " + QString::number(iTotal));
            } else {
                ui->qlTotal->setText("x / x");
            }
        } else {
            ui->qlTotal->setText("\?\? / \?\?");
        }
    }
}

/*
 * Fonctions pour effecer le filtre sur les dates
 */
void FRM_Principale::effacerFiltreDate() {
    ui->qdteFrom->setDateTime(QDateTime(QDate(1970, 01, 01), QTime(0, 0, 0)));
    ui->qdteTo->setDateTime(QDateTime(QDate(2099, 12, 31), QTime(23, 59, 59)));
}

/*
 *
 */
void FRM_Principale::resetVue() {
    // Reset Filtre
    effacerLesFiltres(true);
    // On déconnecte le titre pour éviter les problèmes
    ui->qcbFiltreTitre->disconnect();
    ui->qcbFiltreTitre->clear();
    ui->qcbFiltreTitre->addItem("");
    // On désactive les boutons
    ui->qgbFiltres->setEnabled(false);
    ui->qgbOperations->setEnabled(false);
    // On vide la vue
    proxyModelFiltreTitre->invalidate();
    m_smProgresRealisation->setQuery("", bdd.getBase());

    while (m_smProgresRealisation->rowCount() > 0)
        m_smProgresRealisation->removeRows(0, m_smProgresRealisation->rowCount());

    // On réinitialise la requête de filtre
    m_qslRequeteComparaison.clear();
    m_qslRequeteComparaison << "SELECT * FROM compare_advancements";
    //exclureStats(0);

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

bool FRM_Principale::getEtatFenGraphiqueStats() {
    return fenGraphiqueStatsOuverte;
}

void FRM_Principale::setEtatFenGraphiqueStats(bool stated) {
    fenGraphiqueStatsOuverte = stated;
}

void FRM_Principale::restoreTypeGraphique(QString type) {
    if (type == "Spline") {
        ui->qrbCerce->toggle();
        m_qsTypeGraphique = "Spline";
    } else {
        ui->qrbLigne->toggle();
        m_qsTypeGraphique = "Ligne";
    }
}


/*
 *  ~~~~~~~~~~~~~~~~~~~~~~~
 *  | Pour le développeur |
 *  ~~~~~~~~~~~~~~~~~~~~~~~
 */

/*
 * Utiliser dans le bouton de test
 */
void FRM_Principale::TEST(bool checked) {
    if (checked) {
    }



//    resetVue();

//    QStringList qslLignesValide;
//    QFile inputFile("rcs/blazeandcave-fr_fr.json");
//    bool bEcrireFichier = false;

//    if (inputFile.open(QIODevice::ReadOnly))
//    {
//       QTextStream in(&inputFile);
//       while (!in.atEnd())
//       {
//          QString line = in.readLine();
//          //qDebug() << line;
//          if (!line.contains(QRegExp("^( +#.+| +$|\n$|$)"))) {
//              qslLignesValide << line;
//          } else {
//              bEcrireFichier = true;
//          }
//       }
//       inputFile.close();

//       if (bEcrireFichier) {
//           if (inputFile.open(QIODevice::WriteOnly)) {
//               QTextStream out(&inputFile);
//               for (int i = 0; i < qslLignesValide.count(); i++) {
//                   out << qslLignesValide.at(i) << "\n";
//               }
//           }
//       } else {
//           qDebug() << "Pas besoin, clear !";
//       }
//       inputFile.close();
//    }
}
