#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "sorts.h"

using namespace sf;

extern int M, C;

int T_fact[4];

void SortIntensives(int);

int main()
{
    srand(time(NULL));
    float winSizeX = 800, winSizeY = 400;
    int dy = (winSizeY - 20) / 7, dx = (winSizeX - 20) / 5;
    RenderWindow window(VideoMode(winSizeX, winSizeY), L"Трудоемкость квадратичных методов сортировки");

    Image icon;
    if (!icon.loadFromFile("icon.png"))
    {
        return 35;
    }
    window.setIcon(256, 256, icon.getPixelsPtr());

    Font font;
    if (!font.loadFromFile("futurabookc.ttf"))
    {
        return -1;
    }

    Text text[31];
    for (int i = 0; i < 31; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(24);
        text[i].setFillColor(Color::Black);
    }
    for (int i = 6, N = 100; N <= 500; N += 100, i += 5)
    {
        SortIntensives(N);
        text[i].setPosition(15, 20 + dy * (N / 100 + 1));
        text[i].setString(std::to_string(N));
        for (int j = 0; j < 4; j++)
        {
            text[i + j + 1].setPosition(15 + dx * (1 + j), 20 + dy * (N / 100 + 1));
            text[i + j + 1].setString(std::to_string(T_fact[j]));
        }
    }

    RectangleShape table(Vector2f(winSizeX - 20, winSizeY - 20));
    table.setPosition(10, 10);
    table.setOutlineThickness(1);
    table.setOutlineColor(Color::Black);

    VertexArray lines(Lines, 28);
    for (int i = 0; i < 28; i++)
        lines[i].color = Color::Black;
    // rows
    for (int i = 0, y = 10 + dy; i < 12; i += 2, y += dy)
    {
        lines[i].position = Vector2f(10, y);
        lines[i + 1].position = Vector2f(winSizeX - 10, y);
    }
    // columns
    for (int i = 12, x = 10 + dx; i < 20; i += 2, x += dx)
    {
        lines[i].position = Vector2f(x, 10);
        lines[i + 1].position = Vector2f(x, winSizeY - 10);
    }

    // // header
    lines[0].position = Vector2f(10 + dx, 10 + dy);
    lines[14].position = Vector2f(10 + 2 * dx, 10 + dy);
    lines[16].position = Vector2f(10 + 3 * dx, 10 + dy);
    lines[18].position = Vector2f(10 + 4 * dx, 10 + dy);
    text[0].setPosition(15, 20);
    text[0].setString("N");
    text[1].setPosition(15 + dx, 20 + dy);
    text[1].setString(L"Select");
    text[2].setPosition(15 + dx * 2.5, 20);
    text[2].setString(L"M+C факт.");
    text[3].setPosition(15 + dx * 2, 20 + dy);
    text[3].setString(L"Bubble");
    text[4].setPosition(15 + dx * 3, 20 + dy);
    text[4].setString(L"Shaker");
    text[5].setPosition(15 + dx * 4, 20 + dy);
    text[5].setString(L"Insert");

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
        for (int i = 0; i < 31; i++)
            window.draw(text[i]);
        window.display();
    }

    return 0;
}

void SortIntensives(int n)
{
    int *Select = new int[n];
    int *Bubble = new int[n];
    int *Shaker = new int[n];
    int *Insert = new int[n];
    for (int i = 0; i < n; i++)
    {
        Select[i] = rand();
        Bubble[i] = Select[i];
        Shaker[i] = Select[i];
        Insert[i] = Select[i];
    }
    SelectSort(Select, n);
    T_fact[0] = M + C;
    BubbleSort(Bubble, n);
    T_fact[1] = M + C;
    ShakerSort(Shaker, n);
    T_fact[2] = M + C;
    InsertSort(Insert, n);
    T_fact[3] = M + C;
}
