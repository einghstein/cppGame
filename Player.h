#pragma once

#include "Entity.h"
#include "Item.h"

class Player : public Entity
{
public:
    Player(float x, float y, int width, int height);

    void Update();

private:
    int hp;
    Item inventory[10];

    float velocity_x;
    float velocity_y;
    float drag = 0.0001f;

    float speed = 0.001f;
    float gravity = 0.0005f;
};
