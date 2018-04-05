#ifndef VIDEOOUTPUT_H
#define VIDEOOUTPUT_H

#include "mediaplayer.h"
#include <QObject>
#include <QQuickItem>


class VideoOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *targetOutput READ targetOutput WRITE setTargetOutput NOTIFY targetOutputChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    explicit VideoOutput();

    QQuickItem *targetOutput() { return m_output; }
    void setTargetOutput(QQuickItem *output);

    QString status() { return m_status; }
    void setStatus(const QString& status);

signals:
    void targetOutputChanged();

    void statusChanged();

public slots:

private:
    QQuickItem *m_output = nullptr;
    MediaPlayer *m_player = nullptr;
    QString m_status = "";
};

#endif // VIDEOOUTPUT_H
