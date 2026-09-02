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

    float speed = 0.0001f;
};