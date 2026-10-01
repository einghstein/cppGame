#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "FontLoader.h"

Game::Game(int WINDOW_HEIGHT, int WINDOW_WIDTH, const char* executablePath)
    : clock(),
      debugFont(),
      player(300.f, -100.f, 50, 50, 0.8f, 300.0f), // Player X, Y, width. height, drag, speed
      entities(),
      camera(WINDOW_HEIGHT, WINDOW_WIDTH, 300.f, -100.f, 1.f), // WH, WW, X, Y, Zoom
      window(
          sf::VideoMode({
              static_cast<unsigned int>(WINDOW_WIDTH),
              static_cast<unsigned int>(WINDOW_HEIGHT)
          }),
          "cppGame"
      )
{
    if (!FontLoader::load(debugFont, executablePath))
        std::cerr << "Failed to load font\n";
    entities.push_back(&player);
}

void Game::InitGrid(std::vector<Entity*> entities, const int gridWidth, const int gridHeight, const int blockSize)
{
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;

    grid.reserve(gridWidth * gridHeight);
    entities.reserve(gridWidth * gridHeight + 1);
    entities.push_back(&player);

    for (int i = 0; i < gridWidth; ++i)
    {
        for (int j = 0; j < gridHeight; ++j)
        {
            Block block(i * blockSize, j * blockSize, blockSize, blockSize);
            grid.emplace_back(block);
            entities.push_back(&block);
        }
    }
}









void Game::keyPressHandler(int deltaTime){


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            camera.x -= camera.speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            camera.x += camera.speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            camera.y += camera.speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            camera.y -= camera.speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add))
        {
            camera.zoom += 0.01f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract))
        {
            camera.zoom -= 0.01f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            camera.x = player.hitbox.getPosition().x + (window.getSize().x / 2.f);
            camera.y = player.hitbox.getPosition().y + (window.getSize().y / 2.f);
            camera.zoom = 1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            player.hitbox.setPosition(sf::Vector2f(100.f, -100.f));
            player.resetVelocity();
            camera.x = player.hitbox.getPosition().x + (window.getSize().x / 2.f);
            camera.y = player.hitbox.getPosition().y + (window.getSize().y / 2.f);
            camera.zoom = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F))
        {
            camera.followPlayer = !camera.followPlayer;
        }
        if (camera.followPlayer)
        {
            camera.x =  - player.hitbox.getPosition().x + (window.getSize().x / 2.f);
            camera.y = - player.hitbox.getPosition().y + (window.getSize().y / 2.f);
        }
}

