#include "mainwindow.h"
#include <QFontDatabase>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setFixedSize(500,500);
    this->setStyleSheet("background-color: black;");


    //Font Settings
    int id = QFontDatabase::addApplicationFont(":/font/pretty.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont pretty(family,30);
    //-----------------------------

    //Button Settings
    startButton.setText("START");
    startButton.setFont(QFont(pretty));
    startButton.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(255, 255, 255, 150);} QPushButton:hover{background:rgba(255, 255, 255, 230);}");
    startButton.setFocus();
    startButton.setCursor(Qt::PointingHandCursor);
    startButton.setFixedSize(200, 50);
    //-----------------------------

    //Label Settings
    pointsLabel.setText("Points: 0");
    pointsLabel.setStyleSheet("color: white; font-size:25px; background:rgba(255, 255, 255, 0)");
    pointsLabel.setFont(QFont(pretty));

    recordLabel.setText("Record: 0");
    recordLabel.setStyleSheet("color: white; font-size:25px; background:rgba(255, 255, 255, 0)");
    recordLabel.setFont(QFont(pretty));
    //-----------------------------

    //View and GameWidget creation
    game = new GameWidget(this);
    view = new QGraphicsView(this);
    view->setScene(game);
    view->setFrameStyle(QFrame::NoFrame);
    this->setCentralWidget(view);
    //-----------------------------

    //Layout settings
    buttonLayout.addStretch(0);
    buttonLayout.addWidget(&startButton);
    buttonLayout.addStretch(0);

    layout.addWidget(&recordLabel,0,Qt::AlignTop);
    layout.addLayout(&buttonLayout);
    layout.addWidget(&pointsLabel,0,Qt::AlignBottom);
    view->setLayout(&layout);
    //------------------------------

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

void MainWindow::upPoints(unsigned int pts)
{
    std::string points = std::to_string(pts);
    pointsLabel.setText(QString::fromStdString("Points: "+points));
}

void MainWindow::upRecord(unsigned int rec)
{
    std::string record = std::to_string(rec);
    recordLabel.setText(QString::fromStdString("Record: "+record));
}

