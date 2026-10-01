
#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Player.h"
#include "Camera.h"
#include <list>
#include <vector>

class Game {
public:
    Game(int WINDOW_HEIGHT, int WINDOW_WIDTH, const char* executablePath); 
    std::list<Block> grid;
    int gridWidth;
    int gridHeight;
    int blockSize;
    sf::Clock clock;
    sf::Font debugFont;
    Player player;
    std::vector<Entity*> entities;
    Camera camera;
    sf::RenderWindow window;

    void InitGrid(const int gridWidth, const int gridHeight, const int blockSize);
    bool isOnGround(const Player& player, const std::list<Block>& grid);
    void keyPressHandler(int deltaTime);
    Block* getBlockAtPosition(float x, float y);
    Block* getBlockAtPosition(sf::Vector2f worldPos);
    void removeBlockAtPosition(float x, float y);
    void removeBlockAtPosition(sf::Vector2f worldPos);
    void placeBlockAtPosition(float x, float y);
    
};
