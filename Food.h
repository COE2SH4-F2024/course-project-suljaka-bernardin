#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food {

    private:
        objPos foodPos;

        // We need to inclue a pointer to mainGameMechsRef to access X and Y values
        GameMechs* mainGameMechsRef;

        // We also need a reference to the boardSize in each direction

        int boardX;
        int boardY;

    public:
        Food();
        ~Food();
        Food(GameMechs* thisGMRef);
        Food(const Food &a);
        Food& operator=(const Food &a); 

        void generateFood(objPosArrayList* blockOff);
        objPos getFoodPos();


};

#endif