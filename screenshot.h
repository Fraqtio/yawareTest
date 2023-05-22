#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QScreen>
#include <QPixmap>
#include <QGuiApplication>
#include <QBuffer>

class Screenshot
{
public:
    Screenshot();
    void takeScreenshot();
    QPixmap getScreenshot();
    qint64 getCache();
    QByteArray getByteArray();

private:
    QScreen *screen;
    QPixmap pixmap;
    qint64 cache;
};

#endif // SCREENSHOT_H
