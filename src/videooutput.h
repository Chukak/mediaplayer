#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H

#include "mediaplayer.h"
#include <QObject>
#include <QQuickItem>
#include <QVideoProbe>

/*
 * Class video output.
 * Used for displaying video output, status, and creating screenshots.
 * Inherits QObject.
 */
class VideoOutput : public QObject
{
    Q_OBJECT
    /*
     * A property that inherits object the `VideoOutput` from qml.
     * Readable, can be changed, has signal `targetOutputChanged`.
     */
    Q_PROPERTY(QQuickItem *targetOutput READ targetOutput WRITE setTargetOutput NOTIFY targetOutputChanged)
    /*
     * A property for displaying media status.
     * Read-only, has signal `statusChanged`.
     */
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    /*
     * A property for getting the `MediaPlayer` object.
     * Readable, can be changed, has signal `mediaPlayerChanged`.
     */
    Q_PROPERTY(MediaPlayer *mediaPlayer READ mediaPlayer WRITE setMediaPlayer NOTIFY mediaPlayerChanged)

public:

    /*
     * A constructor.
     */
    explicit VideoOutput(QObject *parent = nullptr);

    /*
     * Returns the `VideoOutput` object in qml.
     */
    QQuickItem *targetOutput() const noexcept { return m_output; }

    /*
     * Gets the `VideoOutput` object from qml and save this object.
     * Emits `targetOutputChanged` signal.
     * @param output - a pointer to the object from qml.
     */
    void setTargetOutput(QQuickItem *output) noexcept;

    /*
     * Returns the `MediaPlayer` object in qml.
     */
    MediaPlayer *mediaPlayer() const noexcept { return m_player; }

    /*
     * Gets the `MediaPlayer` object from qml and save this object.
     * Emits `mediaPlayerChanged` signal.
     * @param player - a pointer to the `MediaPlayer` object.
     */
    void setMediaPlayer(MediaPlayer *player);

    /*
     * Returns the current status of the media.
     */
    QString status() const noexcept { return m_status; }

    /*
     * Creates a screenshot from the video frame.
     * Called from qml.
     */
    Q_INVOKABLE void snapshot();

signals:

    /*
     * Emitted when current the `VideoOutput` object changed (from qml).
     */
    void targetOutputChanged();

    /*
     * Emitted when the `MediaPlayer` object changed (from qml).
     */
    void mediaPlayerChanged();

    /*
     * Emitted when the media status changed.
     */
    void statusChanged();

    /*
     * Emitted if snapshot errors are exist.
     */
    void snapshotError(QString message);

    /*
     * Emitted if the media is invalid.
     */
    void invalidMedia();

    /*
     * Emitted if the media loaded.
     */
    void loadedMedia();

public slots:

    /*
     * Changes the current state of the media player.
     * @param state - a state of the media player.
     */
    void updateState(const QMediaPlayer::State& state) noexcept;

    /*
     * Changes the current status of the media player.
     * @param state - a status of the media player.
     */
    void updateStatus(const QMediaPlayer::MediaStatus& status) noexcept;

private:
    QQuickItem *m_output;
    MediaPlayer *m_player;
    QAbstractVideoSurface *surface;
    QString m_status;
    QVideoProbe *probe;
    QVideoFrame current_frame;
};

#endif // VIDEOOUTPUT_H
