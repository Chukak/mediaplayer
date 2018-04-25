#include "videooutput.h"
#include <QPixmap>
#include <QImage>


QImage convertYUV420pToRGB32(const uchar *data, int width, int height)
{
    if (width > 0 && height > 0) {
        QImage image(width, height, QImage::Format_RGB32);
        for (int y=0; y<height; ++y) {
            const uchar *yLine = data + y*width;
            const uchar *uLine = data + width*height + (y/2)*width/2;
            const uchar *vLine = data + width*height*5/4 + (y/2)*width/2;

            for (int x=0; x<width; ++x) {
                const qreal Y = 1.164*(yLine[x]-16);
                const int U = uLine[x/2]-128;
                const int V = vLine[x/2]-128;

                int b = qBound(0, int(Y + 2.018*U), 255);
                int g = qBound(0, int(Y - 0.813*V - 0.391*U), 255);
                int r = qBound(0, int(Y + 1.596*V), 255);

                image.setPixel(x,y,qRgb(r,g,b));
            }
        }
        return image;
    }
    return QImage();
}

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
    connect(qobject_cast<QMediaPlayer *>(m_player->player()), &QMediaPlayer::playbackRateChanged,
            this, &VideoOutput::snapshot);
    probe = new QVideoProbe();
    probe->setSource(qobject_cast<QMediaPlayer *>(m_player->player()));
    connect(probe, &QVideoProbe::videoFrameProbed, this, &VideoOutput::updateCurrentFrame);
    emit mediaPlayerChanged();
}

void VideoOutput::updateCurrentFrame(const QVideoFrame &frame)
{
    current_frame = frame;
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
    switch (status) {
    case QMediaPlayer::NoMedia:
        m_status = "No media";
        break;
    case QMediaPlayer::LoadingMedia:
        m_status = "Loading media";
        break;
    case QMediaPlayer::LoadedMedia:
        m_status = "Media loaded";
        break;
    case QMediaPlayer::BufferingMedia:
        m_status = "Buffering";
        break;
    case QMediaPlayer::InvalidMedia:
         m_status = "Invalid media";
        break;
    default:
        break;
    }
    emit statusChanged();
}

void VideoOutput::snapshot()
{
    qobject_cast<QMediaPlayer *>(m_player->player())->pause();
    QImage image;
    QVideoFrame frame(current_frame);
    if (!frame.map(QAbstractVideoBuffer::ReadOnly)) {
        return ;
    }
    image = convertYUV420pToRGB32(frame.bits(), frame.width(), frame.height());
    frame.unmap();
    qobject_cast<QMediaPlayer *>(m_player->player())->play();
    if (image.isNull()) {
        return ;
    }
    QPixmap screenshot = QPixmap::fromImage(image);
    QDir directory(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) +
                   QDir::separator() + "player_screenshots");
    if (!directory.exists()) {
        QDir().mkpath(directory.path());
    }
    QString filename = "screen1.png";
    QFile file(directory.path() + QDir::separator() +  filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return ;
    }
    if (!screenshot.save(&file, "png", 100)) {
        return ;
    }
}
