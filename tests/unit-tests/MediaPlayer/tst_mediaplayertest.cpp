#include "../../../src/mediaplayer.h"
#include <QtTest>
#include <QSignalSpy>
#include <QMediaPlayer>

class MediaPlayerTest : public QObject
{
    Q_OBJECT

public:
    MediaPlayerTest();

private Q_SLOTS:
    void testPlayer();
    void testMediaUrl();

private:
};

MediaPlayerTest::MediaPlayerTest()
{
}

void MediaPlayerTest::testPlayer()
{
    MediaPlayer media_player;
    QSignalSpy spy(&media_player, &MediaPlayer::playerChanged);
    QCOMPARE(true, spy.isValid());
    QObject *player = new QObject();
    QMediaPlayer *m_player = qobject_cast<QMediaPlayer *>(player);
    media_player.setPlayer(player);
    QCOMPARE(m_player, media_player.player());
    QCOMPARE(1, spy.count());
    QObject *other_player = new QObject();
    QMediaPlayer *m_other_player = qobject_cast<QMediaPlayer *>(other_player);
    media_player.setPlayer(other_player);
    QCOMPARE(m_other_player, media_player.player());
    QCOMPARE(2, spy.count());
}

void MediaPlayerTest::testMediaUrl()
{
    MediaPlayer media_player;
    QSignalSpy spy(&media_player, &MediaPlayer::mediaUrlChanged);
    QCOMPARE(true, spy.isValid());
}

QTEST_APPLESS_MAIN(MediaPlayerTest)

#include "tst_mediaplayertest.moc"
