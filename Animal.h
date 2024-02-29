#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Animal {
private:
//TODO figure out what to do with health, need or somting else?
    
    //Needs
        double energyNeed;
        double foodNeed;
        double waterNeed; 
    //Stats
        double health;
        int sight;
    //States
        std::string action = "idle"; 
    int width; 
    int height; 
    sf::IntRect rect;
    sf::Sprite sprite;
public:

    double targetX; 
    double targetY;
    double x; 
    double y;  
    double stepSize = 50;
    bool moving;
    bool doingAction;
    Animal(double x, double y, int width, int height, sf::Texture& texture);
    Animal();
    void draw(sf::RenderWindow& window, double& deltaTime, double offsetX, double offsetY, Tile (&map)[35][35]); 
    void moveTo(double x, double y);
    void drink(Tile (&map)[35][35]);
};