#include "videooutput.h"
#include <QPixmap>
#include <QImage>

/*
 * Function for conversion from YUV420P format to RGB32 format.
 * Convert a video frame to an image.
 * Return QImage in RGB32 format.
 * @param data - a pointer toe the start of the frame data duffer.
 * @param width - width of a video frame.
 * @param height - height of a video frame.
 */
QImage convertYUV420pToRGB32(const uchar *data, int width, int height)
{
    if (width > 0 && height > 0) {
        //QImage image(width, height, QImage::Format_RGB32);
        QImage image(width, height, QImage::Format_RGB888);
        for (int y = 0; y < height; ++y) {
            const uchar *yLine = data + y * width;
            const uchar *uLine = data + width * height + (y / 2) * width / 2;
            const uchar *vLine = data + width * height * 5 / 4 + (y / 2) * width / 2;

            for (int x = 0; x < width; ++x) {
                const int Y = 1.164 * (yLine[x] - 16);
                const int U = uLine[x / 2] - 128;
                const int V = vLine[x / 2] - 128;

                const int b = qBound(0, int(Y + 2.018 * U), 255);
                const int g = qBound(0, int(Y - 0.813 * V - 0.391 * U), 255);
                const int r = qBound(0, int(Y + 1.596 * V), 255);

                image.setPixel(x, y, qRgb(r, g, b));
            }
        }
        return image;
    }
    return QImage();
}

/*
 * Returns the unique name of the file.
 */
QString getUniqueName(const QString& path)
{
    QTemporaryFile file(path +  QDir::separator() + "screenshot_XXXXXX");
    if (!file.open()) {
        return QString("");
    }
    file.close();
    return QString(file.fileName());
}


VideoOutput::VideoOutput(QObject *parent) :
    QObject(parent)
{

}

/*
 * Save the `VideoOutput` object from qml.
 */
void VideoOutput::setTargetOutput(QQuickItem *output)
{
    m_output = output;
    emit targetOutputChanged();
}

/*
 * Save the `MediaObject` object from qml.
 */
void VideoOutput::setMediaPlayer(MediaPlayer *player)
{
    m_player = player;
    m_player->setParent(this);
    // Cast `QObject *` to `QMediaPlayer *`.
    QMediaPlayer *p_player = qobject_cast<QMediaPlayer *>(m_player->player());
    connect(p_player, &QMediaPlayer::stateChanged, this, &VideoOutput::updateState);
    connect(p_player, &QMediaPlayer::mediaStatusChanged, this, &VideoOutput::updateStatus);
    // Object for update the current video frame.
    probe = new QVideoProbe();
    probe->setSource(p_player);
    connect(probe, &QVideoProbe::videoFrameProbed, this, &VideoOutput::updateCurrentFrame);
    emit mediaPlayerChanged();
    emit invalidMedia();
}

/*
 * Save the current video frame
 */
void VideoOutput::updateCurrentFrame(const QVideoFrame &frame)
{
    current_frame = frame;
}

/*
 * Changes the state of the media.
 */
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

/*
 * Changes the status of the media.
 */
void VideoOutput::updateStatus(const QMediaPlayer::MediaStatus& status)
{
    switch (status) {
    case QMediaPlayer::NoMedia:
        m_status = "No media";
        emit invalidMedia();
        break;
    case QMediaPlayer::LoadingMedia:
        m_status = "Loading media";
        break;
    case QMediaPlayer::LoadedMedia:
        m_status = "Media loaded";
        emit loadedMedia();
        break;
    case QMediaPlayer::BufferingMedia:
        m_status = "Buffering";
        break;
    case QMediaPlayer::InvalidMedia:
        m_status = "Invalid media";
        emit invalidMedia();
        break;
    default:
        break;
    }
    emit statusChanged();
}

/*
 * Make a screenshot from the video frame.
 */
void VideoOutput::snapshot()
{
    QImage image;
    QVideoFrame frame(current_frame);
    // Map the content of a video frame to system memory.
    if (!frame.map(QAbstractVideoBuffer::ReadOnly)) {
        emit snapshotError("Impossible load the content of video frame into the system memory.");
        return ;
    }
    // Convert the video frame to the image.
    image = convertYUV420pToRGB32(frame.bits(), frame.width(), frame.height());
    // Release memory.
    frame.unmap();
    if (image.isNull()) {
        emit snapshotError("The image is empty.");
        return ;
    }
    QPixmap screenshot = QPixmap::fromImage(image);
    // Creates a directory for saving screenshots.
    // For example: `/home/$(user)/Pictures/player_screenshots/` .
    QDir directory(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) +
                   QDir::separator() + "player_screenshots");
    if (!directory.exists()) {
        QDir().mkpath(directory.path());
    }
    // Gets the unique name of the file.
    QString filename = getUniqueName(directory.path());
    QFile file(filename + ".png");
    if (!file.open(QIODevice::WriteOnly)) {
        emit snapshotError("Can not create image. Maybe you don`t have enough rights.");
        return ;
    }
    if (!screenshot.save(&file, "png", 100)) {
        emit snapshotError("The image can not be saved.");
        return ;
    }
}
