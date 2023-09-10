#include "graphicvisitor.h"
#include "Objects/upbutton.h"
#include "Objects/rightbutton.h"
#include "Objects/downbutton.h"
#include "Objects/leftbutton.h"

GraphicVisitor::GraphicVisitor() :
    RESIZE(1)
{
    //player.setVolume(0.7);
}

void GraphicVisitor::render(std::string upButtonColor, std::string rightButtonColor, std::string downButtonColor, std::string leftButtonColor) {
    QPointF center(150*RESIZE,150*RESIZE);

    path.moveTo(center);
    path.arcTo(QRectF(0,0,300*RESIZE,300*RESIZE),135,-90);
    path.closeSubpath();

    bUp.setPath(path);
    bUp.setBrush(QBrush(QColor(QString::fromStdString(upButtonColor)).rgb()));

    path = QPainterPath();
    path.moveTo(center);
    path.arcTo(QRectF(0,0,300*RESIZE,300*RESIZE),315,-90);
    path.closeSubpath();

    bDown.setPath(path);
    bDown.setBrush(QBrush(QColor(QString::fromStdString(downButtonColor)).rgb()));

    path = QPainterPath();
    path.moveTo(center);
    path.arcTo(QRectF(0,0,300*RESIZE,300*RESIZE),225,-90);
    path.closeSubpath();

    bLeft.setPath(path);
    bLeft.setBrush(QBrush(QColor(QString::fromStdString(leftButtonColor)).rgb()));

    path = QPainterPath();
    path.moveTo(center);
    path.arcTo(QRectF(0,0,300*RESIZE,300*RESIZE),45,-90);
    path.closeSubpath();

    bRight.setPath(path);
    bRight.setBrush(QBrush(QColor(QString::fromStdString(rightButtonColor)).rgb()));

    //TODO: Rendere cliccabili i punti

    group.addToGroup(&bUp);
    group.addToGroup(&bRight);
    group.addToGroup(&bDown);
    group.addToGroup(&bLeft);
}

QGraphicsItemGroup* GraphicVisitor::getGroup(){
    return &group;
}

void GraphicVisitor::playFailSound()
{
    //player.setSource(QUrl::fromLocalFile(":/sounds/Sounds/Fail.wav"));
    //player.play();
}

void GraphicVisitor::visitUpButton(const UpButton* up){
    if(up->isPressed()){
        //player.setSource(QUrl::fromLocalFile(":/sounds/Sounds/Up.wav"));//QUrl::fromLocalFile(QString::fromStdString(up->getSoundAddr())));
        //player.play();
        bUp.setBrush(QBrush(QColor(QString::fromStdString(up->getActiveColor())).rgb()));
    }
    else
    {
        bUp.setBrush(QBrush(QColor(QString::fromStdString(up->getColor())).rgb()));
    }
}

void GraphicVisitor::visitRightButton(const RightButton* right){
    if(right->isPressed()){
        //player.setSource(QUrl::fromLocalFile(QString::fromStdString(right->getSoundAddr())));
        //player.play();
        bRight.setBrush(QBrush(QColor(QString::fromStdString(right->getActiveColor())).rgb()));
    }
    else
    {
        bRight.setBrush(QBrush(QColor(QString::fromStdString(right->getColor())).rgb()));
    }
}

void GraphicVisitor::visitDownButton(const DownButton* down){
    if(down->isPressed()){
        //player.setSource(QUrl::fromLocalFile(QString::fromStdString(down->getSoundAddr())));
        //player.play();
        bDown.setBrush(QBrush(QColor(QString::fromStdString(down->getActiveColor())).rgb()));
    }
    else
    {
        bDown.setBrush(QBrush(QColor(QString::fromStdString(down->getColor())).rgb()));
    }
}

void GraphicVisitor::visitLeftButton(const LeftButton* left){
    if(left->isPressed()){
        //player.setSource(QUrl::fromLocalFile(QString::fromStdString(left->getSoundAddr())));
        //player.play();
        bLeft.setBrush(QBrush(QColor(QString::fromStdString(left->getActiveColor())).rgb()));
    }
    else
    {
        bLeft.setBrush(QBrush(QColor(QString::fromStdString(left->getColor())).rgb()));
    }
}
