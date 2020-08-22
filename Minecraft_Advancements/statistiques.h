#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include <QDialog>
#include <QCloseEvent>
#include <QWidget>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>

#include "settings\settings.h"
#include "settings\database.h"

using namespace QtCharts;

namespace Ui {
class statistiques;
}

class Statistiques : public QDialog
{
    Q_OBJECT

public:
    explicit Statistiques(QWidget *parent = nullptr, QString typeGraph = "Spline", bool test = false);
    ~Statistiques();

protected:
    void closeEvent(QCloseEvent *event);

// Fonctions privées
private:
    void refreshDataGraphique();
    void getDataBdd();

private:
    // Constante
    const QString connectionName = "statistiques";

    QString qsTypeGraphique;
    bool m_test;
    Ui::statistiques *ui;
    bool bRefreshManuel;

    // Settings
    class Settings *param;
    class database bdd;

    // Données
    QList<QDateTime> *m_qlDate;
    QList<int> *m_qlNombreProgres;
    QLineSeries *m_qlsGraphiqueLigne;
    QSplineSeries *m_qssGraphiqueSpline;
    QChart *m_qcGraphique;
    QDateTimeAxis *m_qdtaAbscisse;
    QValueAxis *m_qvaOrdonnees;
    QChartView *m_qcvVue;

private slots:
    void boutonRefreshData();


};

#endif // STATISTIQUES_H
