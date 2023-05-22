#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>


class Db
{
public:
    Db();

    QByteArray getFirstPhoto();
    QString getFirstPercent();
    void insertRow(QByteArray, qint64, qint8);
    bool isPrepared();

private:
    QSqlDatabase db;
    QSqlQuery *query;
};

#endif // DB_H
