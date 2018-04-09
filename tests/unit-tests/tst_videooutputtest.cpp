#include "../../src/videooutput.h"
#include <QString>
#include <QtTest>
#include <QQuickItem>

class VideoOutputTest : public QObject
{
    Q_OBJECT

public:
    VideoOutputTest();

private Q_SLOTS:
    void testTargetOutput();
};

VideoOutputTest::VideoOutputTest()
{
}

void VideoOutputTest::testTargetOutput()
{
    VideoOutput output;
    QQuickItem *target = new QQuickItem();
    output.setTargetOutput(target);
    QCOMPARE(output.targetOutput(), target);
}

QTEST_APPLESS_MAIN(VideoOutputTest)

#include "tst_videooutputtest.moc"
