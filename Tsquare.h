#ifndef TSQUARE_H
#define TSQUARE_H

#include <SFML/Graphics.hpp>

class Tsquare {
public:
    Tsquare(sf::Vector2f position, sf::Vector2f size);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
};

#endif // TSQUARE_H
