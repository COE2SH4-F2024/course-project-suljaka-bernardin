#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

objPos::~objPos() {
    delete pos;
}

// Copy Constructor

objPos::objPos(const objPos &a) {

    symbol = a.symbol;

    // Creating a new position object

    pos = new Pos;

    // Deep Copy

    pos->x = a.pos->x;
    pos->y = a.pos->y;

}

// Copy Assignment Operator

objPos& objPos::operator=(const objPos &a) {
    // Basically identical to copy constructor just with the this part instead.

    if (this != &a) {
            symbol = a.symbol;

    // Creating a new position object

    // Deep Copy

    pos->x = a.pos->x;
    pos->y = a.pos->y;
    }
    return *this;
}


void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
