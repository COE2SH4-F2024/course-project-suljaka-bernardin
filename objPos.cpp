#include "objPos.h"

objPos::objPos()
{

    // Create a new position object that sets x, y and symbol to 0.
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{

    // Specialized constructor to set xPos, yPos, and symbol.
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Deconstructor - The only heap object that we need to delete is pos.

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
}



// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule




void objPos::setObjPos(objPos o)
{

    // Copy from another object
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{

    // Initializes a new object
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{

    // Initializing a new object, and and returns the

    // NO Params passed into this function.
    
    // Makes a constant copy

    // Returns the values of every object we call, but it does this by making a "returnPosition" instance and copying everything over.
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
    // Are we talking about the same thing?????
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{

    // Returns the symbol if the positions are equal
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
