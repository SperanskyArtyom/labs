#pragma once

#include <Animal.h>

class Fox : public Animal
{
private:
    const static inline unsigned maxAge = 15;
    unsigned parentsAge = 0;

public:
    using Animal::Animal;
    Fox(const Fox &parent) : Animal(parent) { parentsAge = parent.getAge(); }

    void move() override
    {
        changeCoord(2);
        Animal::move();
    }

    unsigned getParentsAge() { return parentsAge; }
};
