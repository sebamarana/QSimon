#include "mainwindow.h"
#include <QFontDatabase>
#include <QDebug>


//TODO: Do a menu with options and a walktrough

MainWindow::MainWindow(QWidget *parent):
    QMainWindow{parent},
    Options{this},
    Help{this}
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setMinimumSize(500,500);
    this->setStyleSheet("background-color: black;");

    //Widget Stack
    WidgetStack.addWidget(&MainMenu);
    WidgetStack.addWidget(&Options);
    WidgetStack.addWidget(&Help);
    this->setCentralWidget(&WidgetStack);
    //-----------------------------


    //Font Settings
    int id = QFontDatabase::addApplicationFont(":/font/pretty.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont pretty(family,30);
    //-----------------------------

    //Title Settings
    title.setText("QSimon");
    title.setFont(QFont(pretty));
    title.setStyleSheet("color: white; font-size:55px;");
    //-----------------------------

    //Buttons Settings
    startButton.setText("START");
    startButton.setFont(QFont(pretty));
    startButton.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(255,0,0,1);} QPushButton:hover{background:rgba(139,0,0,1);}");
    startButton.setFocus();
    startButton.setCursor(Qt::PointingHandCursor);
    startButton.setFixedSize(200, 50);

    optionsButton.setText("OPTIONS");
    optionsButton.setFont(QFont(pretty));
    optionsButton.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(255,255,0,1.000);} QPushButton:hover{background:rgba(128,128,0,1.000);}");
    optionsButton.setCursor(Qt::PointingHandCursor);
    optionsButton.setFixedSize(200, 50);

    helpButton.setText("HELP");
    helpButton.setFont(QFont(pretty));
    helpButton.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(50,205,50,1.000);} QPushButton:hover{background:rgba(0,100,0,1.000);}");
    helpButton.setCursor(Qt::PointingHandCursor);
    helpButton.setFixedSize(200, 50);

    exitButton.setText("EXIT");
    exitButton.setFont(QFont(pretty));
    exitButton.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(65,105,225,1.000);} QPushButton:hover{background:rgba(0,0,139,1.000);}");
    exitButton.setCursor(Qt::PointingHandCursor);
    exitButton.setFixedSize(200, 50);
    //-----------------------------

    //Layout settings
    buttonsVLayout.addWidget(&title, 0, Qt::AlignCenter);
    buttonsVLayout.addWidget(&startButton, 0, Qt::AlignCenter);
    buttonsVLayout.addWidget(&optionsButton, 0, Qt::AlignCenter);
    buttonsVLayout.addWidget(&helpButton, 0, Qt::AlignCenter);
    buttonsVLayout.addWidget(&exitButton, 0, Qt::AlignCenter);

    buttonsVLayout.setAlignment(Qt::AlignCenter);
    buttonsVLayout.setSpacing(25);

    MainMenu.setLayout(&buttonsVLayout);
    WidgetStack.setCurrentWidget(&MainMenu);
    //------------------------------

    connect(&startButton,SIGNAL(pressed()),this,SLOT(startGame()));
    connect(&optionsButton,SIGNAL(pressed()),this,SLOT(setOptions()));
    connect(&helpButton,SIGNAL(pressed()),this,SLOT(setHelp()));
    connect(&exitButton,SIGNAL(pressed()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete game;
}

void MainWindow::startGame()
{
    game = new GameWidget(Options.getButtons(),Options.getDifficulty(),this);
    WidgetStack.addWidget(game);
    WidgetStack.setCurrentWidget(game);
    game->setFrameStyle(QFrame::NoFrame);
    game->setFocus();
    game->startGame();
}

void MainWindow::setOptions()
{
    WidgetStack.setCurrentWidget(&Options);
}

void MainWindow::setHelp()
{
    WidgetStack.setCurrentWidget(&Help);
}


void MainWindow::showMenu()
{
    //game->setScene(nullptr);
    WidgetStack.setCurrentWidget(&MainMenu);
    return;
}

