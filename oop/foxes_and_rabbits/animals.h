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

    Animal() : Animal({0, 0}, UP, 1)
    {
    }

    void change(int);

    void move(int N)
    {
        change(N);
    }

    void setCoordinate(Point coordinate)
    {
        this->coordinate = coordinate;
    }

    void setDirection(Direction direction)
    {
        this->direction = direction;
    }

    void setStability(unsigned stability)
    {
        this->stability = stability;
    }

    void setAge(unsigned _age)
    {
        this->age = _age;
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

class Rabbit : public Animal
{
private:
    const unsigned maxAge = 10;

public:
    using Animal::Animal;
};

class Fox : public Animal
{
private:
    const unsigned maxAge = 15;

public:
    using Animal::Animal;
};
