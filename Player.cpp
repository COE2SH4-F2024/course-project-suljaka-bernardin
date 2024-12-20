#include "Player.h"
#include "MacUILib.h"
#include <time.h>

// Our brand new default constructor!

// While this is likely to never be invoked, it will be included just in case and to satify the rule of minimum 4


Player::Player() {
    
    myDir = STOP;

    objPos playerPos;

    // We will arbitrarily set this to 9 and 4, which are the centre of the board-ish

    playerPosList = new objPosArrayList();

    // Passing in playerPos into the objPosArrayList
    playerPos.pos->x = 9;
    playerPos.pos->y = 4;
    playerPos.symbol = '*';

    playerPosList->insertHead(playerPos);


}


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{

    // Setting up our new reference to the Game Mechanics Reference
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Copying over the reference to the new Food class

    foodBin = thisFoodRef;

    // These will start us at the halfway point of the board (9 and 5 ish, should start us at the centre)

    playerPosList = new objPosArrayList();

    objPos playerPos;


    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2-1; 
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2-1;
    playerPos.symbol = '*';

    playerPosList->insertHead(playerPos);


    // more actions to be included in Iteration 3

}




Player::~Player()
{

    if (playerPosList != nullptr) {
        delete playerPosList;
    }
}

// COPY CONSTRUCTOR ----------

Player::Player(const Player &a) {
    mainGameMechsRef = a.mainGameMechsRef;
    foodBin = a.foodBin;


    // Deep copy everything previously in the copy constructor!!

    playerPosList = new objPosArrayList();

    objPos playerPos;


    playerPos.pos->x = a.mainGameMechsRef->getBoardSizeX()/2-1; 
    playerPos.pos->y = a.mainGameMechsRef->getBoardSizeY()/2-1;
    playerPos.symbol = a.playerPosList->getHeadElement().symbol;

    playerPosList->insertHead(playerPos);



}

// COPY ASSIGNMENT CONSTRUCTOR

Player& Player::operator=(const Player &a) {
    // Sanity check to make sure we are not copying into the same object

    if (this != &a) {

        // Deep copy as previously seen in Copy Constructor

        mainGameMechsRef = a.mainGameMechsRef;
        foodBin = a.foodBin;


        objPos playerPos;

        
        playerPos.pos->x = a.mainGameMechsRef->getBoardSizeX()/2-1; 
        playerPos.pos->y = a.mainGameMechsRef->getBoardSizeY()/2-1;
        playerPos.symbol = a.playerPosList->getHeadElement().symbol;

        playerPosList->insertHead(playerPos);



    }

    return *this;
}

objPosArrayList* Player::getPlayerPos() const // In tutorial this is said to be a pointer
{
    // return the reference to the playerPos arrray list

    // I have no idea if this part is right if I am being honest\\
    
    // FOr getPlayerPos, we are supposed to return the reference to the entire list

    return playerPosList;
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

    objPos playerPos = playerPosList->getHeadElement();


    if (myDir == UP) {

        // Checking the wraparound condition
        if (playerPos.pos->y == 1) {
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY()-2;

            // If the wraparound condition is not satisfied, then we do a standard increment
        } else {

            playerPos.pos->y -= 1;
        }

        // Insert the new playerPos into the head of the array.
        // Then remove the last element from the list

        // This is how we provide the illusion that the snake is moving.
        // NEED TO CHECK THIS IMPLEMENTATION BADLY
        // I am not sure if this is all this part is if I am being honest here

        // Checking for if the future position is going to collide with the snake, using the method we previously developed.
        // We pass in playerPos, which is the prediction for the new head.

        if (checkSelfCollision(playerPos)) {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();

        } else {



            if (checkFoodConsumption()) {
                increasePlayerLength(playerPos);
                foodBin->deleteFoodArray();
                foodBin->generateFood(playerPosList);
            } else {
                standardMovement(playerPos);
            }
        }

    // The rest of this is repeated code from PPA3, hence I haven't gone through and commented it all

    } else if (myDir == DOWN) {
        if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY()-2) {
            playerPos.pos->y = 1;
        } else {
            playerPos.pos->y += 1;
        }

        if (checkSelfCollision(playerPos)) {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();

        } else {

            if (checkFoodConsumption()) {
                increasePlayerLength(playerPos);
                foodBin->deleteFoodArray();
                foodBin->generateFood(playerPosList);
            } else {
                standardMovement(playerPos);
            }
        }

    } else if (myDir == LEFT) {
        if (playerPos.pos->x == 1) {
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX()-2;
        } else {
            playerPos.pos->x -=1;
        }

        if (checkSelfCollision(playerPos)) {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();

        } else {

            if (checkFoodConsumption()) {
                increasePlayerLength(playerPos);
                foodBin->deleteFoodArray();
                foodBin->generateFood(playerPosList);

            } else {
                standardMovement(playerPos);
            }
        }

    } else if (myDir == RIGHT) {
        if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX()-2) {
            playerPos.pos->x = 1;
        } else {
            playerPos.pos->x += 1;
        }

        if (checkSelfCollision(playerPos)) {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();

        } else {

            if (checkFoodConsumption()) {
                increasePlayerLength(playerPos);
                foodBin->deleteFoodArray();
                foodBin->generateFood(playerPosList);
            } else {
                standardMovement(playerPos);
            }
        }
    }

    

}

// This a method that has been used for debugging

char Player::getInput() {

    return state;

}

bool Player::checkFoodConsumption()
{
    for (int i = 0; i < foodBin->getFoodPos()->getSize(); i++)
    {
        if (playerPosList->getHeadElement().pos->x == foodBin->getFoodPos()->getElement(i).pos->x && playerPosList->getHeadElement().pos->y == foodBin->getFoodPos()->getElement(i).pos->y)
        {
            if (foodBin->getFoodPos()->getElement(i).symbol == 'A')
                mainGameMechsRef->incrementScore(1);
            else
            {

                // The special food implemented will change the score by a random value between -10 and 10
                // Snake size will increase regardless
                srand(time(NULL));
                int rand_score = rand() %(21) - 10;
                mainGameMechsRef->incrementScore(rand_score);
            }
            return true;
        }
    }
    return false;
}  

void Player::increasePlayerLength(objPos playerPos)
{
    playerPosList->insertHead(playerPos);
}

// This method has been included because this block of code has been reused 4 times and we don't want to rewirte it :)

void Player::standardMovement(objPos playerPos) {

    playerPosList->insertHead(playerPos);
    playerPosList->removeTail();


}

bool Player::checkSelfCollision(objPos playerPos) {

    // Loop through the array, and see if the head is equal to the position of ANY of the snake body characters

    // We need to start at i = 1 because we do not want to check if the head collides with itself.

    for(int i = 1; i < playerPosList->getSize(); i++) {

        // Check to ensure that the head element is the same as any of the tail elements
        if (playerPosList->getElement(i).pos->x == playerPos.pos->x && playerPosList->getElement(i).pos->y == playerPos.pos->y) {
            return true;
        }
    }

    // If it makes it through this entire loop, we will return FALSE

    return false;
}


