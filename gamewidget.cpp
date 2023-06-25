#include "gamewidget.h"
#include "mainwindow.h"
#include <QDebug>
#include <QCoreApplication>


GameWidget::GameWidget(QWidget *parent) :
    QGraphicsScene(parent),
    btnAnimTime(400),
    computerAnimSpeed(700)
{
    this->setFocus();

    computerTurn.setInterval(computerAnimSpeed);
    playerTurn.setInterval(1);

    random.seed(QDateTime::currentDateTime().time().msec()%1000); //For the random

    connect(&playerTurn, &QTimer::timeout, this, &GameWidget::timer_out);
    connect(&computerTurn, &QTimer::timeout, this, &GameWidget::timer_out);
    connect(this, &GameWidget::updatePoints, qobject_cast<MainWindow*>(this->parent()), &MainWindow::upPoints);
    connect(this, &GameWidget::updateRecord, qobject_cast<MainWindow*>(this->parent()), &MainWindow::upRecord);

    loadGame();
}

GameWidget::~GameWidget()
{
    player.clean();
    computer.clean();
}

void GameWidget::loadGame() //On the app load
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
    isPlayerTurn = false;
    movesDone = 0;

    //Computer
    generated = false;
    compIterator = 0;
    compAnimElapsed.start();

    //Save    
    QSettings set("./conf.ini", QSettings::IniFormat);

    //Points
    points = 0;

    if(set.contains("record")) {
        record = set.value("record",0).toInt();
    }
    else {
        set.setValue("record",0);
        record = set.value("record",0).toInt();
    }
    set.sync();
    emit updateRecord(record);
}

void GameWidget::restartGame() //After losing
{
    //MovesContainers
    player.clean();
    computer.clean();

    //Points
    points= 0;
    emit updatePoints(points);

    //Turns
    isPlayerTurn=false;

    //Computer
    generated = false;
    compIterator = 0;

    //Timers
    playerTurn.stop();
    computerTurn.setInterval(computerAnimSpeed);
    computerTurn.start();

    //Elapsed
    switchElapsed.restart();

    //Play Fail Sound
    visitor.playFailSound();
}

void GameWidget::startGame() //After pressing the start button
{
    computerTurn.start();
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
            return;
        }
    if(isPlayerTurn) {
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
                player.push_back(left);
                player.getLast()->setPressed(true);
                player.getLast()->acceptVisitor(&visitor);
                Left_Elapsed.restart();
            }
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            // Down
            if(Down_Elapsed.elapsed()>=100){
                player.push_back(down);
                player.getLast()->setPressed(true);
                player.getLast()->acceptVisitor(&visitor);
                Down_Elapsed.restart();
            }
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            // Right
            if(Right_Elapsed.elapsed()>=100){
                player.push_back(right);
                player.getLast()->setPressed(true);
                player.getLast()->acceptVisitor(&visitor);
                Right_Elapsed.restart();
            }
            break;
        default:
            QGraphicsScene::keyPressEvent(event);
            break;
        }
        checkMoves();
    }
}

void GameWidget::resetBtns()
{
    up.setPressed(false);
    up.acceptVisitor(&visitor);
    left.setPressed(false);
    left.acceptVisitor(&visitor);
    down.setPressed(false);
    down.acceptVisitor(&visitor);
    right.setPressed(false);
    right.acceptVisitor(&visitor);
}

void GameWidget::checkMoves()
{
    QSettings set("./conf.ini", QSettings::IniFormat);
    emit updateRecord(record);
    if(player==computer) { //MOVE IS OK
        if(movesDone+1<compIterator) {
            movesDone++;
        }
        else { //SEQUENCE COMPLETE
            compIterator = 0;
            movesDone = 0;
            points++;
            //Update Label
            emit updatePoints(points);
            if(points>record) {
                record = points;
                //Save Value
                set.setValue("record",record);
                set.sync();
                //Update Label
                emit updateRecord(record);
            }
            playerTurn.stop();
            player.clean();
            isPlayerTurn = false;
            switchElapsed.restart();
            switchElapsed.start();
            computerTurn.start();
        }
    }
    else { //GAME OVER
        restartGame();
    }
}

void GameWidget::timer_out() {
    if(isPlayerTurn || switchElapsed.elapsed()<=1000){ //Player
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
    else if(switchElapsed.elapsed()>=1000){ //Computer, waits one second before starting the new sequence
        if (!generated) {
            switch (QRandomGenerator::global()->bounded(0,4)) { //Makes a random move every new turn
            case 0:
                computer.push_back(up);
                break;
            case 1:
                computer.push_back(right);
                break;
            case 2:
                computer.push_back(down);
                break;
            case 3:
                computer.push_back(left);
                break;

            default:
                break;
            }
            resetBtns();
            generated = true;
        }
        if(computer.findByPos(compIterator)!=nullptr) {
            if(compIterator!=0) { //Clears turned on buttons
                computer.findByPos(compIterator-1)->setPressed(false);
                computer.findByPos(compIterator-1)->acceptVisitor(&visitor);
            }
            if(compAnimElapsed.elapsed()>=computerTurn.interval()*2) {//Gives some more time between consequential press, making it more clear to follow
                computer.findByPos(compIterator)->setPressed(true);
                computer.findByPos(compIterator)->acceptVisitor(&visitor);
                compIterator++;
                compAnimElapsed.restart();
            }
        }
        else {
            isPlayerTurn = true;
            generated = false;
            computerTurn.stop();
            computerTurn.setInterval((computerTurn.interval()-computerTurn.interval()/100*10)); //Decrement Interval making it more difficult to follow
            playerTurn.start();
        }
    }
}

