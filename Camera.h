#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
class Camera {
public:
    float speed = 500.f; // Speed at which the camera moves

    Camera(int WINDOW_HEIGHT, int WINDOW_WIDTH, float X, float Y, float Zoom); // Constructor to initialize the camera with position and size
    void Update(sf::RenderWindow& window, float playerX, float playerY, std::vector<Entity*> DrawBatch); // Updates the camera's position based on the player's position
    
    float x;
    float y;
    float zoom;
};
