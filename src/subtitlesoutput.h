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
    Q_INVOKABLE void addSubtitles(const QUrl& url);

    /*
     * Returns the current text of the subtitles.
     */
    QString text() const noexcept { return current_text; }

    /*
     * Clears the current text of the subtitles.
     * Emits `textChanged` signal.
     */
    void empty() noexcept;

    /*
     * Returns the list of subtitle names.
     */
    QStringList listSubtitles() const noexcept { return names; }

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

    /*
     * Display subtitles or not.
     */
    void setSelected(bool display) noexcept;

public slots:

    /*
     * Updates the current subtitles text.
     * Emits `textChanged` signal.
     * @param time - position in the video.
     * @param seekable - if the slider is moved by the user.
     */
    void updateSubtitlesText(qint64 time, bool seekable);

    /*
     * Clears all loaded subtitles.
     */
     Q_INVOKABLE void clearLoadedSubtitles();

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
    void subtitlesAdded(QString name);

    /*
     * Emitted when all loaded subtitles are deleted.
     */
    void subtitlesCleared();

    /*
     * Emitted if the subtitles file can`t be parsed.
     */
    void subtitlesNotFoundError();

private:

    QStringList names;
    QList<QUrl> urls;
    bool _selected;
    QVector<SubtitleItem> current_subtitles;
    QString current_text;
    qint32 last_index;

};

#endif // SUBTITLESOUTPUT_H
