#pragma once

#include <Model.h>

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
    friend class Model;

private:
    Point coordinate;
    Direction direction;
    const unsigned stability;
    unsigned age = 0;
    unsigned dStability = 0;

protected:
    void changeCoord(int N)
    {
        switch (direction)
        {
        case UP:
            coordinate.y -= N;
            break;
        case DOWN:
            coordinate.y += N;
            break;
        case LEFT:
            coordinate.x -= N;
            break;
        case RIGHT:
            coordinate.x += N;
            break;
        }
    }
    void changeDir() { direction = (Direction)((direction + 1) % 4); }

public:
    Animal(Point coordinate = {0, 0}, Direction direction = UP, unsigned stability = 1)
        : stability{stability}
    {
        this->coordinate = coordinate;
        this->direction = direction;
    }
    Animal(const Animal &animal) : Animal(animal.coordinate, animal.direction, animal.stability) {}

    virtual void move()
    {
        if (++dStability == stability)
        {
            dStability = 0;
            changeDir();
        }
    }

    void setCoordinate(Point coordinate) { this->coordinate = coordinate; }

    void setDirection(Direction direction) { this->direction = direction; }

    Point getCoordinate() const { return coordinate; }

    int getDirection() const { return direction; }

    unsigned getStability() const { return stability; }

    unsigned getAge() const { return age; }
};
