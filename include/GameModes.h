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

/*
 *
 */
char topPlayerName[12];
float topScore = 0.0;

typedef struct {
    enum GameMode mode;
    char playerName[100];
    double score;
} GameStruct;

GameStruct game;

void setGameMode (int mode) {
    GAME_MODE = (enum GameMode)mode;
    game.mode = GAME_MODE;
    printf("****************************************************\n");
    printf("GAME MODE %d CHOSEN: %s\n", mode, GameModeNames[mode]);
    printf("****************************************************\n\n");
}

void setPlayerName(const char *name) {
    strncpy(game.playerName, name, sizeof(game.playerName) - 1);
    game.playerName[sizeof(game.playerName) - 1] = '\0'; // Ensure null termination
}

void promptForPlayerName() {
    printf("Enter your name: ");
    char name[12];
    if (fgets(name, sizeof(name), stdin) != NULL) {
        // Remove newline character if present
        name[strcspn(name, "\n")] = 0;
        setPlayerName(name);
    }
}

void saveScore(GameStruct *game) {
    FILE *file;
    if (game->mode == RUNNER) {
        file = fopen("runner_scores.txt", "a"); 
    }
    else if (game->mode == TIME_CRUNCH) {
        file = fopen("time_crunch_scores.txt", "a");
    }
    if (file != NULL) {
        fprintf(file, "%s %f\n", game->playerName, game->score);
        fclose(file);
    }
}

void readScores(GameStruct *game) {
    FILE *file = NULL;
    char playerName[12];    
    float score;
    if (game->mode == RUNNER) { 
        file = fopen("runner_scores.txt", "r"); 
    }
    else if (game->mode == TIME_CRUNCH) {
        file = fopen("time_crunch_scores.txt", "r");
    }
    if (file != NULL) {
        while (fscanf(file, "%12s %f", playerName, &score) == 2) {
            if (score >= topScore) { 
                topScore = score;
                for (int i = 0; i < 12; i++){ 
                    topPlayerName[i] = playerName[i];
                }
            }
            // Process the score, e.g., display it or add it to a list
        }
        fclose(file);
    }
}

#endif // GAME_MODES_H