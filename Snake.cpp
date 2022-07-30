#include "include/Gameboard.h"

void setfps();

int main() {
    const int screenWidth = 850, screenHeight = 850;
    InitWindow(screenWidth, screenHeight, "Snake");

    InitAudioDevice();
    SetMasterVolume(50.0f);

    setfps();
    GameBoard game;
    enum decisions {restart, quit, proceed};
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);
        game.BoardPhysics();
        if (game.playerDecision() == restart) {
            GameBoard newGame;
            game = newGame;
        } else if (game.playerDecision() == quit) {
            break;
        }
        EndDrawing();
    }


    CloseAudioDevice();
    CloseWindow();
}

void setfps() {
    int refreshrate = 60;
    SetTargetFPS(refreshrate);
    //std::cout << refreshrate;
}