#ifndef RIGHTBUTTON_H
#define RIGHTBUTTON_H

#include "button.h"

class RightButton : public Button
{
public:
    RightButton(): Button("",""){};
    RightButton(std::string c, std::string ac) : Button(c,ac){};
    ~RightButton() = default;

    //Setter
    virtual void setDefaultColors() override
    {
        setColor("#808000");
        setActiveColor("#ffff00");
        return;
    }

    //Visitor
    void acceptVisitor(Visitor* visitor) const override
    {
        visitor->visitRightButton(this);
    }

};

#endif // RIGHTBUTTON_H
