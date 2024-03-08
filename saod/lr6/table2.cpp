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

int Params[4];
void SortIntensives(int[], int);

int main()
{
    srand(time(NULL));
    int *A;
    float winSizeX = 900, winSizeY = 350;
    int dy = (winSizeY - 20) / 6, dx = (winSizeX - 20) / 5;
    RenderWindow window(VideoMode(winSizeX, winSizeY), L"Трудоемкость метода Шелла");

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

    Text text[30];
    for (int i = 0; i < 30; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(20);
        text[i].setFillColor(Color::Black);
    }
    for (int i = 5, N = 100; N <= 500; N += 100, i += 5)
    {
        A = (int *)malloc(N * sizeof(int));
        SortIntensives(A, N);
        text[i].setPosition(15 + dx/3, 20 + dy * (N / 100));
        text[i].setString(std::to_string(N));
        for (int j = 0; j < 4; j++)
        {
            text[i + j + 1].setPosition(15 + dx * (1 + j), 20 + dy * (N / 100));
            text[i + j + 1].setString(std::to_string(Params[j]));
        }
    }

    RectangleShape table(Vector2f(winSizeX - 20, winSizeY - 20));
    table.setPosition(10, 10);
    table.setOutlineThickness(1);
    table.setOutlineColor(Color::Black);

    VertexArray lines(Lines, 18);
    for (int i = 0; i < 18; i++)
        lines[i].color = Color::Black;
    // rows
    for (int i = 0, y = 10 + dy; i < 10; i += 2, y += dy)
    {
        lines[i].position = Vector2f(10, y);
        lines[i + 1].position = Vector2f(winSizeX - 10, y);
    }
    // columns
    for (int i = 10, x = 10 + dx; i < 18; i += 2, x += dx)
    {
        lines[i].position = Vector2f(x, 10);
        lines[i + 1].position = Vector2f(x, winSizeY - 10);
    }

    // // header
    text[0].setPosition(5 + dx/2,  20);
    text[0].setString("n");
    text[1].setPosition(15 + dx, 15);
    text[1].setString(L"     Кол-во К-сорт.\n     по ф-ле Кнута");
    text[2].setPosition(15 + dx * 2, 20);
    text[2].setString(L"\t\tShell M+C");
    text[3].setPosition(10 + dx * 3, 15);
    text[3].setString(L"      Кол-во К-сорт.\n  по ф-ле Седжвика");
    text[4].setPosition(15 + dx * 4, 20);
    text[4].setString(L"\t\tShell M+C");
    for (int i = 1; i <= 5; i++)
    {
        text[5 * i + 1].setPosition(dx + dx/2, 20 + dy * i);
        text[5 * i + 3].setPosition(3*dx + dx/2, 20 + dy * i);
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
        for (int i = 0; i < 30; i++)
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
    int H[m];
    KnuthSequence(H, n);
    ShellSort(arr, n, H, m);
    Params[1] = C+M;
    m = sejsize(n);
    Params[2] = m;
    int H2[m];
    SedgewickSequence(H2, m);
    ShellSort(arr2, n, H2, m);
    Params[3] = C+M;
}
