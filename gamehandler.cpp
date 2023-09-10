#include "gamehandler.h"

//Model

GameHandler::GameHandler() :
    set("./conf.ini", QSettings::IniFormat)
{
    random.seed(QDateTime::currentDateTime().time().msec()%1000); //For the random function

    //Points
    points = 0;

    if(set.contains("record")) {
        record = set.value("record",0).toInt();
    }
    else {
        set.setValue("record",0);
        record = set.value("record",0).toInt();
    }
    set.sync();

    reset();
}

void GameHandler::reset()
{
    PlayerTurn = false;
    isWrong = false;
    isRight = false;
    points = 0;
    computerMoves = 0;
    playerMoves = 0;
}

void GameHandler::start()
{
    reset(); //Security Reset
    player.clear();
    computer.clear();
    generateComputerMove();
}


void GameHandler::generateComputerMove()
{
    switch (QRandomGenerator::global()->bounded(0,4)) { //Pushes Back a Random Move
                case 0:
                    computer.push_back(Moves::Up);
                    break;
                case 1:
                    computer.push_back(Moves::Right);
                    break;
                case 2:
                    computer.push_back(Moves::Down);
                    break;
                case 3:
                    computer.push_back(Moves::Left);
                    break;
                default:
                    break;
                }
    PlayerTurn = true;
}

unsigned int GameHandler::getComputerMove(unsigned int i)
{
    if(i<=computer.size()-1)
    {
        return computer.at(i);
    }
    else
    {
        return 0;
    }
}

void GameHandler::setPlayerMove(unsigned int mov)
{
    if(PlayerTurn)
    {
        player.push_back(mov);
        if(std::equal(player.begin(),player.end(),computer.begin()))
        {
            if(points>playerMoves)
            {
                isRight=false;
                playerMoves++;
            }
            else
            {
                points++;
                if(points>=record)
                {
                    //Save Value
                    record = points;
                    set.setValue("record",record);
                    set.sync();
                }
                playerMoves = 0;
                computerMoves = 0;
                PlayerTurn = false;
                isRight=true;
                generateComputerMove();
                player.clear();
                return;
            }
        }
        else
        {
            reset();
            isWrong = true;
        }
    }
}

bool GameHandler::isWrongSequence()
{
    return isWrong;
}

bool GameHandler::isRightSequence()
{
    return isRight;
}
