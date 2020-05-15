#ifndef DIA_APROPOS_H
#define DIA_APROPOS_H

#include <QDialog>

namespace Ui {
class DIA_apropos;
}

class DIA_apropos : public QDialog
{
    Q_OBJECT

public:
    explicit DIA_apropos(QWidget *parent = nullptr);
    ~DIA_apropos();

private:
    Ui::DIA_apropos *ui;
};

#endif // DIA_APROPOS_H
