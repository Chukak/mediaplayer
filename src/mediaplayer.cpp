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
    setParent(parent);
}

void MediaPlayer::setPlayer(const QObject *player)
{
    QVariant variant = player->property("mediaObject");
    if (variant.canConvert<QMediaPlayer *>()) {
        m_player = variant.value<QMediaPlayer *>();
        connect(m_player, &QMediaPlayer::metaDataAvailableChanged, this, &MediaPlayer::setMetaData);
        connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayer::currentMediaStatus);
        connect(m_player, &QMediaPlayer::positionChanged, this, &MediaPlayer::updatePosition);
        connect(m_player, &QMediaPlayer::durationChanged, this, &MediaPlayer::updateDuration);
    }
    emit playerChanged();
}

void MediaPlayer::setMetaData()
{
    setVideoTitle(m_player->metaData(QMediaMetaData::Title).toString());
}

QString MediaPlayer::currentMediaStatus(QMediaPlayer::MediaStatus status)
{
    QString current_status;
    if (status == QMediaPlayer::LoadedMedia) {
        current_status = "Media loaded";
    }
    return current_status;
}

void MediaPlayer::setVideoUrl(const QUrl &url)
{
    if (video_url != url) {
        video_url = url;
        m_player->setMedia(video_url);
        emit videoUrlChanged();
    }
}

void MediaPlayer::setVideoTitle(const QString &title)
{
    QString new_title;
    if (!title.isEmpty()) {
        new_title = title;
    } else {
        new_title = video_url.fileName();
    }
    if (video_title != new_title) {
        video_title = new_title;
        emit videoTitleChanged();
    }
}

void MediaPlayer::updateDuration(qint64 duration)
{
    if (video_duration != duration) {
        video_duration = duration;
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
    if (video_duration) {
        QTime current_time((info / 3600) % 60, (info / 60) % 60,
                         (info % 60));
        QString format = getFormatDuration(video_duration);
        duration_info = current_time.toString(format);
        emit durationInfoChanged();
    }
}

void MediaPlayer::updateTotalDuration()
{
    if (video_duration) {
        qint64 duration = video_duration / 1000;

        QTime total_time((duration / 3600) % 60, (duration / 60) % 60,
                         (duration % 60));
        QString format = getFormatDuration(duration);
        total_duration = total_time.toString(format);
        emit totalDurationChanged();
    }
}


