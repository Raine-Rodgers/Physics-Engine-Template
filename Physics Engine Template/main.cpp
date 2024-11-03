#include "Game_Engine.h"

int main()
{
    Game_Engine gameEngine;
    while (gameEngine.running())
    {
        gameEngine.Update();

        gameEngine.Render();
    }

    return 0;
}