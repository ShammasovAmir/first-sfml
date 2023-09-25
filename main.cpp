#include <iostream>
#include "Game.h"

int main()
{
    // Init srand
    srand(static_cast<unsigned>(time(NULL)));

    // Init Game Engine
    Game game;

    // Game loop
    while (game.running())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    // App end

    return 0;
}