#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Texture texture;
    Tile tile;
public:
    Game(int sizeX, int sizeY);
    sf::RenderWindow& getWindow();
    void paint(int frame);   
};