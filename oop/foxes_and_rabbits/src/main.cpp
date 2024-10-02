#include <Model.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>

Model setModel(std::string filename);

int main(int argc, char *argv[])
{
    std::string filename;
    if (argc == 1)
        filename = "input.txt";
    else
        filename = argv[1];

    unsigned N, M, moves;
    vector<Rabbit> rabbits;
    vector<Fox> foxes;
    Model model = setModel(filename);

    while (model.getMoves() != 0)
    {
        model.print();
        model.move();
    }

    return 0;
}

Model setModel(std::string filename)
{
    std::ifstream input(filename);

    unsigned R, F, stabilityBuf, dirBuf, N, M, moves;
    int xBuf, yBuf;
    vector<Rabbit> rabbits;
    vector<Fox> foxes;

    input >>
        N >> M >> moves >> R >> F;

    for (int i = 0; i < R; i++)
    {
        input >> xBuf >> yBuf >> dirBuf >> stabilityBuf;
        rabbits.push_back(Rabbit({xBuf, yBuf}, (Direction)dirBuf, stabilityBuf));
    }
    for (int i = 0; i < F; i++)
    {
        input >> xBuf >> yBuf >> dirBuf >> stabilityBuf;
        foxes.push_back(Fox({xBuf, yBuf}, (Direction)dirBuf, stabilityBuf));
    }
    Model model(N, M, moves);
    model.setAnimals(rabbits, foxes);
    return model;
}
