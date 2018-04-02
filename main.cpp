#include <QApplication>
#include <QQmlApplicationEngine>
#include "src/videooutput.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<VideoOutput>("backend.VideoOutput", 1, 0, "VideoOutputHandler");

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("qrc:/icons"));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

