#include "Block.h"

#include <SFML/Graphics.hpp>

Block::Block()
    : Entity(0.f, 0.f, 0, 0)
{
    hitbox.setFillColor(sf::Color::Green);
}

Block::Block(float x, float y, int width, int height)
    : Entity(x, y, width, height)
{
    hitbox.setFillColor(sf::Color::Green);
}

void Block::EDraw(sf::RenderWindow& window, float winX, float winY)
{
    sf::RectangleShape drawHitbox = hitbox;
    drawHitbox.setPosition(sf::Vector2f(winX, winY));
    window.draw(drawHitbox);
    if (DrawHitbox){
    sf::Vertex line[] =
    {
        sf::Vertex{{winX, winY}, sf::Color::Red},
        sf::Vertex{{winX + hitbox.getSize().x, winY}, sf::Color::Red},
        sf::Vertex{{winX + hitbox.getSize().x, winY + hitbox.getSize().y}, sf::Color::Red},
        sf::Vertex{{winX, winY + hitbox.getSize().y}, sf::Color::Red},
        sf::Vertex{{winX, winY}, sf::Color::Red}
    };

        window.draw(line, 5, sf::PrimitiveType::LineStrip);
    }
}
