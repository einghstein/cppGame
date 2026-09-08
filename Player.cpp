#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player(float x, float y, int width, int height)
    : Entity(x, y, width, height),
      hp(100),
      velocity_x(0.f),
      velocity_y(0.f),
      drag(0.0001f),
      gravity(0.0005f)
{
}

void Player::Update()
{
    if (velocity_x > 0)
        velocity_x -= drag;
    else if (velocity_x < 0)
        velocity_x += drag;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity_x += -speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity_x += speed;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && )
        velocity_y += -speed;
    

    hitbox.move({ velocity_x, velocity_y });
    printf("Player Position: (%f, %f)\n", hitbox.getPosition().x, hitbox.getPosition().y);
}
