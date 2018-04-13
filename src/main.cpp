#include <QApplication>
#include <QQmlApplicationEngine>
#include "src/videooutput.h"
#include "src/mediaplayer.h"
#include "src/subtitlesoutput.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qmlRegisterType<VideoOutput>("backend.VideoOutput", 1, 0, "VideoOutputHandler");
    qmlRegisterType<MediaPlayer>("backend.MediaPlayer", 1, 0, "MediaPlayerHandler");
    qmlRegisterType<SubtitlesOutput>("backend.SubtitlesOutput", 1, 0, "SubtitlesHandler");

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("qrc:/icons"));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}

