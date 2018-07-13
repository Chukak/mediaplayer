#ifndef SUBTITLEPARSER_H
#define SUBTITLEPARSER_H

#include <QObject>
#include <QVector>
#include <QRegularExpression>
#include "subtitleitem.h"

/*
 * Parser for .srt files.
 * Gets the file in `.srt` format. Analizes and returns a list of subtitle objects.
 */
class SubtitleParser
{
public:
    SubtitleParser();

    /*
     * Analysis static function. Returns a list of subtitle objects.
     * @param file - file in `.srt` format.
     */
    static QVector<SubtitleItem> parseFile(QFile *file);

private:
    /*
     * Static function. Disassembles a regular expression object
     * and returns the time in milliseconds.
     * @param match - A regular expression object.
     * @param pos - group position in a regular expression.
     */
    static qint64 getValue(const QRegularExpressionMatch& match, int pos);
};

#endif // SUBTITLEPARSER_H
