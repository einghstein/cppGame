#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "Block.h"
#include <algorithm>
#include <cmath>
#include "Game.h"

Player::Player(float x, float y, int width, int height, float drag, float speed, Game* game)
    : Entity(x, y, width, height),
      hp(100),
      velocity_x(0.f),
      velocity_y(0.f),
      drag(drag),
      speed(speed),
      dir_switch_speed_amplifier(2.0f),
      max_speed(30.f),
      game(game)
{
}

void Player::mouseUpdate()
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
            game->placeBlockAtPosition(mousePos.x, mousePos.y);
            printf("No block found at position (%f, %f)\n", static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }
    }
}

void Player::Update(float deltaTime, int steps)
{
    const float dt = std::min(deltaTime, 0.033f);
    bool TrulyOnGround;

    // Handles vertical movement
    bool isOnGround = this->isOnGround(50/steps);
    
    for (int i = 0; i < steps; ++i) {
        if (!isOnGround)
            velocity_y += gravity * dt * (1.f / static_cast<float>(steps));
        else
            velocity_y = 0.f;

        

        hitbox.move({ 0, velocity_y * dt * (1.f / static_cast<float>(steps)) });

        // Check for collisions with other blocks when going downwards
        if (this->isOnGround(50/steps))
        {
            hitbox.move({ 0.f, -velocity_y * dt * (1.f / static_cast<float>(steps)) }); // Move back to previous position
            velocity_y = 0.f; // Stop vertical movement
            TrulyOnGround = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                velocity_y = -jumpForce; // Apply jump force if W is pressed
             
            break; // Exit the loop since we only need to handle one collision at a time
        }
        else
        {
            TrulyOnGround = false;
        }
    }


    // Handles horizontal movement
    

    if (velocity_x > 0.f && TrulyOnGround){
        velocity_x -= drag * dt * std::abs(velocity_x);
    }
    else if (velocity_x < 0.f && TrulyOnGround){
        velocity_x += drag * dt * std::abs(velocity_x);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && TrulyOnGround)
        velocity_x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && TrulyOnGround)
        velocity_x += speed * dt;

    if (!TrulyOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity_x -= speed * dt * 0.5f;
    if (!TrulyOnGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity_x += speed * dt * 0.5f;
    


    
    hitbox.move({ velocity_x * dt, 0 });

    // Check for collisions with other blocks when going sideways
    for (const auto& block : game->grid)
    {
        if (hitbox.getGlobalBounds().findIntersection(block.hitbox.getGlobalBounds()))
        {
            hitbox.move({ -velocity_x * dt, 0.f }); // Move back to previous position
            velocity_x = 0.f; // Stop horizontal movement
            break; // Exit the loop since we only need to handle one collision at a time
        }
    }
}


bool Player::isOnGround(float tolerance) const
{
    for (const auto& block : game->grid)
    {
        float playerBottom = hitbox.getPosition().y + hitbox.getSize().y;
        float blockTop = block.hitbox.getPosition().y;
        float playerLeft = hitbox.getPosition().x;
        float playerRight = hitbox.getPosition().x + hitbox.getSize().x;
        float blockLeft = block.hitbox.getPosition().x;
        float blockRight = block.hitbox.getPosition().x + block.hitbox.getSize().x;

        float playerDistanceToBlock = std::abs(playerBottom - blockTop);

        if (-tolerance <= playerDistanceToBlock && playerDistanceToBlock <= tolerance && // Check if player's bottom is near the block's top
            playerRight > blockLeft && playerLeft < blockRight) // Check if player's horizontal position overlaps with the block
        {
            return true; // Player is on the ground
        }
        

    }
    return false;
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