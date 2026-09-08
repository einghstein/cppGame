#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Camera.h"
#include "Block.h"


const int gridWidth = 30;
const int gridHeight = 3;
Block grid[gridWidth][gridHeight];

const int blockSize = 50; // Size of each block in the grid 

int main()
{
    
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "SFML Window"
    );

    Player player(100.f, 100.f, blockSize, blockSize);

    Camera camera(window.getSize().y, window.getSize().x, player.hitbox.getPosition().x, player.hitbox.getPosition().y, 1.f);

    std::vector<Entity*> entities;
    entities.reserve(gridWidth * gridHeight + 1);
    entities.push_back(&player);

    for (int i = 0; i < gridWidth; ++i)
    {
        for (int j = 0; j < gridHeight; ++j)
        {
            grid[i][j] = Block(i * blockSize, j * blockSize, blockSize, blockSize);
            entities.push_back(&grid[i][j]);
        }
    }

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        player.Update();

        window.clear(sf::Color::Black);

        // Collect blocks and the player and let the camera draw them

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            camera.x -= camera.speed;
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            camera.x += camera.speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            camera.y += camera.speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            camera.y -= camera.speed;
        }


        camera.Update(window, player.hitbox.getPosition().x, player.hitbox.getPosition().y, entities);

        window.display();
    }

    return 0;
}
