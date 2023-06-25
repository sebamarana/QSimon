#include "equalityvisitor.h"
#include "Objects/upbutton.h"
#include "Objects/rightbutton.h"
#include "Objects/downbutton.h"
#include "Objects/leftbutton.h"
#include <typeinfo>

equalityvisitor::equalityvisitor()
{
    equality.first = -1;
    equality.second = -1;
}

// 1: UP, 2: RIGHT, 3: DOWN, 4: LEFT
//TODO: Sistemare i warning!

void equalityvisitor::visitUpButton(const UpButton *up)
{
    if(equality.first==-1) {
        equality.first = 1;
    }
    else {
        equality.second = 1;
    }
}

void equalityvisitor::visitRightButton(const RightButton *right)
{
    if(equality.first==-1) {
        equality.first = 2;
    }
    else {
        equality.second = 2;
    }
}

void equalityvisitor::visitDownButton(const DownButton *down)
{
    if(equality.first==-1) {
        equality.first = 3;
    }
    else {
        equality.second = 3;
    }
}

void equalityvisitor::visitLeftButton(const LeftButton *left)
{
    if(equality.first==-1) {
        equality.first = 4;
    }
    else {
        equality.second = 4;
    }
}

bool equalityvisitor::getEqualityResults()
{
    bool ret = (equality.first == equality.second);
    equality.first = -1;
    equality.second = -1;
    return ret;
}
