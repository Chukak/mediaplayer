#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H

#include "mediaplayer.h"
#include <QObject>
#include <QQuickItem>


class VideoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *targetOutput READ targetOutput WRITE setTargetOutput NOTIFY targetOutputChanged)
    Q_PROPERTY(QString status READ status NOTIFY statusChanged)
    Q_PROPERTY(QObject *mediaPlayer READ mediaPlayer WRITE setMediaPlayer NOTIFY mediaPlayerChanged)

public:
    explicit VideoOutput(QObject *parent = 0);

    QQuickItem *targetOutput() { return m_output; }
    void setTargetOutput(QQuickItem *output);

    QObject *mediaPlayer() { return m_player; }
    void setMediaPlayer(QObject *player);

    QString status() { return m_status; }

signals:
    void targetOutputChanged();

    void mediaPlayerChanged();

    void statusChanged();

private slots:
    void updateState(const QMediaPlayer::State& state);

    void updateStatus(const QMediaPlayer::MediaStatus& status);

private:
    QQuickItem *m_output = nullptr;
    MediaPlayer *m_player = nullptr;
    QString m_status = "No media";
};

#endif // VIDEOOUTPUT_H
