#include <QString>
#include <QtTest>

class SubtitleParserTest : public QObject
{
    Q_OBJECT

public:
    SubtitleParserTest();

private Q_SLOTS:
    void testCase1();
};

SubtitleParserTest::SubtitleParserTest()
{
}

void SubtitleParserTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SubtitleParserTest)

#include "tst_subtitleparsertest.moc"
