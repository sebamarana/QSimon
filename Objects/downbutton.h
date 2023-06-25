#ifndef DOWNBUTTON_H
#define DOWNBUTTON_H

#include "button.h"

class DownButton : public Button
{
public:
    DownButton() : Button("",""){};
    DownButton(std::string c, std::string ac) : Button(c,ac){};
    ~DownButton() = default;

    //Setter
    virtual void setDefaultColors() override
    {
        setColor("#006400");
        setActiveColor("#32cd32");
        return;
    }

    //Visitor
    void acceptVisitor(Visitor* visitor) const override
    {
        visitor->visitDownButton(this);
    }

};

#endif // DOWNBUTTON_H
