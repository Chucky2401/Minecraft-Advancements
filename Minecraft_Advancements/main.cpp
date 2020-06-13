#include "frm_principale.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTime>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Minecraft Advancements");
    QApplication::setApplicationVersion("0.2.5.2b");
    QCommandLineParser parser;
    bool test = false;

    parser.setApplicationDescription(QApplication::translate("main", "Outil pour les recettes de No Man's Sky"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption optionTest(QStringList() << "t" << "test", QApplication::translate("main", "Utilisation base de test."), QApplication::translate("main", "true|false"), "false");
    parser.addOption(optionTest);

    parser.process(app);

    if (parser.value(optionTest) == "true"){
        test = true;
    } else {
        test = false;
    }

    QPixmap pixmap(":/img/Splash-Screen.png");
    QSplashScreen splash(pixmap);
    splash.show();
    //app.processEvents();
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    FRM_Principale w(nullptr, test);
    w.show();
    splash.finish(&w);

    return app.exec();
}
