#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "service_procedures.h"
#include "QuickSort.h"

using namespace sf;
using namespace std;

extern int maxDepth;

int T_fact[6];

void SortIntensives(int[], int);

int main()
{
    srand(time(nullptr));
    int *A;
    int winSizeX = 800, winSizeY = 400;
    const int rows = 7, columns = 7;
    int dy = (winSizeY - 20) / rows, dx = (winSizeX - 20) / columns;
    RenderWindow window(VideoMode(winSizeX, winSizeY), L"Трудоемкость метода Хоара");

    Font font;
    if (!font.loadFromFile("futurabookc.ttf"))
    {
        return -1;
    }

    const size_t textCount = 44;
    Text text[textCount];
    for (auto & i : text)
    {
        i.setFont(font);
        i.setCharacterSize(24);
        i.setFillColor(Color::Black);
    }

    for (int i = 9, N = 100; N <= 500; N += 100, i += 7)
    {
        A = new int[N];
        SortIntensives(A, N);
        text[i].setPosition(15, 20 + dy * (N / 100 + 1));
        text[i].setString(std::to_string(N));
        for (int j = 0; j < 6; j++)
        {
            text[i + j + 1].setPosition(15 + dx * (1 + j), 20 + dy * (N / 100 + 1));
            text[i + j + 1].setString(std::to_string(T_fact[j]));
        }
        delete[] A;
    }

    RectangleShape table(Vector2f(winSizeX - 20, winSizeY - 20));
    table.setPosition(10, 10);
    table.setOutlineThickness(1);
    table.setOutlineColor(Color::Black);

    const int linesCount = (rows - 1) + (columns - 1);
    VertexArray lines(Lines, 2 * linesCount);
    for (int i = 0; i < 2 * linesCount; i++)
        lines[i].color = Color::Black;
    // rows
    for (int i = 0, y = 10 + dy; i < 2 * (rows - 1); i += 2, y += dy)
    {
        lines[i].position = Vector2f(10, y);
        lines[i + 1].position = Vector2f(winSizeX - 10, y);
    }
    // columns
    for (int i = 2 * (rows - 1), x = 10 + dx; i < 2 * linesCount; i += 2, x += dx)
    {
        lines[i].position = Vector2f(x, 10);
        lines[i + 1].position = Vector2f(x, winSizeY - 10);
    }

    // // header
    lines[0].position = Vector2f(10 + 1 * dx, 10 + dy);
    lines[14].position = Vector2f(10 + 2 * dx, 10 + dy);
    lines[16].position = Vector2f(10 + 3 * dx, 10 + dy);
    lines[20].position = Vector2f(10 + 5 * dx, 10 + dy);
    lines[22].position = Vector2f(10 + 6 * dx, 10 + dy);
    text[0].setPosition(15, 20);
    text[0].setString("N");
    text[1].setPosition(15 + dx * 2, 20);
    text[1].setString(L"QuickSort1");
    text[2].setPosition(15 + dx, 20 + dy);
    text[2].setString(L"Убыв.");
    text[3].setPosition(15 + dx * 2, 20 + dy);
    text[3].setString(L"Случ.");
    text[4].setPosition(15 + dx * 3, 20 + dy);
    text[4].setString(L"Возвр.");

    text[5].setPosition(15 + dx * 5, 20);
    text[5].setString(L"QuickSort2");
    text[6].setPosition(15 + dx * 4, 20 + dy);
    text[6].setString(L"Убыв.");
    text[7].setPosition(15 + dx * 5, 20 + dy);
    text[7].setString(L"Случ.");
    text[8].setPosition(15 + dx * 6, 20 + dy);
    text[8].setString(L"Возвр.");

    window.clear(Color::White);
    window.draw(table);
    window.draw(lines);
    for (const auto & i : text)
        window.draw(i);
    window.display();

    while (window.isOpen())
    {
        Event event{};
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
    int arr2[n];
    FillDec(arr, n);
    FillDec(arr2, n);
    maxDepth = 0;
    QuickSort(arr, 0, n - 1);
    T_fact[0] = maxDepth;
    FillRand(arr, n);
    for (int i = 0; i < n; i++)
        arr2[i] = arr[i];
    maxDepth = 0;
    QuickSort(arr, 0, n - 1);
    T_fact[1] = maxDepth;
    FillInc(arr, n);
    FillInc(arr2, n);
    maxDepth = 0;
    QuickSort(arr, 0, n - 1);
    T_fact[2] = maxDepth;

    maxDepth = 0;
    QuickSortV2(arr2, 0, n - 1);
    T_fact[3] = maxDepth;
    maxDepth = 0;
    QuickSortV2(arr2, 0, n - 1);
    T_fact[4] = maxDepth;
    maxDepth = 0;
    QuickSortV2(arr2, 0, n - 1);
    T_fact[5] = maxDepth;
}
