#pragma once

#include <Animal.h>
#include <Rabbit.h>
#include <Fox.h>
#include <vector>

using std::vector;

class Model
{
private:
    const int sizeX;
    const int sizeY;
    unsigned movesCount;

    int **field;

    vector<Rabbit> rabbits;
    vector<Fox> foxes;

    void createField()
    {
        field = new int *[sizeY];
        for (int i = 0; i < sizeY; i++)
        {
            field[i] = new int[sizeX];
            for (int j = 0; j < sizeX; j++)
                field[i][j] = 0;
        }
    }

    void addAnimal(Rabbit rabbit)
    {
        rabbits.push_back(rabbit);
        field[rabbit.getCoordinate().x][rabbit.getCoordinate().y] += 1;
    }

    void addAnimal(Fox fox)
    {
        foxes.push_back(fox);
        field[fox.getCoordinate().x][fox.getCoordinate().y] -= 1;
    }

    void setRabbits(vector<Rabbit> rabbits)
    {
        for (auto rabbit : rabbits)
            addAnimal(rabbit);
    }

    void setFoxes(vector<Fox> foxes)
    {
        for (auto fox : foxes)
            addAnimal(fox);
    }

public:
    Model(int N, int M, unsigned moves) : sizeX{N}, sizeY{M}
    {
        this->movesCount = moves;
        this->createField();
    }

    void setAnimals(vector<Rabbit> rabbits, vector<Fox> foxes)
    {
        setRabbits(rabbits);
        setFoxes(foxes);
    }
};
