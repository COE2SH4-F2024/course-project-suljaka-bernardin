#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs * myGM;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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
    myPlayer = new Player(myGM);

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->movePlayer();
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    objPos playerPos = myPlayer->getPlayerPos();
    int boardY = myGM->getBoardSizeY();
    int boardX = myGM->getBoardSizeX();
    // See the picture that I took in the tutorial
    for (int rows = 0; rows < boardY; rows++)
    {
        for (int cols = 0; cols<boardX;cols++)
        {
            if (rows == 0||rows == boardY-1||cols == 0||cols ==boardX -1)
                MacUILib_printf("#");
            else if(rows == playerPos.pos->y && cols == playerPos.pos->x)
                MacUILib_printf("%c", playerPos.symbol);
            else
                MacUILib_printf(" ");
        }
        MacUILib_printf("\n");
    } 
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();

    delete myPlayer;
    delete myGM;
}
