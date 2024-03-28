#pragma once

#include <vector>

typedef struct {
    int x;
    int y;
} Snake;

enum direction {LEFT, RIGHT, UP, DOWN};

std::vector<Snake> spawnSnake();
void snakeMove(std::vector<Snake> &snake, direction dir);
bool isSnakeCrashed(std::vector<Snake> snake);