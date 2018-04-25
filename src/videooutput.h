#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H

#include "mediaplayer.h"
#include <QObject>
#include <QQuickItem>
#include <QVideoProbe>


class VideoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *targetOutput READ targetOutput WRITE setTargetOutput NOTIFY targetOutputChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(MediaPlayer *mediaPlayer READ mediaPlayer WRITE setMediaPlayer NOTIFY mediaPlayerChanged)

public:
    explicit VideoOutput(QObject *parent = 0);

    QQuickItem *targetOutput() const { return m_output; }
    void setTargetOutput(QQuickItem *output);

    MediaPlayer *mediaPlayer() const { return m_player; }
    void setMediaPlayer(MediaPlayer *player);

    QString status() const { return m_status; }

    Q_INVOKABLE void snapshot();

signals:
    void targetOutputChanged();

    void mediaPlayerChanged();

    void statusChanged();

public slots:
    void updateCurrentFrame(const QVideoFrame& frame);

    void updateState(const QMediaPlayer::State& state);

    void updateStatus(const QMediaPlayer::MediaStatus& status);

private:
    QQuickItem *m_output = nullptr;
    MediaPlayer *m_player = nullptr;
    QAbstractVideoSurface *surface = nullptr;
    QString m_status = "No media";
    QVideoProbe *probe = nullptr;
    QVideoFrame current_frame;
};

#endif // VIDEOOUTPUT_H
