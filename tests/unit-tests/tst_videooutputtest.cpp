#include "../../src/videooutput.h"
#include <QString>
#include <QtTest>
#include <QQuickItem>
#include <QSignalSpy>

class VideoOutputTest : public QObject
{
    Q_OBJECT

public:
    VideoOutputTest();

private Q_SLOTS:
    void testTargetOutput();
    void testMediaPlayer();

    void cleanup();

private:
};

VideoOutputTest::VideoOutputTest()
{
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
    QSignalSpy spy(&output, &VideoOutput::mediaPlayerChanged);
    QCOMPARE(true, spy.isValid());
    MediaPlayer player;
    output.setMediaPlayer(&player);
    QCOMPARE(&player, output.mediaPlayer());
    QCOMPARE(1, spy.count());
    MediaPlayer other_player;
    output.setMediaPlayer(&other_player);
    QCOMPARE(&other_player, output.mediaPlayer());
    QCOMPARE(2, spy.count());
}

void VideoOutputTest::cleanup()
{
}

QTEST_APPLESS_MAIN(VideoOutputTest)

#include "tst_videooutputtest.moc"
