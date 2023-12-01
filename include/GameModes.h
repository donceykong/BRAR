
// GAME MODE
enum GameMode {
    RUNNER,         // 0
    TIME_CRUNCH,    // 1
    VIEW_ROBOTS,    // 2
    NONE
};

const char* GameModeNames[] = {
    "RUNNER",
    "TIME CRUNCH",
    "VIEW ROBOTS",
    "NONE"
};

enum GameMode GAME_MODE;

void setGameMode (int mode) {
    GAME_MODE = (enum GameMode)mode;
    printf("GAME MODE %d CHOSEN: %s\n", mode, GameModeNames[mode]);
}