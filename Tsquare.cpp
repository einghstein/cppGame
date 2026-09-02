#include "Tsquare.h"

Tsquare::Tsquare(sf::Vector2f position, sf::Vector2f size)
    : shape(size) {
    shape.setPosition(position);
}

void Tsquare::draw(sf::RenderWindow& window) {
    window.draw(shape);
}