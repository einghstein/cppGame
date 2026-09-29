#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Block : public Entity
{
public:
    Block();
    Block(float x, float y, int width, int height);

    void EDraw(sf::RenderWindow& window, float winX, float winY) override;
};
