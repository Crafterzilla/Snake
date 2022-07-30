#include "Snake.h"
#include "apple.h"
#include <string>

#define log(x) std::cout << x << std::endl;

class GameBoard {
    Apple apple;
    std::vector<Snake> snakeBody;
    bool gameOver;
    bool justDied;
    bool displayGrid;
    bool gamePaused;
    bool walls;
    bool gameStart;
    enum decisions {restart, quit, proceed};
    int choice;
    int score;
    
    friend class Snake;

    private:
    void MoveSnake();
    void GrowSnake();
    void checkSnakeCollision();
    void checkAppleCollision();
    public:
    GameBoard();
    void DrawGrid();
    void BoardPhysics();
    void gameOverDisplay();
    int playerDecision() {return choice;}
    void getWalls();

    void pauseMenu();
    void gui();
};

GameBoard::GameBoard() {
    snakeBody.clear();
    snakeBody.reserve(1088);

    Snake snake;
    snakeBody.push_back(snake);
    gameOver = false;
    justDied = false;
    gamePaused = false;
    displayGrid = false;
    walls = false;
    gameStart = true;
    choice = proceed;
    score = 0;
    Apple apple;
}
void GameBoard::DrawGrid() {
    for (float i = 0.0f; i < 800.0f; i += 25.0f) {
        Rectangle verticalLine = {0, i, 850.0f, 1.0f};
        DrawRectangleRec(verticalLine, BLACK);
    }
    for (float i = 0.0f; i < 850.0f; i += 25.0f) {
        Rectangle horizontolLine = {i, 0, 1.0f, 800.0f};
        DrawRectangleRec(horizontolLine, BLACK);
    }
}
void GameBoard::BoardPhysics() {
    gui();
    if (gameStart) {
        getWalls();
    } else {
        if (gamePaused == false) {
        checkAppleCollision();
        checkSnakeCollision();
        MoveSnake();
        }
        apple.DrawApple();
        for (unsigned i = 0; i < snakeBody.size(); i++) {
            if (i == 0)
                DrawRectangleRec(snakeBody[i].head, YELLOW);
            else 
                DrawRectangleRec(snakeBody[i].head, GREEN);
        }
        gameOverDisplay();
        if (IsKeyPressed(KEY_P)) {
            if (gamePaused)
                gamePaused = false;
            else
                gamePaused = true;
        }
    }
}

void GameBoard::MoveSnake() {
     Rectangle tmp;
    for (unsigned int i = snakeBody.size() - 1; i > 0; i--) {
        tmp = snakeBody[i].head;
        snakeBody[i].head = snakeBody[i - 1].head;
        snakeBody[i - 1].head = tmp;
    }
    if (gameOver == false)
        snakeBody[0].controlSnake();
    else
        snakeBody[0].aiControlledSnake();
}

void GameBoard::checkAppleCollision() {
    if (CheckCollisionRecs(apple.appleCollision(), snakeBody[0].head)) {
        Snake snakepart;
        snakepart.x = -50;
        snakepart.y = -50;
        snakepart.head = {snakepart.x, snakepart.y, 25, 25};
        snakeBody.push_back(snakepart);


        apple.NewApple();
        for (unsigned int i = 0; i < snakeBody.size(); i++) {
            if (CheckCollisionRecs(apple.appleCollision(), snakeBody[i].head)) {
                apple.NewApple();
                i = 0;
            }
        }
        if (gameOver == false)
            score++;  
    }
}

void GameBoard::checkSnakeCollision() {
    if (walls == false && gameOver == false) {
        if (snakeBody[0].x < 0) {
            snakeBody[0].x = 825;
        } if (snakeBody[0].x > 825) {
            snakeBody[0].x = 0;
        } if (snakeBody[0].y < 0) {
            snakeBody[0].y = 775;
        } if (snakeBody[0].y > 775) {
            snakeBody[0].y = 0;
        }

        snakeBody[0].head = {snakeBody[0].x, snakeBody[0].y, 25, 25};
    } 
    if (walls || gameOver) {
        if (snakeBody[0].x < 0 || snakeBody[0].x > 825 || snakeBody[0].y < 0
        || snakeBody[0].y > 775) {
            Snake newHead;
            snakeBody[0] = newHead;
            snakeBody[0].direction = GetRandomValue(1, 4);
            gameOver = true;
        }
    }

    if (gameOver == false) {
        for (unsigned int i = 1; i < snakeBody.size(); i++) {
            if (CheckCollisionRecs(snakeBody[0].head, snakeBody[i].head)) {
                gameOver = true;
                justDied = true;
                break;
            }
        }
    }
}

void GameBoard::gameOverDisplay() {
    if (gameOver) {
        if (justDied)
            WaitTime(1000.0f);
        for (unsigned i = 0; i < snakeBody.size(); i++) {
            if (i == 0)
                DrawRectangleRec(snakeBody[i].head, RED);
            else
                DrawRectangleRec(snakeBody[i].head, RED);
        }
        DrawRectangle(200, 200, 450, 400, {0, 100, 200, 180});
        DrawText("You Died!", 300, 300, 50, WHITE);
        std::string scoreText = "Score: " + std::to_string(score);
        DrawText(scoreText.c_str(), 300, 400, 45, WHITE);


        //Mouse Controls for GUI for death
        Rectangle buttonPlayagain = {250, 475, 100, 100};
        Color BLUEForNOClick = {0, 90, 225, 200};
        Color BLUEForClick = {0, 90, 200, 200};
        int mousePosX = GetMouseX();
        int mousePosY = GetMouseY();
        if ((mousePosX > 250) && (mousePosX < 350) && (mousePosY > 475) && (mousePosY < 575)) {
            DrawRectangleRec(buttonPlayagain, BLUEForClick);
        } else {
            DrawRectangleRec(buttonPlayagain, BLUEForNOClick);
        }
        DrawText("Play\nAgain?", 275, 500, 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
        (mousePosX > 250) && (mousePosX < 350) && (mousePosY > 475) && (mousePosY < 575)) {
            choice = restart;
        }

        Rectangle buttonExit = {450, 475, 100, 100};
        if ((mousePosX > 450) && (mousePosX < 550) && (mousePosY > 475) && (mousePosY < 575)) {
            DrawRectangleRec(buttonExit, BLUEForClick);
        } else {
            DrawRectangleRec(buttonExit, BLUEForNOClick);
        }
        DrawText("\nExit?", 475, 475, 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
        (mousePosX > 450) && (mousePosX < 550) && (mousePosY > 475) && (mousePosY < 575)) {
            choice = quit;
        }

        justDied = false;
    }
}

void GameBoard::gui() {
    if (walls) {
        Rectangle perimeter = {0, 0, 850, 800};
        DrawRectangleLinesEx(perimeter, 2.0f, RED);
    }
    Rectangle guiBottom = {0, 800, 850, 50};
    if (gameOver == false) {
        DrawRectangleRec(guiBottom, WHITE);
    } else {
        DrawRectangleRec(guiBottom, {153, 0, 0, 255});
    }

    std::string scoreText = "Score: " + std::to_string(score);
    DrawText(scoreText.c_str(), 750, 815, 20, BLACK);

    //Turn On Grids
    int mousePosX = GetMouseX();
    int mousePosY = GetMouseY();
    Rectangle buttonToggleGrid = {0, 800, 50, 100};
    Color GREY = {211, 211, 211, 255};

    if ((mousePosX > 0) && (mousePosX < 50) && (mousePosY > 800) && (mousePosY < 850)) {
        DrawRectangleRec(buttonToggleGrid, GREY);
    } else {
        DrawRectangleRec(buttonToggleGrid, WHITE);
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
    (mousePosX > 0) && (mousePosX < 50) && (mousePosY > 800) && (mousePosY < 850)) {
        if (displayGrid == true)
            displayGrid = false;
        else
            displayGrid = true;
    }

    if (displayGrid == true) {
        DrawText("Grid\nON", 5, 805, 18, BLACK);
        DrawGrid();
    } else {
        DrawText("Grid\nOFF", 5, 805, 18, BLACK);
    }

    //Pause Menu Button
    mousePosX = GetMouseX();
    mousePosY = GetMouseY();
    Rectangle buttonTogglePauseMenu = {50, 800, 50, 100};
    if ((mousePosX > 50) && (mousePosX < 100) && (mousePosY > 800) && (mousePosY < 850)) {
        DrawRectangleRec(buttonTogglePauseMenu, GREY);
    } else {
        DrawRectangleRec(buttonTogglePauseMenu, WHITE);
    } 
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
    (mousePosX > 50) && (mousePosX < 100) && (mousePosY > 800) && (mousePosY < 850)) {
        if (gamePaused)
            gamePaused = false;
        else
            gamePaused = true;
    }
    if (gamePaused) {
        pauseMenu();
        DrawText("Con-\ntinue", 55, 805, 16, BLACK);
    } else {
        DrawText("Pause", 55, 805, 16, BLACK);
    }


    //Wall option
    mousePosX = GetMouseX();
    mousePosY = GetMouseY();
    Rectangle buttonToggleWalls = {100, 800, 50, 100};
    if ((mousePosX > 100) && (mousePosX < 150) && (mousePosY > 800) && (mousePosY < 850)) {
        DrawRectangleRec(buttonToggleWalls, GREY);
    } else {
        DrawRectangleRec(buttonToggleWalls, WHITE);
    } 
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
    (mousePosX > 100) && (mousePosX < 150) && (mousePosY > 800) && (mousePosY < 850)) {
        if (walls)
            walls = false;
        else
            walls = true;
    }
    if (walls) {
        DrawText("Walls\nON", 105, 805, 16, BLACK);
    } else {
        DrawText("Walls\nOFF", 105, 805, 16, BLACK);
    }
}

void GameBoard::pauseMenu() {
    DrawRectangle(200, 200, 450, 400, {0, 100, 200, 180});
        DrawText("Paused", 300, 300, 50, WHITE);
}

void GameBoard::getWalls() {
    DrawRectangle(200, 200, 450, 400, {0, 100, 200, 180});
    DrawText("Walls or \nNo Walls?", 300, 300, 50, WHITE);

        Rectangle buttonNoWalls = {250, 475, 100, 100};
        Color BLUEForNOClick = {0, 90, 225, 200};
        Color BLUEForClick = {0, 90, 200, 200};
        int mousePosX = GetMouseX();
        int mousePosY = GetMouseY();
        if ((mousePosX > 250) && (mousePosX < 350) && (mousePosY > 475) && (mousePosY < 575)) {
            DrawRectangleRec(buttonNoWalls, BLUEForClick);
        } else {
            DrawRectangleRec(buttonNoWalls, BLUEForNOClick);
        }
        DrawText("No \nWalls", 275, 500, 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
        (mousePosX > 250) && (mousePosX < 350) && (mousePosY > 475) && (mousePosY < 575)) {
            walls = false;
            gameStart = false;
        }

        Rectangle buttonWalls = {450, 475, 100, 100};
        if ((mousePosX > 450) && (mousePosX < 550) && (mousePosY > 475) && (mousePosY < 575)) {
            DrawRectangleRec(buttonWalls, BLUEForClick);
        } else {
            DrawRectangleRec(buttonWalls, BLUEForNOClick);
        }
        DrawText("\nWalls", 475, 475, 20, WHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
        (mousePosX > 450) && (mousePosX < 550) && (mousePosY > 475) && (mousePosY < 575)) {
            walls = true;
            gameStart = false;
        }
}