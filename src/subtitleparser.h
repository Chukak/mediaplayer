#ifndef SUBTITLEPARSER_H
#define SUBTITLEPARSER_H

#include <QObject>
#include <QFile>
#include <vector>
#include <QRegularExpression>
#include "subtitleitem.h"


class SubtitleParser
{
public:
    SubtitleParser();

    static std::vector<SubtitleItem> parseFile(QFile *file);

private:
    static qint64 getValue(const QRegularExpressionMatch& match, int pos);
};

#endif // SUBTITLEPARSER_H
