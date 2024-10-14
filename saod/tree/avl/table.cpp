#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "tree.h"

// using namespace sf;
using namespace std;

int comp1(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

string fToStr(double n)
{
    string s = to_string(n);

    // if (s[s.size() - 1] == '0')
    //     for (size_t i = s.size() - 1; s[i] == '0'; i--)
    //         s.erase(i, 1);

    // if (s[s.size() - 1] == '.')
    //     s.erase(s.size() - 1, 1);
    size_t i = 0;
    while (s[i] != '.')
        i++;
    i += 3;
    s.erase(i, s.size() - i);
    return s;
}

int main()
{
    srand(time(NULL));
    int A[100], sortedA[100];
    float winSizeX = 1000, winSizeY = 200;
    const int rows = 3, columns = 5;
    int dy = (winSizeY - 20) / rows, dx = (winSizeX - 20) / columns;

    sf::Font font;
    if (!font.loadFromFile("futurabookc.ttf"))
        return -1;

    const size_t textCount = rows * columns;
    sf::Text text[textCount];
    for (int i = 0; i < textCount; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(24);
        text[i].setFillColor(sf::Color::Black);
    }

    for (int i = 0; i < 100; i++)
    {
        A[i] = rand();
        sortedA[i] = A[i];
    }
    qsort(sortedA, 100, sizeof(int), comp1);

    auto ISDP = createISDP(sortedA, 0, 99);
    auto AVL = createAVL(A, 100);

    Vertex *trees[2] = {ISDP, AVL};
    for (int i = 0; i < 2; i++)
    {
        text[5 + 4 * i].setPosition(15 + dx, 20 + dy * (1 + i));
        text[5 + 4 * i].setString(to_string(size(trees[i])));
        text[6 + 4 * i].setPosition(15 + 2 * dx, 20 + dy * (1 + i));
        text[6 + 4 * i].setString(to_string(summary(trees[i])));
        text[7 + 4 * i].setPosition(15 + 3 * dx, 20 + dy * (1 + i));
        text[7 + 4 * i].setString(to_string(height(trees[i])));
        text[8 + 4 * i].setPosition(15 + 4 * dx, 20 + dy * (1 + i));
        text[8 + 4 * i].setString(fToStr(avgHeight(trees[i])));
    }

    sf::RectangleShape table(sf::Vector2f(winSizeX - 20, winSizeY - 20));
    table.setPosition(10, 10);
    table.setOutlineThickness(1);
    table.setOutlineColor(sf::Color::Black);

    const int linesCount = ((rows - 1) + (columns - 1)) * 2;
    sf::VertexArray lines(sf::Lines, linesCount);
    for (int i = 0; i < linesCount; i++)
        lines[i].color = sf::Color::Black;
    // rows
    for (int i = 0, y = 10 + dy; i < 2 * (rows - 1); i += 2, y += dy)
    {
        lines[i].position = sf::Vector2f(10, y);
        lines[i + 1].position = sf::Vector2f(winSizeX - 10, y);
    }
    // columns
    for (int i = 2 * (rows - 1), x = 10 + dx; i < linesCount; i += 2, x += dx)
    {
        lines[i].position = sf::Vector2f(x, 10);
        lines[i + 1].position = sf::Vector2f(x, winSizeY - 10);
    }

    text[0].setPosition(15, 20);
    text[0].setString("n = 100");
    text[1].setPosition(15 + dx, 20);
    text[1].setString(L"Размер");
    text[2].setPosition(15 + dx * 2, 20);
    text[2].setString(L"Контр. сумма");
    text[3].setPosition(15 + dx * 3, 20);
    text[3].setString(L"Высота");
    text[4].setPosition(15 + dx * 4, 20);
    text[4].setString(L"Средн. высота");

    // 13, 14
    text[13].setPosition(15, 20 + dy);
    text[13].setString(L"ИСДП");
    text[14].setPosition(15, 20 + 2 * dy);
    text[14].setString(L"АВЛ");

    sf::RenderWindow window(sf::VideoMode(winSizeX, winSizeY), L"АВЛ");
    window.clear(sf::Color::White);
    window.draw(table);
    window.draw(lines);
    for (int i = 0; i < textCount; i++)
        window.draw(text[i]);
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    return 0;
}
