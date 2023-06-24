#include "gamewidget.h"
#include <QDebug>

GameWidget::GameWidget(QWidget *parent) :
    QGraphicsScene(parent),
    btnAnimTime(600)
{
    this->setFocus();
    Turn.setInterval(1000);
    playerClick.setInterval(1); // TODO: Possibilmente sistemare la nomenclatura

    connect(&playerClick, &QTimer::timeout, this, &GameWidget::timer_out);
    connect(&Turn, &QTimer::timeout, this, &GameWidget::timer_out);

    loadGame();
}

GameWidget::~GameWidget()
{

}

void GameWidget::loadGame() //Al caricamento dell'applicazione
{
    //Set Default colors of buttons
    up.setDefaultColors();
    down.setDefaultColors();
    right.setDefaultColors();
    left.setDefaultColors();

    //Set Sounds of buttons
    up.setSound(":/sounds/Sounds/Up.wav");
    down.setSound(":/sounds/Sounds/Down.wav");
    right.setSound(":/sounds/Sounds/Right.wav");
    left.setSound(":/sounds/Sounds/Left.wav");

    //Set Elapsing timer for button press animation
    Up_Elapsed.start();
    Left_Elapsed.start();
    Down_Elapsed.start();
    Right_Elapsed.start();

    //Initial rendering of visitor and Adding Group of GraphicalItems from Visitor
    visitor.render(up.getColor(),right.getColor(),down.getColor(),left.getColor());
    this->addItem(visitor.getGroup());

    //Turns
    playerTurn = false;
}

void GameWidget::startGame() //Dopo aver premuto start
{
    //Turn.start();
    playerClick.start();
    playerTurn = true;

    computer.push_back(up);
    computer.push_back(up);
    computer.push_back(up);
    computer.push_back(left);
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
            return;
        }
    if(playerTurn) {
        switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            // Up
            if(Up_Elapsed.elapsed()>=100){
                player.push_back(up);
                player.getLast()->setPressed(true);
                player.getLast()->acceptVisitor(&visitor);
                Up_Elapsed.restart();
            }
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            // Left
            if(Left_Elapsed.elapsed()>=100){
                left.setPressed(true);
                left.acceptVisitor(&visitor);
                Left_Elapsed.restart();
            }
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            // Down
            if(Down_Elapsed.elapsed()>=100){
                down.setPressed(true);
                down.acceptVisitor(&visitor);
                Down_Elapsed.restart();
            }
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            // Right
            if(Right_Elapsed.elapsed()>=100){
                right.setPressed(true);
                right.acceptVisitor(&visitor);
                Right_Elapsed.restart();
            }
            break;
        default:
            QGraphicsScene::keyPressEvent(event);
            break;
        }
        //TODO: Magari aggiungere un check degli input qui per dire se si è corretti o no
        if(player==computer) {
            qDebug()<<"ok!";
        }
        else {
            qDebug()<<"You are wrong boy!";
            player.clean();
        }
    }
}

void GameWidget::timer_out()
{
    if(playerTurn){
        if(Up_Elapsed.elapsed()>=btnAnimTime){
            up.setPressed(false);
            up.acceptVisitor(&visitor);
        }
        if(Left_Elapsed.elapsed()>=btnAnimTime){
            left.setPressed(false);
            left.acceptVisitor(&visitor);
        }
        if(Down_Elapsed.elapsed()>=btnAnimTime){
            down.setPressed(false);
            down.acceptVisitor(&visitor);
        }
        if(Right_Elapsed.elapsed()>=btnAnimTime){
            right.setPressed(false);
            right.acceptVisitor(&visitor);
        }
    }
}

