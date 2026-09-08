#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Camera::Camera(int WINDOW_HEIGHT, int WINDOW_WIDTH, float X, float Y, float Zoom)
    : x(X + (WINDOW_WIDTH / 2.f)),
      y(Y + (WINDOW_HEIGHT / 2.f)),
      zoom(Zoom)
{
}

void Camera::Update(sf::RenderWindow& window, float playerX, float playerY, std::vector<Entity*> DrawBatch)
{
    for (Entity* entity : DrawBatch)
    {
        float entityX = entity->hitbox.getPosition().x * zoom + x;
        float entityY = entity->hitbox.getPosition().y * zoom + y;


        if (!(entityX < 0 || entityX > window.getSize().x || entityY < 0 || entityY > window.getSize().y))
        {
            entity->EDraw(window, entityX, entityY);
        }
    }
}
