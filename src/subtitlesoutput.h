#ifndef SUBTITLESOUTPUT_H
#define SUBTITLESOUTPUT_H

#include <QObject>
#include <QStringList>
#include <QList>
#include "subtitleparser.h"

/*
 * Class for displaying subtitles.
 * Used for display subtitles, add new subtitles, clear,
 * display a list of the subtitles.
 * Inherits QObject.
 */
class SubtitlesOutput : public QObject
{
    Q_OBJECT

    /*
     * The property for changing subtitles the text of the subtitles.
     * Read-only. Has signal `textChanged`.
     */
    Q_PROPERTY(QString text READ text NOTIFY textChanged)

    /*
     * The property for display the current list of the subtitles.
     * Read-only. Has signal `listSubtitlesChanged`.
     */
    Q_PROPERTY(QStringList listSubtitles READ listSubtitles NOTIFY listSubtitlesChanged)

public:

    /*
     * A constructor.
     * @param parent - pointer to the parent object.
     */
    SubtitlesOutput(QObject *parent = nullptr);

    /*
     * Adds a new file from url.
     * Called from qml.
     * Emits `listSubtitlesChanged` signal.
     * @param url - path to the file.
     */
    Q_INVOKABLE void addSubtitles(const QUrl &url);

    /*
     * Returns the current text of the subtitles.
     */
    QString text() const { return current_text; }

    /*
     * Clears the current text of the subtitles.
     * Emits `textChanged` signal.
     */
    void empty();

    /*
     * Returns the list of subtitle names.
     */
    QStringList listSubtitles() const { return names; }

    /*
     * Sets the current subtitles from the list of an available subtitles by key.
     * @param key - name of subtitles that are selected.
     */
    Q_INVOKABLE void setSubtitles(qint32 key);

    /*
     * Returns the subtitles at the time point.
     * Called when a `positionChanged` signal is emitted.
     * @param time - position in the video.
     */
    QString getCurrentSubtitles(qint64 time);

    /*
     * Binary search for the subtitles.
     * Used to search for a position.
     * Called when the slider is moved by the user.
     * @param time - position in the video.
     */
    void binarySearch(qint64 time);

    /*
     * Returns `true` if the subtitles are selected otherwise `false`.
     */
    bool selected() const { return _selected; }

public slots:

    /*
     * Updates the current subtitles text.
     * Emits `textChanged` signal.
     * @param time - position in the video.
     * @param seekable - if the slider is moved by the user.
     */
    void updateSubtitlesText(qint64 time, bool seekable);

signals:

    /*
     * Emitted when the current text was changed.
     */
    void textChanged();

    /*
     * Emitted when the list of the subtitles was changed.
     */
    void listSubtitlesChanged();

    /*
     * Emitted when the subtitles were added.
     */
    //void subtitlesAdded();

private:

    QStringList names;
    QList<QUrl> urls = {QUrl("")};
    bool _selected = false;
    std::vector<SubtitleItem> current_subtitles;
    QString current_text = "";
    qint32 last_index = 0;

};

#endif // SUBTITLESOUTPUT_H
