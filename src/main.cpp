#include <QApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "src/videooutput.h"
#include "src/mediaplayer.h"
#include "src/subtitlesoutput.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLocale loc;
    if (loc.language() == QLocale::Russian)
    {
        QTranslator *translator(new QTranslator(&app));
        // before use this run run lrelease!
        if (translator->load(QStringLiteral("mediaplayer_ru_RU.qm"), TRANSLATIONS_DIR)) {
           app.installTranslator(translator);
        }
    }

    qmlRegisterType<VideoOutput>("backend.VideoOutput", 1, 0, "VideoOutputHandler");
    qmlRegisterType<MediaPlayer>("backend.MediaPlayer", 1, 0, "MediaPlayerHandler");
    qmlRegisterType<SubtitlesOutput>("backend.SubtitlesOutput", 1, 0, "SubtitlesHandler");

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("qrc:/icons"));
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    app.setWindowIcon(QIcon(":/icons/resources/icons/playerIcon.png"));
    app.setOrganizationName("");
    app.setOrganizationDomain("");

    return app.exec();
}
