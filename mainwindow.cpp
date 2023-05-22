#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    picLabel = new QLabel("No data yet", this);
    picLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    textLabel = new QLabel("No data yet", this);
    textLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    textLabel->setFont(QFont("Times", 14));

    pButton = new QPushButton("Start", this);
    pButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(pButton, &QPushButton::clicked, this, &MainWindow::startStopButtonClicked);

    layout  = new QVBoxLayout;
    layout->addWidget(picLabel, 1, Qt::AlignCenter);
    layout->addWidget(textLabel, 1, Qt::AlignCenter);
    layout->addWidget(pButton, 1, Qt::AlignCenter);
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    setCentralWidget(widget);


    if (db.isPrepared()) {
        QByteArray preloadByteArr = db.getFirstPhoto();
        QPixmap preloadPixmap;
        preloadPixmap.loadFromData(preloadByteArr, "BMP");
        picLabel->setPixmap(preloadPixmap.scaled(QSize(800, 500)));
        textLabel->setText(db.getFirstPercent());
    }
}


MainWindow::~MainWindow() {
    delete ui;
}


void delay(qint8 n) {
    QTime dieTime= QTime::currentTime().addSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



void MainWindow::startStopButtonClicked() {
    if (pButton->text() == "Start"){
        pButton->setText("Stop");
        while(true){
            scr.takeScreenshot();

            QTime t1 = QTime::currentTime();

            if (db.isPrepared()) {
                ThreadPerc thread(scr.getByteArray(), db.getFirstPhoto());

                thread.start();
                thread.wait();

                db.insertRow(scr.getByteArray(), scr.getCache(), thread.getPercent());

                picLabel->setPixmap(scr.getScreenshot().scaled(QSize(800, 500)));
                textLabel->setText(QString::number(thread.getPercent())+"% of similarity");
            }
            else {
                db.insertRow(scr.getByteArray(), scr.getCache(), 100);

                picLabel->setPixmap(scr.getScreenshot().scaled(QSize(800, 500)));
                textLabel->setText("100% of similarity");
            }
            QTime t2 = QTime::currentTime();
            delay(60-t1.secsTo(t2));
        }
    }
    else pButton->setText("Start");
}

