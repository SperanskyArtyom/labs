#include "snake.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

void ChangeDirection(direction &dir);

int main() {
    unsigned int winSizeX = 620, winSizeY = 620;
    RenderWindow window(VideoMode(winSizeX, winSizeY), "Python");
    Image winIcon;
    if (!winIcon.loadFromFile("src/image/icon.png")) {
        return 30;
    }
    window.setIcon(512, 512, winIcon.getPixelsPtr());
    Texture snakeTexture;
    snakeTexture.loadFromFile("src/image/SnakeSprite.png");
    Sprite snake(snakeTexture);
    RectangleShape gamaField;
    float fieldWidth = 600;
    gamaField.setSize({fieldWidth, fieldWidth});
    gamaField.setPosition(((float) winSizeX - fieldWidth) / 2, ((float) winSizeY - fieldWidth) / 2);
    gamaField.setFillColor({173, 255, 47});
    RectangleShape segment;
    segment.setSize({40, 40});
    segment.setPosition(10, 10);
    segment.setFillColor(Color::White);
    direction dir = RIGHT;
    auto snakePositions = spawnSnake();
    Clock clock;
    float timer = 0, delay = 0.15;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        ChangeDirection(dir);
        window.clear({70, 102, 16});
        window.draw(gamaField);
        if(timer >= delay) {
            timer = 0;
            snakeMove(snakePositions, dir);
            if (isSnakeCrashed(snakePositions)){
                window.close();
                cout << "Game Over";
                return 0;
            }
        }
        for (int i = 0; i < snakePositions.size(); i++){
            if (i == 0) {
                snake.setTextureRect(IntRect(dir * 40, 40, 40, 40));
            }
            else {
                snake.setTextureRect(IntRect(0, 0, 40, 40));
            }
            snake.setPosition((float) snakePositions[i].x * 40 + 10, (float) snakePositions[i].y * 40 + 10);
            window.draw(snake);
        }
        snake.setTextureRect(IntRect(dir * 40, 41, 40, 40));
        window.display();
    }
    return 0;
}

void ChangeDirection(direction &dir){
    if (Keyboard::isKeyPressed(Keyboard::Left))
        dir = LEFT;
    else if(Keyboard::isKeyPressed(Keyboard::Right))
        dir = RIGHT;
    else if(Keyboard::isKeyPressed(Keyboard::Up))
        dir = UP;
    else if(Keyboard::isKeyPressed(Keyboard::Down))
        dir = DOWN;
}