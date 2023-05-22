#include "db.h"

Db::Db()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./yawareDB.db");
    db.open();

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE IF NOT EXISTS Scrshots(photo BLOB NOT NULL, cache INT64 NOT NULL, perc INT NOT NULL)");
}


bool Db::isPrepared(){
    query->exec("SELECT * FROM Scrshots LIMIT 1");
    return query->first();
}


QByteArray Db::getFirstPhoto(){
    isPrepared();
    return query->value("photo").toByteArray();

};


QString Db::getFirstPercent(){
    isPrepared();
    return query->value(2).toString()+"% of similarity";
};

//i'm not proud about shis, but it works
void Db::insertRow(QByteArray ba, qint64 cache, qint8 perc){
    query->exec("CREATE TABLE  Temp (photo BLOB NOT NULL, cache INT64 NOT NULL, perc INT NOT NULL)");
    query->prepare("INSERT INTO Temp (photo, cache, perc) "
                   "VALUES (?, ?, ?)");
    query->addBindValue(ba);
    query->addBindValue(cache);

    query->addBindValue(perc);
    query->exec();
    query->exec("INSERT INTO Temp (photo, cache, perc) "
                "SELECT * "
                "FROM Scrshots "
                "LIMIT 15");
    query->exec("DELETE FROM Scrshots");
    query->exec("INSERT INTO Scrshots (photo, cache, perc) "
                "SELECT * "
                "FROM Temp ");
    query->exec("DROP TABLE Temp");
};
