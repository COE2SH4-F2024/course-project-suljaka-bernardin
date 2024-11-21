#include "Player.h"
#include "MacUILib.h"

// Our brand new default constructor!

// While this is likely to never be invoked, it will be included just in case and to satify the rule of minimum 4


Player::Player() {

    
    myDir = STOP;

    // We will arbitrarily set this to 9 and 4, which are the centre of the board-ish

    playerPos.pos->x = 9;
    playerPos.pos->y = 4;
    playerPos.symbol = '@';

}


Player::Player(GameMechs* thisGMRef)
{

    // Setting up our new reference to the Game Mechanics Reference
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // These will start us at the halfway point of the board (9 and 5 ish, should start us at the centre)

    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2-1; 
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2-1;
    playerPos.symbol = '@';

    // more actions to be included in Iteration 3
}




Player::~Player()
{
    delete mainGameMechsRef;
}

// COPY CONSTRUCTOR ----------

Player::Player(const Player &a) {
    mainGameMechsRef = a.mainGameMechsRef;

    // Deep copy everything previously in the copy constructor!!

    playerPos.pos->x = a.mainGameMechsRef->getBoardSizeX()/2-1; 
    playerPos.pos->y = a.mainGameMechsRef->getBoardSizeY()/2-1;
    playerPos.symbol = a.playerPos.symbol;


}

// COPY ASSIGNMENT CONSTRUCTOR

Player& Player::operator=(const Player &a) {
    // Sanity check to make sure we are not copying into the same object

    if (this != &a) {

        // Deep copy as previously seen in Copy Constructor
        
        playerPos.pos->x = a.mainGameMechsRef->getBoardSizeX()/2-1; 
        playerPos.pos->y = a.mainGameMechsRef->getBoardSizeY()/2-1;
        playerPos.symbol = a.playerPos.symbol;

    }

    return *this;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list

    // I have no idea if this part is right if I am being honest

    return playerPos;
}

void Player::updatePlayerDir()
{
        // Input processing from PPA3

        char input = mainGameMechsRef->getInput();

        // The following code has nearly been directl copied from Adam's PPA3.

        // There are some adjustments, but this is pretty much a direct copy
        // The only difference is the "state" variable from PPA2/3 appeared to be completely useless since it wasn't referenced anywhere so that has been entirely cut

        if (input != 0) {

            switch(input) {  

                // W PRESS


                case 'w':

                    if (myDir == RIGHT || myDir == LEFT || myDir == STOP) {
                        myDir = UP;
                    }

                    state = 'w';
                    
                    
                    break;

                // A PRESS


                case 'a':

                    if (myDir == UP || myDir == DOWN || myDir == STOP) {
                        myDir = LEFT;
                    }

                    state = 'a';
                    
                    break;

                // S PRESS

                case 's':

                    if (myDir == LEFT || myDir == RIGHT || myDir == STOP) {
                        myDir = DOWN;
                    }

                    state = 's';

                    break;

                // D PRESS
                
                case 'd':

                    if (myDir == UP || myDir == DOWN || myDir == STOP) {

                        myDir = RIGHT;
                    }

                    state = 'd';

                    break;

                // Ensure we account for the spacebar case

                case ' ':
                    // Within here, this is where the ExitFlag will go once we figure out what to do for that
                    break;
                
                // Default statement to break the code

                default:
                    break;

            }
        }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    // This is a near exact port from PPA3, however, the score counter is not being updated
    // This may be something to add in Iteration 3

    // Moving the character up

    if (myDir == UP) {

        // Checking the wraparound condition
        if (playerPos.pos->y == 1) {
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY()-2;

            // If the wraparound condition is not satisfied, then we do a standard increment
        } else {

            playerPos.pos->y -= 1;
        }

    // The rest of this is repeated code from PPA3, hence I haven't gone through and commented it all

    } else if (myDir == DOWN) {
        if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY()-2) {
            playerPos.pos->y = 1;
        } else {
            playerPos.pos->y += 1;
        }
    } else if (myDir == LEFT) {
        if (playerPos.pos->x == 1) {
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX()-2;
        } else {
            playerPos.pos->x -=1;
        }
    } else if (myDir == RIGHT) {
        if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX()-2) {
            playerPos.pos->x = 1;
        } else {
            playerPos.pos->x += 1;
        }
    }

    

}

// This a method that has been used for debugging

char Player::getInput() {

    return state;

}


