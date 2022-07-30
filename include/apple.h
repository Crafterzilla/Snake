#include "raylib.h"
#include <ctime>

#define log(x) std::cout << x << std::endl;

class Apple { 
    Rectangle apple;
    float x, y;
    public:
    Apple();
    void DrawApple();
    Rectangle appleCollision() {return apple;}
    void NewApple();
};

Apple::Apple() {
    x = 425;
    y = 400;
     apple = {x, y, 25, 25};
}

void Apple::DrawApple() {
    DrawRectangleRec(apple, RED);
}

void Apple::NewApple() {
    //SetRandomSeed(time(0));
    x = GetRandomValue(0, 825);
    y = GetRandomValue(0, 775);
    int roundOff = (int)x % 25;
    x -= roundOff;
    roundOff = (int)y % 25;
    y -= roundOff;

    apple = {x, y, 25, 25};
}