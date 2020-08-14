/********************************************************************************
** Form generated from reading UI file 'dia_parametres.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIA_PARAMETRES_H
#define UI_DIA_PARAMETRES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DIA_Parametres
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *general;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *gbMiseAJour;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *cbMiseAJourAuto;
    QHBoxLayout *hlNombreJourMiseAJour;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lMiseAJour1;
    QSpinBox *sbNombreJourMiseAJour;
    QLabel *lMiseAJour2;
    QCheckBox *cbBeta;
    QGroupBox *gbFenetrePrincipale;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *cbRestoreSizePos;
    QCheckBox *cbRestorePath;
    QCheckBox *cbMessageFermeture;
    QSpacerItem *verticalSpacer;
    QWidget *affichage;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *gbCaseACocher;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *cbFarmingVisible;
    QCheckBox *cbEtendreVisible;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbFermer;

    void setupUi(QDialog *DIA_Parametres)
    {
        if (DIA_Parametres->objectName().isEmpty())
            DIA_Parametres->setObjectName(QString::fromUtf8("DIA_Parametres"));
        DIA_Parametres->resize(410, 306);
        DIA_Parametres->setMinimumSize(QSize(410, 230));
        verticalLayout = new QVBoxLayout(DIA_Parametres);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(DIA_Parametres);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        general = new QWidget();
        general->setObjectName(QString::fromUtf8("general"));
        verticalLayout_2 = new QVBoxLayout(general);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gbMiseAJour = new QGroupBox(general);
        gbMiseAJour->setObjectName(QString::fromUtf8("gbMiseAJour"));
        verticalLayout_5 = new QVBoxLayout(gbMiseAJour);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        cbMiseAJourAuto = new QCheckBox(gbMiseAJour);
        cbMiseAJourAuto->setObjectName(QString::fromUtf8("cbMiseAJourAuto"));

        verticalLayout_5->addWidget(cbMiseAJourAuto);

        hlNombreJourMiseAJour = new QHBoxLayout();
        hlNombreJourMiseAJour->setObjectName(QString::fromUtf8("hlNombreJourMiseAJour"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hlNombreJourMiseAJour->addItem(horizontalSpacer_2);

        lMiseAJour1 = new QLabel(gbMiseAJour);
        lMiseAJour1->setObjectName(QString::fromUtf8("lMiseAJour1"));
        lMiseAJour1->setEnabled(false);

        hlNombreJourMiseAJour->addWidget(lMiseAJour1);

        sbNombreJourMiseAJour = new QSpinBox(gbMiseAJour);
        sbNombreJourMiseAJour->setObjectName(QString::fromUtf8("sbNombreJourMiseAJour"));
        sbNombreJourMiseAJour->setEnabled(false);
        sbNombreJourMiseAJour->setMaximumSize(QSize(40, 16777215));
        sbNombreJourMiseAJour->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        sbNombreJourMiseAJour->setMinimum(1);
        sbNombreJourMiseAJour->setMaximum(30);
        sbNombreJourMiseAJour->setValue(7);

        hlNombreJourMiseAJour->addWidget(sbNombreJourMiseAJour);

        lMiseAJour2 = new QLabel(gbMiseAJour);
        lMiseAJour2->setObjectName(QString::fromUtf8("lMiseAJour2"));
        lMiseAJour2->setEnabled(false);

        hlNombreJourMiseAJour->addWidget(lMiseAJour2);


        verticalLayout_5->addLayout(hlNombreJourMiseAJour);

        cbBeta = new QCheckBox(gbMiseAJour);
        cbBeta->setObjectName(QString::fromUtf8("cbBeta"));
        cbBeta->setEnabled(true);

        verticalLayout_5->addWidget(cbBeta);


        verticalLayout_2->addWidget(gbMiseAJour);

        gbFenetrePrincipale = new QGroupBox(general);
        gbFenetrePrincipale->setObjectName(QString::fromUtf8("gbFenetrePrincipale"));
        verticalLayout_6 = new QVBoxLayout(gbFenetrePrincipale);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        cbRestoreSizePos = new QCheckBox(gbFenetrePrincipale);
        cbRestoreSizePos->setObjectName(QString::fromUtf8("cbRestoreSizePos"));

        verticalLayout_6->addWidget(cbRestoreSizePos);

        cbRestorePath = new QCheckBox(gbFenetrePrincipale);
        cbRestorePath->setObjectName(QString::fromUtf8("cbRestorePath"));

        verticalLayout_6->addWidget(cbRestorePath);

        cbMessageFermeture = new QCheckBox(gbFenetrePrincipale);
        cbMessageFermeture->setObjectName(QString::fromUtf8("cbMessageFermeture"));

        verticalLayout_6->addWidget(cbMessageFermeture);


        verticalLayout_2->addWidget(gbFenetrePrincipale);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        tabWidget->addTab(general, QString());
        affichage = new QWidget();
        affichage->setObjectName(QString::fromUtf8("affichage"));
        verticalLayout_3 = new QVBoxLayout(affichage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gbCaseACocher = new QGroupBox(affichage);
        gbCaseACocher->setObjectName(QString::fromUtf8("gbCaseACocher"));
        verticalLayout_4 = new QVBoxLayout(gbCaseACocher);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        cbFarmingVisible = new QCheckBox(gbCaseACocher);
        cbFarmingVisible->setObjectName(QString::fromUtf8("cbFarmingVisible"));

        verticalLayout_4->addWidget(cbFarmingVisible);

        cbEtendreVisible = new QCheckBox(gbCaseACocher);
        cbEtendreVisible->setObjectName(QString::fromUtf8("cbEtendreVisible"));

        verticalLayout_4->addWidget(cbEtendreVisible);


        verticalLayout_3->addWidget(gbCaseACocher);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(affichage, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbFermer = new QPushButton(DIA_Parametres);
        pbFermer->setObjectName(QString::fromUtf8("pbFermer"));

        horizontalLayout->addWidget(pbFermer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DIA_Parametres);
        QObject::connect(pbFermer, SIGNAL(clicked()), DIA_Parametres, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DIA_Parametres);
    } // setupUi

    void retranslateUi(QDialog *DIA_Parametres)
    {
        DIA_Parametres->setWindowTitle(QCoreApplication::translate("DIA_Parametres", "Pr\303\251f\303\251rences", nullptr));
        gbMiseAJour->setTitle(QCoreApplication::translate("DIA_Parametres", "Mise \303\240 jour", nullptr));
        cbMiseAJourAuto->setText(QCoreApplication::translate("DIA_Parametres", "V\303\251rifier les mises \303\240 jours automatiquement ?", nullptr));
        lMiseAJour1->setText(QCoreApplication::translate("DIA_Parametres", "V\303\251rifier les mise \303\240 jour tous les", nullptr));
        lMiseAJour2->setText(QCoreApplication::translate("DIA_Parametres", "jour(s)", nullptr));
        cbBeta->setText(QCoreApplication::translate("DIA_Parametres", "Rechercher les mises \303\240 jour B\303\252ta (Instable) ?", nullptr));
        gbFenetrePrincipale->setTitle(QCoreApplication::translate("DIA_Parametres", "Fen\303\252tre Principale", nullptr));
        cbRestoreSizePos->setText(QCoreApplication::translate("DIA_Parametres", "Restaurer taille et position", nullptr));
        cbRestorePath->setText(QCoreApplication::translate("DIA_Parametres", "Restaurer les derniers chemins utilis\303\251s", nullptr));
        cbMessageFermeture->setText(QCoreApplication::translate("DIA_Parametres", "Message de confirmation de fermeture", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(general), QCoreApplication::translate("DIA_Parametres", "G\303\251n\303\251ral", nullptr));
        gbCaseACocher->setTitle(QCoreApplication::translate("DIA_Parametres", "Case \303\240 cocher", nullptr));
        cbFarmingVisible->setText(QCoreApplication::translate("DIA_Parametres", "Afficher 'Farming ?' sur la fen\303\252tre principale", nullptr));
        cbEtendreVisible->setText(QCoreApplication::translate("DIA_Parametres", "Afficher 'Etendre tout automatiquement ?' sur la fen\303\252tre principale", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(affichage), QCoreApplication::translate("DIA_Parametres", "Affichage", nullptr));
        pbFermer->setText(QCoreApplication::translate("DIA_Parametres", "Fermer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DIA_Parametres: public Ui_DIA_Parametres {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIA_PARAMETRES_H
