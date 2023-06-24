#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPushButton>
#include "gamewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GameWidget * game;
    QGraphicsView *view;

    QVBoxLayout layout;
    QPushButton startButton;

private slots:
    void startGame();
};
#endif // MAINWINDOW_H
