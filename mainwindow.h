#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextBlock>
#include <db.h>
#include <threadperc.h>
#include <screenshot.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startStopButtonClicked();

private:
    Ui::MainWindow *ui;
    Db db;
    QPushButton *pButton;
    QLabel *picLabel;
    QLabel *textLabel;
    QVBoxLayout *layout;
    Screenshot scr;
};
#endif // MAINWINDOW_H
