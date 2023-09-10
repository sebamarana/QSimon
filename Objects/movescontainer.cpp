#include "movescontainer.h"
#include "Objects/upbutton.h"
#include "Objects/downbutton.h"
#include "Objects/rightbutton.h"
#include "Objects/leftbutton.h"
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
        A->button->acceptVisitor(&equal);
        B->button->acceptVisitor(&equal);
        if(!equal.getEqualityResults()) {
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
        current = current->next;
        if(!current) {
            return nullptr;
        }
    }
    return current->button;
}

Button *MovesContainer::findByType(const unsigned int mov)
{
    MoveHolder* current = head;
    switch (static_cast<Moves>(mov)) {
    case Moves::Up:
        while (current!=nullptr) {
            UpButton * up = dynamic_cast<UpButton*>(current->button);
            if(up!=nullptr)
            {
                return up;
            }
            else if(current->next!=nullptr){
                current = current->next;
            }
            else
            {
                return nullptr;
            }
        }
        return nullptr;
        break;
    case Moves::Right:
        while (current!=nullptr) {
            RightButton * right = dynamic_cast<RightButton*>(current->button);
            if(right!=nullptr)
            {
                return right;
            }
            else if(current->next!=nullptr){
                current = current->next;
            }
            else
            {
                return nullptr;
            }
        }
        return nullptr;
        break;
    case Moves::Left:
        while (current!=nullptr) {
            LeftButton * left = dynamic_cast<LeftButton*>(current->button);
            if(left!=nullptr)
            {
                return left;
            }
            else if(current->next!=nullptr){
                current = current->next;
            }
            else
            {
                return nullptr;
            }
        }
        return nullptr;
        break;
    case Moves::Down:
        while (current!=nullptr) {
            DownButton * down = dynamic_cast<DownButton*>(current->button);
            if(down!=nullptr)
            {
                return down;
            }
            else if(current->next!=nullptr){
                current = current->next;
            }
            else
            {
                return nullptr;
            }
        }
        return nullptr;
        break;
    default:
        return nullptr;
        break;
    }
}
