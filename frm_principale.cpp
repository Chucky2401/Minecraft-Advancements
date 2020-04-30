#include "frm_principale.h"
#include "ui_frm_principale.h"

FRM_Principale::FRM_Principale(QWidget *parent, bool test)
    : QMainWindow(parent)
    , ui(new Ui::FRM_Principale), m_test(test) {

    ui->setupUi(this);

    this->setWindowTitle(QApplication::applicationName());
    this->setWindowIcon(QIcon(":/img/icons8_minecraft_logo_48px.png"));

    m_qsAppDataPath = qEnvironmentVariable("APPDATA");

    if (m_tempDir.isValid()) {
        qDebug() << m_tempDir.path();
    }

    m_qs7zBin = "bin/7z.exe";
    m_qp7zProcess = new QProcess(this);

    ui->qcbLauncher->addItem("", QVariant("EMPTY"));
    ui->qcbLauncher->addItem("Minecraft Launcher (Officiel Mojang)", QVariant("Mojang"));
    //ui->qcbLauncher->addItem("MultiMC", QVariant("MultiMC"));
    //ui->qcbLauncher->addItem("ATLauncher", QVariant("ATLauncher"));

    connect(ui->qcbLauncher, SIGNAL(currentIndexChanged(int)), this, SLOT(choixLauncher(int)));
    connect(ui->qcbVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(choixVersion(int)));
    connect(ui->qpbSelectionDossierMonde, SIGNAL(clicked(bool)), this, SLOT(choixDossierSauvegarde(bool)));
    connect(ui->qpbExtraireProgres, SIGNAL(clicked(bool)), this, SLOT(extraireProgres(bool)));
    connect(ui->qpbReadJSON, SIGNAL(clicked(bool)), this, SLOT(readJSON(bool)));

    ui->qcbLauncher->setCurrentIndex(1);
    ui->qpbSelectionDossierLanceur->setEnabled(false);
    ui->qpbExtraireProgres->setEnabled(false);
    ui->qlLevelTrouve->setVisible(false);
    ui->qlAdvancedmentsExtrait->setVisible(false);
}

FRM_Principale::~FRM_Principale() {
    delete ui;
}

void FRM_Principale::choixLauncher(int index) {
    QString qsLanceur = ui->qcbLauncher->itemData(index).toString();
    QString qsFauxCheminLanceur, qsValeurTemp, qsNomVersionTemp, qsNomVersion;
    QStringList qslFormatFichier, qslDossierLanceurTemp, qslNomVersionTemp;

    m_qslListVersionJar.clear();
    ui->qcbVersion->clear();
    ui->qleDossierLanceur->clear();
    qslFormatFichier << "*.jar";
    ui->qpbSelectionDossierLanceur->setEnabled(true);
    m_bUpdateProgres = false;

    ui->qcbVersion->addItem("", QVariant("EMPTY"));

    //qDebug() << qsLanceur;

    if (qsLanceur == "Mojang") {
        ui->qpbSelectionDossierLanceur->setEnabled(false);
        qslDossierLanceurTemp = m_qsAppDataPath.split("\\");
        //qDebug() << qslDossierLanceurTemp;
        for (int i = 0 ; i < qslDossierLanceurTemp.length() ; i++) {
            if (i != 2) {
                qsFauxCheminLanceur += qslDossierLanceurTemp.at(i);
            } else {
                qsFauxCheminLanceur += "fake_Utilisateur";
            }

            if (i + 1 != qslDossierLanceurTemp.length())
                qsFauxCheminLanceur += "\\";
        }

        //qDebug() << qsFauxCheminLanceur;

        ui->qleDossierLanceur->setText(qsFauxCheminLanceur);
        m_qsDossierMinecraft = m_qsAppDataPath + "\\.minecraft";
        m_qsDossierVersion = m_qsAppDataPath + "\\.minecraft\\versions";
        QDirIterator qdiMinecraftVersion(m_qsDossierVersion, qslFormatFichier, QDir::Files, QDirIterator::Subdirectories);

        while (qdiMinecraftVersion.hasNext()) {
            qsNomVersion.clear();
            qsValeurTemp = qdiMinecraftVersion.next();
            m_qslListVersionJar << qsValeurTemp;
            qsNomVersionTemp = qsValeurTemp.split("/").last();

            qslNomVersionTemp = qsNomVersionTemp.split(".");
            for (int i = 0; i < qslNomVersionTemp.length()-1; i++) {
                qsNomVersion = qsNomVersion + qslNomVersionTemp.at(i);
                if (i + 1 != qslNomVersionTemp.length()-1) {
                    qsNomVersion = qsNomVersion + ".";
                }
            }

            ui->qcbVersion->addItem(qsNomVersion, QVariant(qsValeurTemp));
        }

        //qDebug() << m_qslListVersionJar;
    }
}

void FRM_Principale::choixVersion(int index) {
    QString qsCheminVersion = ui->qcbVersion->itemData(index).toString();
    QString qsFauxChemin;
    m_qsl7zipArguments.clear();

    if (qsCheminVersion != "EMPTY") {
        ui->qleCheminVersion->setText("C:\\fake_Path\\" + qsCheminVersion.split("/").last());
        //qDebug() << qsCheminVersion;
    } else
        ui->qleCheminVersion->setText("");

    m_qdDossierAdvancedments.setPath("advancements/" + ui->qcbVersion->currentText() + "/");

    if (m_qdDossierAdvancedments.exists() && ui->qcbVersion->currentData() != "EMPTY") {
        ui->qpbExtraireProgres->setText("Update Progrès");
        ui->qpbExtraireProgres->setEnabled(true);
        m_bUpdateProgres = true;
    } else if (ui->qcbVersion->currentData() == "EMPTY") {
        ui->qpbExtraireProgres->setEnabled(false);
    } else {
        if (m_qdDossierAdvancedments.mkpath(".")) {
            ui->qpbExtraireProgres->setEnabled(true);
            ui->qpbExtraireProgres->setText("Extraire Progrès");
            m_bUpdateProgres = false;
        }
    }

    if (ui->qcbVersion->currentData() != "EMPTY")
        m_qsl7zipArguments << "x" << qsCheminVersion << "-o"+m_tempDir.path() << "-ir!data\\minecraft\\advancements\\*.json";
    qDebug() << m_qsl7zipArguments;
}

void FRM_Principale::choixDossierSauvegarde(bool checked) {
    QStringList qslDossierSauvegardeTemp;
    QString qsFauxDossierSauvegarde;

    ui->qlLevelTrouve->setVisible(false);

    QString qsDossierSauvegarde = QFileDialog::getExistingDirectory(this, tr("Choisir le dossier de votre sauvegardes Minecraft"),
                                                    m_qsDossierMinecraft,
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    qslDossierSauvegardeTemp = qsDossierSauvegarde.split("/");
    //qDebug() << qslDossierSauvegardeTemp;
    for (int i = 0 ; i < qslDossierSauvegardeTemp.length() ; i++) {
        if (i != 2) {
            qsFauxDossierSauvegarde += qslDossierSauvegardeTemp.at(i);
        } else {
            qsFauxDossierSauvegarde += "fake_Utilisateur";
        }

        if (i + 1 != qslDossierSauvegardeTemp.length())
            qsFauxDossierSauvegarde += "\\";
    }

    ui->qleDossierMonde->setText(qsFauxDossierSauvegarde.replace("/", "\\"));
    if (QFileInfo::exists(qsDossierSauvegarde + "\\level.dat")) {
        m_qsDossierSauvegarde = qsDossierSauvegarde;
        ui->qlLevelTrouve->setText("level.dat trouvé !");
        ui->qlLevelTrouve->setStyleSheet("color: green;");
        ui->qlLevelTrouve->setVisible(true);
        ui->qleDossierMonde->setStyleSheet("QLineEdit {border: 1px solid limeGreen;}");
    } else {
        ui->qlLevelTrouve->setText("level.dat non trouvé !");
        ui->qlLevelTrouve->setStyleSheet("color: red;");
        ui->qlLevelTrouve->setVisible(true);
        ui->qleDossierMonde->setStyleSheet("QLineEdit {border: 1px solid red;}");
    }
}

void FRM_Principale::extraireProgres(bool checked) {
    QStringList qslFormatFichier;
    QString qsTempNom, qsNouveauNom;

    qslFormatFichier << "*.json";

    if (m_bUpdateProgres) {
        m_qdDossierAdvancedments.removeRecursively();
        m_qdDossierAdvancedments.mkpath(".");
    }

    m_qp7zProcess->start(m_qs7zBin, m_qsl7zipArguments);
    if (m_qp7zProcess->waitForFinished()) {
        QDirIterator qdiFichierProgres(m_tempDir.path()+"/data/minecraft/advancements/", QDirIterator::Subdirectories);

        while (qdiFichierProgres.hasNext()) {
            qsTempNom = qdiFichierProgres.next();
            qsNouveauNom = qsTempNom;
            qsNouveauNom.replace(m_tempDir.path()+"/data/minecraft/advancements/", m_qdDossierAdvancedments.path() + "/");
            //qDebug() << "Ancien : " << qsTempNom;
            //qDebug() << "Nouvea : " << qsNouveauNom;
            QFile::rename(qsTempNom, qsNouveauNom);
        }
        QMessageBox::information(this, "Extraction terminée", "L'extraction des advancements Vanilla est terminée.");
        ui->qpbExtraireProgres->setText("Update Progrès");
    }
    //DEBUG
    //m_qdDossierAdvancedments.removeRecursively();
}

void FRM_Principale::readJSON(bool checked) {
    //QString qsJsonFile = "advancements/1.15.2/adventure/adventuring_time.json";
    //QString qsJsonFile = "advancements/1.15.2/adventure/arbalistic.json";
    QString qsJsonFile = "advancements/1.15.2/story/iron_tools.json";
    //QString qsJsonFile = "D:/MultiMC_Develop/instances/GoC_1.15.2/.minecraft/saves/Hard Solo #01/datapacks/bac_advancements/data/blazeandcave/advancements/farming/meat_lovers.json";
    QFile qfJsonFile(qsJsonFile);
    if(!qfJsonFile.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<< qsJsonFile;
        exit(1);
    }

    QTextStream file_text(&qfJsonFile);
    QString json_string;
    json_string = file_text.readAll();
    qfJsonFile.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

    if(json_doc.isNull()){
        qDebug()<<"Failed to create JSON doc.";
        exit(2);
    }
    if(!json_doc.isObject()){
        qDebug()<<"JSON is not an object.";
        exit(3);
    }

    QJsonObject json_obj = json_doc.object();

    if(json_obj.isEmpty()){
        qDebug()<<"JSON object is empty.";
        exit(4);
    }

    QVariantMap json_map = json_obj.toVariantMap();
    QMap<QString, QVariant> qmDisplay = json_map["display"].toMap();
    QMap<QString, QVariant> qmTitle = qmDisplay["title"].toMap();
    QMap<QString, QVariant> qmDescription = qmDisplay["description"].toMap();
    QMap<QString, QVariant> qmCriteres = json_map["criteria"].toMap();


    qDebug() << json_map["parent"].toString();
    qDebug() << qmTitle["translate"].toString();
    qDebug() << qmDescription["translate"].toString();
    //qDebug( << qmCriteres;

    QMapIterator<QString, QVariant> i(qmCriteres);
    while (i.hasNext()) {
        i.next();
        QMap<QString, QVariant> qmCritere = qmCriteres[i.key()].toMap();
        //qDebug() << i.key();// << ": " << i.value();

        QMapIterator<QString, QVariant> j(qmCritere);
        while (j.hasNext()) {
            j.next();
            //qDebug() << j.key() << ": " << j.value();
            QMap<QString, QVariant> qmConditions = qmCritere[j.key()].toMap();
            QString qmTrigger = qmCritere[j.key()].toString();
            //qDebug() << qmType;
            if (!(qmConditions.isEmpty())) {
                if (qmConditions.value(qmConditions.keys().at(0)).toString() == "") {
                    qDebug() << "Conditions : " << qmConditions.keys().at(0) << " - " << qmConditions.value(qmConditions.keys().at(0));


                } else {
                    qDebug() << "Conditions : " << qmConditions.keys().at(0) << " - " << qmConditions.value(qmConditions.keys().at(0)).toString();
                }
            }

            if (!(qmTrigger.isEmpty()))
                qDebug() << "Triggers : " << qmTrigger;
        }
        //qDebug() << qmConditions;
    }
}
