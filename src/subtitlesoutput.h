#ifndef SUBTITLESOUTPUT_H
#define SUBTITLESOUTPUT_H

#include <QObject>
#include <QList>
#include "subtitleparser.h"

class SubtitlesOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    Q_PROPERTY(QStringList listSubtitles READ listSubtitles NOTIFY listSubtitlesChanged)
public:
    SubtitlesOutput(QObject *parent = nullptr);

    Q_INVOKABLE void addSubtitles(const QUrl &url);

    QString text() const { return current_text; }

    void empty();

    QStringList listSubtitles() const { return names; }

    Q_INVOKABLE void setSubtitles(qint32 key);

    QString getCurrentSubtitles(qint64 time);

    void binarySearch(qint64 time);

    bool selected() const { return selected_subs; }

public slots:
    void updateSubtitlesText(qint64 time, bool seekable);

signals:

    void textChanged();

    void listSubtitlesChanged();

    void subtitlesAdded();

private:
    QStringList names;
    QList<QUrl> urls = {QUrl("")};
    bool selected_subs = false;
    std::vector<SubtitleItem> current_subtitles;
    QString current_text = "";
    qint32 last_index = 0;

};

#endif // SUBTITLESOUTPUT_H
