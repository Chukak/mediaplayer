#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include "subtitlesoutput.h"

/*
 * Class for displaying media player. Displays the information about the duration of the video,
 * the title of video, sets the subtitles to the current video.
 * Inherits QObject.
 */
class MediaPlayer : public QObject
{
    Q_OBJECT
    /*
     * Sets mediaplayer from qml.
     * Readable, can be changed, has signal `playerChanged`.
     */
    Q_PROPERTY(QObject *player READ player WRITE setPlayer NOTIFY playerChanged)
    /*
     * Sets the media url to qml.
     * Readable, can be changed, has signal `mediaUrlChanged`.
     */
    Q_PROPERTY(QUrl mediaUrl READ mediaUrl WRITE setMediaUrl NOTIFY mediaUrlChanged)
    /*
     * Sets the media title to qml.
     * Readable, can be changed, has signal `mediaTitleChanged`.
     */
    Q_PROPERTY(QString mediaTitle READ mediaTitle WRITE setMediaTitle NOTIFY mediaTitleChanged)
    /*
     * A property for displaying the duration of the video.
     * Read-only, has signal `durationChanged`.
     */
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    /*
     * A property for displaying the current position of the video.
     * Read-only, has signal `_positionChanged`.
     */
    Q_PROPERTY(qint64 position READ position NOTIFY _positionChanged)
    /*
     * Displays the current position of the video in qml.
     * Read-only, has signal `durationInfoChanged`.
     */
    Q_PROPERTY(QString durationInfo READ durationInfo NOTIFY durationInfoChanged)
    /*
     * Displays the durationn of the video in qml.
     * Read-only, has signal `totalDurationChanged`.
     */
    Q_PROPERTY(QString totalDuration READ totalDuration NOTIFY totalDurationChanged)

    /*
     * Sets a `SubtitlesOutput` object from qml.
     * Readable, can be changed, has signal `subtitlesOutputChanged`.
     */
    Q_PROPERTY(SubtitlesOutput *subtitlesOutput READ subtitlesOutput WRITE setSubtitlesOutput NOTIFY subtitlesOutputChanged)

public:

    /*
     * A construstor.
     */
    explicit MediaPlayer(QObject *parent = 0);

    /*
     * Returns `QMediaObject` as the `QObject` type in qml.
     */
    QObject *player() const { return m_player; }

    /*
     * Gets the `QMediaObject` object as the `QObject` type from qml.
     * Emits `playerChanged` signal.
     * @param player - a pointer to the `QObject` object.
     */
    void setPlayer(const QObject *player);

    /*
     * Returns the media url in qml.
     */
    QUrl mediaUrl() const { return media_url; }

    /*
     * Gets the url from qml.
     * Emits `mediaUrlChanged` signal.
     * @param url - the video url.
     */
    void setMediaUrl(const QUrl& url);

    /*
     * Returns the titles of the media.
     */
    QString mediaTitle() const { return media_title; }

    /*
     * Gets the media title from qml.
     * Emits `mediaTitleChanged` signal.
     * @param title - the video title.
     */
    void setMediaTitle(const QString& title);

    /*
     * Returns the total duration of the video in seconds.
     */
    qint64 duration() const { return media_duration / 1000; }

    /*
     * Returns the current position of the video in seconds.
     */
    qint64 position() const { return m_current_position / 1000; }

    /*
     * Returns the information about the current position of the video in milliseconds.
     */
    QString durationInfo() const{ return duration_info; }

    /*
     * Returns the information about the total duration of the video in milliseconds.
     */
    QString totalDuration() const { return total_duration; }

    /*
     * Returns the `SubtitlesOutput` object.
     */
    SubtitlesOutput *subtitlesOutput() const { return subtitles_output; }

    /*
     * Gets the `Subtitlesoutput` object.
     * Emits `subtitlesOutputChanged` signal.
     * @param subs_out - a pointer to the `SubtitlesOutput` object.
     */
    void setSubtitlesOutput(SubtitlesOutput *subs_out);

    /*
     * Displays the subtitles.
     * Called from qml.
     * @param show - `true` or `false`.
     */
    Q_INVOKABLE void showSubtitles(bool show);

    /*
     * Sets the speed of video playback.
     * Called from qml.
     * @param rate - speed.
     */
    Q_INVOKABLE void setPlaybackRate(double rate);

signals:

    /*
     * Emitted when current the `QMediaObject` object changed (from qml).
     */
    void playerChanged();

    /*
     * Emitted when the url changed (from qml).
     */
    void mediaUrlChanged();

    /*
     * Emitted when the current title changed (from qml).
     */
    void mediaTitleChanged();

    /*
     * Emitted when the total duration changed.
     */
    void durationChanged();

    /*
     * Emitted when the information of the current position changed.
     */
    void durationInfoChanged();

    /*
     * Emitted when the current position changed.
     */
    void _positionChanged();

    /*
     * Emitted when the information of the total duration changed.
     */
    void totalDurationChanged();

    /*
     * Emitted when current the `SubtitlesOutput` object changed (from qml).
     */
    void subtitlesOutputChanged();

public slots:

    /*
     * Sets the current postion of the video. Rewind the video.
     * Called from qml.
     * @param position - position in seconds.
     */
    void seek(qint64 position);

private slots:

    /*
     * Sets the metadata from the video.
     * Called when the video is available.
     */
    void setMetaData();

private:

    /*
     * Updates the current position of the video.
     * Called the position of the video changed.
     * @param position - a new position.
     */
    void updatePosition(qint64 position);

    /*
     * Updates the information about the current position of the video.
     * Called the position of the video updated.
     * @param info - the position of the video.
     */
    void updateDurationInfo(qint64 info);

    /*
     * Updates the information about the total duration of the video.
     * Called the duration of the video updated.
     */
    void updateTotalDuration();

    /*
     * Updates the duration of the video.
     * Called the duration of the video changed.
     * @param duration - the duration of the video.
     */
    void updateDuration(qint64 duration);

    QMediaPlayer *m_player = nullptr;
    QUrl media_url = QString("");
    QString media_title = "";
    qint64  media_duration = 0;
    qint64 m_current_position = 0;
    QString duration_info = "00:00:00";
    QString total_duration = "00:00:00";
    SubtitlesOutput *subtitles_output = nullptr;
};

#endif // MEDIAPLAYER_H
