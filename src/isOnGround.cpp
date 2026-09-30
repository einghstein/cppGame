#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Block.h"

bool isOnGround(const Player& player, const std::vector<Block>& grid)
{
    for (const auto& block : grid)
    {
        if (player.hitbox.getGlobalBounds().findIntersection(block.hitbox.getGlobalBounds()))
        {
            return true;
        }
    }
    return false;
}