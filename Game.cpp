//
// Created by Amir on 25.09.2023.
//

#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;

    // Game logic
    this->endGame            = false;
    this->points             = 0;
    this->health             = 30;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer    = this->enemySpawnTimerMax;
    this->maxEnemies         = 5;
    this->mouseHeld          = false;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width  = 800;
    this->window           = new sf::RenderWindow(
            this->videoMode,
            "Game 1",
            sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if (!this->font.loadFromFile("../fonts/Skranji-Regular.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts!\n";
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("HELLO I'M PETER");
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
//    this->enemy.setOutlineColor(sf::Color::Green);
//    this->enemy.setOutlineThickness(1.f);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

// Accessors
bool Game::running() const
{
    return this->window->isOpen();
}

bool Game::getEndGame() const {
    return this->endGame;
}

// Functions
void Game::spawnEnemy()
{
    /**
     * @return void
     *
     * Spawns enemies and sets their types and colors. Spawns them randomly.
     * - Sets type (diff)
     * - Sets a random position.
     * - Sets a random color.
     * - Adds enemy to the vector.
     */

    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.f
            );

    // Randomize enemy type
    int type = rand() % 5;

    switch (type)
    {
        case 0:
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
        case 2:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
        case 3:
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 4:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Green);
            break;
        default:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Yellow);
            break;
    }

    // Spawn the enemy
    this->enemies.push_back(this->enemy);

    // remove enemies at the end of screen

}

void Game::pollEvents() {
    // Event polling
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}
void Game::updateMousePositions()
{
    /**
     *  Updates the mouse positions
     *      - Mouse pos relative to window
     */
     this->mousePosWindow = sf::Mouse::getPosition(*this->window);
     this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << "\n"
       << "Health: " << this->health << "\n";

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    /**
     * @return void
     *
     * Updates the enemy spawn timer and spawns enemies
     * when the total amount is smaller than max
     * Moves the enemies downwards.
     * Removes the enemies at the edge of the screen // TODO
     */

    // updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 1.f;
        }
        else this->enemySpawnTimer += 1.f;
    }

    // Move and update the enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;
        this->enemies[i].move(0.f, 5.f);

        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }
    }

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->mouseHeld)
        {
            this->mouseHeld = true;
            bool deleted    = false;

            for (size_t i = 0; i < this->enemies.size() && !deleted; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    // Gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 3;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                            this->points += 1;

                    // Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
}

void Game::update()
{
    this->pollEvents();

    if (!this->endGame)
    {
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }

    // death
    if (this->health <= 0)
    {
        this->endGame = true;
    }
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    // Rendering all the enemies
    for (auto &e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
    /**
     * @return void
     *
     *  - clear old frame
     *  - render objects
     *  - display frame in window
     *
     *  Renders the game objects.
     */
    this->window->clear();

    // draw game objects
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}













