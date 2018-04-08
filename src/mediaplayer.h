#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>

class MediaPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(QUrl videoUrl READ videoUrl WRITE setVideoUrl NOTIFY videoUrlChanged)
    Q_PROPERTY(QString videoTitle READ videoTitle WRITE setVideoTitle NOTIFY videoTitleChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY _positionChanged)
    Q_PROPERTY(QString durationInfo READ durationInfo NOTIFY durationInfoChanged)
    Q_PROPERTY(QString totalDuration READ totalDuration NOTIFY totalDurationChanged)

public:
    explicit MediaPlayer(QObject *parent = 0);

    QObject *player() { return m_player; }
    void setPlayer(const QObject *player);

    QUrl videoUrl() { return video_url; }
    void setVideoUrl(const QUrl& url);

    QString videoTitle() { return video_title; }
    void setVideoTitle(const QString& title);

    qint64 duration() { return video_duration / 1000; }

    qint64 position() { return m_current_position / 1000; }

    QString durationInfo() { return duration_info; }

    QString totalDuration() { return total_duration; }

signals:
    void playerChanged();

    void videoUrlChanged();

    void videoTitleChanged();

    void durationChanged();

    void durationInfoChanged();

    void _positionChanged();

    void totalDurationChanged();

public slots:
    void seek(qint64 position);

private slots:
    void setMetaData();

private:
    void updatePosition(qint64 position);
    void updateDurationInfo(qint64 info);
    void updateTotalDuration();
    void updateDuration(qint64 duration);

    QMediaPlayer *m_player = nullptr;
    QUrl video_url = QString("");
    QString video_title = "";
    qint64  video_duration = 0;
    qint64 m_current_position = 0;
    QString duration_info = "00:00:00";
    QString total_duration = "00:00:00";
};

#endif // MEDIAPLAYER_H
