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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
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
    QLabel *qlVersion;
    QPushButton *qpbExtraireProgres;
    QLineEdit *qleCheminVersion;
    QLabel *qlLangExtraite;
    QLabel *qlAdvancementsExtrait;
    QFrame *line;
    QGridLayout *gridLayout_6;
    QPushButton *qpbDossierBlazeandcave;
    QLabel *qlDossierBlazeandcave;
    QCheckBox *qcbStatistiques;
    QLineEdit *qleDossierBlazeandcave;
    QCheckBox *qcbMilestones;
    QFrame *line_3;
    QGridLayout *gridLayout;
    QPushButton *qpbSelectionFichierProgres;
    QLineEdit *qleFichierProgres;
    QLabel *qlFichierProgres;
    QLabel *qlProgresPersoOuvert;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *qpbReadJSONsVanilla;
    QPushButton *qpbReadJSONsBlazeandcave;
    QFrame *line_5;
    QPushButton *qpbReadAllJSONs;
    QFrame *lineInDebug;
    QPushButton *qpbReadJSON;
    QProgressBar *qpbTraitementProgres;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *qgbFiltres;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QComboBox *qcbFiltreType;
    QLabel *label_13;
    QCheckBox *qcbRegExp;
    QLabel *label_6;
    QComboBox *qcbFiltreProgresFinis;
    QLabel *label_4;
    QDateTimeEdit *qdteFrom;
    QDateTimeEdit *qdteTo;
    QLabel *label_12;
    QLabel *label_3;
    QComboBox *qcbFiltreOrigine;
    QLabel *label_11;
    QLabel *label_2;
    QCheckBox *qcbAutoCompletion;
    QComboBox *qcbFiltreTitre;
    QComboBox *qcbFiltreConditionFait;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *qgbOperations;
    QGridLayout *gridLayout_4;
    QPushButton *qpbClearFilter;
    QPushButton *pbImprimer;
    QPushButton *qpbResetDates;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QMenuBar *qmbMenuPrincipal;
    QMenu *qmFichier;
    QMenu *qmOutils;
    QMenu *qmAide;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FRM_Principale)
    {
        if (FRM_Principale->objectName().isEmpty())
            FRM_Principale->setObjectName(QString::fromUtf8("FRM_Principale"));
        FRM_Principale->resize(1000, 800);
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

        qlVersion = new QLabel(centralwidget);
        qlVersion->setObjectName(QString::fromUtf8("qlVersion"));
        qlVersion->setMinimumSize(QSize(140, 0));
        qlVersion->setMaximumSize(QSize(120, 16777215));

        gdVersion->addWidget(qlVersion, 0, 0, 1, 1);

        qpbExtraireProgres = new QPushButton(centralwidget);
        qpbExtraireProgres->setObjectName(QString::fromUtf8("qpbExtraireProgres"));

        gdVersion->addWidget(qpbExtraireProgres, 0, 4, 1, 1);

        qleCheminVersion = new QLineEdit(centralwidget);
        qleCheminVersion->setObjectName(QString::fromUtf8("qleCheminVersion"));
        qleCheminVersion->setCursor(QCursor(Qt::ArrowCursor));
        qleCheminVersion->setReadOnly(true);

        gdVersion->addWidget(qleCheminVersion, 0, 2, 1, 1);

        qlLangExtraite = new QLabel(centralwidget);
        qlLangExtraite->setObjectName(QString::fromUtf8("qlLangExtraite"));

        gdVersion->addWidget(qlLangExtraite, 1, 2, 1, 1);

        qlAdvancementsExtrait = new QLabel(centralwidget);
        qlAdvancementsExtrait->setObjectName(QString::fromUtf8("qlAdvancementsExtrait"));

        gdVersion->addWidget(qlAdvancementsExtrait, 1, 0, 1, 2);


        verticalLayout->addLayout(gdVersion);

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
        qlDossierBlazeandcave->setMinimumSize(QSize(120, 0));
        qlDossierBlazeandcave->setMaximumSize(QSize(120, 16777215));

        gridLayout_6->addWidget(qlDossierBlazeandcave, 0, 0, 1, 1);

        qcbStatistiques = new QCheckBox(centralwidget);
        qcbStatistiques->setObjectName(QString::fromUtf8("qcbStatistiques"));

        gridLayout_6->addWidget(qcbStatistiques, 2, 1, 1, 1);

        qleDossierBlazeandcave = new QLineEdit(centralwidget);
        qleDossierBlazeandcave->setObjectName(QString::fromUtf8("qleDossierBlazeandcave"));
        qleDossierBlazeandcave->setCursor(QCursor(Qt::ArrowCursor));
        qleDossierBlazeandcave->setReadOnly(true);

        gridLayout_6->addWidget(qleDossierBlazeandcave, 0, 1, 1, 1);

        qcbMilestones = new QCheckBox(centralwidget);
        qcbMilestones->setObjectName(QString::fromUtf8("qcbMilestones"));
        qcbMilestones->setMinimumSize(QSize(140, 0));

        gridLayout_6->addWidget(qcbMilestones, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_6);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        qpbSelectionFichierProgres = new QPushButton(centralwidget);
        qpbSelectionFichierProgres->setObjectName(QString::fromUtf8("qpbSelectionFichierProgres"));
        qpbSelectionFichierProgres->setMaximumSize(QSize(30, 16777215));
        qpbSelectionFichierProgres->setIcon(icon5);

        gridLayout->addWidget(qpbSelectionFichierProgres, 1, 2, 1, 1);

        qleFichierProgres = new QLineEdit(centralwidget);
        qleFichierProgres->setObjectName(QString::fromUtf8("qleFichierProgres"));
        qleFichierProgres->setMaximumSize(QSize(16777215, 16777215));
        qleFichierProgres->setCursor(QCursor(Qt::ArrowCursor));
        qleFichierProgres->setReadOnly(true);

        gridLayout->addWidget(qleFichierProgres, 1, 1, 1, 1);

        qlFichierProgres = new QLabel(centralwidget);
        qlFichierProgres->setObjectName(QString::fromUtf8("qlFichierProgres"));
        qlFichierProgres->setMinimumSize(QSize(140, 0));
        qlFichierProgres->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(qlFichierProgres, 1, 0, 1, 1);

        qlProgresPersoOuvert = new QLabel(centralwidget);
        qlProgresPersoOuvert->setObjectName(QString::fromUtf8("qlProgresPersoOuvert"));

        gridLayout->addWidget(qlProgresPersoOuvert, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 0, -1, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);

        horizontalLayout_8->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        qpbReadJSONsVanilla = new QPushButton(centralwidget);
        qpbReadJSONsVanilla->setObjectName(QString::fromUtf8("qpbReadJSONsVanilla"));

        horizontalLayout_5->addWidget(qpbReadJSONsVanilla);

        qpbReadJSONsBlazeandcave = new QPushButton(centralwidget);
        qpbReadJSONsBlazeandcave->setObjectName(QString::fromUtf8("qpbReadJSONsBlazeandcave"));

        horizontalLayout_5->addWidget(qpbReadJSONsBlazeandcave);

        line_5 = new QFrame(centralwidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_5);

        qpbReadAllJSONs = new QPushButton(centralwidget);
        qpbReadAllJSONs->setObjectName(QString::fromUtf8("qpbReadAllJSONs"));

        horizontalLayout_5->addWidget(qpbReadAllJSONs);

        lineInDebug = new QFrame(centralwidget);
        lineInDebug->setObjectName(QString::fromUtf8("lineInDebug"));
        lineInDebug->setFrameShape(QFrame::VLine);
        lineInDebug->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(lineInDebug);

        qpbReadJSON = new QPushButton(centralwidget);
        qpbReadJSON->setObjectName(QString::fromUtf8("qpbReadJSON"));

        horizontalLayout_5->addWidget(qpbReadJSON);


        verticalLayout->addLayout(horizontalLayout_5);

        qpbTraitementProgres = new QProgressBar(centralwidget);
        qpbTraitementProgres->setObjectName(QString::fromUtf8("qpbTraitementProgres"));
        qpbTraitementProgres->setValue(24);

        verticalLayout->addWidget(qpbTraitementProgres);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSortingEnabled(true);

        verticalLayout->addWidget(tableView);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 0, -1, -1);
        qgbFiltres = new QGroupBox(centralwidget);
        qgbFiltres->setObjectName(QString::fromUtf8("qgbFiltres"));
        qgbFiltres->setMinimumSize(QSize(0, 0));
        gridLayout_3 = new QGridLayout(qgbFiltres);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(qgbFiltres);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label, 0, 2, 1, 1);

        qcbFiltreType = new QComboBox(qgbFiltres);
        qcbFiltreType->setObjectName(QString::fromUtf8("qcbFiltreType"));

        gridLayout_3->addWidget(qcbFiltreType, 2, 6, 1, 1);

        label_13 = new QLabel(qgbFiltres);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_3->addWidget(label_13, 1, 7, 1, 1);

        qcbRegExp = new QCheckBox(qgbFiltres);
        qcbRegExp->setObjectName(QString::fromUtf8("qcbRegExp"));

        gridLayout_3->addWidget(qcbRegExp, 1, 3, 1, 1);

        label_6 = new QLabel(qgbFiltres);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 2, 5, 1, 1);

        qcbFiltreProgresFinis = new QComboBox(qgbFiltres);
        qcbFiltreProgresFinis->setObjectName(QString::fromUtf8("qcbFiltreProgresFinis"));
        qcbFiltreProgresFinis->setMinimumSize(QSize(100, 0));

        gridLayout_3->addWidget(qcbFiltreProgresFinis, 2, 1, 1, 1);

        label_4 = new QLabel(qgbFiltres);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(100, 0));
        label_4->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        qdteFrom = new QDateTimeEdit(qgbFiltres);
        qdteFrom->setObjectName(QString::fromUtf8("qdteFrom"));
        qdteFrom->setCalendarPopup(true);

        gridLayout_3->addWidget(qdteFrom, 1, 8, 1, 1);

        qdteTo = new QDateTimeEdit(qgbFiltres);
        qdteTo->setObjectName(QString::fromUtf8("qdteTo"));
        qdteTo->setCalendarPopup(true);

        gridLayout_3->addWidget(qdteTo, 2, 8, 1, 1);

        label_12 = new QLabel(qgbFiltres);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 2, 7, 1, 1);

        label_3 = new QLabel(qgbFiltres);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(100, 0));
        label_3->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        qcbFiltreOrigine = new QComboBox(qgbFiltres);
        qcbFiltreOrigine->setObjectName(QString::fromUtf8("qcbFiltreOrigine"));
        qcbFiltreOrigine->setMinimumSize(QSize(100, 0));

        gridLayout_3->addWidget(qcbFiltreOrigine, 0, 1, 1, 1);

        label_11 = new QLabel(qgbFiltres);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_11, 0, 7, 1, 2);

        label_2 = new QLabel(qgbFiltres);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setMaximumSize(QSize(100, 16777215));

        gridLayout_3->addWidget(label_2, 2, 2, 1, 1);

        qcbAutoCompletion = new QCheckBox(qgbFiltres);
        qcbAutoCompletion->setObjectName(QString::fromUtf8("qcbAutoCompletion"));

        gridLayout_3->addWidget(qcbAutoCompletion, 1, 4, 1, 1);

        qcbFiltreTitre = new QComboBox(qgbFiltres);
        qcbFiltreTitre->setObjectName(QString::fromUtf8("qcbFiltreTitre"));
        qcbFiltreTitre->setMinimumSize(QSize(200, 0));
        qcbFiltreTitre->setEditable(true);
        qcbFiltreTitre->setMaxVisibleItems(30);
        qcbFiltreTitre->setInsertPolicy(QComboBox::NoInsert);

        gridLayout_3->addWidget(qcbFiltreTitre, 0, 3, 1, 2);

        qcbFiltreConditionFait = new QComboBox(qgbFiltres);
        qcbFiltreConditionFait->setObjectName(QString::fromUtf8("qcbFiltreConditionFait"));
        qcbFiltreConditionFait->setMinimumSize(QSize(100, 0));
        qcbFiltreConditionFait->setEditable(false);
        qcbFiltreConditionFait->setInsertPolicy(QComboBox::NoInsert);

        gridLayout_3->addWidget(qcbFiltreConditionFait, 2, 3, 1, 2);


        horizontalLayout_7->addWidget(qgbFiltres);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(-1, 0, -1, -1);
        qgbOperations = new QGroupBox(centralwidget);
        qgbOperations->setObjectName(QString::fromUtf8("qgbOperations"));
        gridLayout_4 = new QGridLayout(qgbOperations);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
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

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setTextFormat(Qt::RichText);

        gridLayout_5->addWidget(label_8, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setTextFormat(Qt::RichText);

        gridLayout_5->addWidget(label_7, 1, 0, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setTextFormat(Qt::RichText);

        gridLayout_5->addWidget(label_9, 0, 0, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setTextFormat(Qt::RichText);

        gridLayout_5->addWidget(label_10, 3, 0, 1, 1);


        horizontalLayout_9->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_9);

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
        qpbExtraireProgres->setText(QCoreApplication::translate("FRM_Principale", "Extraire Progr\303\250s", nullptr));
        qlLangExtraite->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qlAdvancementsExtrait->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qpbDossierBlazeandcave->setText(QString());
        qlDossierBlazeandcave->setText(QCoreApplication::translate("FRM_Principale", "Dossier 'Blaze and Cave'", nullptr));
        qcbStatistiques->setText(QCoreApplication::translate("FRM_Principale", "Afficher les Statistiquess ?", nullptr));
        qleDossierBlazeandcave->setPlaceholderText(QCoreApplication::translate("FRM_Principale", "C:\\Users\\fake_Utilisateur\\AppData\\Roaming\\.minecraft\\saves\\Une_Sauvegarde\\datapacks\\bac_advancements", nullptr));
        qcbMilestones->setText(QCoreApplication::translate("FRM_Principale", "Afficher les Milestones ?", nullptr));
        qpbSelectionFichierProgres->setText(QString());
        qleFichierProgres->setInputMask(QString());
        qleFichierProgres->setPlaceholderText(QCoreApplication::translate("FRM_Principale", "C:\\Users\\fake_Utilisateur\\AppData\\Roaming\\.minecraft\\saves\\Une_Sauvegarde\\advancements\\3b6b3dcb-58ee-4538-b019-fa2e694cef8c.json", nullptr));
        qlFichierProgres->setText(QCoreApplication::translate("FRM_Principale", "Fichier Progr\303\250s", nullptr));
        qlProgresPersoOuvert->setText(QCoreApplication::translate("FRM_Principale", "TextLabel", nullptr));
        qpbReadJSONsVanilla->setText(QCoreApplication::translate("FRM_Principale", "Comparer progr\303\250s Vanilla (seulement)", nullptr));
        qpbReadJSONsBlazeandcave->setText(QCoreApplication::translate("FRM_Principale", "Comparer progr\303\250s 'Blaze and Cave' (seulement)", nullptr));
        qpbReadAllJSONs->setText(QCoreApplication::translate("FRM_Principale", "Comparer tous les progr\303\250s (Vanilla + Blaze and Cave)", nullptr));
        qpbReadJSON->setText(QCoreApplication::translate("FRM_Principale", "Read JSON (TEST)", nullptr));
        qgbFiltres->setTitle(QCoreApplication::translate("FRM_Principale", "Filtres", nullptr));
        label->setText(QCoreApplication::translate("FRM_Principale", "Titre", nullptr));
        label_13->setText(QCoreApplication::translate("FRM_Principale", "Du", nullptr));
        qcbRegExp->setText(QCoreApplication::translate("FRM_Principale", "Expression R\303\251guli\303\250re", nullptr));
        label_6->setText(QCoreApplication::translate("FRM_Principale", "Type Condition", nullptr));
        label_4->setText(QCoreApplication::translate("FRM_Principale", "Progr\303\250s Finis", nullptr));
        label_12->setText(QCoreApplication::translate("FRM_Principale", "Au", nullptr));
        label_3->setText(QCoreApplication::translate("FRM_Principale", "Origine", nullptr));
        label_11->setText(QCoreApplication::translate("FRM_Principale", "Date r\303\251alisation", nullptr));
        label_2->setText(QCoreApplication::translate("FRM_Principale", "Condition Faite", nullptr));
        qcbAutoCompletion->setText(QCoreApplication::translate("FRM_Principale", "Autocompl\303\251tion", nullptr));
        qgbOperations->setTitle(QCoreApplication::translate("FRM_Principale", "Op\303\251rations", nullptr));
        qpbClearFilter->setText(QCoreApplication::translate("FRM_Principale", "Effacer les filtres", nullptr));
        pbImprimer->setText(QCoreApplication::translate("FRM_Principale", "Imprimer", nullptr));
        qpbResetDates->setText(QCoreApplication::translate("FRM_Principale", "Reset dates", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FRM_Principale", "L\303\251gende", nullptr));
        label_8->setText(QCoreApplication::translate("FRM_Principale", "<span style=\"color: blue;\">Condition de type OU</span>", nullptr));
        label_7->setText(QCoreApplication::translate("FRM_Principale", "<html><head/><body><p><span style=\" color:#8b0000;\">Condition de type ET</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("FRM_Principale", "<html><head/><body><p><span style=\" color:#006400;\">Progr\303\250s r\303\251alis\303\251</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("FRM_Principale", "<html><head/><body><p><span style=\" color:#808000;\">Condition Unique</span></p></body></html>", nullptr));
        qmFichier->setTitle(QCoreApplication::translate("FRM_Principale", "&Fichier", nullptr));
        qmOutils->setTitle(QCoreApplication::translate("FRM_Principale", "&Outils", nullptr));
        qmAide->setTitle(QCoreApplication::translate("FRM_Principale", "&?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FRM_Principale: public Ui_FRM_Principale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRM_PRINCIPALE_H
