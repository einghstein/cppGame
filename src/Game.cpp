#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "FontLoader.h"

Game::Game(int WINDOW_HEIGHT, int WINDOW_WIDTH, const char* executablePath)
    : clock(),
      debugFont(),
      player(300.f, -100.f, 50, 50, 0.8f, 300.0f, this), // Player X, Y, width. height, drag, speed, game
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
}

Block* Game::getBlockAtPosition(float x, float y)
{
    for (Block& block : grid)
    {
        if (block.hitbox.getGlobalBounds().contains(sf::Vector2f(x, y)))
        {
            return &block;
        }
    }
    return nullptr; // Return a default Block if no block is found at the position
}
Block* Game::getBlockAtPosition(sf::Vector2f worldPos)
{
    for (Block& block : grid)
    {
        if (block.hitbox.getGlobalBounds().contains(worldPos))
        {
            return &block;
        }
    }
    return nullptr; // Return a default Block if no block is found at the position
}

void Game::removeBlockAtPosition(float x, float y)
{
    for (auto it = grid.begin(); it != grid.end(); ++it)
    {
        if (it->hitbox.getGlobalBounds().contains(sf::Vector2f(x, y)))
        {
            grid.erase(it);
            return; // Exit after removing the block
        }
    }
}

void Game::InitGrid( const int gridWidth, const int gridHeight, const int blockSize)
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
            grid.emplace_back(i * blockSize, j * blockSize, blockSize, blockSize);
            entities.push_back(&grid.back());
        }
    }
    printf("Entity count after InitGrid: %zu\n", entities.size());
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

