#include "../../../src/subtitlesoutput.h"
#include <QSignalSpy>
#include <QtTest>

class SubtitlesOutputTest : public QObject
{
    Q_OBJECT

public:
    SubtitlesOutputTest();

private Q_SLOTS:
    void testAddingSubtitles();
    void testSettingSubtitles();
    void testGettingCurrentSubtitles();
    void testBinarySearch();
    void testClearingLoadedSubtitles();

private:
    QFileInfo test_file;
};

SubtitlesOutputTest::SubtitlesOutputTest()
{
    test_file.setFile("../resources/subtitles/test.srt");
    if (!test_file.exists()) {
        test_file.setFile("../../resources/subtitles/test.srt");
    }
}

void SubtitlesOutputTest::testAddingSubtitles()
{
    SubtitlesOutput subs;
    QSignalSpy spy(&subs, &SubtitlesOutput::listSubtitlesChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy spy_added(&subs, &SubtitlesOutput::subtitlesAdded);
    QCOMPARE(true, spy_added.isValid());
    QUrl subtitle_url = QUrl::fromLocalFile(test_file.absoluteFilePath());
    subs.addSubtitles(subtitle_url);
    QCOMPARE(1, spy.count());
    QCOMPARE(subs.listSubtitles().count(), 1);
    QCOMPARE(subs.listSubtitles().at(0), subtitle_url.fileName());
    QCOMPARE(1, spy_added.count());
}

void SubtitlesOutputTest::testSettingSubtitles()
{
    SubtitlesOutput subs;
    QSignalSpy spy(&subs, &SubtitlesOutput::listSubtitlesChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy spy_added(&subs, &SubtitlesOutput::subtitlesAdded);
    QCOMPARE(true, spy_added.isValid());
    QSignalSpy spy_error(&subs, &SubtitlesOutput::subtitlesNotFoundError);
    QCOMPARE(true, spy_error.isValid());
    QSignalSpy spy_text(&subs, &SubtitlesOutput::textChanged);
    QCOMPARE(true, spy_text.isValid());

    QUrl subtitle_url = QUrl::fromLocalFile(test_file.absoluteFilePath());
    subs.addSubtitles(subtitle_url);
    QCOMPARE(1, spy.count());
    QCOMPARE(subs.listSubtitles().count(), 1);
    QCOMPARE(1, spy_added.count());
    subs.setSubtitles(1);
    QCOMPARE(0, spy_text.count());
    QCOMPARE(0, spy_error.count());
    QCOMPARE(true, subs.selected());

    QUrl other_subtitles_url("/path/to/invalid/url");
    subs.addSubtitles(other_subtitles_url);
    QCOMPARE(2, spy.count());
    QCOMPARE(subs.listSubtitles().at(1), QString("url"));
    QCOMPARE(2, spy_added.count());
    subs.setSubtitles(2);
    QCOMPARE(false, subs.selected());
    QCOMPARE(1, spy_error.count());
    QCOMPARE(1, spy_text.count());

    QUrl other_subtitle_url = QUrl::fromLocalFile(test_file.absoluteFilePath());
    subs.addSubtitles(other_subtitle_url);
    QCOMPARE(3, spy.count());
    QCOMPARE(subs.listSubtitles().count(), 3);
    QCOMPARE(3, spy_added.count());
    subs.setSubtitles(3);
    QCOMPARE(1, spy_text.count());
    QCOMPARE(1, spy_error.count());
    QCOMPARE(true, subs.selected());

    subs.setSubtitles(0);
    QCOMPARE(false, subs.selected());
    QCOMPARE(2, spy_text.count());
    QCOMPARE(1, spy_error.count());
}

void SubtitlesOutputTest::testGettingCurrentSubtitles()
{
    SubtitlesOutput subs;
    QSignalSpy spy(&subs, &SubtitlesOutput::listSubtitlesChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy spy_added(&subs, &SubtitlesOutput::subtitlesAdded);
    QCOMPARE(true, spy_added.isValid());
    QSignalSpy spy_error(&subs, &SubtitlesOutput::subtitlesNotFoundError);
    QCOMPARE(true, spy_error.isValid());

    QUrl subtitle_url = QUrl::fromLocalFile(test_file.absoluteFilePath());
    subs.addSubtitles(subtitle_url);
    QCOMPARE(1, spy.count());
    QCOMPARE(subs.listSubtitles().count(), 1);
    QCOMPARE(1, spy_added.count());
    subs.setSubtitles(1);
    QCOMPARE(0, spy_error.count());
    QCOMPARE(true, subs.selected());

    // hours + minutes + seconds + milliseconds
    int64_t position = 0 * 60 * 60 * 1000 + 0 * 60 * 1000 + 1 * 1000 + 200;
    QString text = subs.getCurrentSubtitles(position);
    QCOMPARE(text, QString("- Example text\n- Example test two\n\n"));

    position = 00 * 60 * 60 * 1000 + 00 * 60 * 1000 + 2 * 1000 + 600;
    text = subs.getCurrentSubtitles(position);
    QCOMPARE(text, QString("- Example\n\n"));

    position = 00 * 60 * 60 * 1000 + 00 * 60 * 1000 + 4 * 1000 + 700;
    text = subs.getCurrentSubtitles(position);
    QCOMPARE(text, QString("- End\n"));

    position = 00 * 60 * 60 * 1000 + 00 * 60 * 1000 + 8 * 1000 + 600;
    text = subs.getCurrentSubtitles(position);
    QCOMPARE(true, text.isEmpty());
}

void SubtitlesOutputTest::testBinarySearch()
{
    SubtitlesOutput subs;
    QSignalSpy spy(&subs, &SubtitlesOutput::listSubtitlesChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy spy_added(&subs, &SubtitlesOutput::subtitlesAdded);
    QCOMPARE(true, spy_added.isValid());
    QSignalSpy spy_error(&subs, &SubtitlesOutput::subtitlesNotFoundError);
    QCOMPARE(true, spy_error.isValid());

    QUrl subtitle_url = QUrl::fromLocalFile(test_file.absoluteFilePath());
    subs.addSubtitles(subtitle_url);
    QCOMPARE(1, spy.count());
    QCOMPARE(subs.listSubtitles().count(), 1);
    QCOMPARE(1, spy_added.count());
    subs.setSubtitles(1);
    QCOMPARE(0, spy_error.count());
    QCOMPARE(true, subs.selected());

    int64_t position = 0 * 60 * 60 * 1000 + 0 * 60 * 1000 + 1 * 1000 + 200;
    subs.updateSubtitlesText(position, true);
    QString text = subs.text();
    QCOMPARE(text, QString("- Example text\n- Example test two\n\n"));

    position = 0 * 60 * 60 * 1000 + 0 * 60 * 1000 + 2 * 1000 + 600;
    subs.updateSubtitlesText(position, true);
    text = subs.text();
    QCOMPARE(text, QString("- Example\n\n"));

    position = 0 * 60 * 60 * 1000 + 0 * 60 * 1000 + 4 * 1000 + 700;
    qDebug() << position;
    subs.updateSubtitlesText(position, true);
    text = subs.text();
    QCOMPARE(text, QString("- End\n"));

    position = 0 * 60 * 60 * 1000 + 0 * 60 * 1000 + 6 * 1000 + 600;
    subs.updateSubtitlesText(position, false);
    text = subs.text();
    QCOMPARE(true, text.isEmpty());
}

void SubtitlesOutputTest::testClearingLoadedSubtitles()
{
    SubtitlesOutput subs;
    QSignalSpy spy(&subs, &SubtitlesOutput::listSubtitlesChanged);
    QCOMPARE(true, spy.isValid());
    QSignalSpy spy_added(&subs, &SubtitlesOutput::subtitlesAdded);
    QCOMPARE(true, spy_added.isValid());
    QSignalSpy spy_error(&subs, &SubtitlesOutput::subtitlesNotFoundError);
    QCOMPARE(true, spy_error.isValid());
    QSignalSpy spy_clear(&subs, &SubtitlesOutput::subtitlesCleared);
    QCOMPARE(true, spy_clear.isValid());

    QUrl subtitle_url = QUrl::fromLocalFile(test_file.absoluteFilePath());
    subs.addSubtitles(subtitle_url);
    QCOMPARE(1, spy.count());
    QCOMPARE(subs.listSubtitles().count(), 1);
    QCOMPARE(1, spy_added.count());
    subs.setSubtitles(1);
    QCOMPARE(0, spy_error.count());
    QCOMPARE(true, subs.selected());

    subs.clearLoadedSubtitles();
    QCOMPARE(subs.listSubtitles().isEmpty(), true);
    QCOMPARE(subs.selected(), false);
    QCOMPARE(1, spy_clear.count());
}

QTEST_MAIN(SubtitlesOutputTest)

#include "tst_subtitlesoutputtest.moc"
