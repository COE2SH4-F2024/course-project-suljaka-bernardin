#include "Food.h"
#include "MacUILib.h"
#include <time.h>

Food::Food()
{

    // Setting them to the default size, just in case we end up in here

    boardX = 30;
    boardY = 15;

    
    
}

// do you need a destructor?
Food::~Food()
{


}

Food::Food(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;

    boardX = mainGameMechsRef->getBoardSizeX();
    boardY = mainGameMechsRef->getBoardSizeY();
}

Food::Food(const Food &a)
{
    boardX = a.mainGameMechsRef->getBoardSizeX();
    boardY = a.mainGameMechsRef->getBoardSizeY();
}

Food& Food::operator=(const Food &a)
{
    if (this != &a)
    {
        boardX = a.mainGameMechsRef->getBoardSizeX();
        boardY = a.mainGameMechsRef->getBoardSizeY();
    }
    return *this;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    
    
        srand(time(NULL));
        int rand_x = rand() % (boardX - 2)+1; //Initially sets x and y coordinates
        int rand_y = rand() % (boardY - 2)+1;
        
        
            
            for (int i = 0; i<blockOff->getSize();i++)
            {
                int reset = 0;
                if ((blockOff->getElement(i).pos->x == rand_x && blockOff->getElement(i).pos->y == rand_y) ||(foodPos.pos->x == rand_x && foodPos.pos->y == rand_y) ) //Player or prev. obj pos
                {
                    rand_x = rand() % (boardX-2)+1;
                    rand_y = rand() % (boardY-2)+1;
                    reset = 1;
                }
                if (reset)
                {
                    i = -1;
                    
                }
            }
            foodPos.setObjPos(rand_x,rand_y,'A');

            // if ((str[rand_char] == list[k].player) && i<2) //Generates for only 0,1
            // {
            //     rand_char = rand() % (12);
            //     reset = 1;
            // }
            // else if ((rand_char == list[k].player && i>1)|| (rand_char == 64 || rand_char == 35)) //Won't make @ or #, gens any rand char
            // {
            //     rand_char = rand() %(127-33)+33;
            //     reset = 1;
            // }
            // if (reset) 
            // k--;
        
        
        // list[i].x = rand_x;
        // list[i].y = rand_y;
        // if (i<2)
        // list[i].player = str[rand_char]; //rand char is index and picks from goal string
        // else
        // list[i].player = rand_char; //rand char is ascii value
    }


objPos Food::getFoodPos()
{
    return foodPos;
}


