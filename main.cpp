#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Camera.h"

class Block : public Entity
{
public:
    Block()
        : Entity(0.f, 0.f, 0, 0)
    {
        hitbox.setFillColor(sf::Color::Green);
    }

    Block(float x, float y, int width, int height)
        : Entity(x, y, width, height)
    {
        hitbox.setFillColor(sf::Color::Green);
    }
};


const int gridWidth = 10;
const int gridHeight = 5;
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

    for (int i = 0; i < gridWidth; ++i)
    {
        for (int j = 0; j < gridHeight; ++j)
        {
            grid[i][j] = Block(i * blockSize, j * blockSize, blockSize, blockSize);
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

        camera.Update(window, player.hitbox.getPosition().x, player.hitbox.getPosition().y, std::vector<Entity*>{ &player });

        window.display();
    }

    return 0;
}