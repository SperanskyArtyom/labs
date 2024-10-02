#pragma once

#include <Animal.h>

class Rabbit : public Animal
{
private:
    const static inline unsigned maxAge = 10;

public:
    using Animal::Animal;
    Rabbit(const Rabbit &rabbit) : Animal(rabbit) {}

    void move() override
    {
        changeCoord(1);
        Animal::move();
    }
};
