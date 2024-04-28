#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "controller/TestModel.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    TestCtlr testCtlr;

    QQmlApplicationEngine engine;
    engine.setInitialProperties({ {"testCtlr", QVariant::fromValue(&testCtlr)} });
    engine.load(QUrl(QStringLiteral("qrc:/gui/qml/main.qml")));

    return app.exec();
}
