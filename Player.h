#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:

        // It is interesting that this is public, and to be honest, not fully determined why this is public
        enum Dir {STOP, UP, DOWN, LEFT, RIGHT};  // This is the direction state

        Player(GameMechs* thisGMRef);

        // Adding the default constructor
        Player();
        ~Player();

        // Adding the Rule of Minimum 4 to the Project!!!
        Player(const Player &a);
        Player& operator=(const Player &a);

        objPosArrayList* getPlayerPos() const; // Upgrade this in iteration 3.       
        void updatePlayerDir();
        void movePlayer();

        char getInput();

        bool checkFoodConsumption();
        void increasePlayerLength(objPos playerPos);
        void standardMovement(objPos playerPos);
        // More methods to be added here

    private:

        // This is used for holding the player position 
        objPosArrayList* playerPosList; // Upgrade this in iteration 3.    
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        // This is a character that will be used for debugging
        char state = 'x';
};

#endif