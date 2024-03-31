#include <pythonlib/snake.h>
#include <SFML/Graphics.hpp>
#include <ctime>

using namespace sf;
using namespace std;

void ChangeDirection(direction &dir, direction previousDir);
void drawSnake(RenderWindow &window, vector<Snake> snakePositions, Sprite snake, direction dir);
void drawMenu(RenderWindow &window);
void drawGameOver(RenderWindow &window, unsigned int currentScore, unsigned int bestScore);

Font font;
RectangleShape deathBlock, menuBlock;
Text deathMessage, menuMessage;
const unsigned int winSizeX = 620, winSizeY = 660, segmentSize = 40;
const float fieldW = 600, margin = (winSizeX - fieldW) / 2,
menuBlockW = 350, menuBlockH = 120, deathBlockW = 400, deathBlockH = 300;

int main() {

    unsigned score = 0, bestScore;
    srand(time(nullptr));

    FILE *in = fopen("local/BestScore.dat", "rb");
    if (in) {
        fread(&bestScore, sizeof(unsigned int), 1, in);
        fclose(in);
    }
    else
        bestScore = 0;

    RenderWindow window(VideoMode(winSizeX, winSizeY), "Python");
    window.setFramerateLimit(60);
    Image winIcon;
    if (!winIcon.loadFromFile("src/image/icon.png"))
        return 30;
    winIcon.setPixel(0, 0, {0,0,0});
    window.setIcon(512, 512, winIcon.getPixelsPtr());

    deathBlock.setSize({deathBlockW, deathBlockH});
    deathBlock.setPosition((winSizeX - deathBlockW) / 2, (winSizeY - deathBlockH) / 2);
    deathBlock.setFillColor({70, 102, 16});
    deathBlock.setOutlineThickness(5);
    deathMessage.setFont(font);
    deathMessage.setPosition((winSizeX - deathBlockW) / 2 + 25, (winSizeY - deathBlockH) / 2 + 50);
    deathMessage.setCharacterSize(38);

    menuBlock.setSize({menuBlockW, menuBlockH});
    menuBlock.setPosition((winSizeX - menuBlockW) / 2, 70);
    menuBlock.setFillColor({70, 102, 16});
    menuBlock.setOutlineThickness(5);

    menuMessage.setFont(font);
    menuMessage.setPosition((winSizeX - menuBlockW) / 2 + 25, 80);

    Texture snakeTexture;
    if (!snakeTexture.loadFromFile("src/image/SnakeSprite.png"))
        return 30;
    Sprite snake(snakeTexture);

    Texture appleTexture;
    if (!appleTexture.loadFromFile("src/image/apple.png"))
        return 30;
    Sprite apple(appleTexture);
    apple.setTextureRect(IntRect(0, 0,segmentSize, segmentSize));

    Texture fieldTexture;
    if (!fieldTexture.loadFromFile("src/image/field.png"))
        return 30;
    RectangleShape gameField({fieldW, fieldW});
    gameField.setTexture(&fieldTexture);
    gameField.setPosition(margin, margin);
    gameField.setOutlineThickness(2);

    direction dir = RIGHT, previousDir = RIGHT;
    vector<Snake> startPosition = {{3, 7}, {2, 7}, {1, 7}, {0, 7}};
    auto snakePositions = startPosition;
    Apple applePosition = spawnApple(snakePositions);

    font.loadFromFile("src/font/ScoreFont.otf");
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(38);
    scoreText.setPosition((float) winSizeX / 2 - 90, fieldW + margin);

    Clock clock;
    float timer = 0;
    const float delay = 0.15;

    bool gameIsRunning = true, gameStarted = false;

    while (window.isOpen())
    {
        Event event{};
        while (window.pollEvent(event))
        {
            if  (event.type == Event::Closed ||
                (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Q))) {
                window.close();
            }
        }

        window.clear({70, 102, 16});
        window.draw(gameField);

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        if (gameStarted && gameIsRunning){
            ChangeDirection(dir, previousDir);
            scoreText.setString( "Score: " + to_string(score));
            if(timer >= delay) {
                timer = 0;
                snakeMove(snakePositions, dir);
                previousDir = dir;
                if (isSnakeCrashed(snakePositions)){
                    gameIsRunning = false;
                    if (score > bestScore)
                        bestScore = score;
                }
                if (isSnakeEatApple(snakePositions, applePosition)) {
                    addSegment(snakePositions);
                    if (snakePositions.size() != 15 * 15)
                        applePosition = spawnApple(snakePositions);
                    score++;
                }
            }
        }

        if (gameIsRunning){
            drawSnake(window, snakePositions, snake, dir);
            window.draw(scoreText);
            apple.setPosition((float) applePosition.x * segmentSize + margin,
                              (float) applePosition.y * segmentSize + margin);
            window.draw(apple);
        }
        else {
            drawGameOver(window, score, bestScore);
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                gameIsRunning = true;
                score = 0;
                dir = RIGHT;
                snakePositions = startPosition;
                applePosition = spawnApple(snakePositions);
            }
        }

        if (!gameStarted){
            drawMenu(window);
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                gameStarted = true;
            }
        }

        window.display();
    }
    FILE *out = fopen("local/BestScore.dat", "wb");
    fwrite(&bestScore, sizeof(unsigned int), 1, out);
    fclose(out);
    return 0;
}

void ChangeDirection(direction &dir, direction previousDir) {
    if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
        && previousDir != RIGHT)
        dir = LEFT;
    else if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
            && previousDir != LEFT)
        dir = RIGHT;
    else if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
            && previousDir != DOWN)
        dir = UP;
    else if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
            && previousDir != UP)
        dir = DOWN;
}

void drawMenu(RenderWindow &window){
    window.draw(menuBlock);
    menuMessage.setCharacterSize(30);
    menuMessage.setString("\tPYTHON GAME");
    window.draw(menuMessage);
    menuMessage.setCharacterSize(20);
    menuMessage.setString("\n\n\n\t press Enter to start");
    window.draw(menuMessage);
}

void drawGameOver(RenderWindow &window, unsigned int currentScore, unsigned int bestScore){
    deathMessage.setString("    GAME OVER\n\nYour score: " + to_string(currentScore) + "\n\nBest  score: " + to_string(bestScore));
    window.draw(deathBlock);
    window.draw(deathMessage);
}

void drawSnake(RenderWindow &window, vector<Snake> snakePositions, Sprite snake, direction dir){
    for (int i = (int) snakePositions.size() - 1; i >= 0; i--){
        if (i == 0) {
            snake.setTextureRect(IntRect((int) (dir * segmentSize), segmentSize,
                                         segmentSize, segmentSize));
        }
        else {
            snake.setTextureRect(IntRect(0, 0, 40, 40));
        }
        snake.setPosition((float) snakePositions[i].x * segmentSize + margin,
                          (float) snakePositions[i].y * segmentSize + margin);
        window.draw(snake);
    }
}
