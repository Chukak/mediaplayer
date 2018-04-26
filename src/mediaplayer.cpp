#include "mediaplayer.h"
#include <QMediaMetaData>
#include <QTime>
#include <QTimer>
#include <iostream>

QString getFormatDuration(const qint64 duration)
{
    QString format = duration > 3600 ? "hh:mm:ss" : "mm:ss";
    return format;
}



MediaPlayer::MediaPlayer(QObject *parent)
{
    setParent(parent);
}


void MediaPlayer::setPlayer(const QObject *player)
{
    QVariant variant = player->property("mediaObject");
    if (variant.canConvert<QMediaPlayer *>()) {
        m_player = variant.value<QMediaPlayer *>();
        connect(m_player, &QMediaPlayer::metaDataAvailableChanged, this, &MediaPlayer::setMetaData);
        connect(m_player, &QMediaPlayer::positionChanged, this, &MediaPlayer::updatePosition);
        connect(m_player, &QMediaPlayer::durationChanged, this, &MediaPlayer::updateDuration);
        emit playerChanged();
    }
}

void MediaPlayer::setMetaData()
{
    setMediaTitle(m_player->metaData(QMediaMetaData::Title).toString());
}

void MediaPlayer::setMediaUrl(const QUrl &url)
{
    if (media_url != url) {
        QMediaContent content(url);
        if (!content.isNull()) {
            media_url = url;
            m_player->setMedia(content);
            emit mediaUrlChanged();
        }
    }
}

void MediaPlayer::setMediaTitle(const QString &title)
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

    if (position <= media_duration && position >= 0) {
        m_current_position = position;
        updateDurationInfo(m_current_position / 1000);
        emit _positionChanged();
        emit durationInfoChanged();
    }
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
    qint64 pos = position > 0 ? position * 1000 : 0;
    if (pos > 0 && pos > media_duration){
        pos = media_duration;
    }
    if (subtitles_output && subtitles_output->selected()) {
        subtitles_output->updateSubtitlesText(pos, true);
    }
    m_player->setPosition(pos);
}

void MediaPlayer::setSubtitlesOutput(SubtitlesOutput *subs_out)
{
    subtitles_output = subs_out;
    subtitles_output->setParent(this);
    connect(m_player, &QMediaPlayer::positionChanged, this, [=](qint64 position) {
        if (subtitles_output->selected()) {
            subtitles_output->updateSubtitlesText(position, false);
        }
    });
    emit subtitlesOutputChanged();
}

void MediaPlayer::showSubtitles(bool show)
{
    subtitles_output->setSelected(show);
    subtitles_output->empty();
}

void MediaPlayer::setPlaybackRate(double rate)
{
    if (rate >= -10.0 && rate <= 10.0 &&
            m_player->playbackRate() != rate) {
        m_player->setPlaybackRate(rate);
    }
}

