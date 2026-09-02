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
    if (DrawHitbox)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(hitbox.getSize());
        rectangle.setPosition({ winX, winY });

        window.draw(rectangle);
    }
}