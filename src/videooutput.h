#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H

#include <QObject>
#include <QQuickItem>
#include <QMediaPlayer>

class VideoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *targetOutput READ targetOutput WRITE setTargetOutput NOTIFY targetOutputChanged)
    Q_PROPERTY(QObject *targetPlayer READ targetPlayer WRITE setTargetPlayer NOTIFY targetPlayerChanged)
    Q_PROPERTY(QUrl videoUrl READ videoUrl WRITE setVideoUrl NOTIFY videoUrlChanged)

public:
    explicit VideoOutput();

    QQuickItem *targetOutput() { return m_output; }
    void setTargetOutput(QQuickItem *output);

    QMediaPlayer *targetPlayer() { return m_player; }
    void setTargetPlayer(QObject *player);

    QUrl videoUrl() { return video_url; }
    void setVideoUrl(const QUrl& url);

signals:
    void targetOutputChanged();

    void targetPlayerChanged();

    void videoUrlChanged();

public slots:

private:
    QQuickItem *m_output;
    QMediaPlayer *m_player;
    QUrl video_url;
};

#endif // VIDEOOUTPUT_H
