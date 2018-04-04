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
    Q_PROPERTY(QString videoTitle READ videoTitle WRITE setVideoTitle NOTIFY videoTitleChanged)
    Q_PROPERTY(qint64 duration READ duration WRITE setDuration NOTIFY durationChanged)

public:
    explicit VideoOutput();

    QQuickItem *targetOutput() { return m_output; }
    void setTargetOutput(QQuickItem *output);

    QMediaPlayer *targetPlayer() { return m_player; }
    void setTargetPlayer(QObject *player);

    QUrl videoUrl() { return video_url; }
    void setVideoUrl(const QUrl& url);

    QString videoTitle() { return video_title; }
    void setVideoTitle(const QString& title);

    qint64 duration() { return video_duration; }
    void setDuration(qint64 duration);

signals:
    void targetOutputChanged();

    void targetPlayerChanged();

    void videoUrlChanged();

    void videoTitleChanged();

    void durationChanged();

public slots:
    void setMetaData();

    void currentMediaStatus(QMediaPlayer::MediaStatus status);

private:
    QQuickItem *m_output;
    QMediaPlayer *m_player;
    QUrl video_url;
    QString video_title;
    qint64  video_duration;
};

#endif // VIDEOOUTPUT_H
