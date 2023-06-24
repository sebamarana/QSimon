#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QElapsedTimer>
#include <QSoundEffect>
#include <QRandomGenerator>
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
    QLabel points;
    QGraphicsPathItem B_Up,B_Down,B_Left,B_Right;
    QPainter painter;
    QPainterPath path;
    QTimer Turn;
    QTimer playerClick;
    QElapsedTimer Up_Elapsed, Left_Elapsed, Down_Elapsed, Right_Elapsed;

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

    //Utils
    bool playerTurn;
    void keyPressEvent(QKeyEvent* event) override;

    //Settings
    const unsigned int btnAnimTime;

    //Main Functions
    void loadGame();

private slots:
    void timer_out();



};

#endif // GAMEWIDGET_H
