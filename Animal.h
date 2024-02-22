#pragma once
#include <SFML/Graphics.hpp>

class Animal {
private:
    double health;
    double energy;
    double hunger;
    double thirst; 
    double x; 
    double y;  
    int width; 
    int height; 
    sf::IntRect rect;
    sf::Sprite sprite;
public:

    double targetX; 
    double targetY;
    double stepSize = 50;
    bool moving;
    Animal(double x, double y, int width, int height, sf::Texture& texture);
    Animal();
    void draw(sf::RenderWindow& window, double& deltaTime, double offsetX, double offsetY); 

    double getHealth();
    double getEnergy();
    double getHunger();
    double getThirst();
    double getX();
    double getY();
    int getWidth();
    int getHeight();

    void setHealth(double health);
    void setEnergy(double energy);
    void setHunger(double hunger);
    void setThirst(double thirst);
    void setX(double x);
    void setY(double y);
    void setWidth(int width);
    void setHeight(int height);
    void moveTo(double x, double y);
};