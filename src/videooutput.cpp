#include "videooutput.h"
#include <iostream>

VideoOutput::VideoOutput(QObject *parent) :
    QObject(parent)
{

}

void VideoOutput::setTargetOutput(QQuickItem *output)
{
    m_output = output;
    emit targetOutputChanged();
}

void VideoOutput::setMediaPlayer(MediaPlayer *player)
{
    m_player = player;
    m_player->setParent(this);
    connect(qobject_cast<QMediaPlayer *>(m_player->player()), &QMediaPlayer::stateChanged,
            this, &VideoOutput::updateState);
    connect(qobject_cast<QMediaPlayer *>(m_player->player()), &QMediaPlayer::mediaStatusChanged,
            this, &VideoOutput::updateStatus);
    emit mediaPlayerChanged();
}


void VideoOutput::updateState(const QMediaPlayer::State& state)
{
    switch (state) {
    case QMediaPlayer::PlayingState:
        m_status = "Playing";
        break;
    case QMediaPlayer::PausedState:
        m_status = "Paused";
        break;
    case QMediaPlayer::StoppedState:
        m_status = "Stopped";
        break;
    }
    emit statusChanged();
}

void VideoOutput::updateStatus(const QMediaPlayer::MediaStatus& status)
{
    QMediaPlayer::State state = static_cast<QMediaPlayer *>(m_player->player())->state();
    switch (status) {
    case QMediaPlayer::NoMedia:
        m_status = "No media";
        break;
    case QMediaPlayer::LoadingMedia:
        m_status = "Loading media";
        break;
    case QMediaPlayer::LoadedMedia:
        if (state != QMediaPlayer::StoppedState) {
            m_status = "Media loaded";
        }
        break;
    case QMediaPlayer::BufferingMedia:
        if (state != QMediaPlayer::PlayingState ||
                state != QMediaPlayer::PausedState) {
            m_status = "Buffering";
        }
        break;
    case QMediaPlayer::InvalidMedia:
        if (state != QMediaPlayer::StoppedState) {
            m_status = "Invalid media";
        }
        break;
    default:
        break;
    }
    emit statusChanged();
}
