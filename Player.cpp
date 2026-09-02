#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player(float x, float y, int width, int height)
    : Entity(x, y, width, height),
      hp(100),
      velocity_x(0.f),
      velocity_y(0.f)
{
}

void Player::Update()
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity_x += -speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity_x += speed;

    

    hitbox.move({ velocity_x, velocity_y });
}