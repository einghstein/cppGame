
#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Player.h"
#include "Camera.h"

class Game {
public:
    Game(int WINDOW_HEIGHT, int WINDOW_WIDTH, const char* executablePath); 
    std::vector<Block> grid;
    int gridWidth;
    int gridHeight;
    sf::Clock clock;
    sf::Font debugFont;
    Player player;
    Camera camera;
    sf::RenderWindow window;
    std::vector<Entity*> entities;

    void InitGrid(std::vector<Entity*> entities, const int gridWidth, const int gridHeight, const int blockSize);
    bool isOnGround(const Player& player, const std::vector<Block>& grid);
    void keyPressHandler(int deltaTime);
};
