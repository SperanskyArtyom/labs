#pragma once

#include <Rabbit.h>
#include <Fox.h>
#include <vector>
#include <iostream>

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

    void clearField()
    {
        for (int i = 0; i < sizeY; i++)
        {
            field[i] = new int[sizeX];
            for (int j = 0; j < sizeX; j++)
                field[i][j] = 0;
        }
    }

    void createField()
    {
        field = new int *[sizeY];
        clearField();
    }

    void updateField()
    {
        clearField();
        for (auto rabbit : rabbits)
            field[rabbit.coordinate.y][rabbit.coordinate.x]++;
        for (auto fox : foxes)
            field[fox.coordinate.y][fox.coordinate.x]--;
    }

    void addAnimal(Rabbit rabbit)
    {
        rabbits.push_back(rabbit);
        field[rabbit.coordinate.y][rabbit.coordinate.x] += 1;
    }

    void addAnimal(Fox fox)
    {
        foxes.push_back(fox);
        field[fox.coordinate.y][fox.coordinate.x] -= 1;
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

    void checkCoordinate(Animal &animal)
    {
        if (animal.coordinate.x < 0)
            animal.coordinate.x = sizeX - animal.coordinate.x;
        else if (animal.coordinate.x >= sizeX)
            animal.coordinate.x = animal.coordinate.x - sizeX;
        else if (animal.coordinate.y < 0)
            animal.coordinate.y = sizeY - animal.coordinate.y;
        else if (animal.coordinate.y >= sizeY)
            animal.coordinate.y = animal.coordinate.y - sizeY;
    }

    bool isElder(Fox a, Fox b)
    {
        if (a.age > b.age)
            return true;
        if (a.age < b.age)
            return false;
        if (a.getParentsAge() > b.getParentsAge())
            return true;
        if (a.getParentsAge() < b.getParentsAge())
            return false;
        return true;
    }

public:
    Model(int N, int M, unsigned moves) : sizeX{N}, sizeY{M}
    {
        movesCount = moves;
        createField();
    }
    Model(const Model &model) : Model(model.sizeX, model.sizeY, model.movesCount) {}

    void setAnimals(vector<Rabbit> rabbits, vector<Fox> foxes)
    {
        setRabbits(rabbits);
        setFoxes(foxes);
    }

    void print() const
    {
        for (int i = 0; i < sizeY; i++)
        {
            for (int j = 0; j < sizeX; j++)
            {
                if (field[i][j] == 0)
                    std::cout << '*';
                else
                    std::cout << field[i][j];
                std::cout << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void move()
    {
        for (auto &rabbit : rabbits)
        {
            rabbit.move();
            checkCoordinate(rabbit);
        }
        for (auto &fox : foxes)
        {
            fox.move();
            checkCoordinate(fox);
        }
        updateField();
        movesCount--;
    }

    unsigned getMoves() const { return movesCount; }
};
