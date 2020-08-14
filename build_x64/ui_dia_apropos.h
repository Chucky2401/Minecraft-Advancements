/********************************************************************************
** Form generated from reading UI file 'dia_apropos.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIA_APROPOS_H
#define UI_DIA_APROPOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DIA_apropos
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lNomApp;
    QLabel *lVersionApp;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbFermer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *DIA_apropos)
    {
        if (DIA_apropos->objectName().isEmpty())
            DIA_apropos->setObjectName(QString::fromUtf8("DIA_apropos"));
        DIA_apropos->setWindowModality(Qt::ApplicationModal);
        DIA_apropos->resize(400, 220);
        DIA_apropos->setMinimumSize(QSize(400, 220));
        DIA_apropos->setMaximumSize(QSize(400, 220));
        DIA_apropos->setModal(true);
        verticalLayout = new QVBoxLayout(DIA_apropos);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lNomApp = new QLabel(DIA_apropos);
        lNomApp->setObjectName(QString::fromUtf8("lNomApp"));
        lNomApp->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(lNomApp);

        lVersionApp = new QLabel(DIA_apropos);
        lVersionApp->setObjectName(QString::fromUtf8("lVersionApp"));
        lVersionApp->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(lVersionApp);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(DIA_apropos);
        label->setObjectName(QString::fromUtf8("label"));
        label->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(DIA_apropos);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pbFermer = new QPushButton(DIA_apropos);
        pbFermer->setObjectName(QString::fromUtf8("pbFermer"));

        horizontalLayout->addWidget(pbFermer);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DIA_apropos);
        QObject::connect(pbFermer, SIGNAL(clicked()), DIA_apropos, SLOT(close()));

        QMetaObject::connectSlotsByName(DIA_apropos);
    } // setupUi

    void retranslateUi(QDialog *DIA_apropos)
    {
        DIA_apropos->setWindowTitle(QCoreApplication::translate("DIA_apropos", "A Propos", nullptr));
        lNomApp->setText(QCoreApplication::translate("DIA_apropos", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Minecraft Advancements</span></p></body></html>", nullptr));
        lVersionApp->setText(QCoreApplication::translate("DIA_apropos", "<html><head/><body><p align=\"center\"><span style=\" font-style:italic;\">Version 0.1.5.1a</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("DIA_apropos", "<html><head/><body><p align=\"center\">Cr\303\251\303\251 par et imagin\303\251 par : <span style=\" font-weight:600;\">Chucky2401<br/></span>Une id\303\251e originale de : <a href=\"https://www.youtube.com/channel/UCyiDEVOTRt2Qf4P52A4zkRw\"><span style=\" font-weight:600; text-decoration: underline; color:#000000;\">Olchaldir</span></a> et <a href=\"https://www.youtube.com/channel/UCd2Q46ctrfG2qItzF7odLnA\"><span style=\" font-weight:600; text-decoration: underline; color:#000000;\">Athlif</span></a></p><p align=\"center\">Merci \303\240 tous les <a href=\"https://discord.gg/6Q6tK9A\"><span style=\" font-weight:600; text-decoration: underline; color:#000000;\">Gentlemen of Craft</span></a></p><p align=\"center\">Disponible sur <a href=\"https://github.com/Chucky2401/Minecraft-Advancements\"><span style=\" font-weight:600; text-decoration: underline; color:#000000;\">GitHub</span></a></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("DIA_apropos", "<html><head/><body><p align=\"center\">Copyright \302\251 2020 BlackWizard Company</p></body></html>", nullptr));
        pbFermer->setText(QCoreApplication::translate("DIA_apropos", "Fermer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DIA_apropos: public Ui_DIA_apropos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIA_APROPOS_H
