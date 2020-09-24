#include "statistiques.h"
#include "ui_statistiques.h"

Statistiques::Statistiques(QWidget *parent, QString typeGraph, bool test) :
    QDialog(parent), qsTypeGraphique(typeGraph), m_test(test),
    ui(new Ui::statistiques) {
    ui->setupUi(this);

    param = new Settings();
    param->initialisation(m_test);
    bdd.initialisation(m_test);

    bool testBdd = bdd.createConnection(connectionName);
    if(!testBdd){
        QString lastBddError = bdd.getError();
        QMessageBox::critical(this, "Connexion à la BDD", "Echec de la connexion à la Base de Données.\nDétails:\n"+bdd.getError());
    }

    bRefreshManuel = false;
    m_qlDate = new QList<QDateTime>;
    m_qlNombreProgres = new QList<int>;
    m_qcGraphique = new QChart();
    m_qdtaAbscisse = new QDateTimeAxis;
    m_qvaOrdonnees = new QValueAxis;

    refreshDataGraphique();

    connect(ui->qpbRafraichir, SIGNAL(clicked()), this, SLOT(boutonRefreshData()));
}

Statistiques::~Statistiques() {
    if (bdd.isOpen(connectionName))
        bdd.closeConnection(connectionName);
    delete ui;
}

void Statistiques::closeEvent(QCloseEvent *event){
    if (bdd.isOpen(connectionName))
        bdd.closeConnection(connectionName);
    emit finished(0);
    event->accept();
}

void Statistiques::getDataBdd() {
    QSqlQuery qsqGetNombre(bdd.getBase());
    QString qsqRequeteNombre = "SELECT"
                               "      COUNT(DISTINCT titre) nbrProgres"
                               "    , strftime('%Y-%m-%d', date_fait) dateProgres"
                               " FROM"
                               "    compare_advancements"
                               " WHERE"
                               "    progres_fait = 'true'"
                               " GROUP BY"
                               "    strftime('%Y-%m-%d', date_fait)"
                               " ORDER BY"
                               "    strftime('%Y-%m-%d', date_fait)";

    m_qlDate->clear();
    m_qlNombreProgres->clear();

    if (qsqGetNombre.exec(qsqRequeteNombre)) {
        while (qsqGetNombre.next()) {
            QDateTime qdtJourProgres = QDateTime::fromString(qsqGetNombre.value("dateProgres").toString(), "yyyy-MM-dd");
            //qdtJourProgres = qdtJourProgres.addSecs(1*60*60);
            int iNombreProgres = qsqGetNombre.value("nbrProgres").toInt();

            m_qlDate->append(qdtJourProgres);
            m_qlNombreProgres->append(iNombreProgres);
        }
    } else {
        QMessageBox::critical(this, "Impossible de récupérer les valeurs", qsqGetNombre.lastError().text());
    }
}

void Statistiques::refreshDataGraphique() {
    bool bValeurPourGraphOk = true;
    qreal qrValeurMax = 0;

    m_qcGraphique->removeAllSeries();
    ui->qhblGraphic->removeWidget(m_qcvVue);

    // On utilise une fonction qui remplis les méthodes pour les données
    getDataBdd();

    if (m_qlDate->count() == 0 && m_qlNombreProgres->count() == 0) {
        // Pas de valeur
        bValeurPourGraphOk = false;
    } else if (m_qlDate->count() == 1 && m_qlNombreProgres->count() == 1) {
        // Qu'une valeur, pas utile pour un graph
        bValeurPourGraphOk = false;
    } else if (m_qlDate->count() != m_qlNombreProgres->count()) {
        // Différence anormal
        bValeurPourGraphOk = false;
    }

    if (bValeurPourGraphOk) {
        // On met les valeurs dans la série choisi par l'utilisateur
        if (qsTypeGraphique == "Spline") {
            m_qssGraphiqueSpline = new QSplineSeries();

            m_qssGraphiqueSpline->setName(qsTypeGraphique);
            for (int i = 0; i < m_qlDate->count(); i++) {
                if (qrValeurMax < m_qlNombreProgres->at(i))
                        qrValeurMax = m_qlNombreProgres->at(i);
                m_qssGraphiqueSpline->append(m_qlDate->at(i).toMSecsSinceEpoch(), m_qlNombreProgres->at(i));
            }
            m_qcGraphique->addSeries(m_qssGraphiqueSpline);
        } else {
            m_qlsGraphiqueLigne = new QLineSeries();

            m_qlsGraphiqueLigne->setName(qsTypeGraphique);
            for (int i = 0; i < m_qlDate->count(); i++) {
                if (qrValeurMax < m_qlNombreProgres->at(i))
                        qrValeurMax = m_qlNombreProgres->at(i);

                m_qlsGraphiqueLigne->append(m_qlDate->at(i).toMSecsSinceEpoch(), m_qlNombreProgres->at(i));
            }
            m_qcGraphique->addSeries(m_qlsGraphiqueLigne);
        }

        if (!bRefreshManuel) {
            m_qcGraphique->legend()->hide();
            m_qcGraphique->setTitle("Vos Progrès");

            // AxisX
            m_qdtaAbscisse->setTickCount(9);
            m_qdtaAbscisse->setFormat(QString("dd/MM/yyyy"));
            m_qdtaAbscisse->setTitleText("Date");
            m_qcGraphique->addAxis(m_qdtaAbscisse, Qt::AlignBottom);

            if (qsTypeGraphique == "Spline") {
                m_qdtaAbscisse->setRange(QDateTime::fromMSecsSinceEpoch(m_qssGraphiqueSpline->at(0).x()).addDays(-1),
                                         QDateTime::fromMSecsSinceEpoch(m_qssGraphiqueSpline->at(m_qssGraphiqueSpline->count()-1).x()).addDays(1));
                m_qssGraphiqueSpline->attachAxis(m_qdtaAbscisse);
            } else {
                m_qdtaAbscisse->setRange(QDateTime::fromMSecsSinceEpoch(m_qlsGraphiqueLigne->at(0).x()).addDays(-1),
                                         QDateTime::fromMSecsSinceEpoch(m_qlsGraphiqueLigne->at(m_qlsGraphiqueLigne->count()-1).x()).addDays(1));
                m_qlsGraphiqueLigne->attachAxis(m_qdtaAbscisse);
            }
            // AxisY
            m_qvaOrdonnees->setLabelFormat("%i");
            m_qvaOrdonnees->setTitleText("Progrès");
            m_qvaOrdonnees->setRange(0, qrValeurMax+5);
            m_qcGraphique->addAxis(m_qvaOrdonnees, Qt::AlignLeft);

            if (qsTypeGraphique == "Spline") {
                m_qssGraphiqueSpline->attachAxis(m_qvaOrdonnees);
            } else {
                m_qlsGraphiqueLigne->attachAxis(m_qvaOrdonnees);
            }
        }


        // On affiche le graphique
        m_qcvVue = new QChartView(m_qcGraphique);
        m_qcvVue->setRenderHint(QPainter::Antialiasing);

        ui->qhblGraphic->addWidget(m_qcvVue);
    }
}

void Statistiques::boutonRefreshData() {
    bRefreshManuel = true;
    refreshDataGraphique();
    bRefreshManuel = false;
}
