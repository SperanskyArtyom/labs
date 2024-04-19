#pragma once // Директива для исключения повторного поключения заголовочного файла

#include <vector> // Подключаем библиотеку для использования векторов

using std::vector;

// Структура координат змейки
typedef struct
{
    int x, y;
} Snake;

// Структура координат яблока
typedef struct
{
    int x, y;
} Apple;

enum direction
{
    DOWN,
    UP,
    RIGHT,
    LEFT
}; // Перечисление направлений движения

// Объявления функций
Apple spawnApple(const vector<Snake> &snake);
void addSegment(vector<Snake> &snake);
void snakeMove(vector<Snake> &snake, direction dir);
bool isSnakeCrashed(vector<Snake> snake);
bool isSnakeEatApple(vector<Snake> snake, Apple apple);
