#include "../../../src/videooutput.h"
#include <QtTest>
#include <QQuickItem>
#include <QSignalSpy>

class VideoOutputTest : public QObject
{
    Q_OBJECT

public:
    VideoOutputTest();
    QMediaPlayer *getMediaPlayer(QObject *object);

private Q_SLOTS:
    void testTargetOutput();
    void testMediaPlayer();
    void testStatus();

    void cleanup();

private:
    QMediaPlayer *player_value;
    QFileInfo test_file_one;
};

VideoOutputTest::VideoOutputTest() :
    player_value(new QMediaPlayer())
{
    test_file_one.setFile("../resources/test1.avi");
    if (!test_file_one.exists()) {
        test_file_one.setFile("../../resources/test1.avi");
    }
}

QMediaPlayer *VideoOutputTest::getMediaPlayer(QObject *object)
{
    object->setProperty("mediaObject", QVariant::fromValue(player_value));
    QMediaPlayer *m_player = qvariant_cast<QMediaPlayer *>(QVariant::fromValue(object->property("mediaObject")));
    return m_player;
}

void VideoOutputTest::testTargetOutput()
{
    VideoOutput output;
    QSignalSpy spy(&output, &VideoOutput::targetOutputChanged);
    QCOMPARE(true, spy.isValid());
    QQuickItem *target = new QQuickItem();
    output.setTargetOutput(target);
    QCOMPARE(output.targetOutput(), target);
    QCOMPARE(1, spy.count());
    QQuickItem *other_target = new QQuickItem();
    output.setTargetOutput(other_target);
    QCOMPARE(output.targetOutput(), other_target);
    QCOMPARE(2, spy.count());
}

void VideoOutputTest::testMediaPlayer()
{
    VideoOutput output;
    MediaPlayer media_player;
    QObject player;
    QMediaPlayer *m_player = getMediaPlayer(&player);
    media_player.setPlayer(&player);
    QCOMPARE(media_player.player(), m_player);
    QSignalSpy spy(&output, &VideoOutput::mediaPlayerChanged);
    QCOMPARE(true, spy.isValid());
    output.setMediaPlayer(&media_player);
    QCOMPARE(output.mediaPlayer(), &media_player);
    QCOMPARE(1, spy.count());
    MediaPlayer other_media_player;
    other_media_player.setPlayer(&player);
    QCOMPARE(other_media_player.player(), m_player);
    output.setMediaPlayer(&other_media_player);
    QCOMPARE(&other_media_player, output.mediaPlayer());
    QCOMPARE(2, spy.count());
}

void VideoOutputTest::testStatus()
{
    VideoOutput output;
    MediaPlayer media_player;
    QObject player;
    QMediaPlayer *m_player = getMediaPlayer(&player);
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    output.setMediaPlayer(&media_player);
    QCOMPARE(output.mediaPlayer(), &media_player);
    QSignalSpy spy(&output, &VideoOutput::statusChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy valid_media_player(m_player, &QMediaPlayer::mediaStatusChanged);
    QCOMPARE(true, valid_media_player.isValid());
    QSignalSpy media_state(m_player, &QMediaPlayer::stateChanged);
    QCOMPARE(true, media_state.isValid());
    QCOMPARE(QString("No media"), output.status());

    QUrl media_url = QUrl::fromLocalFile(test_file_one.absoluteFilePath());
    media_player.setMediaUrl(media_url);
    QCOMPARE(QString("Loading media"), output.status());
    QCOMPARE(1, spy.count());
    QVERIFY(valid_media_player.wait());
    QCOMPARE(QString("Media loaded"), output.status());
    QCOMPARE(2, valid_media_player.count());
    QCOMPARE(2, spy.count());
    m_player->play();
    QCOMPARE(QString("Playing"), output.status());
    m_player->pause();
    QCOMPARE(QString("Paused"), output.status());
    m_player->stop();
    QCOMPARE(QString("Stopped"), output.status());
    QCOMPARE(3, media_state.count());
    QCOMPARE(3, valid_media_player.count()); // stopped state - LoadedMedia, EndOfMedia
    QCOMPARE(6, spy.count());
    qDebug() << "Set an invalid url for this test. You can see some warnings.";
    QUrl other_media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test_invalid_url.avi").absoluteFilePath());
    media_player.setMediaUrl(other_media_url);
    QCOMPARE(QString("Loading media"), output.status());
    QVERIFY(valid_media_player.wait());
    qDebug() << "Finised.";
    QCOMPARE(QString("Invalid media"), output.status());
    QCOMPARE(8, spy.count());
}

void VideoOutputTest::cleanup()
{
}

QTEST_MAIN(VideoOutputTest)

#include "tst_videooutputtest.moc"
