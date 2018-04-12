#include "subtitleparser.h"

#include <QRegularExpressionMatchIterator>

SubtitleParser::SubtitleParser()
{
}

std::vector<SubtitleItem> SubtitleParser::parseFile(QFile *file)
{
    std::vector<SubtitleItem> subtitles;
    QTextStream stream(file);
    stream.setCodec("UTF-8");
    QString content = stream.readAll();
    qDebug() << file->fileName();
    QRegularExpression pattern(
                "(\\d{1}).*?\n(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3}) --> (\\d{2}):(\\d{2}):(\\d{2}),(\\d{3}).*?\n([\\s\\S]*?)\r\n");
    qDebug() << pattern.pattern();
    qDebug() << content.at(0);
    QRegularExpressionMatchIterator iterator = pattern.globalMatch(content);
    qDebug() << iterator.hasNext();
    while (iterator.hasNext()) {
        QRegularExpressionMatch match = iterator.next();
        qint32 section = match.captured(1).toLong();
        qint64 start = getValue(match, 2);
        qint64 end = getValue(match, 6);
        QString text = match.captured(10);
        qDebug() << text;
        SubtitleItem item(section, start, end, text);
        subtitles.push_back(item);
    }
    return subtitles;
}

qint64 SubtitleParser::getValue(const QRegularExpressionMatch& match, int pos)
{
    qint64 h = match.captured(pos).toLongLong() * 60 * 60 * 1000;
    qint64 m = match.captured(pos + 1).toLongLong() * 60 * 1000;
    qint64 s = match.captured(pos + 2).toLongLong() * 1000;
    qint64 ms = match.captured(pos + 3).toLongLong();
    return h + m + s + ms;
}
