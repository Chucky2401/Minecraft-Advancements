#include "dia_parametres.h"
#include "ui_dia_parametres.h"

DIA_Parametres::DIA_Parametres(Settings *set, QWidget *parent, bool m_test) :
    QDialog(parent),
    ui(new Ui::DIA_Parametres), param(set)
{
    ui->setupUi(this);
    set->initialisation(m_test);

    /*
     * Définitions de l'état des objets en fonction des paramètres INI
     */
    // CheckBox
    ui->cbBeta->setChecked(param->getMiseAJourBeta());
    ui->cbRestoreSizePos->setChecked(param->getRestoreSizePos());
    ui->cbRestorePath->setChecked(param->getRestoreData());
    ui->cbMessageFermeture->setChecked(param->getMessageConfirmationFermeture());

    /*
     * Connections !
     */
    // Général
    connect(ui->cbMiseAJourAuto, SIGNAL(toggled(bool)), this, SLOT(setMiseAJourAuto(bool)));
    connect(ui->sbNombreJourMiseAJour, SIGNAL(valueChanged(int)), this, SLOT(setNombreJourMiseAJour(int)));
    connect(ui->cbBeta, SIGNAL(toggled(bool)), this, SLOT(setMiseAJourBeta(bool)));
    connect(ui->cbRestoreSizePos, SIGNAL(toggled(bool)), this, SLOT(setRestoreSizePos(bool)));
    connect(ui->cbRestorePath, SIGNAL(toggled(bool)), this, SLOT(setRestorePath(bool)));
    connect(ui->cbMessageFermeture, SIGNAL(toggled(bool)), this, SLOT(setMessageConfirmationFermeture(bool)));

    /*
     * Définitions de l'état des objets en fonction des paramètres INI
     * Cette partie doit être fait après connexion pour mise à jour d'autres champs
     */
    // CheckBox
    ui->cbMiseAJourAuto->setChecked(set->getVerificationAutoMiseAJour());
    // SpinBox
    ui->sbNombreJourMiseAJour->setValue(set->getNombreJourMiseAJour());

    if(set->getNombreJourMiseAJour() == 1) {
        ui->lMiseAJour2->setText("jour");
    } else {
        ui->lMiseAJour2->setText("jours");
    }

    // On supprime l'onglet qui provient d'un autre projet.
    // On le garde au cas où pour plus tard
    ui->tabWidget->removeTab(1);
}

DIA_Parametres::~DIA_Parametres()
{
    delete ui;
}

/*       *
 * SLOTS *
 *       *
 */
void DIA_Parametres::setRestorePath(bool state){
    //param->setRestoreRecipe(state);
    param->setRestoreData(state);
}

void DIA_Parametres::setRestoreSizePos(bool state){
    param->setRestoreSizePos(state);
}

void DIA_Parametres::setMessageConfirmationFermeture(bool state){
    param->setMessageConfirmationFermeture(state);
}

void DIA_Parametres::setMiseAJourAuto(bool enabled){
    param->setVerificationAutoMiseAJour(enabled);
    ui->lMiseAJour1->setEnabled(enabled);
    ui->sbNombreJourMiseAJour->setEnabled(enabled);
    ui->lMiseAJour2->setEnabled(enabled);
    //ui->cbBeta->setEnabled(enabled);
}

void DIA_Parametres::setNombreJourMiseAJour(int nombreJour){
    param->setNombreJourMiseAJour(nombreJour);
    if(nombreJour == 1) {
        ui->lMiseAJour2->setText("jour");
    } else {
        ui->lMiseAJour2->setText("jours");
    }
}

void DIA_Parametres::setMiseAJourBeta(bool checked) {
    param->setMiseAJourBeta(checked);
}
