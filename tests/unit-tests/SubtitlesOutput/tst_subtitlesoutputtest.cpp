#include <QString>
#include <QtTest>

class SubtitlesOutputTest : public QObject
{
    Q_OBJECT

public:
    SubtitlesOutputTest();

private Q_SLOTS:
    void testCase1();
};

SubtitlesOutputTest::SubtitlesOutputTest()
{
}

void SubtitlesOutputTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SubtitlesOutputTest)

#include "tst_subtitlesoutputtest.moc"
