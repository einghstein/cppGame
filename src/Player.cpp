#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "Block.h"
#include <algorithm>
#include <cmath>
#include "Game.h"

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

void Player::mouseUpdate(Game* game)
{

    char button = 'N'; // Default to 'N' for no button pressed
                sf::Vector2i mousePosWin = sf::Mouse::getPosition(game->window);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    button = 'L';
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                {
                    button = 'R';
                   
                }
                
                sf::Vector2f mousePos = game->camera.screenToWorld(mousePosWin.x, mousePosWin.y);

    if (button == 'L') {
        game->removeBlockAtPosition(mousePos.x, mousePos.y);
    } else if (button == 'R') {
        // Handle right mouse button click
        if (game->getBlockAtPosition(mousePos.x, mousePos.y) != nullptr) {
            printf("%p\n", static_cast<void*>(game->getBlockAtPosition(mousePos.x, mousePos.y)));
        }
        else {
            printf("No block found at position (%f, %f)\n", static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }
    }
}

void Player::Update(bool isOnGround, float deltaTime, Game* game)
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

    // Check for collisions with other blocks when going sideways
    for (const auto& block : game->grid)
    {
        if (hitbox.getGlobalBounds().intersects(block.hitbox.getGlobalBounds()))
        {
            if (velocity_x > 0.f) // Moving right
            {
                hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x - hitbox.getSize().x, hitbox.getPosition().y));
                velocity_x = 0.f;
            }
            else if (velocity_x < 0.f) // Moving left
            {
                hitbox.setPosition(sf::Vector2f(block.hitbox.getPosition().x + block.hitbox.getSize().x, hitbox.getPosition().y));
                velocity_x = 0.f;
            }
        }
    }
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