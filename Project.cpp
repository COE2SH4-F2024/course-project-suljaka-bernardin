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

            for (int k = 0; k < playerPosArrayList->getSize(); k++) {
                if (rows == playerPosArrayList->getElement(k).pos->y && cols == playerPosArrayList->getElement(k).pos->x) {                    
                    // Copying the snake values in if we have any.  We set those to the rows and columns of the array that are in.
                    // If we print from here, the printing of the snake will not be done in the if/else statement and we will get a sapce character

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

            
            if (rows == 0 || rows == boardY - 1||cols == 0||cols == boardX - 1) {
                MacUILib_printf("#");


            } else if (cols == snakePrint.pos->x && rows == snakePrint.pos->y) {

                MacUILib_printf("%c", snakePrint.symbol);
            

            

            // This is problematic because we will probably need another drawing condition here.
            // Like we also need to check EVERY value of the snake which is going to be a bit of a nightmare
            // We also need to make sure food won't print over the snake but that should be Iteration 2.
            }
            else if (rows == foodPrint.pos->y && cols == foodPrint.pos->x)
            {
                MacUILib_printf("%c", foodPrint.symbol);
            }
            else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }
    MacUILib_printf("Score: %d\n",  myGM->getScore());

    // Also for debugging
    //MacUILib_printf("ListSize: %d\n",foodPosArrayList->getSize()); 

    // For debugging purposes - commented out

    // for (int i = 0; i < foodPosArrayList->getSize(); i++) {
    //     MacUILib_printf("X Coord: %d Y Coord %d\n", foodPosArrayList->getElement(i).pos->x, foodPosArrayList->getElement(i).pos->y);
    // }

    // for (int i = 0; i < 5; i++) {
    //     MacUILib_printf("X Coord: %d Y Coord %d LAST\n", lastFoodPrint[i].pos->x, lastFoodPrint[i].pos->y);

    //}
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

    delete myPlayer;
    delete myGM;
}
