#include "mediaplayer.h"
#include <QMediaMetaData>
#include <QTime>
#include <iostream>

QString getFormatDuration(const qint64 duration)
{
    QString format = duration > 3600 ? "hh:mm:ss" : "mm:ss";
    return format;
}



MediaPlayer::MediaPlayer(QObject *parent) :
    QObject(parent)
{
}

void MediaPlayer::setPlayer(const QObject *player)
{
    QVariant variant = player->property("mediaObject");
    if (variant.canConvert<QMediaPlayer *>()) {
        m_player = variant.value<QMediaPlayer *>();
        connect(m_player, &QMediaPlayer::metaDataAvailableChanged, this, &MediaPlayer::setMetaData);
        connect(m_player, &QMediaPlayer::positionChanged, this, &MediaPlayer::updatePosition);
        connect(m_player, &QMediaPlayer::durationChanged, this, &MediaPlayer::updateDuration);
    }
    emit playerChanged();
}

void MediaPlayer::setMetaData()
{
    setmediaTitle(m_player->metaData(QMediaMetaData::Title).toString());
}

void MediaPlayer::setmediaUrl(const QUrl &url)
{
    if (media_url != url) {
        media_url = url;
        m_player->setMedia(media_url);
        emit mediaUrlChanged();
    }
}

void MediaPlayer::setmediaTitle(const QString &title)
{
    QString new_title;
    if (!title.isEmpty()) {
        new_title = title;
    } else {
        new_title = media_url.fileName();
    }
    if (media_title != new_title) {
        media_title = new_title;
        emit mediaTitleChanged();
    }
}

void MediaPlayer::updateDuration(qint64 duration)
{
    if (media_duration != duration) {
        media_duration = duration;
        emit durationChanged();
    }
    updateTotalDuration();
}

void MediaPlayer::updatePosition(qint64 position)
{
    m_current_position = m_player->position();
    emit _positionChanged();
    updateDurationInfo(position / 1000);
    emit durationInfoChanged();
}


void MediaPlayer::updateDurationInfo(qint64 info)
{
    if (media_duration) {
        QTime current_time((info / 3600) % 60, (info / 60) % 60,
                         (info % 60));
        QString format = getFormatDuration(media_duration / 1000);
        duration_info = current_time.toString(format);
        emit durationInfoChanged();
    }
}

void MediaPlayer::updateTotalDuration()
{
    if (media_duration) {
        qint64 duration = media_duration / 1000;

        QTime total_time((duration / 3600) % 60, (duration / 60) % 60,
                         (duration % 60));
        QString format = getFormatDuration(duration);
        total_duration = total_time.toString(format);
        emit totalDurationChanged();
    }
}

void MediaPlayer::seek(qint64 position)
{
    m_player->setPosition(position * 1000);
}

