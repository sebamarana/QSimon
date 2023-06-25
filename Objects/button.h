#ifndef BUTTON_H
#define BUTTON_H

#include "./Visitors/visitor.h"
#include <string>

class Button
{
private:
    bool pressed; //Indica se il pulsante è stato premuto
    std::string sound_addr; //Indirizzo locale del suono da riprodurre

    //Colors
    std::string active_color;
    std::string color;
public:
    Button();
    Button(std::string c="", std::string ac="");
    virtual ~Button() = default;

    //Getter
    bool isPressed() const {return pressed;};
    std::string getSoundAddr() const {return sound_addr;};
    std::string getActiveColor() const {return active_color;};
    std::string getColor() const {return color;};

    //Setter
    virtual void setDefaultColors() = 0;
    void setColor(std::string c){color = c;};
    void setActiveColor(std::string ac){active_color = ac;};
    void setSound(std::string s){sound_addr = s;};
    void setPressed(bool newPressed){ pressed = newPressed;}

    //Virtual Visitor
    virtual void acceptVisitor(Visitor* visitor) const = 0;

};

#endif // Button_H
