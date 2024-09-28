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
protected:
    Point coordinate;
    Direction direction;
    const unsigned stability;
    unsigned age = 0;
    unsigned dStability = 0;

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

    void changeDir()
    {
        if (direction == LEFT)
            direction = UP;
        else
            direction = (Direction)(direction + 1);
    }

public:
    Animal(Point coordinate = {0, 0}, Direction direction = UP, unsigned stability = 1) : stability{stability}
    {
        this->coordinate = coordinate;
        this->direction = direction;
    }

    virtual void move()
    {
        if (++dStability == stability)
        {
            dStability = 0;
            this->changeDir();
        }
    }

    void setCoordinate(Point coordinate)
    {
        this->coordinate = coordinate;
    }

    void setDirection(Direction direction)
    {
        this->direction = direction;
    }

    Point getCoordinate()
    {
        return coordinate;
    }

    int getDirection()
    {
        return direction;
    }

    unsigned getStability()
    {
        return stability;
    }

    unsigned getAge()
    {
        return age;
    }
};
