#ifndef MOVESCONTAINER_H
#define MOVESCONTAINER_H

#include "button.h"

class MoveHolder {
public:
    Button* button;
    MoveHolder* next;
    MoveHolder(Button &btn) : button(&btn) {};
};

class MovesContainer{
private:
    MoveHolder* head;
    MoveHolder* tail;
public:
    MovesContainer() : head(nullptr), tail(nullptr){};

    //TODO: Implement Methods
    void push_back(Button &button); //Insert an object from the back
    void clean(); //Deletes all object in container
    Button* getLast(); //Returns last obj in container
    bool operator==(const MovesContainer& mov); //Check if containers match
    Button* findByPos(const int &pos); //Return obj in container by its pos

};

#endif // MOVESCONTAINER_H
