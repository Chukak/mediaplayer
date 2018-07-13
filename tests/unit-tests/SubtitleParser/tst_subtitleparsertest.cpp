#include "../../../src/subtitleparser.h"
#include <QtTest>

class SubtitleParserTest : public QObject
{
    Q_OBJECT

public:
    SubtitleParserTest();

private Q_SLOTS:
    void testParser();

private:
    QFileInfo test_file;
};

SubtitleParserTest::SubtitleParserTest()
{
    test_file.setFile("../resources/subtitles/test.srt");
    if (!test_file.exists()) {
        test_file.setFile("../../resources/subtitles/test.srt");
    }
}

void SubtitleParserTest::testParser()
{
    QUrl file_url = QUrl::fromLocalFile(test_file.absoluteFilePath());
    QCOMPARE(file_url.isEmpty(), false);
    QFile file(file_url.toLocalFile());
    QCOMPARE(file.exists(), true);
    file.open(QIODevice::ReadOnly);
    QCOMPARE(file.isReadable(), true);
    QVector<SubtitleItem> list = SubtitleParser::parseFile(&file);
    int size = 3;
    QCOMPARE(list.size(), size);
    QCOMPARE(list.at(0).timeStart(), 1123);
    QCOMPARE(list.at(0).timeEnd(), 2456);
    QCOMPARE(list.at(0).text(), QString("- Example text\n- Example test two\n\n"));
    QCOMPARE(list.at(0).section(), 1);

    QCOMPARE(list.at(1).timeStart(), 2563);
    QCOMPARE(list.at(1).timeEnd(), 3384);
    QCOMPARE(list.at(1).text(), QString("- Example\n\n"));
    QCOMPARE(list.at(1).section(), 2);

    QCOMPARE(list.at(2).timeStart(), 3563);
    QCOMPARE(list.at(2).timeEnd(), 5654);
    QCOMPARE(list.at(2).text(), QString("- End\n"));
    QCOMPARE(list.at(2).section(), 3);
}

QTEST_MAIN(SubtitleParserTest)

#include "tst_subtitleparsertest.moc"
