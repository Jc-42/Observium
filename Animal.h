#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <list>

class Animal {
private:
//TODO figure out what to do with health, need or somting else?
    
   
    int width; 
    int height; 
    sf::IntRect rect;
    sf::Sprite lSprite;
    sf::Sprite rSprite;
    sf::Sprite lSleepingSprite;
    sf::Sprite rSleepingSprite;
    Tile* nextTile; //Pointer to the next tile the animal is moving to, used so that the animal moves from tile to tile untill it reaches the destination
    std::vector<std::vector<int>> pathMemory; //List of hex cordinates of the hex's the animal has moved through during its current walk 
    std::vector<std::string> actionQueue; //Queue of actions is read from last index to first, the action is ran until it is complete. Note walking is not an action it is a state.
public:
    //Needs
        double energyNeed;
        double foodNeed;
        double waterNeed; 
    //Stats
        double health;
        int sight;
    //States
        //std::string action = "idle"; 
        int directionFacing; //1 is right and -1 is left
    double targetX; 
    double targetY;
    double x; 
    double y; 
    std::vector<int> animalHexPos; 
    double stepSize = 50;
    bool isWalking;
    //bool idle = true;
    bool doingAction; //may be unneccary it could be possible to replace this by checking is action is "idle"
    int backtrackStep = 2; //Used to track how many tiles back the animal should backtrack, incremented everytime the animal hits a dead end on its current walk.
    //betweenHex is used to check if the animal has made it to the next hex yet so that the animal moves smoothly, 
    //it is different from isWalking because when the animal is walking it is isWalking many hexes 
    bool betweenHex = false;
    Animal(double x, double y, int width, int height, sf::Texture& lTexture, sf::Texture& rTexture, sf::Texture& lSleepTexture, sf::Texture& rSleepTexture);
    Animal();
    void draw(sf::RenderWindow& window, double offsetX, double offsetY, std::string state);
    void update(sf::RenderWindow& window, double& deltaTime, double offsetX, double offsetY, Tile (&map)[35][35]);
    bool move(double& deltaTime, Tile (&map)[35][35], std::string action); //Returns true if the animal has reached the target position
    void setMoveTarget(double x, double y);
    Tile* findWater(Tile (&map)[35][35], sf::RenderWindow& window);
    void sleep(double& deltaTime);
    void drink(double& deltaTime);
    std::vector<std::vector<int>> getTilesWithinRange(int range);
    void completeAction();
};