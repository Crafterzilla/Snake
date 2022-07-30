#include <ctime>
#include "raylib.h"
#include <iostream>
#include <vector>

class Snake {
    Rectangle head;
    float x, y;
    float movex, movey;
    float speed;
    float waitTime;
    int direction;
    friend class GameBoard;
    public:
    Snake();
    void DrawSnake();
    void controlSnake();
    void aiControlledSnake();
    Rectangle snakePosCollision() {return head;}
};

Snake::Snake() {
    SetRandomSeed(time(0));
    x = GetRandomValue(0, 825);
    y = GetRandomValue(0, 775);
    int roundOff = (int)x % 25;
    x -= roundOff;
    roundOff = (int)y % 25;
    y -= roundOff;


    movex = 0;
    movey = 0;
    speed = 25;
    waitTime = 75.0f;

    direction = 0;
    head = {x, y, 25, 25};
}

void Snake::DrawSnake() {
    DrawRectangleRec(head, BLACK);
}

void Snake::controlSnake() {
    const int moveFactor = 1;
    enum directions {nodir, left, right, up, down};


    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && (direction != down || direction == nodir)) {
        movey = moveFactor;
        movey *= -speed;
        movex = 0;
        direction = up;
    } if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && (direction != right || direction == nodir)) {
        movex = moveFactor;
        movex *= -speed;
        movey = 0;
        direction = left;
    } if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && (direction != up || direction == nodir)) {
        movey = moveFactor;
        movey *= speed;
        movex = 0;
        direction = down;
    } if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && (direction != left || direction == nodir)) {
        movex = moveFactor;
        movex *= speed;
        movey = 0;
        direction = right;
    }
    x += movex;// * GetFrameTime();
    y += movey;// * GetFrameTime();
    head = {x, y, 25, 25};
    WaitTime(waitTime);
    //std::cout << x << ' ' << y << '\n' << movex << ' ' << movey << '\n';
}

void Snake::aiControlledSnake() {
    const int moveFactor = 1;
    enum directions {nodir, left, right, up, down};


    if (direction == up) {
        movey = moveFactor;
        movey *= -speed;
        movex = 0;
        direction = up;
    } if (direction == left) {
        movex = moveFactor;
        movex *= -speed;
        movey = 0;
        direction = left;
    } if (direction == down) {
        movey = moveFactor;
        movey *= speed;
        movex = 0;
        direction = down;
    } if (direction == right) {
        movex = moveFactor;
        movex *= speed;
        movey = 0;
        direction = right;
    }
    x += movex;// * GetFrameTime();
    y += movey;// * GetFrameTime();
    head = {x, y, 25, 25};
    WaitTime(100.0f);
}