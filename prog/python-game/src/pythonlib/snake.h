#pragma once

#include <vector>

typedef struct {
    int x, y;
} Snake;

typedef struct {
    int x, y;
} Apple;

enum direction {DOWN, UP, RIGHT, LEFT};

Apple spawnApple(const std::vector<Snake> &snake);
void addSegment(std::vector<Snake> &snake);
void snakeMove(std::vector<Snake> &snake, direction dir);
bool isSnakeCrashed(std::vector<Snake> snake);
bool isSnakeEatApple(std::vector<Snake> snake, Apple apple);