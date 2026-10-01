#include "Entity.h"
#include <SFML/Graphics.hpp>

Entity::Entity(float x, float y, int width, int height)
{
    hitbox.setPosition({ x, y });
    hitbox.setSize({
        static_cast<float>(width),
        static_cast<float>(height)
    });
}

void Entity::EDraw(sf::RenderWindow& window, float winX, float winY)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(hitbox.getSize());
    rectangle.setPosition({ winX, winY });
    window.draw(rectangle);
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