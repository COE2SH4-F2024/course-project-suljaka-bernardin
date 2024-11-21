#include "GameMechs.h"
#include "MacUILib.h"

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