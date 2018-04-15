import QtQuick 2.9
import QtMultimedia 5.9

MediaPlayer {
    property QtObject idMediaPlayerHandler
    property QtObject playerButtons
    id: mediaplayer
    source: idMediaPlayerHandler.mediaUrl
    volume: 1.0
    onPlaying: {
        playerButtons.playVideo()
    }
    onPaused: {
        playerButtons.pauseVideo()
    }
    onStopped: {
        playerButtons.stopVideo()
    }
}
