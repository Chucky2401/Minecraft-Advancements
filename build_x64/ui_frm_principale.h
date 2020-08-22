/********************************************************************************
** Form generated from reading UI file 'frm_principale.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRM_PRINCIPALE_H
#define UI_FRM_PRINCIPALE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FRM_Principale
{
public:
    QAction *qaQuitter;
    QAction *qaSettings;
    QAction *qaAbout;
    QAction *qaUpdate;
    QAction *qaImprimerVue;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *hlLanceurLangue;
    QLabel *qlLanceur;
    QComboBox *qcbLauncher;
    QFrame *line_4;
    QLabel *label_5;
    QComboBox *qcbLangue;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *hlDossierLanceur;
    QLabel *qlDossierLanceur;
    QLineEdit *qleDossierLanceur;
    QPushButton *qpbSelectionDossierLanceur;
    QGridLayout *gdVersion;
    QComboBox *qcbVersion;
    QLineEdit *qleCheminVersion;
    QLabel *qlVersion;
    QPushButton *qpbExtraireProgresVanilla;
    QHBoxLayout *horizontalLayout_2;
    QLabel *qlAdvancementsVanillaExtrait;
    QLabel *qlDernierImportVanilla;
    QFrame *line;
    QGridLayout *gridLayout_6;
    QPushButton *qpbDossierBlazeandcave;
    QLabel *qlDossierBlazeandcave;
    QLineEdit *qleDossierBlazeandcave;
    QPushButton *qpbExtraireProgresBacap;
    QHBoxLayout *horizontalLayout;
    QLabel *qlAdvancementsBacapExtrait;
    QLabel *qlDernierImportBacap;
    QFrame *line_3;
    QGridLayout *gridLayout;
    QLineEdit *qleFichierProgres;
    QPushButton *qpbSelectionFichierProgres;
    QPushButton *qpbImportProgresJoueur;
    QLabel *qlFichierProgres;
    QHBoxLayout *horizontalLayout_4;
    QLabel *qlProgresPerso;
    QLabel *qlDernierImportPerso;
    QFrame *line_2;
    QLabel *label_14;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *qpbReadJSONsVanilla;
    QPushButton *qpbReadJSONsBlazeandcave;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_5;
    QPushButton *qpbReadAllJSONs;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *qpbReadJSON;
    QMenuBar *qmbMenuPrincipal;
    QMenu *qmFichier;
    QMenu *qmOutils;
    QMenu *qmAide;
    QStatusBar *statusbar;
    QDockWidget *qdwOpe;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *qgbFiltres;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *qcbStatistiques;
    QCheckBox *qcbMilestones;
    QLabel *label_13;
    QComboBox *qcbFiltreTitre;
    QLabel *label_2;
    QLabel *label_11;
    QFrame *line_8;
    QCheckBox *qcbAutoCompletion;
    QComboBox *qcbFiltreOrigine;
    QFrame *line_7;
    QLabel *label_4;
    QDateTimeEdit *qdteFrom;
    QComboBox *qcbFiltreType;
    QLabel *label_3;
    QFrame *line_9;
    QDateTimeEdit *qdteTo;
    QComboBox *qcbFiltreProgresFinis;
    QLabel *label;
    QComboBox *qcbFiltreConditionFait;
    QLabel *label_6;
    QLabel *label_12;
    QCheckBox *qcbRegExp;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *qgbOperations;
    QGridLayout *gridLayout_4;
    QPushButton *qpbClearFilter;
    QPushButton *pbImprimer;
    QPushButton *qpbResetDates;
    QGroupBox *qgbStats;
    QGridLayout *gridLayout_5;
    QRadioButton *qrbCerce;
    QRadioButton *qrbLigne;
    QPushButton *qpbAfficherGraphique;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *qlVanilla;
    QLabel *qlBacap;
    QLabel *qlTotal;
    QLabel *qlTitreVanilla;
    QLabel *qlTitreBacap;
    QLabel *qlTitreTotal;
    QGroupBox *qgbLegende;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_10;

    void setupUi(QMainWindow *FRM_Principale)
    {
        if (FRM_Principale->objectName().isEmpty())
            FRM_Principale->setObjectName(QString::fromUtf8("FRM_Principale"));
        FRM_Principale->resize(1000, 850);
        qaQuitter = new QAction(FRM_Principale);
        qaQuitter->setObjectName(QString::fromUtf8("qaQuitter"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/close_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        qaQuitter->setIcon(icon);
        qaSettings = new QAction(FRM_Principale);
        qaSettings->setObjectName(QString::fromUtf8("qaSettings"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/settings_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        qaSettings->setIcon(icon1);
        qaAbout = new QAction(FRM_Principale);
        qaAbout->setObjectName(QString::fromUtf8("qaAbout"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/about_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        qaAbout->setIcon(icon2);
        qaUpdate = new QAction(FRM_Principale);
        qaUpdate->setObjectName(QString::fromUtf8("qaUpdate"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/update_24.png"), QSize(), QIcon::Normal, QIcon::Off);
        qaUpdate->setIcon(icon3);
        qaImprimerVue = new QAction(FRM_Principale);
        qaImprimerVue->setObjectName(QString::fromUtf8("qaImprimerVue"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/icons8_print_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
        qaImprimerVue->setIcon(icon4);
        centralwidget = new QWidget(FRM_Principale);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        hlLanceurLangue = new QHBoxLayout();
        hlLanceurLangue->setObjectName(QString::fromUtf8("hlLanceurLangue"));
        qlLanceur = new QLabel(centralwidget);
        qlLanceur->setObjectName(QString::fromUtf8("qlLanceur"));
        qlLanceur->setMinimumSize(QSize(140, 0));
        qlLanceur->setMaximumSize(QSize(120, 16777215));

        hlLanceurLangue->addWidget(qlLanceur);

        qcbLauncher = new QComboBox(centralwidget);
        qcbLauncher->setObjectName(QString::fromUtf8("qcbLauncher"));

        hlLanceurLangue->addWidget(qcbLauncher);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        hlLanceurLangue->addWidget(line_4);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        hlLanceurLangue->addWidget(label_5);

        qcbLangue = new QComboBox(centralwidget);
        qcbLangue->setObjectName(QString::fromUtf8("qcbLangue"));

        hlLanceurLangue->addWidget(qcbLangue);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlLanceurLangue->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(hlLanceurLangue);

        hlDossierLanceur = new QHBoxLayout();
        hlDossierLanceur->setObjectName(QString::fromUtf8("hlDossierLanceur"));
        hlDossierLanceur->setContentsMargins(-1, 0, -1, -1);
        qlDossierLanceur = new QLabel(centralwidget);
        qlDossierLanceur->setObjectName(QString::fromUtf8("qlDossierLanceur"));
        qlDossierLanceur->setMinimumSize(QSize(140, 0));
        qlDossierLanceur->setMaximumSize(QSize(120, 16777215));

        hlDossierLanceur->addWidget(qlDossierLanceur);

        qleDossierLanceur = new QLineEdit(centralwidget);
        qleDossierLanceur->setObjectName(QString::fromUtf8("qleDossierLanceur"));
        qleDossierLanceur->setReadOnly(true);

        hlDossierLanceur->addWidget(qleDossierLanceur);

        qpbSelectionDossierLanceur = new QPushButton(centralwidget);
        qpbSelectionDossierLanceur->setObjectName(QString::fromUtf8("qpbSelectionDossierLanceur"));
        qpbSelectionDossierLanceur->setMinimumSize(QSize(30, 0));
        qpbSelectionDossierLanceur->setMaximumSize(QSize(30, 16777215));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/folder_24px_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        qpbSelectionDossierLanceur->setIcon(icon5);

        hlDossierLanceur->addWidget(qpbSelectionDossierLanceur);


        verticalLayout->addLayout(hlDossierLanceur);

        gdVersion = new QGridLayout();
        gdVersion->setObjectName(QString::fromUtf8("gdVersion"));
        gdVersion->setContentsMargins(-1, 0, -1, -1);
        qcbVersion = new QComboBox(centralwidget);
        qcbVersion->setObjectName(QString::fromUtf8("qcbVersion"));
        qcbVersion->setMinimumSize(QSize(100, 0));

        gdVersion->addWidget(qcbVersion, 0, 1, 1, 1);

        qleCheminVersion = new QLineEdit(centralwidget);
        qleCheminVersion->setObjectName(QString::fromUtf8("qleCheminVersion"));
        qleCheminVersion->setCursor(QCursor(Qt::ArrowCursor));
        qleCheminVersion->setReadOnly(true);

        gdVersion->addWidget(qleCheminVersion, 0, 2, 1, 1);

        qlVersion = new QLabel(centralwidget);
        qlVersion->setObjectName(QString::fromUtf8("qlVersion"));
        qlVersion->setMinimumSize(QSize(140, 0));
        qlVersion->setMaximumSize(QSize(120, 16777215));

        gdVersion->addWidget(qlVersion, 0, 0, 1, 1);

        qpbExtraireProgresVanilla = new QPushButton(centralwidget);
        qpbExtraireProgresVanilla->setObjectName(QString::fromUtf8("qpbExtraireProgresVanilla"));

        gdVersion->addWidget(qpbExtraireProgresVanilla, 0, 3, 1, 2);


        verticalLayout->addLayout(gdVersion);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        qlAdvancementsVanillaExtrait = new QLabel(centralwidget);
        qlAdvancementsVanillaExtrait->setObjectName(QString::fromUtf8("qlAdvancementsVanillaExtrait"));

        horizontalLayout_2->addWidget(qlAdvancementsVanillaExtrait);

        qlDernierImportVanilla = new QLabel(centralwidget);
        qlDernierImportVanilla->setObjectName(QString::fromUtf8("qlDernierImportVanilla"));

        horizontalLayout_2->addWidget(qlDernierImportVanilla);


        verticalLayout->addLayout(horizontalLayout_2);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(-1, 0, -1, -1);
        qpbDossierBlazeandcave = new QPushButton(centralwidget);
        qpbDossierBlazeandcave->setObjectName(QString::fromUtf8("qpbDossierBlazeandcave"));
        qpbDossierBlazeandcave->setIcon(icon5);

        gridLayout_6->addWidget(qpbDossierBlazeandcave, 0, 2, 1, 1);

        qlDossierBlazeandcave = new QLabel(centralwidget);
        qlDossierBlazeandcave->setObjectName(QString::fromUtf8("qlDossierBlazeandcave"));
        qlDossierBlazeandcave->setMinimumSize(QSize(140, 0));
        qlDossierBlazeandcave->setMaximumSize(QSize(120, 16777215));

        gridLayout_6->addWidget(qlDossierBlazeandcave, 0, 0, 1, 1);

        qleDossierBlazeandcave = new QLineEdit(centralwidget);
        qleDossierBlazeandcave->setObjectName(QString::fromUtf8("qleDossierBlazeandcave"));
        qleDossierBlazeandcave->setCursor(QCursor(Qt::ArrowCursor));
        qleDossierBlazeandcave->setReadOnly(true);

        gridLayout_6->addWidget(qleDossierBlazeandcave, 0, 1, 1, 1);

        qpbExtraireProgresBacap = new QPushButton(centralwidget);
        qpbExtraireProgresBacap->setObjectName(QString::fromUtf8("qpbExtraireProgresBacap"));

        gridLayout_6->addWidget(qpbExtraireProgresBacap, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        qlAdvancementsBacapExtrait = new QLabel(centralwidget);
        qlAdvancementsBacapExtrait->setObjectName(QString::fromUtf8("qlAdvancementsBacapExtrait"));

        horizontalLayout->addWidget(qlAdvancementsBacapExtrait);

        qlDernierImportBacap = new QLabel(centralwidget);
        qlDernierImportBacap->setObjectName(QString::fromUtf8("qlDernierImportBacap"));

        horizontalLayout->addWidget(qlDernierImportBacap);


        verticalLayout->addLayout(horizontalLayout);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        qleFichierProgres = new QLineEdit(centralwidget);
        qleFichierProgres->setObjectName(QString::fromUtf8("qleFichierProgres"));
        qleFichierProgres->setMaximumSize(QSize(16777215, 16777215));
        qleFichierProgres->setCursor(QCursor(Qt::ArrowCursor));
        qleFichierProgres->setReadOnly(true);

        gridLayout->addWidget(qleFichierProgres, 0, 1, 1, 1);

        qpbSelectionFichierProgres = new QPushButton(centralwidget);
        qpbSelectionFichierProgres->setObjectName(QString::fromUtf8("qpbSelectionFichierProgres"));
        qpbSelectionFichierProgres->setMaximumSize(QSize(30, 16777215));
        qpbSelectionFichierProgres->setIcon(icon5);

        gridLayout->addWidget(qpbSelectionFichierProgres, 0, 2, 1, 1);

        qpbImportProgresJoueur = new QPushButton(centralwidget);
        qpbImportProgresJoueur->setObjectName(QString::fromUtf8("qpbImportProgresJoueur"));

        gridLayout->addWidget(qpbImportProgresJoueur, 0, 3, 1, 1);

        qlFichierProgres = new QLabel(centralwidget);
        qlFichierProgres->setObjectName(QString::fromUtf8("qlFichierProgres"));
        qlFichierProgres->setMinimumSize(QSize(140, 0));
        qlFichierProgres->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(qlFichierProgres, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        qlProgresPerso = new QLabel(centralwidget);
        qlProgresPerso->setObjectName(QString::fromUtf8("qlProgresPerso"));

        horizontalLayout_4->addWidget(qlProgresPerso);

        qlDernierImportPerso = new QLabel(centralwidget);
        qlDernierImportPerso->setObjectName(QString::fromUtf8("qlDernierImportPerso"));

        horizontalLayout_4->addWidget(qlDernierImportPerso);


        verticalLayout->addLayout(horizontalLayout_4);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        label_14 = new QLabel(centralwidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        QFont font;
        font.setFamily(QString::fromUtf8("Minecrafter"));
        font.setPointSize(10);
        label_14->setFont(font);
        label_14->setTextFormat(Qt::RichText);
        label_14->setScaledContents(false);

        verticalLayout->addWidget(label_14);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSortingEnabled(true);

        verticalLayout->addWidget(tableView);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        qpbReadJSONsVanilla = new QPushButton(centralwidget);
        qpbReadJSONsVanilla->setObjectName(QString::fromUtf8("qpbReadJSONsVanilla"));

        horizontalLayout_5->addWidget(qpbReadJSONsVanilla);

        qpbReadJSONsBlazeandcave = new QPushButton(centralwidget);
        qpbReadJSONsBlazeandcave->setObjectName(QString::fromUtf8("qpbReadJSONsBlazeandcave"));

        horizontalLayout_5->addWidget(qpbReadJSONsBlazeandcave);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_5);

        qpbReadAllJSONs = new QPushButton(centralwidget);
        qpbReadAllJSONs->setObjectName(QString::fromUtf8("qpbReadAllJSONs"));

        horizontalLayout_5->addWidget(qpbReadAllJSONs);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        qpbReadJSON = new QPushButton(centralwidget);
        qpbReadJSON->setObjectName(QString::fromUtf8("qpbReadJSON"));

        horizontalLayout_3->addWidget(qpbReadJSON);


        verticalLayout->addLayout(horizontalLayout_3);

        FRM_Principale->setCentralWidget(centralwidget);
        qmbMenuPrincipal = new QMenuBar(FRM_Principale);
        qmbMenuPrincipal->setObjectName(QString::fromUtf8("qmbMenuPrincipal"));
        qmbMenuPrincipal->setGeometry(QRect(0, 0, 1000, 21));
        qmFichier = new QMenu(qmbMenuPrincipal);
        qmFichier->setObjectName(QString::fromUtf8("qmFichier"));
        qmOutils = new QMenu(qmbMenuPrincipal);
        qmOutils->setObjectName(QString::fromUtf8("qmOutils"));
        qmAide = new QMenu(qmbMenuPrincipal);
        qmAide->setObjectName(QString::fromUtf8("qmAide"));
        FRM_Principale->setMenuBar(qmbMenuPrincipal);
        statusbar = new QStatusBar(FRM_Principale);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FRM_Principale->setStatusBar(statusbar);
        qdwOpe = new QDockWidget(FRM_Principale);
        qdwOpe->setObjectName(QString::fromUtf8("qdwOpe"));
        qdwOpe->setMinimumSize(QSize(957, 278));
        qdwOpe->setFloating(false);
        qdwOpe->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        dockWidgetContents_2->setAutoFillBackground(false);
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        qgbFiltres = new QGroupBox(dockWidgetContents_2);
        qgbFiltres->setObjectName(QString::fromUtf8("qgbFiltres"));
        qgbFiltres->setMinimumSize(QSize(0, 0));
        gridLayout_3 = new QGridLayout(qgbFiltres);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 12, 1, 1);

        qcbStatistiques = new QCheckBox(qgbFiltres);
        qcbStatistiques->setObjectName(QString::fromUtf8("qcbStatistiques"));

        gridLayout_3->addWidget(qcbStatistiques, 1, 8, 1, 1);

        qcbMilestones = new QCheckBox(qgbFiltres);
        qcbMilestones->setObjectName(QString::fromUtf8("qcbMilestones"));
        qcbMilestones->setMinimumSize(QSize(140, 0));

        gridLayout_3->addWidget(qcbMilestones, 0, 8, 1, 1);

        label_13 = new QLabel(qgbFiltres);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 1, 10, 1, 1);

        qcbFiltreTitre = new QComboBox(qgbFiltres);
        qcbFiltreTitre->setObjectName(QString::fromUtf8("qcbFiltreTitre"));
        qcbFiltreTitre->setMinimumSize(QSize(200, 0));
        qcbFiltreTitre->setEditable(true);
        qcbFiltreTitre->setMaxVisibleItems(30);
        qcbFiltreTitre->setInsertPolicy(QComboBox::NoInsert);

        gridLayout_3->addWidget(qcbFiltreTitre, 0, 4, 1, 2);

        label_2 = new QLabel(qgbFiltres);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label_2, 2, 3, 1, 1);

        label_11 = new QLabel(qgbFiltres);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_11, 0, 10, 1, 2);

        line_8 = new QFrame(qgbFiltres);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_8, 0, 6, 3, 1);

        qcbAutoCompletion = new QCheckBox(qgbFiltres);
        qcbAutoCompletion->setObjectName(QString::fromUtf8("qcbAutoCompletion"));

        gridLayout_3->addWidget(qcbAutoCompletion, 1, 5, 1, 1);

        qcbFiltreOrigine = new QComboBox(qgbFiltres);
        qcbFiltreOrigine->setObjectName(QString::fromUtf8("qcbFiltreOrigine"));
        qcbFiltreOrigine->setMinimumSize(QSize(100, 0));

        gridLayout_3->addWidget(qcbFiltreOrigine, 0, 1, 1, 1);

        line_7 = new QFrame(qgbFiltres);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_7, 0, 2, 3, 1);

        label_4 = new QLabel(qgbFiltres);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(100, 0));
        label_4->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        qdteFrom = new QDateTimeEdit(qgbFiltres);
        qdteFrom->setObjectName(QString::fromUtf8("qdteFrom"));
        qdteFrom->setCalendarPopup(true);

        gridLayout_3->addWidget(qdteFrom, 1, 11, 1, 1);

        qcbFiltreType = new QComboBox(qgbFiltres);
        qcbFiltreType->setObjectName(QString::fromUtf8("qcbFiltreType"));

        gridLayout_3->addWidget(qcbFiltreType, 2, 8, 1, 1);

        label_3 = new QLabel(qgbFiltres);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(100, 0));
        label_3->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        line_9 = new QFrame(qgbFiltres);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setFrameShape(QFrame::VLine);
        line_9->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_9, 0, 9, 3, 1);

        qdteTo = new QDateTimeEdit(qgbFiltres);
        qdteTo->setObjectName(QString::fromUtf8("qdteTo"));
        qdteTo->setCalendarPopup(true);

        gridLayout_3->addWidget(qdteTo, 2, 11, 1, 1);

        qcbFiltreProgresFinis = new QComboBox(qgbFiltres);
        qcbFiltreProgresFinis->setObjectName(QString::fromUtf8("qcbFiltreProgresFinis"));
        qcbFiltreProgresFinis->setMinimumSize(QSize(100, 0));

        gridLayout_3->addWidget(qcbFiltreProgresFinis, 2, 1, 1, 1);

        label = new QLabel(qgbFiltres);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label, 0, 3, 1, 1);

        qcbFiltreConditionFait = new QComboBox(qgbFiltres);
        qcbFiltreConditionFait->setObjectName(QString::fromUtf8("qcbFiltreConditionFait"));
        qcbFiltreConditionFait->setMinimumSize(QSize(100, 0));
        qcbFiltreConditionFait->setEditable(false);
        qcbFiltreConditionFait->setInsertPolicy(QComboBox::NoInsert);

        gridLayout_3->addWidget(qcbFiltreConditionFait, 2, 4, 1, 2);

        label_6 = new QLabel(qgbFiltres);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 2, 7, 1, 1);

        label_12 = new QLabel(qgbFiltres);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 2, 10, 1, 1);

        qcbRegExp = new QCheckBox(qgbFiltres);
        qcbRegExp->setObjectName(QString::fromUtf8("qcbRegExp"));

        gridLayout_3->addWidget(qcbRegExp, 1, 4, 1, 1);


        verticalLayout_2->addWidget(qgbFiltres);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_9->setContentsMargins(-1, 0, -1, -1);
        qgbOperations = new QGroupBox(dockWidgetContents_2);
        qgbOperations->setObjectName(QString::fromUtf8("qgbOperations"));
        qgbOperations->setFlat(false);
        qgbOperations->setCheckable(false);
        gridLayout_4 = new QGridLayout(qgbOperations);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(-1, 0, -1, 0);
        qpbClearFilter = new QPushButton(qgbOperations);
        qpbClearFilter->setObjectName(QString::fromUtf8("qpbClearFilter"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/icons8_broom_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
        qpbClearFilter->setIcon(icon6);

        gridLayout_4->addWidget(qpbClearFilter, 0, 0, 1, 1);

        pbImprimer = new QPushButton(qgbOperations);
        pbImprimer->setObjectName(QString::fromUtf8("pbImprimer"));
        pbImprimer->setIcon(icon4);

        gridLayout_4->addWidget(pbImprimer, 0, 1, 1, 1);

        qpbResetDates = new QPushButton(qgbOperations);
        qpbResetDates->setObjectName(QString::fromUtf8("qpbResetDates"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/icons8_day_off_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
        qpbResetDates->setIcon(icon7);

        gridLayout_4->addWidget(qpbResetDates, 1, 0, 1, 1);


        horizontalLayout_9->addWidget(qgbOperations);

        qgbStats = new QGroupBox(dockWidgetContents_2);
        qgbStats->setObjectName(QString::fromUtf8("qgbStats"));
        gridLayout_5 = new QGridLayout(qgbStats);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        qrbCerce = new QRadioButton(qgbStats);
        qrbCerce->setObjectName(QString::fromUtf8("qrbCerce"));

        gridLayout_5->addWidget(qrbCerce, 1, 0, 1, 1);

        qrbLigne = new QRadioButton(qgbStats);
        qrbLigne->setObjectName(QString::fromUtf8("qrbLigne"));

        gridLayout_5->addWidget(qrbLigne, 0, 0, 1, 1);

        qpbAfficherGraphique = new QPushButton(qgbStats);
        qpbAfficherGraphique->setObjectName(QString::fromUtf8("qpbAfficherGraphique"));

        gridLayout_5->addWidget(qpbAfficherGraphique, 2, 0, 1, 1);


        horizontalLayout_9->addWidget(qgbStats);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        groupBox = new QGroupBox(dockWidgetContents_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        qlVanilla = new QLabel(groupBox);
        qlVanilla->setObjectName(QString::fromUtf8("qlVanilla"));
        qlVanilla->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(qlVanilla, 0, 1, 1, 1);

        qlBacap = new QLabel(groupBox);
        qlBacap->setObjectName(QString::fromUtf8("qlBacap"));
        qlBacap->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(qlBacap, 1, 1, 1, 1);

        qlTotal = new QLabel(groupBox);
        qlTotal->setObjectName(QString::fromUtf8("qlTotal"));
        qlTotal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(qlTotal, 2, 1, 1, 1);

        qlTitreVanilla = new QLabel(groupBox);
        qlTitreVanilla->setObjectName(QString::fromUtf8("qlTitreVanilla"));

        gridLayout_2->addWidget(qlTitreVanilla, 0, 0, 1, 1);

        qlTitreBacap = new QLabel(groupBox);
        qlTitreBacap->setObjectName(QString::fromUtf8("qlTitreBacap"));

        gridLayout_2->addWidget(qlTitreBacap, 1, 0, 1, 1);

        qlTitreTotal = new QLabel(groupBox);
        qlTitreTotal->setObjectName(QString::fromUtf8("qlTitreTotal"));

        gridLayout_2->addWidget(qlTitreTotal, 2, 0, 1, 1);


        horizontalLayout_9->addWidget(groupBox);

        qgbLegende = new QGroupBox(dockWidgetContents_2);
        qgbLegende->setObjectName(QString::fromUtf8("qgbLegende"));
        verticalLayout_4 = new QVBoxLayout(qgbLegende);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_4->setContentsMargins(-1, 0, -1, 0);
        label_9 = new QLabel(qgbLegende);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setLineWidth(1);
        label_9->setTextFormat(Qt::RichText);

        verticalLayout_4->addWidget(label_9);

        label_7 = new QLabel(qgbLegende);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setTextFormat(Qt::RichText);

        verticalLayout_4->addWidget(label_7);

        label_8 = new QLabel(qgbLegende);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setTextFormat(Qt::RichText);

        verticalLayout_4->addWidget(label_8);

        label_10 = new QLabel(qgbLegende);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setTextFormat(Qt::RichText);

        verticalLayout_4->addWidget(label_10);


        horizontalLayout_9->addWidget(qgbLegende);


        verticalLayout_2->addLayout(horizontalLayout_9);

        qdwOpe->setWidget(dockWidgetContents_2);
        FRM_Principale->addDockWidget(Qt::BottomDockWidgetArea, qdwOpe);

        qmbMenuPrincipal->addAction(qmFichier->menuAction());
        qmbMenuPrincipal->addAction(qmOutils->menuAction());
        qmbMenuPrincipal->addAction(qmAide->menuAction());
        qmFichier->addAction(qaQuitter);
        qmOutils->addAction(qaImprimerVue);
        qmOutils->addAction(qaSettings);
        qmAide->addAction(qaUpdate);
        qmAide->addAction(qaAbout);

        retranslateUi(FRM_Principale);

        QMetaObject::connectSlotsByName(FRM_Principale);
    } // setupUi

    void retranslateUi(QMainWindow *FRM_Principale)
    {
        FRM_Principale->setWindowTitle(QCoreApplication::translate("FRM_Principale", "FRM_Principale", nullptr));
        qaQuitter->setText(QCoreApplication::translate("FRM_Principale", "&Quitter", nullptr));
#if QT_CONFIG(shortcut)
        qaQuitter->setShortcut(QCoreApplication::translate("FRM_Principale", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        qaSettings->setText(QCoreApplication::translate("FRM_Principale", "&Pr\303\251f\303\251rences...", nullptr));
#if QT_CONFIG(tooltip)
        qaSettings->setToolTip(QCoreApplication::translate("FRM_Principale", "Pr\303\251f\303\251rences (Ctrl+I)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        qaSettings->setShortcut(QCoreApplication::translate("FRM_Principale", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        qaAbout->setText(QCoreApplication::translate("FRM_Principale", "&A Propos...", nullptr));
#if QT_CONFIG(tooltip)
        qaAbout->setToolTip(QCoreApplication::translate("FRM_Principale", "A Propos (Ctrl+H)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        qaAbout->setShortcut(QCoreApplication::translate("FRM_Principale", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        qaUpdate->setText(QCoreApplication::translate("FRM_Principale", "V\303\251rifier les &mise \303\240 jour", nullptr));
#if QT_CONFIG(tooltip)
        qaUpdate->setToolTip(QCoreApplication::translate("FRM_Principale", "V\303\251rifier les mise \303\240 jour (Ctrl+U)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        qaUpdate->setShortcut(QCoreApplication::translate("FRM_Principale", "Ctrl+U", nullptr));
#endif // QT_CONFIG(shortcut)
        qaImprimerVue->setText(QCoreApplication::translate("FRM_Principale", "&Imprimer la vue", nullptr));
#if QT_CONFIG(tooltip)
        qaImprimerVue->setToolTip(QCoreApplication::translate("FRM_Principale", "Imprimer la vue (Ctrl+P)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        qaImprimerVue->setShortcut(QCoreApplication::translate("FRM_Principale", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        qlLanceur->setText(QCoreApplication::translate("FRM_Principale", "Lanceur Minecraft", nullptr));
        label_5->setText(QCoreApplication::translate("FRM_Principale", "Langue", nullptr));
        qlDossierLanceur->setText(QCoreApplication::translate("FRM_Principale", "Dossier Lanceur", nullptr));
        qpbSelectionDossierLanceur->setText(QString());
        qlVersion->setText(QCoreApplication::translate("FRM_Principale", "Version", nullptr));
        qpbExtraireProgresVanilla->setText(QCoreApplication::translate("FRM_Principale", "Extraire Progr\303\250s", nullptr));
        qlAdvancementsVanillaExtrait->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qlDernierImportVanilla->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qpbDossierBlazeandcave->setText(QString());
        qlDossierBlazeandcave->setText(QCoreApplication::translate("FRM_Principale", "Dossier 'Blaze and Cave'", nullptr));
        qleDossierBlazeandcave->setPlaceholderText(QCoreApplication::translate("FRM_Principale", "C:\\Users\\fake_Utilisateur\\AppData\\Roaming\\.minecraft\\saves\\Une_Sauvegarde\\datapacks\\bac_advancements", nullptr));
        qpbExtraireProgresBacap->setText(QCoreApplication::translate("FRM_Principale", "Extraire Progr\303\250s", nullptr));
        qlAdvancementsBacapExtrait->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qlDernierImportBacap->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qleFichierProgres->setInputMask(QString());
        qleFichierProgres->setPlaceholderText(QCoreApplication::translate("FRM_Principale", "C:\\Users\\fake_Utilisateur\\AppData\\Roaming\\.minecraft\\saves\\Une_Sauvegarde\\advancements\\3b6b3dcb-58ee-4538-b019-fa2e694cef8c.json", nullptr));
        qpbSelectionFichierProgres->setText(QString());
        qpbImportProgresJoueur->setText(QCoreApplication::translate("FRM_Principale", "Importer Progr\303\250s", nullptr));
        qlFichierProgres->setText(QCoreApplication::translate("FRM_Principale", "Fichier Progr\303\250s", nullptr));
        qlProgresPerso->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qlDernierImportPerso->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        label_14->setText(QCoreApplication::translate("FRM_Principale", "<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; color:#8bc34a;\">Vos Progres</span></p></body></html>", nullptr));
        qpbReadJSONsVanilla->setText(QCoreApplication::translate("FRM_Principale", "Comparer progr\303\250s Vanilla (seulement)", nullptr));
        qpbReadJSONsBlazeandcave->setText(QCoreApplication::translate("FRM_Principale", "Comparer progr\303\250s BACAP (seulement)", nullptr));
        qpbReadAllJSONs->setText(QCoreApplication::translate("FRM_Principale", "Comparer tous les progr\303\250s", nullptr));
        qpbReadJSON->setText(QCoreApplication::translate("FRM_Principale", "Read JSON (TEST)", nullptr));
        qmFichier->setTitle(QCoreApplication::translate("FRM_Principale", "&Fichier", nullptr));
        qmOutils->setTitle(QCoreApplication::translate("FRM_Principale", "&Outils", nullptr));
        qmAide->setTitle(QCoreApplication::translate("FRM_Principale", "&?", nullptr));
        qdwOpe->setWindowTitle(QCoreApplication::translate("FRM_Principale", "Op\303\251rations (Ctrl+O)", nullptr));
        qgbFiltres->setTitle(QCoreApplication::translate("FRM_Principale", "Filtres", nullptr));
        qcbStatistiques->setText(QCoreApplication::translate("FRM_Principale", "Masquer les Statistiques ?", nullptr));
        qcbMilestones->setText(QCoreApplication::translate("FRM_Principale", "Masquer les Milestones ?", nullptr));
        label_13->setText(QCoreApplication::translate("FRM_Principale", "Du", nullptr));
        label_2->setText(QCoreApplication::translate("FRM_Principale", "Condition Faite", nullptr));
        label_11->setText(QCoreApplication::translate("FRM_Principale", "Date r\303\251alisation", nullptr));
        qcbAutoCompletion->setText(QCoreApplication::translate("FRM_Principale", "Autocompl\303\251tion", nullptr));
        label_4->setText(QCoreApplication::translate("FRM_Principale", "Progr\303\250s Finis", nullptr));
        label_3->setText(QCoreApplication::translate("FRM_Principale", "Origine", nullptr));
        label->setText(QCoreApplication::translate("FRM_Principale", "Titre", nullptr));
        label_6->setText(QCoreApplication::translate("FRM_Principale", "Type Condition", nullptr));
        label_12->setText(QCoreApplication::translate("FRM_Principale", "Au", nullptr));
        qcbRegExp->setText(QCoreApplication::translate("FRM_Principale", "Expression R\303\251guli\303\250re", nullptr));
        qgbOperations->setTitle(QCoreApplication::translate("FRM_Principale", "Op\303\251rations", nullptr));
        qpbClearFilter->setText(QCoreApplication::translate("FRM_Principale", "Effacer les filtres", nullptr));
        pbImprimer->setText(QCoreApplication::translate("FRM_Principale", "Imprimer", nullptr));
        qpbResetDates->setText(QCoreApplication::translate("FRM_Principale", "Reset dates", nullptr));
        qgbStats->setTitle(QCoreApplication::translate("FRM_Principale", "Statistiques", nullptr));
        qrbCerce->setText(QCoreApplication::translate("FRM_Principale", "Graphique Ligne courbe", nullptr));
        qrbLigne->setText(QCoreApplication::translate("FRM_Principale", "Graphique Ligne", nullptr));
        qpbAfficherGraphique->setText(QCoreApplication::translate("FRM_Principale", "Afficher le Graphique", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FRM_Principale", "Compteurs Progr\303\250s", nullptr));
        qlVanilla->setText(QCoreApplication::translate("FRM_Principale", "x / x", nullptr));
        qlBacap->setText(QCoreApplication::translate("FRM_Principale", "x / x", nullptr));
        qlTotal->setText(QCoreApplication::translate("FRM_Principale", "x / x", nullptr));
        qlTitreVanilla->setText(QCoreApplication::translate("FRM_Principale", "Vanilla  :", nullptr));
        qlTitreBacap->setText(QCoreApplication::translate("FRM_Principale", "BACAP :", nullptr));
        qlTitreTotal->setText(QCoreApplication::translate("FRM_Principale", "Total    :", nullptr));
        qgbLegende->setTitle(QCoreApplication::translate("FRM_Principale", "L\303\251gende", nullptr));
        label_9->setText(QCoreApplication::translate("FRM_Principale", "<html><head/><body><p><span style=\" color:#006400;\">Progr\303\250s r\303\251alis\303\251</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("FRM_Principale", "<html><head/><body><p><span style=\" color:#8b0000;\">Condition de type ET</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("FRM_Principale", "<span style=\"color: blue;\">Condition de type OU</span>", nullptr));
        label_10->setText(QCoreApplication::translate("FRM_Principale", "<html><head/><body><p><span style=\" color:#808000;\">Condition Unique</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FRM_Principale: public Ui_FRM_Principale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_PRINCIPALE_H
