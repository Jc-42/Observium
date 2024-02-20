#include <SFML/Graphics.hpp>
#include "Animal.h" 

#include <iostream>
#include <cmath>

Animal::Animal(double x, double y, int width, int height, sf::Texture& texture) : x(x), y(y), width(width), height(height), rect(x, y, width, height), sprite(texture), moving(false){
    sprite.setScale((double)width / (double)texture.getSize().x, (double)height / (double)texture.getSize().y);
    sprite.setPosition(x,y);
    health = 100;
    energy = 100;
    hunger = 0;
    thirst = 0;
}

Animal::Animal(){

}

void Animal::draw(sf::RenderWindow& window, double& deltaTime){
    if(moving){
        if(targetX > x){
            setX(x + stepSize * deltaTime);
        }
        else if(targetX < x){            
            setX(x - stepSize * deltaTime);
        }
        if(targetY > y){
            setY(y + stepSize * deltaTime);
        }
        else if(targetY < y){
            setY(y - stepSize * deltaTime);
        }

        if(abs(targetX - x) <= 10 * stepSize * deltaTime && abs(targetY - y) <= 10 * stepSize * deltaTime){
            moving = false;
        }
    }
    window.draw(sprite);
}


void Animal::moveTo(double x, double y){
    targetX = x; 
    targetY = y;
    moving = true;
}

double Animal::getHealth(){
    return health;
}

double Animal::getEnergy(){
    return energy;
}

double Animal::getHunger(){
    return hunger;
}

double Animal::getThirst(){
    return thirst;
}

double Animal::getX(){
    return x;
}

double Animal::getY(){
    return y;
}

int Animal::getWidth(){
    return width;
}

int Animal::getHeight(){
    return height;
}

void Animal::setHealth(double health){
    this->health = health;
}

void Animal::setEnergy(double energy){
    this->energy = energy;
}

void Animal::setHunger(double hunger){
    this->hunger = hunger;
}

void Animal::setThirst(double thirst){
    this->thirst = thirst;
}

void Animal::setX(double x){
    this->x = x;
    sprite.setPosition(x,y);
}

void Animal::setY(double y){
    this->y = y;
    sprite.setPosition(x,y);
}

void Animal::setWidth(int width){
    this->width = width;
}

void Animal::setHeight(int height){
    this->height = height;
}
