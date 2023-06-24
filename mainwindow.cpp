#include "mainwindow.h"
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setFixedSize(500,500);
    this->setStyleSheet("background-color: black;");

    game = new GameWidget(this);
    view = new QGraphicsView(this);
    view->setScene(game);
    this->setCentralWidget(view);

    int id = QFontDatabase::addApplicationFont(":/font/pretty.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont pretty(family,30);
    startButton.setText("START");
    startButton.setFont(QFont(pretty));
    startButton.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(255, 255, 255, 150);} QPushButton:hover{background:rgba(255, 255, 255, 230);}");
    startButton.setFocus();
    startButton.setCursor(Qt::PointingHandCursor);
    startButton.setFixedSize(200, 50);

    layout.addWidget(&startButton,0,Qt::AlignCenter);
    view->setLayout(&layout);

    connect(&startButton,SIGNAL(pressed()),this,SLOT(startGame()));
}

MainWindow::~MainWindow()
{
    delete game;
    delete view;
}

void MainWindow::startGame()
{
    startButton.hide();
    game->setFocus();
    game->startGame();
}

