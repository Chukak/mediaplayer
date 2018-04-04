#include "videooutput.h"
#include <iostream>
#include <QtGlobal>
#include <QMediaMetaData>

VideoOutput::VideoOutput() :
    m_output(0),
    m_player(0),
    video_url(""),
    video_title(""),
    video_duration(0)
{

}

void VideoOutput::setTargetOutput(QQuickItem *output)
{
    m_output = output;
    emit targetOutputChanged();
}

void VideoOutput::setTargetPlayer(QObject *player)
{
    QVariant variant = player->property("mediaObject");
    if (variant.canConvert<QMediaPlayer *>()) {
        m_player = variant.value<QMediaPlayer *>();
        connect(m_player, &QMediaPlayer::metaDataAvailableChanged, this, &VideoOutput::setMetaData);
        connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &VideoOutput::currentMediaStatus);
    }
    emit targetPlayerChanged();
}

void VideoOutput::setVideoUrl(const QUrl &url)
{
    if (video_url != url) {
        video_url = url;
        m_player->setMedia(video_url);
        emit videoUrlChanged();
    }
}

void VideoOutput::setMetaData()
{
    setVideoTitle(m_player->metaData(QMediaMetaData::Title).toString());
}

void VideoOutput::currentMediaStatus(QMediaPlayer::MediaStatus status)
{

}

void VideoOutput::setVideoTitle(const QString &title)
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

void VideoOutput::setDuration(qint64 duration)
{
    if (video_duration != duration) {
        video_duration = duration;
        emit durationChanged();
    }
}
