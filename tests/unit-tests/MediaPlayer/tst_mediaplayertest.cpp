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
    void testMediaTitle();

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
    QObject player;
    QMediaPlayer player_value;
    player.setProperty("mediaObject", QVariant::fromValue(&player_value));
    QMediaPlayer *m_player = qvariant_cast<QMediaPlayer *>(QVariant::fromValue(player.property("mediaObject")));
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    QCOMPARE(1, spy.count());
    QObject other_player;
    other_player.setProperty("mediaObject", QVariant::fromValue(&player_value));
    QMediaPlayer *m_other_player = qvariant_cast<QMediaPlayer *>(QVariant::fromValue(other_player.property("mediaObject")));
    media_player.setPlayer(&other_player);
    QCOMPARE(m_other_player, media_player.player());
    QCOMPARE(2, spy.count());
}

void MediaPlayerTest::testMediaUrl()
{
    MediaPlayer media_player;
    QSignalSpy spy(&media_player, &MediaPlayer::mediaUrlChanged);
    QCOMPARE(true, spy.isValid());
    QObject player;
    QMediaPlayer player_value;
    player.setProperty("mediaObject", QVariant::fromValue(&player_value));
    QMediaPlayer *m_player = qvariant_cast<QMediaPlayer *>(QVariant::fromValue(player.property("mediaObject")));
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    QUrl media_url("path/to/video");
    media_player.setMediaUrl(media_url);
    QCOMPARE(media_player.mediaUrl(), media_url);
    QCOMPARE(1, spy.count());
    QUrl other_media_url("path/to/other/video");
    media_player.setMediaUrl(other_media_url);
    QCOMPARE(media_player.mediaUrl(), other_media_url);
    QCOMPARE(2, spy.count());
}

void MediaPlayerTest::testMediaTitle()
{
    MediaPlayer media_player;
    QSignalSpy spy(&media_player, &MediaPlayer::mediaTitleChanged);
    QCOMPARE(true, spy.isValid());
    QString title("valid_title");
    media_player.setMediaTitle(title);
    QCOMPARE(media_player.mediaTitle(), title);
    QCOMPARE(1, spy.count());
    QString other_title("valid_title2");
    media_player.setMediaTitle(other_title);
    QCOMPARE(media_player.mediaTitle(), other_title);
    QCOMPARE(2, spy.count());
}

QTEST_APPLESS_MAIN(MediaPlayerTest)

#include "tst_mediaplayertest.moc"
