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
    
    foodBucket = new objPosArrayList;

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
    // objPos nullPos(0,0,NULL);
    // for (int i = 0; i < NUMFOODS; i++)
    // {
    //     foodBucket->insertHead(nullPos);
    //     foodBucket->removeTail();
    // }

    for (int j = 0; j<NUMFOODS; j++)
    {
        int prev_reset = 1;
        int rand_x;
        int rand_y;
        objPos food_pos;
        srand(time(NULL));
        while (prev_reset)
        {
            prev_reset = 0;
            
            rand_x = rand() % (boardX - 2)+1; //Initially sets x and y coordinates
            rand_y = rand() % (boardY - 2)+1;
        
        
            
            for (int i = 0; i<blockOff->getSize();i++)
            {
                int reset = 0;
                if ((blockOff->getElement(i).pos->x == rand_x && blockOff->getElement(i).pos->y == rand_y))
                {
                    rand_x = rand() % (boardX-2)+1;
                    rand_y = rand() % (boardY-2)+1;
                    reset = 1;
                    prev_reset = 0;
                }
                if (reset)
                {
                    i = -1;
                    
                }
            }
            for (int p = 0; p < j;p++)
            {
                int reset = 0;
                if ((foodBucket->getElement(p).pos->x == rand_x && foodBucket->getElement(p).pos->y == rand_y) ) //Player or prev. obj pos
                {
                    rand_x = rand() % (boardX-2)+1;
                    rand_y = rand() % (boardY-2)+1;
                    reset = 1;
                    prev_reset = 0;
                }
                if (reset)
                {
                    p = -1;
                    
                }
            }
            if (prev_reset)
                prev_reset = 1;

        }
            food_pos.pos->x = rand_x;
            food_pos.pos->y = rand_y;
            food_pos.symbol = 'A';

            if (firstPass < NUMFOODS) {
                foodBucket->insertTail(food_pos);
                firstPass++;
            } else {
                foodBucket->insertHead(food_pos);
                foodBucket->removeTail();
            }

            // foodBucket->insertTail(food_pos);

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
        
        
    }
}


objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}