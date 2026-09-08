#pragma once
#include <SFML/Graphics.hpp>
class Entity {
public:
    sf::RectangleShape hitbox; // hitbox representing the entity hitbox
    bool DrawHitbox = true; // Flag to determine whether to draw the hitbox or not
    virtual void EDraw(sf::RenderWindow& window, float winX, float winY); // Function to draw the entity hitbox on the window
    Entity(float x, float y, int width, int height); // Constructor to initialize the entity with position and size
    virtual ~Entity() = default;
};
