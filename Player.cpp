#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '@';

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list

    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic    

        char input = mainGameMechsRef->getInput();

        switch(input) {  

            // W PRESS


            case 'w':

                if (myDir == RIGHT || myDir == LEFT) {
                    myDir = UP;
                }
                
                break;

            // A PRESS


            case 'a':

                if (myDir == UP || myDir == DOWN) {
                    myDir = LEFT;
                }
                
                break;

            // S PRESS

            case 's':

                if (myDir == LEFT || myDir == RIGHT) {
                    myDir = DOWN;
                }

                break;
            
            case 'd':

                if (myDir == UP || myDir == DOWN) {

                    myDir = RIGHT;
                }

                break;

                // Still need to cleean up some of this ported code, bc we need to include the default statement as well.  Also remember the lack of a NONE case here.
        }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    // Port from PPA2, just make sure you change the board size to the game mechanics stuff


}

// More methods to be added