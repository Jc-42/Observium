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
    Tile* nextTile; //Pointer to the next tile the animal is moving to, used so that the animal moves from tile to tile untill it reaces the destination
public:

    double targetX; 
    double targetY;
    double x; 
    double y;  
    double stepSize = 50;
    bool isWalking;
    bool doingAction;
    //betweenHex is used to check if the animal has made it to the next hex yet so that the animal moves smoothly, 
    //it is different from isWalking because when the animal is walking it is isWalking many hexes 
    bool betweenHex = false;
    Animal(double x, double y, int width, int height, sf::Texture& texture);
    Animal();
    void draw(sf::RenderWindow& window, double& deltaTime, double offsetX, double offsetY, Tile (&map)[35][35]); 
    void move(double& deltaTime, Tile (&map)[35][35]);
    void moveTo(double x, double y);
    void drink(Tile (&map)[35][35]);
};