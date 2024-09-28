#pragma once

#include <Animal.h>

class Rabbit : public Animal
{
private:
    const unsigned maxAge = 10;

public:
    using Animal::Animal;

    void move() override
    {
        this->changeCoord(1);
        Animal::move();
    }
};
