#include "subtitlesoutput.h"
#include <QDebug>

SubtitlesOutput::SubtitlesOutput(QObject *parent) :
    QObject(parent)
{
}

void SubtitlesOutput::addSubtitles(const QUrl &url)
{
    urls.push_back(url);
    names.push_back(url.fileName());
    emit listSubtitlesChanged();
}

void SubtitlesOutput::setSubtitles(qint32 key)
{
    QUrl url("");
    if (urls.size()) {
        url = urls[key];
    }
    if (!url.isEmpty()) {
        QFile file(url.toLocalFile());
        if (file.exists()) {
            file.open(QIODevice::ReadOnly);
            if (file.isReadable()) {
                current_subtitles = SubtitleParser::parseFile(&file);
                selected_subs = true;
            }
        }
    } else {
        empty();
    }
}

QString SubtitlesOutput::getCurrentSubtitles(qint64 time)
{
    for (qint32 i = last_index; i < static_cast<qint32>(current_subtitles.size()); ++i) {
        if (current_subtitles.at(i).timeStart() <= time
                && current_subtitles.at(i).timeEnd() >= time) {
            last_index = i;
            return current_subtitles.at(i).text();
        }
    }
    return "";
}

void SubtitlesOutput::binarySearch(qint64 time)
{
    int start = 0, middle = 0;
    int end = current_subtitles.size() - 1;
    while (start < end) {
        middle = start + (end - start) / 2;
        if (current_subtitles.at(middle).timeStart() <= time
                && current_subtitles.at(middle).timeEnd() >= time) {
            last_index = middle;
            break;
        }
        if (current_subtitles.at(middle).timeEnd() < time) {
            start = middle + 1;
        } else {
            end = middle;
        }
    }
}

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

void SubtitlesOutput::empty()
{
    current_text.clear();
    emit textChanged();
}

