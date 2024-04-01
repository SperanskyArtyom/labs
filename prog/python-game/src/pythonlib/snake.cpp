#include <pythonlib/snake.h>
#include <cstdlib>

Apple spawnApple(const vector<Snake> &snake) {
    Apple apple;
    int x = (int) rand() % 15;
    int y = (int) rand() % 15;
    for (auto segment: snake)
        if (segment.x == x && segment.y == y)
            return spawnApple(snake);
    apple.x = x;
    apple.y = y;
    return apple;
}

void addSegment(vector<Snake> &snake)
{
    snake.push_back(snake.back());
}

void snakeMove(vector<Snake> &snake, direction dir)
{
    for (auto i = snake.size() - 1; i > 0; i--){
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
        if (dir == LEFT)
            snake[0].x--;
        else if (dir == RIGHT)
            snake[0].x++;
        else if (dir == UP)
            snake[0].y--;
        else if (dir == DOWN)
            snake[0].y++;
}

bool isSnakeCrashed(vector<Snake> snake)
{
    if (snake[0].x < 0 || snake[0].x > 14 || snake[0].y < 0 || snake[0].y > 14)
        return true;
    for (auto i = snake.size() - 1; i > 0; i--)
        if (snake[i].x == snake[0].x && snake[i].y == snake[0]. y)
            return true;
    return false;
}

bool isSnakeEatApple(vector<Snake> snake, Apple apple)
{
    return (snake[0].x == apple.x && snake[0].y == apple.y);
}