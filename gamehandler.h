#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <QRandomGenerator>
#include <QDateTime>
#include <QSettings>
#include <vector>

class GameHandler
{
private:
    //QUtils
    QRandomGenerator random;
    QSettings set;

    //Turns Containers
    std::vector<unsigned int> computer, player;

    //Utils
    bool PlayerTurn;
    bool isWrong;
    bool isRight;
    unsigned int points;
    unsigned int record;
    unsigned int computerMoves;
    unsigned int playerMoves;

    //Functions
    void generateComputerMove();

public:
    GameHandler();

    enum Moves{
        Up=1,
        Down=3,
        Right=2,
        Left=4
    };

    unsigned int isPlayerTurn() const { return PlayerTurn; }; //True if player turn False if computer turn
    unsigned int getPoints() const { return points;};
    unsigned int getRecord() const {return record;};

    unsigned int getComputerMove(unsigned int i); //Returns the last move made by the computer

    void setPlayerMove(unsigned int mov); //Set the player move, returns false if the sequence is wrong

    bool isWrongSequence();// Returns if the sequence is wrong
    bool isRightSequence();// Returns if the sequence is right

    void reset(); //Reset all the stats and the game
    void start(); //Starts the game generation
};

#endif // GAMEHANDLER_H
