#include "videooutput.h"
#include <iostream>

VideoOutput::VideoOutput() :
    m_output(0),
    m_player(0),
    video_url("")
{

}

void VideoOutput::setTargetOutput(QQuickItem *output)
{
    m_output = output;
    emit targetOutputChanged();
}

void VideoOutput::setTargetPlayer(QObject *player)
{
    QVariant variant = player->property("mediaObject");
    if (variant.canConvert<QMediaPlayer *>()) {
        m_player = variant.value<QMediaPlayer *>();
    }
    emit targetPlayerChanged();
}

void VideoOutput::setVideoUrl(const QUrl &url)
{
    video_url = url;
    m_player->setMedia(video_url);
    emit videoUrlChanged();
}
