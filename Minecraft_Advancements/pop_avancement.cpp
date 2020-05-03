#include "pop_avancement.h"
#include "ui_pop_avancement.h"

POP_Avancement::POP_Avancement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::POP_Avancement)
{
    ui->setupUi(this);
}

POP_Avancement::~POP_Avancement()
{
    delete ui;
}
