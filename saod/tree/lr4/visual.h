#include "tree.h"
#include <SFML/Graphics.hpp>
#include <cmath>

void drawVertex(sf::RenderWindow &win, Vertex *p, int L, int R, int h);
void drawTree(Vertex *);

sf::Font font;
sf::Text text;
sf::VertexArray lines(sf::Lines, 2);

void drawTree(Vertex *root)
{
    font.loadFromFile("futurabookc.ttf");
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    lines[0].color = sf::Color::Black;
    lines[1].color = sf::Color::Black;
    int h = height(root);
    int k;
    if (h < 6)
        k = 40;
    else if (h > 6)
    {
        text.setCharacterSize(10);
        k = 3;
    }
    else
        k = 20;
    int winSizeY = (h + 1) * 100, winSizeX = pow(2, h) * k;
    sf::RenderWindow window(sf::VideoMode(winSizeX, winSizeY), L"Дерево");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            window.clear(sf::Color::White);
            drawVertex(window, root, 0, winSizeX, 0);
            window.display();
        }
    }
}

void drawVertex(sf::RenderWindow &win, Vertex *p, int L, int R, int h)
{
    int x = (R + L) / 2;
    int y = 85 + 100 * h;
    std::string strData = std::to_string(p->Data);
    text.setPosition(x - 7 * strData.length(), y - 14);
    text.setString(strData);
    win.draw(text);
    if (p->Left != nullptr)
    {
        int xl = (L + x) / 2;
        lines[0].position = sf::Vector2f(x, y + 20);
        lines[1].position = sf::Vector2f(xl, y + 80);
        win.draw(lines);
        drawVertex(win, p->Left, L, x, h + 1);
    }
    if (p->Right != nullptr)
    {
        int xr = (x + R) / 2;
        lines[0].position = sf::Vector2f(x, y + 20);
        lines[1].position = sf::Vector2f(xr, y + 80);
        win.draw(lines);
        drawVertex(win, p->Right, x, R, h + 1);
    }
}
