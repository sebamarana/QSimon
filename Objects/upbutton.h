#ifndef UPBUTTON_H
#define UPBUTTON_H

#include "button.h"

class UpButton : public Button
{
public:
    UpButton() : Button("",""){};
    UpButton(std::string c, std::string ac) : Button(c,ac){};

    //Setter
    virtual void setDefaultColors() override
    {
        setColor("#8b0000");
        setActiveColor("#ff0000");
        return;
    }

    //Visitor
    virtual void acceptVisitor(Visitor* visitor) const override
    {
        visitor->visitUpButton(this);
    }

};

#endif // UPBUTTON_H


