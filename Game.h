#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Texture texture;
    Tile map[35][35];
public:
    Game(int sizeX, int sizeY);
    sf::RenderWindow& getWindow();
    void paint();   
};