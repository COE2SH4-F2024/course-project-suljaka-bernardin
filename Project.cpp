#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs * myGM;
Food *myFood;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    myFood->generateFood(myPlayer->getPlayerPos());


}

void GetInput(void)
{
   myGM->getInput();
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    myGM->clearInput();
    
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPosArrayList* playerPosArrayList = myPlayer->getPlayerPos(); // This is an edit implemented to accept the right data type
    objPosArrayList* foodPosArrayList = myFood->getFoodPos();
    int boardY = myGM->getBoardSizeY();
    int boardX = myGM->getBoardSizeX();
    objPos snakePrint;
    objPos foodPrint;
    objPos* lastFoodPrint = myFood->getLastFood();

    // At this iteration, we need to change this to print the full snake
    for (int rows = 0; rows < boardY; rows++)
    {
        for (int cols = 0; cols<boardX; cols++)
        {

            // We first use a FOR loop to print out the snake.  We check to see if we are at values of the snake, and then copy them to a temporary object.

            for (int k = 0; k < playerPosArrayList->getSize(); k++) {
                if (rows == playerPosArrayList->getElement(k).pos->y && cols == playerPosArrayList->getElement(k).pos->x) {                    
                    // Copying the snake values in if we have any.  We set those to the rows and columns of the array that are in.
                    // If we print from here, the printing of the snake will not be done in the if/else statement and we will get a space character

                    snakePrint.pos->x = cols;
                    snakePrint.pos->y = rows;
                    snakePrint.symbol = playerPosArrayList->getElement(k).symbol;
                }
            }

            // We copy the same logic for food printing, as we need to cycle through a number of elements

            for (int k = 0; k < foodPosArrayList->getSize(); k++) {
                if (rows == foodPosArrayList->getElement(k).pos->y && cols == foodPosArrayList->getElement(k).pos->x) {                    
                    // Copying the food values in if we have any.  We set those to the rows and columns of the array that are in.
                    // If we print from here, the printing of the food will not be done in the if/else statement and we will get a sapce character

                    foodPrint.pos->x = cols;
                    foodPrint.pos->y = rows;
                    foodPrint.symbol = foodPosArrayList->getElement(k).symbol;
                }
            }

            // If we are at the edges of the board, print the border character #

            
            if (rows == 0 || rows == boardY - 1||cols == 0||cols == boardX - 1) {
                MacUILib_printf("#");

            // If we are at an index of the snake, print whatever character is next in the snake

            } else if (cols == snakePrint.pos->x && rows == snakePrint.pos->y) {

                MacUILib_printf("%c", snakePrint.symbol);
            
            // If we are at a food character, print out whatever food character we are at

            }

            else if (rows == foodPrint.pos->y && cols == foodPrint.pos->x)
            {
                MacUILib_printf("%c", foodPrint.symbol);
            }

            // If none of the above are satisfied, print out a space character.
            else {
                MacUILib_printf(" ");
            }
        }

        // At the end of the nested FOR loop, go to a new line

        MacUILib_printf("\n");
    }

    // Printing the score

    MacUILib_printf("Score: %d\n",  myGM->getScore());

    // Printing the ending message based on if the player loses or if the player gives up
    if(myGM->getLoseFlagStatus())
        MacUILib_printf("YOU LOSE\n");
    else if(myGM->getExitFlagStatus())
        MacUILib_printf("YOU GAVE UP!\n");
        // This is amazing

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    

    MacUILib_uninit();

    // Making sure we do not double delete (sanity checks with null pointers to prevent this)

    if (myPlayer != nullptr) {
        delete myPlayer;
    }

    if (myGM != nullptr) {
        delete myGM;
    }
    
    if (myFood != nullptr) {
        delete myFood;
    }
    // myPlayer->~Player();
    // myGM->~GameMechs();
    // myFood->~Food();
}
