#include "threadperc.h"

ThreadPerc::ThreadPerc(QByteArray bA1, QByteArray bA2){
    ba1=bA1;
    ba2=bA2;
    percent = 100;
}

qint8 ThreadPerc::getPercent(){
    return percent;
}

void compareScreenshots(QByteArray ba1, QByteArray& ba2, qint8& result){
    qint32 count = 0;
    for (qint32 i=0; i<ba1.size();i++)
        if (ba1[i]==ba2[i]) ++count;
    result = qint8(100*count/ba1.size());
}

void ThreadPerc::run(){
    compareScreenshots(ba1, ba2, percent);
}
