#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Animal.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Texture tileTexture;
    sf::Texture animalTexture;
    Animal rabbit;
    Tile map[70][70];
    double deltaTime;
public:
    Game(int sizeX, int sizeY);
    sf::RenderWindow& getWindow();
    void paint();   
};