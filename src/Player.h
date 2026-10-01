#pragma once

#include "Entity.h"
#include "Item.h"

class Game;

class Player : public Entity
{
public:
    Player(float x, float y, int width, int height, float drag, float speed, Game* game);

    void Update(float deltaTime, int steps);
    void resetVelocity() { velocity_x = 0.f; velocity_y = 0.f; }
    void mouseUpdate();
    bool isOnGround(float tolerance = 5.f) const;
    
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;
    int hp;

    Game *game; // Pointer to the Game instance

private:
    Item inventory[10];

    float drag;
    float speed;
    float dir_switch_speed_amplifier;
    float max_speed;

    float gravity = 1600.0f;
    float jumpForce = 700.0f;
};
