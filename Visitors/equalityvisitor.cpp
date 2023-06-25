#include "equalityvisitor.h"
#include "Objects/upbutton.h"
#include "Objects/rightbutton.h"
#include "Objects/downbutton.h"
#include "Objects/leftbutton.h"
#include <typeinfo>

equalityvisitor::equalityvisitor()
{
    equality.first = "";
    equality.second = "";
}

void equalityvisitor::visitUpButton(const UpButton *up)
{
    if(equality.first=="") {
        equality.first = up->getColor();
    }
    else {
        equality.second = up->getColor();
    }
}

void equalityvisitor::visitRightButton(const RightButton *right)
{
    if(equality.first=="") {
        equality.first = right->getColor();
    }
    else {
        equality.second = right->getColor();
    }
}

void equalityvisitor::visitDownButton(const DownButton *down)
{
    if(equality.first=="") {
        equality.first = down->getColor();
    }
    else {
        equality.second = down->getColor();
    }
}

void equalityvisitor::visitLeftButton(const LeftButton *left)
{
    if(equality.first=="") {
        equality.first = left->getColor();
    }
    else {
        equality.second = left->getColor();
    }
}

bool equalityvisitor::getEqualityResults()
{
    bool ret = (equality.first == equality.second);
    equality.first = "";
    equality.second = "";
    return ret;
}
