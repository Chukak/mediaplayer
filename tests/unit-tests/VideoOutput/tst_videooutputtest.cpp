#include <QString>
#include <QtTest>

class VideoOutputTest : public QObject
{
    Q_OBJECT

public:
    VideoOutputTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

VideoOutputTest::VideoOutputTest()
{
}

void VideoOutputTest::initTestCase()
{
}

void VideoOutputTest::cleanupTestCase()
{
}

void VideoOutputTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VideoOutputTest)

#include "tst_videooutputtest.moc"
