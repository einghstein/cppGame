#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <Block.h>
#include <algorithm>
#include <cmath>

Player::Player(float x, float y, int width, int height, float drag, float speed)
    : Entity(x, y, width, height),
      hp(100),
      velocity_x(0.f),
      velocity_y(0.f),
      drag(drag),
      speed(speed)
{
}

void Player::Update(bool isOnGround, float deltaTime)
{
    const float dt = std::min(deltaTime, 0.033f);

    if (!isOnGround)
        velocity_y += gravity * dt;
    else
        velocity_y = 0.f;

    if (velocity_x > 0.f && isOnGround)
        velocity_x -= drag * dt;
    else if (velocity_x < 0.f && isOnGround)
        velocity_x += drag * dt;

    if (std::abs(velocity_x) < 5.f)
        velocity_x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && isOnGround)
        velocity_x -= speed ;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && isOnGround)
        velocity_x += speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isOnGround)
        velocity_y = -jumpForce;

    hitbox.move({ velocity_x * dt, velocity_y * dt });
}
