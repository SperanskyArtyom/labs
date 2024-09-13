#pragma once

struct Point
{
    int x, y;
};

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Animal
{
private:
    Point coordinate;
    Direction direction;
    unsigned stability;
    unsigned age;

public:
    Animal(Point coordinate, Direction direction, unsigned stability)
    {
        this->coordinate = coordinate;
        this->direction = direction;
        this->stability = stability;
        age = 0;
    }

    Animal()
    {
        coordinate = {0, 0};
        direction = UP;
        stability = 1;
        age = 0;
    }

    void change(int);

    void move(int N)
    {
        change(N);
    }

    void coordinate(Point coordinate)
    {
        this->coordinate = coordinate;
    }

    void direction(Direction direction)
    {
        this->direction = direction;
    }

    void stability(unsigned stability)
    {
        this->stability = stability;
    }

    void age(unsigned _age)
    {
        this->age = _age;
    }

    Point coordinate()
    {
        return coordinate;
    }

    int direction()
    {
        return direction;
    }

    unsigned stability()
    {
        return stability;
    }

    unsigned age()
    {
        return age;
    }
};

class Rabbit : Animal // Stupid suchka bitchy rabbit Varya
{
private:
public:
};

class Fox : Animal // I am. Sly fox
{
private:
public:
};
