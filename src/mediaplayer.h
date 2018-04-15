#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include "subtitlesoutput.h"

class MediaPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *player READ player WRITE setPlayer NOTIFY playerChanged)
    Q_PROPERTY(QUrl mediaUrl READ mediaUrl WRITE setMediaUrl NOTIFY mediaUrlChanged)
    Q_PROPERTY(QString mediaTitle READ mediaTitle WRITE setMediaTitle NOTIFY mediaTitleChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY _positionChanged)
    Q_PROPERTY(QString durationInfo READ durationInfo NOTIFY durationInfoChanged)
    Q_PROPERTY(QString totalDuration READ totalDuration NOTIFY totalDurationChanged)

    Q_PROPERTY(SubtitlesOutput *subtitlesOutput READ subtitlesOutput WRITE setSubtitlesOutput NOTIFY subtitlesOutputChanged)

public:
    explicit MediaPlayer(QObject *parent = 0);

    QObject *player() const { return m_player; }
    void setPlayer(const QObject *player);

    QUrl mediaUrl() const { return media_url; }
    void setMediaUrl(const QUrl& url);

    QString mediaTitle() const { return media_title; }
    void setMediaTitle(const QString& title);

    qint64 duration() const { return media_duration / 1000; }

    qint64 position() const { return m_current_position / 1000; }

    QString durationInfo() const{ return duration_info; }

    QString totalDuration() const { return total_duration; }

    SubtitlesOutput *subtitlesOutput() const { return subtitles_output; }
    void setSubtitlesOutput(SubtitlesOutput *subs_out);

    Q_INVOKABLE void showSubtitles(bool show);

signals:
    void playerChanged();

    void mediaUrlChanged();

    void mediaTitleChanged();

    void durationChanged();

    void durationInfoChanged();

    void _positionChanged();

    void totalDurationChanged();

    void subtitlesOutputChanged();

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
    QUrl media_url = QString("");
    QString media_title = "";
    qint64  media_duration = 0;
    qint64 m_current_position = 0;
    QString duration_info = "00:00:00";
    QString total_duration = "00:00:00";
    SubtitlesOutput *subtitles_output = nullptr;
    bool subtitles_added = false;
};

#endif // MEDIAPLAYER_H
