#ifndef GAME_MODES_H
#define GAME_MODES_H

// GAME MODE
enum GameMode {
    RUNNER,         // 0
    TIME_CRUNCH,    // 1
    VIEW_ROBOT,    // 2
    NONE
};

const char* GameModeNames[] = {
    "RUNNER",
    "TIME CRUNCH",
    "VIEW ROBOT",
    "NONE"
};

extern enum GameMode GAME_MODE;

void setGameMode (int mode) {
    GAME_MODE = (enum GameMode)mode;
    printf("****************************************************\n");
    printf("GAME MODE %d CHOSEN: %s\n", mode, GameModeNames[mode]);
    printf("****************************************************\n\n");
}

#endif // GAME_MODES_H