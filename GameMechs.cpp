#include "GameMechs.h"
#include "MacUILib.h"
#include <time.h>

GameMechs::GameMechs()
{

    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    
}

GameMechs::GameMechs(int boardX, int boardY)
{

    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    

}

GameMechs::GameMechs(const GameMechs &a)
{
    input = a.input;
    exitFlag = a.exitFlag;
    loseFlag = a.loseFlag;
    score = a.score;
    boardSizeX = a.boardSizeX;
    boardSizeY = a.boardSizeY;
}

GameMechs& GameMechs::operator=(const GameMechs &a)
{
    if (this != &a)
    {
    input = a.input;
    exitFlag = a.exitFlag;
    loseFlag = a.loseFlag;
    score = a.score;
    boardSizeX = a.boardSizeX;
    boardSizeY = a.boardSizeY;
    }
    return *this;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput()
{

    if (MacUILib_hasChar() == 1) {
        input = MacUILib_getChar();
    }

    if (input == ' ') {
        exitFlag = true;
    }
    
    return input;
    

}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    // Port from PPA2, the macui has character part.  Very very easy port.

    

}

void GameMechs::clearInput()
{
    input = NULL;
}

// More methods should be added here
void GameMechs::generateFood(objPos blockOff)
{
    
    
        srand(time(NULL));
        int rand_x = rand() % (boardSizeX - 2)+1; //Initially sets x and y coordinates
        int rand_y = rand() % (boardSizeY - 2)+1;
        int rand_char = 0;
        
            int pass= 0;
            while (!pass){
            if (blockOff.pos->x == rand_x || blockOff.pos->y == rand_y ||food.pos->x == rand_x || food.pos->y == rand_y ) //Player or prev. obj pos
            {
                rand_x = rand() % (boardSizeX-2)+1;
                rand_y = rand() % (boardSizeY-2)+1;
            }
            else
            pass = 1;
            }
            food.setObjPos(rand_x,rand_y,'A');
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
        
        
        // list[i].x = rand_x;
        // list[i].y = rand_y;
        // if (i<2)
        // list[i].player = str[rand_char]; //rand char is index and picks from goal string
        // else
        // list[i].player = rand_char; //rand char is ascii value
    }


objPos GameMechs::getFoodPos()
{
    return food;
}