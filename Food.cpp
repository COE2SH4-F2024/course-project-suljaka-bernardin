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
    delete[] foodBucket;

}

Food::Food(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;
    
    foodBucket = new objPosArrayList; //Creates an new instance of a objPos Array List to hold all positions of the apples on the board

    boardX = mainGameMechsRef->getBoardSizeX(); // Food generation requires board sizes to ensure porper coordinate generations
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



// void Food::generateFood(objPosArrayList* blockOff)
// {
    // objPos nullPos(0,0,NULL);
    // for (int i = 0; i < NUMFOODS; i++)
    // {
    //     foodBucket->insertHead(nullPos);
    //     foodBucket->removeTail();
    // }

//     for (int j = 0; j<NUMFOODS; j++)
//     {
//         int prev_reset = 1;
//         int rand_x;
//         int rand_y;
//         objPos food_pos;
//         srand(time(NULL));
//         while (prev_reset)
//         {
//             prev_reset = 0;
            
//             rand_x = rand() % (boardX - 2)+1; //Initially sets x and y coordinates
//             rand_y = rand() % (boardY - 2)+1;
        
        
            
//             for (int i = 0; i<blockOff->getSize();i++)
//             {
//                 int reset = 0;
//                 if ((blockOff->getElement(i).pos->x == rand_x && blockOff->getElement(i).pos->y == rand_y))
//                 {
//                     rand_x = rand() % (boardX-2)+1;
//                     rand_y = rand() % (boardY-2)+1;
//                     reset = 1;
//                     prev_reset = 0;
//                 }
//                 if (reset)
//                 {
//                     i = -1;
                    
//                 }
//             }
//             for (int p = 0; p < j;p++)
//             {
//                 int reset = 0;
//                 if ((foodBucket->getElement(p).pos->x == rand_x && foodBucket->getElement(p).pos->y == rand_y) ) //Player or prev. obj pos
//                 {
//                     rand_x = rand() % (boardX-2)+1;
//                     rand_y = rand() % (boardY-2)+1;
//                     reset = 1;
//                     prev_reset = 0;
//                 }
//                 if (reset)
//                 {
//                     p = -1;
                    
//                 }
//             }
//             if (prev_reset)
//                 prev_reset = 1;

//         }
//             food_pos.pos->x = rand_x;
//             food_pos.pos->y = rand_y;
//             food_pos.symbol = 'A';

//             if (firstPass < NUMFOODS) {
//                 foodBucket->insertTail(food_pos);
//                 firstPass++;
//             } else {
//                 foodBucket->insertHead(food_pos);
//                 foodBucket->removeTail();
//             }

//             // foodBucket->insertTail(food_pos);

//             // if ((str[rand_char] == list[k].player) && i<2) //Generates for only 0,1
//             // {
//             //     rand_char = rand() % (12);
//             //     reset = 1;
//             // }
//             // else if ((rand_char == list[k].player && i>1)|| (rand_char == 64 || rand_char == 35)) //Won't make @ or #, gens any rand char
//             // {
//             //     rand_char = rand() %(127-33)+33;
//             //     reset = 1;
//             // }
//             // if (reset) 
//             // k--;
        
        
//     }
// }

void Food::generateFood(objPosArrayList* blockOff)
{
    // objPos nullPos(0,0,NULL);
    // for (int i = 0; i < NUMFOODS; i++)
    // {
    //     foodBucket->insertHead(nullPos);
    //     foodBucket->removeTail();
    // }

    int currentPosition = 0; // This is an index
    int noMatches; // This is for a boolean (using integer because of PPA3 port)
    int rand_x; // Proposed X Value
    int rand_y; // proposed Y Value
    int specialIndex;
    objPos foodPos; // Local index of Food Position
    objPos *prevFood = lastFood; // Local index of Last Food, set in Food.h

    // Randomly generate which symbol is going to be the special food, marked as S

    // It's just NumFoods because we want 0, 1, 2, 3, 4

    specialIndex = rand() % (NUMFOODS);
    

        do 
        {

            noMatches = 1;

            // Randomly set X and Y Coordinates
            
            rand_x = rand() % (boardX - 2)+1; //Initially sets x and y coordinates
            rand_y = rand() % (boardY - 2)+1;


            // Checking if we overlap with the actual snake.

            // We need to loop through all indexes of the snake, and make sure it does not equal our proposed position
            // If it does, we exit the loop and regenerate
        
        
            
            for (int i = 0; i<blockOff->getSize();i++)
            {

                // If our random generated integers conflicts with the snake position
                if ((blockOff->getElement(i).pos->x == rand_x && blockOff->getElement(i).pos->y == rand_y))
                {
                    noMatches = 0;
                    break;
                }
            }

            // Now, we check the snake against the current food positions

            // This is a matter of checking all of the food positions, and ensuring that we are not setting food to where food was previously located.

            // We will only run this is NoMatches is true, because we need to make sure it passed the snake test first

            if (noMatches) {
            
                for (int p = 0; p < NUMFOODS; p++)
                {
                    if ((foodBucket->getElement(p).pos->x == rand_x && foodBucket->getElement(p).pos->y == rand_y) ) //Player or prev. obj pos
                    {
                        noMatches = 0;
                        break;
                    }
                    
                }
            }

            // Now, we need to make sure nothing from the previous array is used.

            // We will use the previous array in Food.h to ensure this

            // Logic works mostly the name

            if (noMatches) {

                for (int i = 0; i < NUMFOODS; i++) {
                    if (rand_x == prevFood[i].pos->x && rand_y == prevFood[i].pos->y) {
                        noMatches = 0;
                        break;
                    }
                }
            }

            // Now, ensuring noMatches is true, we assign the position of the food to the array

            if (noMatches) {

                // Update the current positions
                foodPos.pos->x = rand_x;
                foodPos.pos->y = rand_y;
                // Setting the random simple based on a random number generation from above

                if (currentPosition == specialIndex) {
                    foodPos.symbol = 'S';
                } else {
                    foodPos.symbol = 'A';
                }
                currentPosition++;

                // Set the current positions in the array

                foodBucket->insertTail(foodPos);

                // foodBucket->insertHead(foodPos);
                // foodBucket->removeTail();

            }
        } while (currentPosition < NUMFOODS);

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


objPosArrayList* Food::getFoodPos() //Function was changed for advanced feature to return an objPosArrayList pointer to the food bucket of all apple postions
{
    return foodBucket;
}

objPos* Food::getLastFood() {
    return lastFood;
}

void Food::deleteFoodArray() {

    // This funtion will bookmark the last food generated into a new lastFood array.
    // Then, it will completely clear the list.

    for (int i = NUMFOODS - 1; i >= 0; i--) {

        // Bookmark the coordinates of the last position in the food array
        lastFood[i].pos->x = foodBucket->getTailElement().pos->x;
        lastFood[i].pos->y = foodBucket->getTailElement().pos->y;
        foodBucket->removeTail();
    }
}