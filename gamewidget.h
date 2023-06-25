#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QDateTime>
#include <QSettings>
#include "Objects/movescontainer.h"
#include "Objects/upbutton.h"
#include "Objects/rightbutton.h"
#include "Objects/downbutton.h"
#include "Objects/leftbutton.h"
#include "Visitors/graphicvisitor.h"

class GameWidget : public QGraphicsScene
{
    Q_OBJECT
public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();

public slots:
    void startGame();

private:
    //QObjects
    QGraphicsPathItem B_Up,B_Down,B_Left,B_Right;
    QPainter painter;
    QPainterPath path;
    QTimer computerTurn;
    QTimer playerTurn;
    QElapsedTimer Up_Elapsed, Left_Elapsed, Down_Elapsed, Right_Elapsed;
    QElapsedTimer switchElapsed;
    QElapsedTimer compAnimElapsed;
    QRandomGenerator random;

    //Objects
    UpButton up;
    DownButton down;
    RightButton right;
    LeftButton left;

    //Objects Containers
    MovesContainer player;
    MovesContainer computer;

    //Visitor
    GraphicVisitor visitor;

    //Computer Utils
    bool generated;
    unsigned int compIterator;

    //Utils
    bool isPlayerTurn;
    void keyPressEvent(QKeyEvent* event) override;
    unsigned int movesDone;
    unsigned int points;
    unsigned int record;
    void resetBtns();
    void checkMoves();

    //Settings
    const unsigned int btnAnimTime;
    const unsigned int computerAnimSpeed;

    //Main Functions
    void loadGame();
    void restartGame();

signals:
    void updatePoints(unsigned int p);
    void updateRecord(unsigned int r);
private slots:
    void timer_out();
};

#endif // GAMEWIDGET_H
