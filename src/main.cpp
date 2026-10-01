#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.h"
#include "Camera.h"
#include "Block.h"
#include "FontLoader.h"
#include "Game.h"
#include "isOnGround.h"

// constants for window dimensions and grid configuration

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int gridWidth = 300;
const int gridHeight = 3;
const int blockSize = 50; // Size of each block in the grid 


int main(int, char* argv[])
{
    // Initi
    Game game(WINDOW_HEIGHT, WINDOW_WIDTH, argv[0]);


    sf::Text debugText(game.debugFont);
    debugText.setCharacterSize(20);
    debugText.setFillColor(sf::Color::White);
    debugText.setPosition(sf::Vector2f(10.f, 10.f));

    game.InitGrid(gridWidth, gridHeight, blockSize);

    game.player.DrawHitbox = true;

    // Main game loop

    while (game.window.isOpen())
    {

        // dt and event handling

        const float deltaTime = game.clock.restart().asSeconds();

        while (const auto event = game.window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                game.window.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                game.player.mouseUpdate(&game);
            }
        }

        // Game update

        game.player.Update(isOnGround(game.player, game.grid), deltaTime, &game);

        game.keyPressHandler(deltaTime);



        game.getBlockAtPosition(game.camera.screenToWorld(sf::Vector2f(sf::Mouse::getPosition(game.window))));

        // Rendering
        

        game.camera.Update(game.window, game.entities);

        debugText.setString(
            "Camera: (" + std::to_string((int)game.camera.x) + ", " + std::to_string((int)game.camera.y) + ")\n" +
            "Player Position: (" + std::to_string((int)game.player.hitbox.getPosition().x) + ", " + std::to_string((int)game.player.hitbox.getPosition().y) + ")\n" +
            "Player Speed: " + std::to_string(game.player.velocity_x) + ", " + std::to_string(game.player.velocity_y) + "\n"
        );
        game.window.draw(debugText);
        game.window.display();
    }

    return 0;
}
