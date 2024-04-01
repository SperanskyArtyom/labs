#pragma once

#include <vector>

using std::vector;

typedef struct {
    int x, y;
} Snake;

typedef struct {
    int x, y;
} Apple;

enum direction {DOWN, UP, RIGHT, LEFT};

Apple spawnApple(const vector<Snake> &snake);
void addSegment(vector<Snake> &snake);
void snakeMove(vector<Snake> &snake, direction dir);
bool isSnakeCrashed(vector<Snake> snake);
bool isSnakeEatApple(vector<Snake> snake, Apple apple);