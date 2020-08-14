#include "dia_apropos.h"
#include "ui_dia_apropos.h"

DIA_apropos::DIA_apropos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DIA_apropos)
{
    ui->setupUi(this);

    ui->lVersionApp->setText("<html><head/><body><p align=\"center\"><span style=\"font-size:8pt; font-style:italic;\">Version " + QApplication::applicationVersion() + "</span></p></body></html>");

    ui->label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->label->setOpenExternalLinks(true);
}

DIA_apropos::~DIA_apropos()
{
    delete ui;
}
