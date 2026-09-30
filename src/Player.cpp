#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "Block.h"
#include <algorithm>
#include <cmath>

Player::Player(float x, float y, int width, int height, float drag, float speed)
    : Entity(x, y, width, height),
      hp(100),
      velocity_x(0.f),
      velocity_y(0.f),
      drag(drag),
      speed(speed),
      dir_switch_speed_amplifier(2.0f),
      max_speed(30.f)
{
}

void Player::Update(bool isOnGround, float deltaTime)
{
    const float dt = std::min(deltaTime, 0.033f);

    // Handles vertical movement
    if (!isOnGround)
        velocity_y += gravity * dt;
    else
        velocity_y = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isOnGround)
        velocity_y = -jumpForce;

    // Handles horizontal movement
    

    if (velocity_x > 0.f && isOnGround){
        velocity_x -= drag * dt * std::abs(velocity_x);
    }
    else if (velocity_x < 0.f && isOnGround){
        velocity_x += drag * dt * std::abs(velocity_x);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && isOnGround)
        velocity_x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && isOnGround)
        velocity_x += speed * dt;

    if (!isOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity_x -= speed * dt * 0.5f;
    if (!isOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity_x += speed * dt * 0.5f;
    

    hitbox.move({ velocity_x * dt, velocity_y * dt });
}



/*if (velocity_x > 0.f){ // Going right
        if (isOnGround) {
            velocity_x -= drag * dt;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && velocity_x < max_speed)
                velocity_x -= speed * dt * dir_switch_speed_amplifier;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                velocity_x += speed * dt;
                printf("velocity_x: %f\n", velocity_x);
        }
    }


    else if (velocity_x < 0.f){ // Going left
        if (isOnGround){
            velocity_x += drag * dt;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                velocity_x -= speed * dt;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && velocity_x > -max_speed)
                velocity_x += speed * dt * dir_switch_speed_amplifier;
        }
    }
    else { // Not moving
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && isOnGround)
            velocity_x -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && isOnGround)
            velocity_x += speed * dt;
    }*/