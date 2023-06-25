#ifndef GRAPHICVISITOR_H
#define GRAPHICVISITOR_H

class UpButton;
class RightButton;
class LeftButton;
class DownButton;

#include "Visitors/visitor.h"
#include <QGraphicsPathItem>
#include <QGraphicsItemGroup>
#include <QPainterPath>
#include <string>
#include <QBrush>
//#include <QSoundEffect>
#include <QUrl>

class GraphicVisitor : public Visitor
{
public:
    GraphicVisitor();
    void render(std::string upButtonColor, std::string rightButtonColor, std::string downButtonColor, std::string leftButtonColor);
    void visitUpButton(const UpButton* up);
    void visitRightButton(const RightButton* right);
    void visitDownButton(const DownButton* down);
    void visitLeftButton(const LeftButton* left);
    QGraphicsItemGroup * getGroup();
    void playFailSound();
private:
    QGraphicsPathItem bUp,bRight,bDown,bLeft;
    QGraphicsItemGroup group;
    QPainterPath path;
    //QSoundEffect player;
    const qreal RESIZE;

};

#endif // GRAPHICVISITOR_H
