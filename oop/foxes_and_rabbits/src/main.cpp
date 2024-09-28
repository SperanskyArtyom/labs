#include <Model.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>

void initialData(std::string, unsigned &, unsigned &, unsigned &, vector<Rabbit> &, vector<Fox> &);

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
    initialData(filename, N, M, moves, rabbits, foxes);

    Model model(N, M, moves);
    model.setAnimals(rabbits, foxes);

    return 0;
}

void initialData(std::string filename, unsigned &N, unsigned &M, unsigned &moves, vector<Rabbit> &rabbits, vector<Fox> &foxes)
{
    std::ifstream input(filename);

    unsigned R, F, stabilityBuf, dirBuf;
    int xBuf, yBuf;

    input >> N >> M >> moves >> R >> F;

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
}
