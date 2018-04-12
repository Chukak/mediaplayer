#ifndef SUBTITLEITEM_H
#define SUBTITLEITEM_H

#include <QtCore>

class  SubtitleItem {
public:
    SubtitleItem(qint32 number, qint64 start, qint64 end, QString string) :
        number_section(number),
        time_start(start),
        time_end(end),
        _text(string)
    {
    }

    qint32 section() { return number_section; }

    qint64 timeStart() { return time_start; }

    qint64 timeEnd() { return time_end; }

    QString text() { return _text; }

private:
    qint32 number_section;
    qint64 time_start;
    qint64 time_end;
    QString _text;
};


#endif // SUBTITLEITEM_H
