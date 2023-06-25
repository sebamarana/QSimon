#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
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
    QHBoxLayout buttonLayout;

    QPushButton startButton;

    QLabel pointsLabel,recordLabel;
private slots:
    void startGame();
public slots:
    void upPoints(unsigned int pts);
    void upRecord(unsigned int rec);

};
#endif // MAINWINDOW_H
