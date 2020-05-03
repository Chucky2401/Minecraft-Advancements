#ifndef POP_AVANCEMENT_H
#define POP_AVANCEMENT_H

#include <QDialog>

namespace Ui {
class POP_Avancement;
}

class POP_Avancement : public QDialog
{
    Q_OBJECT

public:
    explicit POP_Avancement(QWidget *parent = nullptr);
    ~POP_Avancement();

private:
    Ui::POP_Avancement *ui;
};

#endif // POP_AVANCEMENT_H
