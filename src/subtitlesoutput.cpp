#include "subtitlesoutput.h"

SubtitlesOutput::SubtitlesOutput(QObject *parent) :
    QObject(parent)
{
}

/*
 * Adds a new file from url.
 */
void SubtitlesOutput::addSubtitles(const QUrl &url)
{
    urls.push_back(url); // The list of urls.
    names.push_back(url.fileName()); // The list of file names.
    emit listSubtitlesChanged();
    emit subtitlesAdded(url.fileName());
}

/*
 * Sets the current subtitles from the list of an available subtitles by key.
 */
void SubtitlesOutput::setSubtitles(qint32 key)
{
    QUrl url("");
    uint error = 1;
    if (urls.size()) {
        url = urls[key]; // Get url from the list by key.
    }
    if (!url.isEmpty()) {
        QFile file(url.toLocalFile());
        if (file.exists()) {
            file.open(QIODevice::ReadOnly);
            if (file.isReadable()) {
                current_subtitles = SubtitleParser::parseFile(&file); // Analyze an open file.
                if (current_subtitles.size() > 0) {
                    _selected = true;
                    error = 0;
                }
            }
        }
    } else {
        empty(); // Clear.
        _selected = false;
    }

    if (error > 0) {
        empty(); // Clear.
        _selected = false;
        if (key != 0) {
            emit subtitlesNotFoundError();
        }
    }
}

/*
 * Returns the subtitles at the time point.
 */
QString SubtitlesOutput::getCurrentSubtitles(qint64 time)
{
    uint size = current_subtitles.size();
    for (uint i = last_index; i < size; ++i) {
        if (current_subtitles.at(i).timeStart() <= time
                && current_subtitles.at(i).timeEnd() >= time) {
            last_index = i;
            return current_subtitles.at(i).text();
        }
    }
    return "";
}

/*
 * Binary search for the subtitles.
 * Finds the subtitles and set the index of these subtitles.
 */
void SubtitlesOutput::binarySearch(qint64 time)
{
    int start = 0, middle = 0;
    int end = current_subtitles.size() - 1;
    while (start < end) {
        middle = start + (end - start) / 2;
        if (current_subtitles.at(middle).timeStart() <= time
                && current_subtitles.at(middle).timeEnd() >= time) {
            last_index = middle;
            return ;
        }
        if (current_subtitles.at(middle).timeEnd() < time) {
            start = middle + 1;
        } else {
            end = middle;
        }
    }
    if (current_subtitles.front().timeStart() <= time &&
            current_subtitles.front().timeEnd() >= time) {
        last_index = 0;
        return ;
    }
    if (current_subtitles.back().timeStart() <= time &&
            current_subtitles.back().timeEnd() >= time) {
        last_index = current_subtitles.size() - 1;
        return ;
    }
    empty();
    last_index = 0;
}

/*
 * Updates the current text.
 */
void SubtitlesOutput::updateSubtitlesText(qint64 time, bool seekable)
{
    if (current_subtitles.size() > 0) {
        if (!seekable) {
            current_text = getCurrentSubtitles(time);
        } else {
            binarySearch(time);
            current_text = current_subtitles.at(last_index).text();
        }
        emit textChanged();
    }
}

/*
 * Display subtitles.
 */
void SubtitlesOutput::setSelected(bool display)
{
    _selected = display;
}

/*
 * Clears the current text of the subtitles.
 */
void SubtitlesOutput::empty()
{
    current_text.clear();
    emit textChanged();
}

/*
 * Clears all loaded subtitles.
 */
void SubtitlesOutput::clearLoadedSubtitles()
{
    urls.clear();
    urls.append(QUrl(""));
    names.clear();
    current_subtitles.clear();
    empty();
    _selected = false;
    last_index = 0;
    emit subtitlesCleared();
}
