#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.h"
#include "Camera.h"
#include "Block.h"


const int gridWidth = 300;
const int gridHeight = 3;
Block grid[gridWidth][gridHeight];

const int blockSize = 50; // Size of each block in the grid 

int main(int argc, char* argv[])
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "SFML Window"
    );

    sf::Clock clock;

    sf::Font debugFont;
    if (!debugFont.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
    {
        return 1;
    }

    sf::Text debugText(debugFont);
    debugText.setCharacterSize(20);
    debugText.setFillColor(sf::Color::White);
    debugText.setPosition(sf::Vector2f(10.f, 10.f));

    Player player(300.f, -100.f, blockSize, blockSize, 0.8f, 300.0f);

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
        const float deltaTime = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        bool isOnGround = false;
        for (int i = 0; i < gridWidth; ++i)
        {
            for (int j = 0; j < gridHeight; ++j)
            {
                Block& block = grid[i][j];
                if (player.hitbox.getGlobalBounds().findIntersection(block.hitbox.getGlobalBounds()))
                {
                    isOnGround = true;
                    break;
                }
            }
            if (isOnGround)
                break;
        }

        player.Update(isOnGround, deltaTime);

        

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

        camera.Update(window, entities);

        debugText.setString(
            "Camera: (" + std::to_string((int)camera.x) + ", " + std::to_string((int)camera.y) + ")\n" +
            "Player Position: (" + std::to_string((int)player.hitbox.getPosition().x) + ", " + std::to_string((int)player.hitbox.getPosition().y) + ")" + "\n" +
            "Player Speed: " + std::to_string(player.velocity_x) + ", " + std::to_string(player.velocity_y) + "\n"
        );
        window.draw(debugText);
        window.display();
    }

    return 0;
}
