#include "screenshot.h"


Screenshot::Screenshot(){
    screen = QGuiApplication::primaryScreen();
}

void Screenshot::takeScreenshot(){
    pixmap = screen->grabWindow(0);
};

QPixmap Screenshot::getScreenshot(){
    return pixmap;
};

qint64 Screenshot::getCache(){
    cache = pixmap.cacheKey();
    return cache;
};

QByteArray Screenshot::getByteArray(){
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "BMP");
    return byteArray;
}

