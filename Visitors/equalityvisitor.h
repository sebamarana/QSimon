#ifndef EQUALITYVISITOR_H
#define EQUALITYVISITOR_H


class UpButton;
class RightButton;
class LeftButton;
class DownButton;

#include "Visitors/visitor.h"
#include <utility>
#include <string>

class equalityvisitor : public Visitor
{
public:
    equalityvisitor();
    void visitUpButton(const UpButton* up);
    void visitRightButton(const RightButton* right);
    void visitDownButton(const DownButton* down);
    void visitLeftButton(const LeftButton* left);
    bool getEqualityResults();
private:
    std::pair<std::string,std::string> equality;
};

#endif // EQUALITYVISITOR_H
