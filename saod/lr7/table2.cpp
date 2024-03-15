#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "sorts.h"

using namespace sf;
using namespace std;

extern int M, C;

int Params[2];
void SortIntensives(int[], int);

int main()
{
    srand(time(NULL));
    int *A;
    float winSizeX = 600, winSizeY = 800;
    int dy = (winSizeY - 20) / 11, dx = (winSizeX - 20) / 3;
    RenderWindow window(VideoMode(winSizeX, winSizeY), L"Трудоемкость двоичного поиска всех элементов");

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

    Text text[33];
    for (auto & i : text)
    {
        i.setFont(font);
        i.setCharacterSize(24);
        i.setFillColor(Color::Black);
    }
    for (int i = 3, N = 100; N <= 1000; N += 100, i += 3)
    {
        A = (int *)malloc(N * sizeof(int));
        SortIntensives(A, N);
        text[i].setPosition(15 + dx/3, 30 + dy * (N / 100));
        text[i].setString(std::to_string(N));
        for (int j = 0; j < 2; j++)
        {
            text[i + j + 1].setPosition(15 + dx * (1 + j) + dx/2 - 20, 30 + dy * (N / 100));
            text[i + j + 1].setString(std::to_string(Params[j]));
        }
    }

    RectangleShape table(Vector2f(winSizeX - 20, winSizeY - 20));
    table.setPosition(10, 10);
    table.setOutlineThickness(1);
    table.setOutlineColor(Color::Black);

    VertexArray lines(Lines, 24);
    for (int i = 0; i < 24; i++)
        lines[i].color = Color::Black;
    // rows
    for (int i = 0, y = 10 + dy; i < 20; i += 2, y += dy)
    {
        lines[i].position = Vector2f(10, y);
        lines[i + 1].position = Vector2f(winSizeX - 10, y);
    }
    // columns
    for (int i = 20, x = 10 + dx; i < 24; i += 2, x += dx)
    {
        lines[i].position = Vector2f(x, 10);
        lines[i + 1].position = Vector2f(x, winSizeY - 10);
    }

    // // header
    text[0].setPosition(5 + dx/2,  30);
    text[0].setString("n");
    text[1].setPosition(30 + dx, 30);
    text[1].setString(L"Cф All I версия");
    text[2].setPosition(30 + dx * 2, 30);
    text[2].setString(L"Сф All II версия");

    text[30].setPosition(15 + dx/3 - 7, 30 + dy * 10);

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
        for (int i = 0; i < 33; i++)
            window.draw(text[i]);
        window.display();
    }

    return 0;
}

void SortIntensives(int arr[], int n)
{
    FillRand(arr, n);
    InsertSort(arr, n);
//    int key = rand() % n;
    int key = 0;
    BSearchAll1(arr, n, arr[key]);
    Params[0] = C;
    BSearchAll2(arr, n, arr[key]);
    Params[1] = C;
}
