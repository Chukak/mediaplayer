#ifndef SUBTITLEITEM_H
#define SUBTITLEITEM_H

#include <QtCore>

/*
 * Class SubtitleItem.
 * Creates the subtitle object by using a data from .srt file.
 * Used to passing to the parser.
 */
class  SubtitleItem {
public:
    /*
     * Default constructor.
     */
    SubtitleItem()
    {
    }

    /*
     * A constructor.
     * Gets four parameters.
     * @param number - section number
     * @param start, end - start time and end time, when subtitles must be displayed
     * @parant string - subtitles text
     */
    explicit SubtitleItem(qint32 number, qint64 start, qint64 end, const QString& string) :
        number_section(number),
        time_start(start),
        time_end(end),
        _text(string)
    {
    }

    /*
     * Constant function, returns the section number.
     */
    qint32 section() const noexcept { return number_section; }

    /*
     * Constant function, returns the start time.
     */
    qint64 timeStart() const noexcept { return time_start; }

    /*
     * Constant function, returns the end time.
     */
    qint64 timeEnd() const noexcept { return time_end; }

    /*
     * Constant function, returns the subtitles text.
     */
    QString text() const noexcept { return _text; }

private:
    qint32 number_section;
    qint64 time_start;
    qint64 time_end;
    QString _text;
};

#endif // SUBTITLEITEM_H
