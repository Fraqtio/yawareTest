#ifndef THREADPERC_H
#define THREADPERC_H

#include <QThread>


class ThreadPerc: public QThread
{
public:
    ThreadPerc(QByteArray, QByteArray);
    qint8 getPercent();
    void run();
private:
    QByteArray ba1;
    QByteArray ba2;
    qint8 percent;
};
#endif // THREADPERC_H
