#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "service_procedures.h"
#include "QuickSort.h"

using namespace sf;
using namespace std;

extern int M, C;

int T_fact[3];

void SortIntensives(int[], int);

int main()
{
    srand(time(NULL));
    int *A;
    float winSizeX = 800, winSizeY = 400;
    const int rows = 7, columns = 4;
    int dy = (winSizeY - 20) / rows, dx = (winSizeX - 20) / columns;
    RenderWindow window(VideoMode(winSizeX, winSizeY), L"Трудоемкость метода Хоара");

    Font font;
    if (!font.loadFromFile("futurabookc.ttf"))
    {
        return -1;
    }

    const size_t textCount = 25;
    Text text[textCount];
    for (int i = 0; i < textCount; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(24);
        text[i].setFillColor(Color::Black);
    }

    for (int i = 5, N = 100; N <= 500; N += 100, i += 4)
    {
        A = (int *)malloc(N * sizeof(int));
        SortIntensives(A, N);
        text[i].setPosition(15, 20 + dy * (N / 100 + 1));
        text[i].setString(std::to_string(N));
        for (int j = 0; j < 3; j++)
        {
            text[i + j + 1].setPosition(15 + dx * (1 + j), 20 + dy * (N / 100 + 1));
            text[i + j + 1].setString(std::to_string(T_fact[j]));
        }
    }

    RectangleShape table(Vector2f(winSizeX - 20, winSizeY - 20));
    table.setPosition(10, 10);
    table.setOutlineThickness(1);
    table.setOutlineColor(Color::Black);

    const int linesCount = (rows - 1) + (columns) - 1;
    VertexArray lines(Lines, 2 * linesCount);
    for (int i = 0; i < linesCount * 2; i++)
        lines[i].color = Color::Black;
    // rows
    for (int i = 0, y = 10 + dy; i < 2 * (rows - 1); i += 2, y += dy)
    {
        lines[i].position = Vector2f(10, y);
        lines[i + 1].position = Vector2f(winSizeX - 10, y);
    }
    // columns
    for (int i = 12, x = 10 + dx; i < (linesCount * 2) - 1; i += 2, x += dx)
    {
        lines[i].position = Vector2f(x, 10);
        lines[i + 1].position = Vector2f(x, winSizeY - 10);
    }

    // // header
    lines[0].position = Vector2f(10 + 1 * dx, 10 + dy);
    lines[14].position = Vector2f(10 + 2 * dx, 10 + dy);
    lines[16].position = Vector2f(10 + 3 * dx, 10 + dy);
    text[0].setPosition(15, 20);
    text[0].setString("N");
    text[1].setPosition(15 + dx * 2, 20);
    text[1].setString(L"QuickSort (Mф + Cф)");
    text[2].setPosition(15 + dx, 20 + dy);
    text[2].setString(L"Убыв.");
    text[3].setPosition(15 + dx * 2, 20 + dy);
    text[3].setString(L"Случ.");
    text[4].setPosition(15 + dx * 3, 20 + dy);
    text[4].setString(L"Возвр.");

    window.clear(Color::White);
    window.draw(table);
    window.draw(lines);
    for (int i = 0; i < textCount; i++)
        window.draw(text[i]);
    window.display();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

    }

    return 0;
}

void SortIntensives(int arr[], int n)
{
    FillDec(arr, n);
    M = C = 0;
    QuickSort(arr, 0, n - 1);
    T_fact[0] = M + C;
    FillRand(arr, n);
    M = C = 0;
    QuickSort(arr, 0, n - 1);
    T_fact[1] = M + C;
    FillInc(arr, n);
    M = C = 0;
    QuickSort(arr, 0, n - 1);
    T_fact[2] = M + C;
}
