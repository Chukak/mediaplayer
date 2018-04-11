#include "../../../src/mediaplayer.h"
#include <QtTest>
#include <QSignalSpy>
#include <QMediaPlayer>

class MediaPlayerTest : public QObject
{
    Q_OBJECT

public:
    MediaPlayerTest();
    QMediaPlayer *getMediaPlayer(QObject *object);

private Q_SLOTS:
    void testPlayer();
    void testMediaUrl();
    void testMediaTitle();
    void testDuration();
    void testPosition();
    void testSeek();
    //void testDurationInfo();
    //void testTotalDuration();

private:
    QMediaPlayer *player_value;
};

MediaPlayerTest::MediaPlayerTest() :
    player_value(new QMediaPlayer())
{
}

QMediaPlayer *MediaPlayerTest::getMediaPlayer(QObject *object)
{
    object->setProperty("mediaObject", QVariant::fromValue(player_value));
    QMediaPlayer *m_player = qvariant_cast<QMediaPlayer *>(QVariant::fromValue(object->property("mediaObject")));
    return m_player;
}

void MediaPlayerTest::testPlayer()
{
    MediaPlayer media_player;
    QSignalSpy spy(&media_player, &MediaPlayer::playerChanged);
    QCOMPARE(true, spy.isValid());
    QObject player;
    QMediaPlayer *m_player = getMediaPlayer(&player);
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    QCOMPARE(1, spy.count());
    QObject other_player;
    QMediaPlayer *m_other_player = getMediaPlayer(&other_player);
    media_player.setPlayer(&other_player);
    QCOMPARE(m_other_player, media_player.player());
    QCOMPARE(2, spy.count());
}

void MediaPlayerTest::testMediaUrl()
{
    MediaPlayer media_player;
    QObject player;
    QMediaPlayer *m_player = getMediaPlayer(&player);
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    QSignalSpy spy(&media_player, &MediaPlayer::mediaUrlChanged);
    QCOMPARE(true, spy.isValid());

    QUrl media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test1.avi").absoluteFilePath());;
    media_player.setMediaUrl(media_url);
    QCOMPARE(media_player.mediaUrl(), media_url);
    QCOMPARE(1, spy.count());

    QUrl other_media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test2.avi").absoluteFilePath());;
    media_player.setMediaUrl(other_media_url);
    QCOMPARE(media_player.mediaUrl(), other_media_url);
    QCOMPARE(2, spy.count());
}

void MediaPlayerTest::testMediaTitle()
{
    MediaPlayer media_player;
    QSignalSpy spy(&media_player, &MediaPlayer::mediaTitleChanged);
    QCOMPARE(true, spy.isValid());

    QUrl media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test1.avi").absoluteFilePath());;
    media_player.setMediaTitle(media_url.fileName());
    QCOMPARE(media_player.mediaTitle(), media_url.fileName());
    QCOMPARE(1, spy.count());

    QUrl other_media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test2.avi").absoluteFilePath());;
    media_player.setMediaTitle(other_media_url.fileName());
    QCOMPARE(media_player.mediaTitle(), other_media_url.fileName());
    QCOMPARE(2, spy.count());
}

void MediaPlayerTest::testDuration()
{
    MediaPlayer media_player;
    QObject player;
    QMediaPlayer *m_player = getMediaPlayer(&player);
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    QSignalSpy spy(&media_player, &MediaPlayer::durationChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy valid_media_player(m_player, &QMediaPlayer::mediaStatusChanged);
    QCOMPARE(true, valid_media_player.isValid());

    QUrl media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test1.avi").absoluteFilePath());
    media_player.setMediaUrl(media_url);
    QVERIFY(valid_media_player.wait());
    QCOMPARE(1, spy.count());
    QCOMPARE(m_player->duration() / 1000, media_player.duration());

    QUrl other_media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test2.avi").absoluteFilePath());
    media_player.setMediaUrl(other_media_url);
    QVERIFY(valid_media_player.wait());
    QCOMPARE(2, spy.count());
    QCOMPARE(m_player->duration() / 1000, media_player.duration());
}

void MediaPlayerTest::testPosition()
{
    MediaPlayer media_player;
    QObject player;
    QMediaPlayer *m_player = getMediaPlayer(&player);
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    QSignalSpy spy(&media_player, &MediaPlayer::_positionChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy valid_media_player(m_player, &QMediaPlayer::mediaStatusChanged);
    QCOMPARE(true, valid_media_player.isValid());

    QUrl media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test1.avi").absoluteFilePath());
    media_player.setMediaUrl(media_url);
    QVERIFY(valid_media_player.wait());
    QCOMPARE(0, media_player.position());
    m_player->setPosition(7000);
    QCOMPARE(7, media_player.position());
    m_player->setPosition(27000);
    QCOMPARE(27, media_player.position());
    m_player->setPosition(600);
    QCOMPARE(0, media_player.position());
    m_player->setPosition(1200);
    QCOMPARE(1, media_player.position());
    m_player->setPosition(12000);
    QCOMPARE(12, media_player.position());
    m_player->setPosition(29000);
    QCOMPARE(12, media_player.position());
    m_player->setPosition(-2);
    QCOMPARE(0, media_player.position());
    m_player->setPosition(3902);
    QCOMPARE(3, media_player.position());
    QCOMPARE(8, spy.count());
}

void MediaPlayerTest::testSeek()
{
    MediaPlayer media_player;
    QObject player;
    QMediaPlayer *m_player = getMediaPlayer(&player);
    media_player.setPlayer(&player);
    QCOMPARE(m_player, media_player.player());
    QSignalSpy spy(&media_player, &MediaPlayer::_positionChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy valid_media_player(m_player, &QMediaPlayer::mediaStatusChanged);
    QCOMPARE(true, valid_media_player.isValid());

    QUrl media_url = QUrl::fromLocalFile(QFileInfo("../../resources/test1.avi").absoluteFilePath());
    media_player.setMediaUrl(media_url);
    QVERIFY(valid_media_player.wait());
    media_player.seek(14);
    QCOMPARE(14, media_player.position());
    media_player.seek(-2);
    QCOMPARE(0, media_player.position());
    media_player.seek(18);
    QCOMPARE(18, media_player.position());
    media_player.seek(14);
    QCOMPARE(14, media_player.position());
    media_player.seek(140);
    QCOMPARE(27, media_player.position());
    media_player.seek(-1000);
    QCOMPARE(0, media_player.position());
    media_player.seek(14000);
    QCOMPARE(27000, media_player.position() * 1000);
    media_player.seek(0);
    QCOMPARE(0, media_player.position());
    media_player.seek(100);
    QCOMPARE(27000, media_player.position() * 1000);
    media_player.seek(5);
    QCOMPARE(5000, m_player->position());
    media_player.seek(41);
    QCOMPARE(m_player->duration(), m_player->position());
    media_player.seek(0);
    QCOMPARE(0, m_player->position());
    media_player.seek(16);
    QCOMPARE(16000, m_player->position());
    media_player.seek(-12);
    QCOMPARE(0, m_player->position());
}



QTEST_MAIN(MediaPlayerTest)

#include "tst_mediaplayertest.moc"
