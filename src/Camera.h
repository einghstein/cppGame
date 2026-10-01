#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>
class Camera {
public:
    float speed = 500.f; // Speed at which the camera moves

    Camera(int WINDOW_HEIGHT, int WINDOW_WIDTH, float X, float Y, float Zoom); // Constructor to initialize the camera with position and size
    void Update(sf::RenderWindow& window, std::vector<Entity*> DrawBatch); // Updates the camera's position based on the player's position
    sf::Vector2f screenToWorld(sf::Vector2f screenPos) const; // Converts screen coordinates to world coordinates
    sf::Vector2f screenToWorld(float screenX, float screenY) const;

    float x;
    float y;
    float zoom;
    bool followPlayer = true; // Flag to determine whether the camera should follow the player or not
};
