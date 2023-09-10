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
#include <QMessageBox>
#include <QGraphicsView>
#include <QLabel>
#include <QFontDatabase>
#include <QVBoxLayout>
#include "Objects/movescontainer.h"
#include "Visitors/graphicvisitor.h"
#include "gamehandler.h"



class GameWidget : public QGraphicsView
{
    Q_OBJECT
public:
    GameWidget(MovesContainer mov, int diff, QWidget *parent = nullptr);
    ~GameWidget();

public slots:
    void startGame();

private:
    //Scene
    QGraphicsScene gameScene;

    //Logic Handler
    GameHandler Simon;

    //MovesContainer
    MovesContainer Buttons;

    //QObjects
    QGraphicsPathItem B_Up,B_Down,B_Left,B_Right;
    QPainter painter;
    QPainterPath path;
    QTimer computerTurn;
    QTimer playerTurn;
    QElapsedTimer Up_Elapsed, Left_Elapsed, Down_Elapsed, Right_Elapsed;
    QElapsedTimer switchElapsed;
    QElapsedTimer compAnimElapsed;

    //Visitor
    GraphicVisitor visitor;

    //Labels
    QLabel pointsLabel, recordLabel;

    //Messagebox
    QMessageBox win, lose, play_again;

    //Layout
    QVBoxLayout layout;

    //Utils
    void keyPressEvent(QKeyEvent* event) override;
    void resetBtns();
    void checkMove();
    unsigned int computerIterator;
    bool computerAnimEnd;

    //Settings
    const unsigned int btnAnimTime;
    const unsigned int computerAnimSpeed;

    //Main Functions
    void loadGame();
    void restartGame();
    void playAgain();

signals:
    void updatePoints(unsigned int p);
    void updateRecord(unsigned int r);
    void backToMenu();
private slots:
    void timer_out();
    void upPoints(unsigned int pts);
    void upRecord(unsigned int rec);
};

#endif // GAMEWIDGET_H
