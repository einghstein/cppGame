#pragma once

#include "Entity.h"
#include "Item.h"

class Player : public Entity
{
public:
    Player(float x, float y, int width, int height, float drag, float speed);

    void Update(bool isOnGround, float deltaTime);
    void resetVelocity() { velocity_x = 0.f; velocity_y = 0.f; }
    
    float velocity_x = 0.0f;
    float velocity_y = 0.0f;
    int hp;

private:
    Item inventory[10];

    float drag;
    float speed;
    float dir_switch_speed_amplifier;
    float max_speed;

    float gravity = 1600.0f;
    float jumpForce = 700.0f;
};
