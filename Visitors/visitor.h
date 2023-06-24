#ifndef VISITOR_H
#define VISITOR_H

class UpButton;
class RightButton;
class LeftButton;
class DownButton;

class Visitor
{
public:
    virtual void visitUpButton(const UpButton* up) = 0;
    virtual void visitRightButton(const RightButton* right) = 0;
    virtual void visitDownButton(const DownButton* down) = 0;
    virtual void visitLeftButton(const LeftButton* left) = 0;
};

#endif // VISITOR_H
