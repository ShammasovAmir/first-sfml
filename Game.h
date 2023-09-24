//
// Created by Amir on 25.09.2023.
//

#ifndef FIRST_SFML_GAME_H
#define FIRST_SFML_GAME_H

#include <iostream>

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
    sf::VideoMode videoMode;
    sf::Event event;

    // Game objects
    sf::RectangleShape enemy;

    // Private functions
    void initVariables();
    void initWindow();
    void initEnemies();


public:
    // Constructors / Destructors
    Game();
    virtual ~Game();

    // Accessors
    [[nodiscard]] bool running() const;

    // Functions
    void pollEvents();
    void update();
    void render();
};


#endif //FIRST_SFML_GAME_H
