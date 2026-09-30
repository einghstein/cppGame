#pragma once
#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Player.h"
#include "Camera.h"

class Game {
public:
    Game(int WINDOW_HEIGHT, int WINDOW_WIDTH, const int gridWidth, const int gridHeight, const int blockSize); 
    Block grid[][];
    sf::Clock clock;
    sf::Font debugFont;
    sf::Text debugText;
    Player player;
    Camera camera;
};
