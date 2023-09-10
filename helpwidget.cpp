#include "helpwidget.h"
#include "mainwindow.h"

HelpWidget::HelpWidget(QWidget * parent) : QWidget{parent}
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setMinimumSize(500,500);

    //Font Settings
    int id = QFontDatabase::addApplicationFont(":/font/pretty.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont pretty(family,30);

    //Label

    text.setText("Hello and Welcome to QSimon. </br>This is a digital copy of the simon says game. </br>Follow the sequence <u>Simon</u> shows you and try to replicate it. Use the <span style='color:red;'>Arrow Keys</span> or the <span style='color:red;'>WASD keys</span> to select the button in the corresponding direction (EXAMPLE: Up button then i shall press W or the UP Arrow). </br>The backgorund will flash <span style='color:green;'>green</span> when the sequence is correct, if it isn't, you will be notified and prompted to play again!");
    text.setFont(QFont(pretty));
    text.setWordWrap(true);
    text.setTextFormat(Qt::RichText);
    text.setStyleSheet("color: white; font-size:20px;");
    text.setAlignment(Qt::AlignJustify);

    //Button

    returnMenu.setText("RETURN");
    returnMenu.setFont(QFont(pretty));
    returnMenu.setStyleSheet("QPushButton {color: black; font-size:25px; background:rgba(50,205,50,1.000);} QPushButton:hover{background:rgba(0,100,0,1.000);}");
    returnMenu.setCursor(Qt::PointingHandCursor);
    returnMenu.setFixedSize(200, 50);

    //Layout

    mainLayout.addSpacing(20);
    mainLayout.addWidget(&text,0,Qt::AlignCenter);
    mainLayout.addSpacing(50);
    mainLayout.addWidget(&returnMenu,0,Qt::AlignCenter);

    this->setLayout(&mainLayout);

    connect(&returnMenu, &QPushButton::clicked, qobject_cast<MainWindow*>(this->parent()), &MainWindow::showMenu);
}
