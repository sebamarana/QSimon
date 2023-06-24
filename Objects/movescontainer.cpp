#include "movescontainer.h"
#include <typeinfo>

void MovesContainer::push_back(Button &button)
{
    if(head) {
        tail->next = new MoveHolder(button);
        tail = tail->next;
        tail->next = nullptr;
    }
    else {
        tail = new MoveHolder(button);
        head = tail;
        head->next = nullptr;
    }
}

void MovesContainer::clean()
{
    MoveHolder* current = head;
    while (current != nullptr) {
        MoveHolder* next = current->next;
        delete current->button;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

Button *MovesContainer::getLast()
{
    return tail->button;
}

bool MovesContainer::operator==(const MovesContainer &mov)
{
    MoveHolder* A = head;
    MoveHolder* B = mov.head;
    while (A!=nullptr && B!=nullptr) {
        if(typeid(A->button)!=typeid(B->button)) {
            return false;
        }
        A = A->next;
        B = B->next;
    }
    return true;
}

Button *MovesContainer::findByPos(const int &pos)
{
    MoveHolder* current = head;
    for (int i = 0; i < pos; ++i) {
        if(!current) {
            return nullptr;
        }
        current = current->next;
    }
    return current->button;
}
