#ifndef EQUALITYVISITOR_H
#define EQUALITYVISITOR_H

class UpButton;
class RightButton;
class LeftButton;
class DownButton;

class EqualityVisitor
{
public:
    virtual void visitUpButton(const UpButton* up) = 0;
    virtual void visitRightButton(const RightButton* right) = 0;
    virtual void visitDownButton(const DownButton* down) = 0;
    virtual void visitLeftButton(const LeftButton* left) = 0;
};

#endif // EQUALITYVISITOR_H
