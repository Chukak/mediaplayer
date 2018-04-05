#include "videooutput.h"
#include <iostream>
#include <QtGlobal>
#include <QMediaMetaData>

VideoOutput::VideoOutput()
{
    m_player = new MediaPlayer(this);
}

void VideoOutput::setTargetOutput(QQuickItem *output)
{
    m_output = output;
    emit targetOutputChanged();
}

void VideoOutput::setStatus(const QString &status)
{
    if (m_status != status) {
        m_status = status;
        emit statusChanged();
    }
}
