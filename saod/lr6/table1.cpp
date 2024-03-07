#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "sorts.h"
#include <cmath>

using namespace sf;
using namespace std;

extern int M, C;

int Params[3];
void SortIntensives(int[], int);

int main()
{
    srand(time(NULL));
    int *A;
    float winSizeX = 800, winSizeY = 400;
    int dy = (winSizeY - 20) / 6, dx = (winSizeX - 20) / 4;
    RenderWindow window(VideoMode(winSizeX, winSizeY), L"Трудоемкость метода прямого включения InsertSort");

    Image icon;
    if (!icon.loadFromFile("source/icon.png"))
    {
        return 35;
    }
    window.setIcon(256, 256, icon.getPixelsPtr());

    Font font;
    if (!font.loadFromFile("source/futurabookc.ttf"))
    {
        return -1;
    }

    Text text[24];
    for (int i = 0; i < 24; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(24);
        text[i].setFillColor(Color::Black);
    }
    for (int i = 4, N = 100; N <= 500; N += 100, i += 4)
    {
        A = (int *)malloc(N * sizeof(int));
        SortIntensives(A, N);
        text[i].setPosition(15 + dx/3, 20 + dy * (N / 100));
        text[i].setString(std::to_string(N));
        for (int j = 0; j < 3; j++)
        {
            text[i + j + 1].setPosition(15 + dx * (1 + j), 20 + dy * (N / 100));
            text[i + j + 1].setString(std::to_string(Params[j]));
        }
    }

    RectangleShape table(Vector2f(winSizeX - 20, winSizeY - 20));
    table.setPosition(10, 10);
    table.setOutlineThickness(1);
    table.setOutlineColor(Color::Black);

    VertexArray lines(Lines, 16);
    for (int i = 0; i < 16; i++)
        lines[i].color = Color::Black;
    // rows
    for (int i = 0, y = 10 + dy; i < 10; i += 2, y += dy)
    {
        lines[i].position = Vector2f(10, y);
        lines[i + 1].position = Vector2f(winSizeX - 10, y);
    }
    // columns
    for (int i = 10, x = 10 + dx; i < 16; i += 2, x += dx)
    {
        lines[i].position = Vector2f(x, 10);
        lines[i + 1].position = Vector2f(x, winSizeY - 10);
    }

    // // header
    text[0].setPosition(5 + dx/2,  20);
    text[0].setString("n");
    text[1].setPosition(15 + dx, 10);
    text[1].setString(L"     Количество\n   К-сортировок");
    text[2].setPosition(15 + dx * 2, 20);
    text[2].setString(L"\t  Insert M+C");
    text[3].setPosition(15 + dx * 3, 20);
    text[3].setString(L"\t  Select M+C");
    for (int i = 1; i <= 5; i++)
    {
        text[4 * i + 1].setPosition(dx + dx/2, 20 + dy * i);
    }
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        window.draw(table);
        window.draw(lines);
        for (int i = 0; i < 24; i++)
            window.draw(text[i]);
        window.display();
    }

    return 0;
}

void SortIntensives(int arr[], int n)
{
    FillRand(arr, n);
    int arr2[n];
    for (int i = 0; i<n; i++)
        arr2[i] = arr[i];
    int m = (int)floor(std::log2(n)) - 1;
    Params[0] = m;
    InsertSort(arr, n);
    Params[1] = C+M;
    int H[m];
    KnuthSequence(H, n);
    ShellSort(arr2, n, H, m);
    Params[2] = C+M;
}
