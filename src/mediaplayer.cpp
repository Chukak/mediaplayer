#include "mediaplayer.h"
#include <QMediaMetaData>
#include <QTime>

/*
 * Returns the information about the duration of the video in the format "hh:mm:ss" or "mm:ss",
 * "hh" - hours, "mm" - minutes, "ss" - seconds.
 */
QString getFormatDuration(const qint64 duration)
{
    QString format = duration > 3600 ? "hh:mm:ss" : "mm:ss";
    return format;
}



MediaPlayer::MediaPlayer(QObject *parent)
{
    setParent(parent);
}

/*
 * Save the `QMediaObject` from qml.
 */
void MediaPlayer::setPlayer(const QObject *player)
{
    QVariant variant = player->property("mediaObject"); // Get a media object.
    if (variant.canConvert<QMediaPlayer *>()) {
        m_player = variant.value<QMediaPlayer *>(); // Convert QObject to QMediaObject.
        connect(m_player, &QMediaPlayer::metaDataAvailableChanged, this, &MediaPlayer::setMetaData);
        connect(m_player, &QMediaPlayer::positionChanged, this, &MediaPlayer::updatePosition);
        connect(m_player, &QMediaPlayer::durationChanged, this, &MediaPlayer::updateDuration);
        emit playerChanged();
    }
}

/*
 * Save the metadata from the video.
 */
void MediaPlayer::setMetaData()
{
    setMediaTitle(m_player->metaData(QMediaMetaData::Title).toString());
}

/*
 * Open a media content from the url.
 */
void MediaPlayer::setMediaUrl(const QUrl &url)
{
    if (media_url != url) {
        QMediaContent content(url); // Set content.
        if (!content.isNull()) {
            media_url = url;
            m_player->setMedia(content);
            emit mediaUrlChanged();
        }
    }
}

/*
 * Sets the title of the video.
 */
void MediaPlayer::setMediaTitle(const QString &title)
{
    QString new_title;
    if (!title.isEmpty()) {
        new_title = title; // An embedded title.
    } else {
        new_title = media_url.fileName(); // A name of the video.
    }
    if (media_title != new_title) {
        media_title = new_title;
        emit mediaTitleChanged();
    }
}

/*
 * Updates the duration of the video.
 */
void MediaPlayer::updateDuration(qint64 duration)
{
    if (media_duration != duration) {
        media_duration = duration;
        emit durationChanged();
    }
    updateTotalDuration(); // Update the information about the duration of the video.
}

/*
 * Updates the position of the video.
 */
void MediaPlayer::updatePosition(qint64 position)
{

    if (position <= media_duration && position >= 0) {
        m_current_position = position;
        updateDurationInfo(m_current_position / 1000); // Update the information about the position.
        emit _positionChanged();
        emit durationInfoChanged();
    }
}

/*
 * Updates the information about the position of the video.
 */
void MediaPlayer::updateDurationInfo(qint64 info)
{
    if (media_duration) {
        // Set time from milliseconds.
        QTime current_time((info / 3600) % 60, (info / 60) % 60,
                         (info % 60));
        // Get the format.
        QString format = getFormatDuration(media_duration / 1000);
        duration_info = current_time.toString(format);
        emit durationInfoChanged();
    }
}

/*
 * Updates the duration of the video.
 */
void MediaPlayer::updateTotalDuration()
{
    if (media_duration) {
        qint64 duration = media_duration / 1000;
        // Set tile from milliseconds.
        QTime total_time((duration / 3600) % 60, (duration / 60) % 60,
                         (duration % 60));
        // Get the format.
        QString format = getFormatDuration(duration);
        total_duration = total_time.toString(format);
        emit totalDurationChanged();
    }
}

/*
 * Rewinding the video.
 */
void MediaPlayer::seek(qint64 position)
{
    qint64 pos = position > 0 ? position * 1000 : 0;
    if (pos > 0 && pos > media_duration){
        pos = media_duration;
    }
    // Check the subtitles.
    if (subtitles_output && subtitles_output->selected()) {
        subtitles_output->updateSubtitlesText(pos, true);
    }
    m_player->setPosition(pos);
}

/*
 * Sets the `SubtitlesOutput` object.
 */
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

/*
 * Displaying the subtitles.
 */
void MediaPlayer::showSubtitles(bool show)
{
    if (subtitles_output->selected()) {
        subtitles_output->setSelected(show);
        subtitles_output->empty(); // Clear.
    }
}

/*
 * Sets the speed of video playback.
 */
void MediaPlayer::setPlaybackRate(double rate)
{
    if (rate >= -10.0 && rate <= 10.0 &&
            m_player->playbackRate() != rate &&
            m_player->duration() != -1) {
        m_player->setPlaybackRate(rate);
    }
}
