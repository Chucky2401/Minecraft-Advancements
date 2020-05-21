#ifndef DIA_PARAMETRES_H
#define DIA_PARAMETRES_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class DIA_Parametres;
}

class DIA_Parametres : public QDialog
{
    Q_OBJECT

public:
    explicit DIA_Parametres(Settings *set, QWidget *parent = nullptr, bool m_test = false);
    ~DIA_Parametres();

private:
    Ui::DIA_Parametres *ui;
    // Divers
    bool m_test;
    // Classe complémentaires
    class Settings *param;

signals:


private slots:
    void setRestorePath(bool state);
    void setRestoreSizePos(bool state);
    void setMessageConfirmationFermeture(bool state);
    void setMiseAJourAuto(bool enabled);
    void setNombreJourMiseAJour(int nombreJour);
    void setMiseAJourBeta(bool checked);
};

#endif // DIA_PARAMETRES_H
