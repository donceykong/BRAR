#ifndef GAME_MODES_H
#define GAME_MODES_H

#include <string.h>
#include <stdio.h>

// GAME MODE
enum GameMode {
    RUNNER,         // 0
    TIME_CRUNCH,    // 1
    VIEW_ROBOT,    // 2
    NONE
};

extern const char* GameModeNames[];

/*
 *
 */
typedef struct {
    enum GameMode mode;
    char playerName[100];
    double score;
} GameStruct;

extern enum GameMode GAME_MODE;     //
extern GameStruct game;             //
extern char topPlayerName[12];      //
extern float topScore;              //

void setGameMode (int mode);

void setPlayerName(const char *name);

void promptForPlayerName();

void saveScore(GameStruct *game);

void readScores(GameStruct *game);

#endif // GAME_MODES_H