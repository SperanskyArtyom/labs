#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "service_procedures.h"
#include "sorts.h"

using namespace sf;
using namespace std;

extern int M, C;

int T_fact[3];

void SortIntensives(int[], int);
string Theoretical_T(int n)
{
    float T = (float)(n * n + 4 * n - 5) / 2;
    string s = to_string(T);

    if (s[s.size() - 1] == '0')
        for (size_t i = s.size() - 1; s[i] == '0'; i--)
            s.erase(i, 1);

    if (s[s.size() - 1] == '.')
        s.erase(s.size() - 1, 1);
    return s;
}

int main()
{
    srand(time(NULL));
    int *A;
    float winSizeX = 800, winSizeY = 400;
    int dy = (winSizeY - 20) / 7, dx = (winSizeX - 20) / 5;
    RenderWindow window(VideoMode(winSizeX, winSizeY), L"Трудоемкость метода прямого включения InsertSort");

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
        A = (int *)malloc(N * sizeof(int));
        SortIntensives(A, N);
        text[i].setPosition(15, 20 + dy * (N / 100 + 1));
        text[i].setString(std::to_string(N));
        text[i + 1].setPosition(15 + dx, 20 + dy * (N / 100 + 1));
        text[i + 1].setString(Theoretical_T(N));
        for (int j = 0; j < 3; j++)
        {
            text[i + j + 2].setPosition(15 + dx * (2 + j), 20 + dy * (N / 100 + 1));
            text[i + j + 2].setString(std::to_string(T_fact[j]));
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
    lines[0].position = Vector2f(10 + 2 * dx, 10 + dy);
    lines[16].position = Vector2f(10 + 3 * dx, 10 + dy);
    lines[18].position = Vector2f(10 + 4 * dx, 10 + dy);
    text[0].setPosition(15, 20);
    text[0].setString("N");
    text[1].setPosition(15 + dx, 20);
    text[1].setString(L"M + C\nтеоретич.");
    text[2].setPosition(15 + dx * 3, 20);
    text[2].setString(L"M+C факт.");
    text[3].setPosition(15 + dx * 2, 20 + dy);
    text[3].setString(L"Убыв.");
    text[4].setPosition(15 + dx * 3, 20 + dy);
    text[4].setString(L"Случ.");
    text[5].setPosition(15 + dx * 4, 20 + dy);
    text[5].setString(L"Возвр.");

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

void SortIntensives(int arr[], int n)
{
    FillDec(arr, n);
    InsertSort(arr, n);
    T_fact[0] = M + C;
    FillRand(arr, n);
    InsertSort(arr, n);
    T_fact[1] = M + C;
    FillInc(arr, n);
    InsertSort(arr, n);
    T_fact[2] = M + C;
}
