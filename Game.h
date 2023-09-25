//
// Created by Amir on 25.09.2023.
//

#ifndef FIRST_SFML_GAME_H
#define FIRST_SFML_GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/**
 * Game wrapper class
 */
class Game
{
private:
    // Variables
    // Window
    sf::RenderWindow* window;
    sf::VideoMode     videoMode;
    sf::Event         event;

    // Mouse Positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Resources
    sf::Font font;

    // Text
    sf::Text uiText;

    // Game logic
    bool     endGame;
    unsigned points;
    int      health;
    float    enemySpawnTimer;
    float    enemySpawnTimerMax;
    int      maxEnemies;
    bool     mouseHeld;

    // Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();
    void initEnemies();


public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Accessors
    bool running() const;
    bool getEndGame() const;

    // Functions
    void spawnEnemy();
    void pollEvents();

    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();

    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();
};


#endif //FIRST_SFML_GAME_H
