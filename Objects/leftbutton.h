#ifndef LEFTBUTTON_H
#define LEFTBUTTON_H

#include "button.h"

class LeftButton : public Button
{
public:
    LeftButton() : Button("",""){};
    LeftButton(std::string c, std::string ac) : Button(c,ac){};
    ~LeftButton() = default;

    //Setter
    virtual void setDefaultColors() override
    {
        setColor("#00008b");
        setActiveColor("#4169e1");
        return;
    }

    //Visitor
    void acceptVisitor(Visitor* visitor) const override
    {
        visitor->visitLeftButton(this);
    }

};

#endif // LEFTBUTTON_H
