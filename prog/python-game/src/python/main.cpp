// Подключение заголовочных файлов и библиотек
#include <pythonlib/snake.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>

using namespace sf; // Используем пространство имён SFML для упрощения доступа к классам и функциям библиотеки
using std::vector, std::to_string;

// Объявление глобальных переменных
Font font;
RectangleShape deathBlock, menuBlock;
Text deathMessage, menuMessage;

// Объявление констант
const unsigned winSizeX = 620, winSizeY = 660, segmentSize = 40, fieldW = 600,
               menuBlockW = 350, menuBlockH = 120, deathBlockW = 400, deathBlockH = 300;
const float margin = (winSizeX - fieldW) / 2;

void ChangeDirection(direction &dir, direction previousDir);                                     // Функция для изменения направления движения змейки
void drawSnake(RenderWindow &window, vector<Snake> snakePositions, Sprite snake, direction dir); // Функция для отрисовки змейки
void drawMenu(RenderWindow &window);                                                             // Функция для отрисовки стартового меню
void drawGameOver(RenderWindow &window, unsigned currentScore, unsigned bestScore);              // Функция для отрисовки меню конца игры

int main()
{

    unsigned score = 0, bestScore;
    srand(time(nullptr)); // Задаём сид для генерации случайных чисел

    // Работа с бинарным файлом для чтения значения bestScore
    std::ifstream in("local/BestScore.dat", std::ios::binary);
    if (in.is_open())
        in.read((char *)&bestScore, sizeof(bestScore));
    else
        bestScore = 0;
    in.close();

    RenderWindow window(VideoMode(winSizeX, winSizeY), "Python"); // Объявляем окно программы
    window.setFramerateLimit(60);
    // Задаём иконку приложения
    Image winIcon;
    if (!winIcon.loadFromFile("src/image/icon.png"))
        return 30;
    winIcon.setPixel(0, 0, {0, 0, 0});
    window.setIcon(512, 512, winIcon.getPixelsPtr());

    // Задаём характеристики интерфейса меню конца игры
    deathBlock.setSize({deathBlockW, deathBlockH});
    deathBlock.setPosition((winSizeX - deathBlockW) / 2, (winSizeY - deathBlockH) / 2);
    deathBlock.setFillColor({70, 102, 16});
    deathBlock.setOutlineThickness(5);
    deathMessage.setFont(font);
    deathMessage.setPosition((winSizeX - deathBlockW) / 2 + 25, (winSizeY - deathBlockH) / 2 + 50);
    deathMessage.setCharacterSize(38);

    // Задаём характеристики интерфейса стартового меню
    menuBlock.setSize({menuBlockW, menuBlockH});
    menuBlock.setPosition((winSizeX - menuBlockW) / 2, 70);
    menuBlock.setFillColor({70, 102, 16});
    menuBlock.setOutlineThickness(5);
    menuMessage.setFont(font);
    menuMessage.setPosition((winSizeX - menuBlockW) / 2 + 25, 80);

    direction dir = RIGHT, previousDir = RIGHT;                     // Начальное направление змейки
    vector<Snake> startPosition = {{3, 7}, {2, 7}, {1, 7}, {0, 7}}; // Стартовые позиции сегментов змейки
    auto snakePositions = startPosition;
    Apple applePosition = spawnApple(snakePositions); // Генерация позиции яблока

    // Объявление текстур и спрайтов змейки, яблока и игрового поля
    Texture snakeTexture;
    if (!snakeTexture.loadFromFile("src/image/SnakeSprite.png"))
        return 30;
    Sprite snake(snakeTexture);

    Texture appleTexture;
    if (!appleTexture.loadFromFile("src/image/apple.png"))
        return 30;
    Sprite apple(appleTexture);
    apple.setTextureRect(IntRect(0, 0, segmentSize, segmentSize));
    apple.setPosition(applePosition.x * segmentSize + margin,
                      applePosition.y * segmentSize + margin);

    Texture fieldTexture;
    if (!fieldTexture.loadFromFile("src/image/field.png"))
        return 30;
    RectangleShape gameField({fieldW, fieldW});
    gameField.setTexture(&fieldTexture);
    gameField.setPosition(margin, margin);
    gameField.setOutlineThickness(2);

    // Объявление звуков при смерти и поедания яблока
    SoundBuffer eatSoundBuffer, deathSoundBuffer;
    eatSoundBuffer.loadFromFile("src/sound/eat.wav");
    Sound eatSound, deathSound;
    eatSound.setBuffer(eatSoundBuffer);
    deathSoundBuffer.loadFromFile("src/sound/death.wav");
    deathSound.setBuffer(deathSoundBuffer);

    font.loadFromFile("src/font/ScoreFont.otf");
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(38);
    scoreText.setPosition(winSizeX / 2 - 90, fieldW + margin);

    // Инициализация таймера
    Clock clock;
    float timer = 0;
    const float delay = 0.15;

    // Флаги для начала игры
    bool gameIsRunning = true, gameStarted = false;

    while (window.isOpen()) // Игровой цикл
    {
        Event event{};
        while (window.pollEvent(event)) // Проверка на закрытие окна программы
        {
            if (event.type == Event::Closed ||
                (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::Q)))
            {
                window.close();
            }
        }

        window.clear({70, 102, 16}); // Очистка окна в зелёный цвет
        window.draw(gameField);      // Отрисовка игрового поля

        // Увеличение таймера
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        // Алгоритм при запущенной игре
        if (gameStarted && gameIsRunning)
        {
            ChangeDirection(dir, previousDir);
            scoreText.setString("Score: " + to_string(score));
            if (timer >= delay)
            { // Проверка, прошло ли достаточно времени после предыдущего движения змейки
                timer = 0;
                snakeMove(snakePositions, dir); // Изменение координат змейки
                previousDir = dir;
                if (isSnakeCrashed(snakePositions))
                { // Проверка, врезалась ли змейка
                    deathSound.play();
                    gameIsRunning = false;
                    if (score > bestScore) // Обновление лучшего счёта
                        bestScore = score;
                }
                if (isSnakeEatApple(snakePositions, applePosition))
                { // Проверка, съедает ли змейка яблоко
                    eatSound.play();
                    addSegment(snakePositions); // Добавление сегмента в конец змейки
                    if (snakePositions.size() != 15 * 15)
                        applePosition = spawnApple(snakePositions); // Генерация новых координат яблока

                    apple.setPosition(applePosition.x * segmentSize + margin,
                                      applePosition.y * segmentSize + margin);
                    score++;
                }
            }
        }

        if (gameIsRunning)
        { // Проверка, идёт ли игра
            // Отрисовка змейки, текущего счёта и яблока
            drawSnake(window, snakePositions, snake, dir);
            window.draw(scoreText);
            window.draw(apple);
        }
        else
        {
            drawGameOver(window, score, bestScore); // Отрисовка окна конца игры
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            { // Если нажата клавиша Enter игра запускается
                gameIsRunning = true;
                // Задание стартовых характеристик
                score = 0;
                dir = RIGHT;
                snakePositions = startPosition;
                applePosition = spawnApple(snakePositions);
                apple.setPosition(applePosition.x * segmentSize + margin,
                                  applePosition.y * segmentSize + margin);
            }
        }

        if (!gameStarted)
        {                     // Проверка не начата ли игра
            drawMenu(window); // Отрисовка стартового меню
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            { // Если нажата клавиша Enter игра запускается
                gameStarted = true;
            }
        }

        window.display(); // Отображение на икране отрисованных элементов
    }
    // Запись обновлённого лучшего счёта в бинарный файл
    std::ofstream out("local/BestScore.dat", std::ios::binary);
    out.write((char *)&bestScore, sizeof(bestScore));
    out.close();
    return 0;
}

void ChangeDirection(direction &dir, direction previousDir)
{
    // Сопоставление нажатых на клавиатуре клавиш и направлений движения змейки
    if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && previousDir != RIGHT)
        dir = LEFT;
    else if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && previousDir != LEFT)
        dir = RIGHT;
    else if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && previousDir != DOWN)
        dir = UP;
    else if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && previousDir != UP)
        dir = DOWN;
}

void drawMenu(RenderWindow &window)
{
    window.draw(menuBlock);
    menuMessage.setCharacterSize(30);
    menuMessage.setString("\tPYTHON GAME");
    window.draw(menuMessage);
    menuMessage.setCharacterSize(20);
    menuMessage.setString("\n\n\n\t press Enter to start");
    window.draw(menuMessage);
}

void drawGameOver(RenderWindow &window, unsigned currentScore, unsigned bestScore)
{
    deathMessage.setString("    GAME OVER\n\nYour score: " + to_string(currentScore) + "\n\nBest  score: " + to_string(bestScore));
    window.draw(deathBlock);
    window.draw(deathMessage);
}

void drawSnake(RenderWindow &window, vector<Snake> snakePositions, Sprite snake, direction dir)
{
    for (int i = snakePositions.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            snake.setTextureRect(IntRect(dir * segmentSize, segmentSize,
                                         segmentSize, segmentSize)); // Задаём текстуру головы змейки в соответсвие с направлением
        }
        else
        {
            snake.setTextureRect(IntRect(0, 0, 40, 40)); // Задаём текстуру всех остальных сегментов
        }
        snake.setPosition(snakePositions[i].x * segmentSize + margin,
                          snakePositions[i].y * segmentSize + margin); // Задаём позицию сегмента змейки
        window.draw(snake);                                            // Отрисовка сегмента
    }
}
