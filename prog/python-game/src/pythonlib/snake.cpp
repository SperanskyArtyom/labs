#include <pythonlib/snake.h>
#include <cstdlib> // Подключение библиотеки для генерации случайных чисел

Apple spawnApple(const vector<Snake> &snake) // Функция для генерации координат яблока
{
    Apple apple;
    int x = (int)rand() % 15;
    int y = (int)rand() % 15;
    // Проверка совпадает ли сгенерированный координаты яблока и координаты каждого сегмента змейки
    for (auto segment : snake)
        if (segment.x == x && segment.y == y)
            return spawnApple(snake); // Если совпадает, генерируем заново
    apple.x = x;
    apple.y = y;
    return apple;
}

void addSegment(vector<Snake> &snake)
{
    snake.push_back(snake.back()); // Добавление в хвост змейки сегмента с координатами хвоста
}

void snakeMove(vector<Snake> &snake, direction dir)
{
    // Задаём каждому сегменту змейки, кроме головы, координаты предыдущего сегмента
    for (auto i = snake.size() - 1; i > 0; i--)
    {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    // Изменение координат головы, в зависимости от направления движения
    if (dir == LEFT)
        snake[0].x--;
    else if (dir == RIGHT)
        snake[0].x++;
    else if (dir == UP)
        snake[0].y--;
    else
        snake[0].y++;
}

bool isSnakeCrashed(vector<Snake> snake)
{
    if (snake[0].x < 0 || snake[0].x > 14 || snake[0].y < 0 || snake[0].y > 14) // Проверка, достигла ли змейка границы игрового поля
        return true;
    for (auto i = snake.size() - 1; i > 0; i--) // Проверка, пересекает ли голова координаты остальных сегментов
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
            return true;
    return false;
}

bool isSnakeEatApple(vector<Snake> snake, Apple apple)
{
    return (snake[0].x == apple.x && snake[0].y == apple.y); // Проверка, достигла ли голова координат яблока
}
