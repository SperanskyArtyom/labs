#include "snake.h"

using namespace std;

vector<Snake> spawnSnake()
{
    vector<Snake> snake = {{3, 7}, {2, 7}, {1, 7}, {0, 7}};
    return snake;
}

void snakeMove(vector<Snake> &snake, direction dir)
{
    for (int i = snake.size() - 1; i > 0; i--){
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
        if (dir == LEFT)
            snake[0].x -= 1;
        else if (dir == RIGHT)
            snake[0].x += 1;
        else if (dir == UP)
            snake[0].y -= 1;
        else if (dir == DOWN)
            snake[0].y += 1;
}

bool isSnakeCrashed(vector<Snake> snake)
{
    if (snake[0].x < 0 || snake[0].x > 14 || snake[0].y < 0 || snake[0].y > 14)
        return true;
    for (auto i = snake.size(); i > 0; i--)
        if (snake[i].x == snake[0].x && snake[i].y == snake[0]. y)
            return true;
    return false;
}