#include "gamewidget.h"
#include "mainwindow.h"
#include <QDebug>
#include <QCoreApplication>

//View

GameWidget::GameWidget(MovesContainer mov, int diff, QWidget *parent) :
    QGraphicsView(parent),
    Buttons(mov),
    btnAnimTime(400),
    computerAnimSpeed(diff)
{
    this->setFocus();

    computerTurn.setInterval(computerAnimSpeed); // TO ADD DIFFICULTY
    playerTurn.setInterval(1);

    connect(&playerTurn, &QTimer::timeout, this, &GameWidget::timer_out);
    connect(&computerTurn, &QTimer::timeout, this, &GameWidget::timer_out);
    connect(this, &GameWidget::updatePoints, this, &GameWidget::upPoints);
    connect(this, &GameWidget::updateRecord, this, &GameWidget::upRecord);
    connect(this, &GameWidget::backToMenu, qobject_cast<MainWindow*>(this->parent()), &MainWindow::showMenu);

    loadGame();
}

GameWidget::~GameWidget()
{
}

void GameWidget::loadGame() //On the app load
{
    this->setScene(&gameScene);

    //Set Elapsing timer for button press animation
    Up_Elapsed.start();
    Left_Elapsed.start();
    Down_Elapsed.start();
    Right_Elapsed.start();

    //Initial rendering of visitor and Adding Group of GraphicalItems from Visitor
    visitor.render(Buttons.findByType(MovesContainer::Up)->getColor(),
                   Buttons.findByType(MovesContainer::Right)->getColor(),
                   Buttons.findByType(MovesContainer::Down)->getColor(),
                   Buttons.findByType(MovesContainer::Left)->getColor());
    gameScene.addItem(visitor.getGroup());

    //Computer
    compAnimElapsed.start();
    computerIterator = 0;
    computerAnimEnd = false;

    //Font Settings
    int id = QFontDatabase::addApplicationFont(":/font/pretty.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont pretty(family,30);
    //-----------------------------

    //Label Settings
    pointsLabel.setText("Points: 0");
    pointsLabel.setStyleSheet("color: white; font-size:25px; background:rgba(255, 255, 255, 0)");
    pointsLabel.setFont(QFont(pretty));

    recordLabel.setText("Record: 0");
    recordLabel.setStyleSheet("color: white; font-size:25px; background:rgba(255, 255, 255, 0)");
    recordLabel.setFont(QFont(pretty));

    layout.addWidget(&pointsLabel,0,Qt::AlignLeft);
    layout.addWidget(&recordLabel,0,Qt::AlignLeft);
    layout.setSpacing(400);
    layout.setAlignment(Qt::AlignCenter);

    this->setLayout(&layout);
    //-----------------------------

    //Messageboxes
    win.setText("Right Sequence!");
    win.setWindowTitle("QSimon");
    win.setIcon(QMessageBox::Information);
    win.setStyleSheet("background: white");

    lose.setText("Wrong, You Lose!");
    lose.setWindowTitle("QSimon");
    lose.setIcon(QMessageBox::Information);
    lose.setStyleSheet("background: white");

    play_again.setText("Want to retry?");
    play_again.setWindowTitle("QSimon");
    play_again.setStyleSheet("background: white");
    play_again.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
}

void GameWidget::restartGame() //After losing
{
    //Handler
    Simon.reset();

    //Points
    emit updatePoints(Simon.getPoints());
    emit updateRecord(Simon.getRecord());

    //Timers
    playerTurn.stop();
    computerTurn.setInterval(computerAnimSpeed);
    computerTurn.stop();

    //Computer
    computerIterator = 0;
    computerAnimEnd = false;

    //Elapsed
    switchElapsed.restart();

    //Buttons
    resetBtns();

    //Play Fail Sound
    visitor.playFailSound();
}

void GameWidget::playAgain()
{
    //Ask if the player wants to play again
    if(play_again.exec() == QMessageBox::Yes)
    {
        startGame();
    }
    else
    {
        emit backToMenu();
    }
}

void GameWidget::startGame() //After pressing the start button
{
    computerTurn.start();
    switchElapsed.restart();
    Simon.start();
    emit updateRecord(Simon.getRecord());
}

void GameWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        emit backToMenu();
    }
    if (event->isAutoRepeat()) {
            return;
        }
    if(Simon.isPlayerTurn() && computerAnimEnd) {
        switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            // Up
            if(Up_Elapsed.elapsed()>=100){
                Simon.setPlayerMove(MovesContainer::Up);
                Buttons.findByType(MovesContainer::Up)->setPressed(true);
                Buttons.findByType(MovesContainer::Up)->acceptVisitor(&visitor);
                Up_Elapsed.restart();
                checkMove();
            }
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            // Left
            if(Left_Elapsed.elapsed()>=100){
                Simon.setPlayerMove(MovesContainer::Left);
                Buttons.findByType(MovesContainer::Left)->setPressed(true);
                Buttons.findByType(MovesContainer::Left)->acceptVisitor(&visitor);
                Left_Elapsed.restart();
                checkMove();
            }
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            // Down
            if(Down_Elapsed.elapsed()>=100){
                Simon.setPlayerMove(MovesContainer::Down);
                Buttons.findByType(MovesContainer::Down)->setPressed(true);
                Buttons.findByType(MovesContainer::Down)->acceptVisitor(&visitor);
                Down_Elapsed.restart();
                checkMove();
            }
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            // Right
            if(Right_Elapsed.elapsed()>=100){
                Simon.setPlayerMove(MovesContainer::Right);
                Buttons.findByType(MovesContainer::Right)->setPressed(true);
                Buttons.findByType(MovesContainer::Right)->acceptVisitor(&visitor);
                Right_Elapsed.restart();
                checkMove();
            }
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            break;
        }

    }
}

void GameWidget::resetBtns()
{
    Buttons.findByType(MovesContainer::Up)->setPressed(false);
    Buttons.findByType(MovesContainer::Right)->setPressed(false);
    Buttons.findByType(MovesContainer::Down)->setPressed(false);
    Buttons.findByType(MovesContainer::Left)->setPressed(false);
    Buttons.findByType(MovesContainer::Up)->acceptVisitor(&visitor);
    Buttons.findByType(MovesContainer::Right)->acceptVisitor(&visitor);
    Buttons.findByType(MovesContainer::Down)->acceptVisitor(&visitor);
    Buttons.findByType(MovesContainer::Left)->acceptVisitor(&visitor);
}

void GameWidget::checkMove()
{
    if(Simon.isWrongSequence())
    {
        restartGame();
        lose.exec();
        playAgain();
    }
    else if(Simon.isRightSequence())
    {
        //win.exec();
        this->setStyleSheet("background: lime");
        playerTurn.stop();
        switchElapsed.restart();
        switchElapsed.start();
        computerTurn.start();
        computerAnimEnd = false;
        emit updatePoints(Simon.getPoints());
        emit updateRecord(Simon.getRecord());
    }
}

void GameWidget::timer_out() {
    this->setStyleSheet("background: black");
    if((Simon.isPlayerTurn() && computerAnimEnd) || switchElapsed.elapsed()<=1000){ //Player
        if(Up_Elapsed.elapsed()>=btnAnimTime){
            Buttons.findByType(MovesContainer::Up)->setPressed(false);
            Buttons.findByType(MovesContainer::Up)->acceptVisitor(&visitor);
        }
        if(Left_Elapsed.elapsed()>=btnAnimTime){
            Buttons.findByType(MovesContainer::Left)->setPressed(false);
            Buttons.findByType(MovesContainer::Left)->acceptVisitor(&visitor);
        }
        if(Down_Elapsed.elapsed()>=btnAnimTime){
            Buttons.findByType(MovesContainer::Down)->setPressed(false);
            Buttons.findByType(MovesContainer::Down)->acceptVisitor(&visitor);
        }
        if(Right_Elapsed.elapsed()>=btnAnimTime){
            Buttons.findByType(MovesContainer::Right)->setPressed(false);
            Buttons.findByType(MovesContainer::Right)->acceptVisitor(&visitor);
        }
    }
    else if(switchElapsed.elapsed()>=1000){ //Computer, waits one second before starting the new sequence
        unsigned int mov;
        if(Simon.getComputerMove(computerIterator)!=0) {
            if(computerIterator>0)
            {
                mov = Simon.getComputerMove(computerIterator-1);
                Buttons.findByType(mov)->setPressed(false);
                Buttons.findByType(mov)->acceptVisitor(&visitor);
            }
            mov = Simon.getComputerMove(computerIterator);
            Buttons.findByType(mov)->setPressed(true);
            Buttons.findByType(mov)->acceptVisitor(&visitor);
            switchElapsed.restart();
            computerIterator++;
        }
        else {
            mov = Simon.getComputerMove(computerIterator-1);
            Buttons.findByType(mov)->setPressed(false);
            Buttons.findByType(mov)->acceptVisitor(&visitor);
            computerIterator = 0;
            computerTurn.stop();
            computerTurn.setInterval((computerTurn.interval()-computerTurn.interval()/100*10)); //Decrement Interval making it more difficult to follow
            computerAnimEnd = true;
            playerTurn.start();
        }
    }
}

void GameWidget::upPoints(unsigned int pts)
{
    std::string points = std::to_string(pts);
    pointsLabel.setText(QString::fromStdString("Points: "+points));
    return;
}

void GameWidget::upRecord(unsigned int rec)
{
    std::string record = std::to_string(rec);
    recordLabel.setText(QString::fromStdString("Record: "+record));
    return;
}

