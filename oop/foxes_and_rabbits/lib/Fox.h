#pragma once

#include <Animal.h>

class Fox : public Animal
{
private:
    const unsigned maxAge = 15;

public:
    using Animal::Animal;

    void move() override
    {
        this->changeCoord(2);
        Animal::move();
    }
};
