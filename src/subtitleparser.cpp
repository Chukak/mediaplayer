#include "subtitleparser.h"
#include <QFile>
#include <QRegularExpressionMatchIterator>

SubtitleParser::SubtitleParser()
{
}

/*
 * Analysis function. Returns a list of subtitle objects.
 */
std::vector<SubtitleItem> SubtitleParser::parseFile(QFile *file)
{
    std::vector<SubtitleItem> subtitles;
    QTextStream stream(file);
    stream.setCodec("UTF-8"); // Set UTF-8.
    QString content = stream.readAll();
    /*
     * A pattern for parsing `.srt` files.
     * Structure of the `.srt` file.
     * `section number \n start time --> end time \n subtitle text \r\n\r\n`
     */
    QString string_pattern("(\\d{1}).*?\n(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3}) --> "
                           "(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3}).*?\n([\\s\\S]*?\r\n\r\n)");
    QRegularExpression pattern(string_pattern);
    QRegularExpressionMatchIterator iterator = pattern.globalMatch(content);
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        // Section number.
        qint32 section = match.captured(1).toLong();
        // Start and end time in milliseconds.
        qint64 start = getValue(match, 2);
        qint64 end = getValue(match, 6);
        // Subtitle text
        QString text = match.captured(10);
        SubtitleItem item(section, start, end, text);
        subtitles.push_back(item);
    }
    return subtitles;
}

/*
 * Disassembles a regular expression object
 * and returns the time in milliseconds.
 */
qint64 SubtitleParser::getValue(const QRegularExpressionMatch& match, int pos)
{
    qint64 h = match.captured(pos).toLongLong() * 60 * 60 * 1000;
    qint64 m = match.captured(pos + 1).toLongLong() * 60 * 1000;
    qint64 s = match.captured(pos + 2).toLongLong() * 1000;
    qint64 ms = match.captured(pos + 3).toLongLong();
    return h + m + s + ms;
}
