#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QApplication>
#include "gamewidget.h"
#include "optionswidget.h"
#include "helpwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStackedWidget WidgetStack;

    // Widget for the GameWidget
    GameWidget * game;

    // Widget for the Menu
    QHBoxLayout buttonsHLayout;
    QVBoxLayout buttonsVLayout;

    QWidget MainMenu;
    QLabel title;

    QPushButton startButton;
    QPushButton optionsButton;
    QPushButton helpButton;
    QPushButton exitButton;
    //--------------------------------------

    //Options
    OptionsWidget Options;
    //--------------------------------------

    //Help
    HelpWidget Help;
    //--------------------------------------

private slots:
    void startGame();
    void setOptions();
    void setHelp();
public slots:
    void showMenu();


};
#endif // MAINWINDOW_H
