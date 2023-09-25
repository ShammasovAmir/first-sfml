//
// Created by Amir on 25.09.2023.
//

#include "Game.h"

// Private functions
void Game::initVariables()
{
    this->window = nullptr;

    // Game logic
    this->points             = 0;
    this->enemySpawnTimerMax = 1000.f;
    this->enemySpawnTimer    = this->enemySpawnTimerMax;
    this->maxEnemies         = 5;
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

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);
}

// Constructors / Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
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

// Functions
void Game::spawnEnemy()
{
    /**
     * @return void
     *
     * Spawns enemies and sets their colors and positions
     * - Sets a random position.
     * - Sets a random color.
     * - Adds enemy to the vector.
     */

    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.f
            );

    this->enemy.setFillColor(sf::Color::Green);

    // Spawn the enemy
    this->enemies.push_back(this->enemy);
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
            this->enemySpawnTimer = 0.f;
        }
        else this->enemySpawnTimer += 0.f;
    }

    // Move the enemies
    for (auto &e : this->enemies)
    {
        e.move(0.f, 5.f);
    }
}

void Game::update()
{
    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();
}

void Game::renderEnemies()
{
    // Rendering all the enemies
    for (auto &e : this->enemies)
    {
        this->window->draw(e);
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
    this->renderEnemies();

    this->window->display();
}







