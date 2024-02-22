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

void Animal::draw(sf::RenderWindow& window, double& deltaTime, double offsetX, double offsetY){
    if(moving){
        if(targetX > x){
            x += stepSize * deltaTime;
        }
        else if(targetX < x){            
            x -= stepSize * deltaTime;
        }
        if(targetY > y){
            y += stepSize * deltaTime;
        }
        else if(targetY < y){
            y -= stepSize * deltaTime;
        }

        if(abs(targetX - x) <= 10 * stepSize * deltaTime && abs(targetY - y) <= 10 * stepSize * deltaTime){
            moving = false;
        }
    }

    if(x + offsetX != sprite.getPosition().x || y + offsetY != sprite.getPosition().y){
        sprite.setPosition(x + offsetX, y + offsetY);
    }
    
    if((x + offsetX - 30 - (sprite.getTexture()->getSize().x * sprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (sprite.getTexture()->getSize().x * sprite.getScale().x) > 0) && (y + offsetY - 30 - (sprite.getTexture()->getSize().y * sprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (sprite.getTexture()->getSize().y * sprite.getScale().y) > 0)){
        window.draw(sprite);
    }
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
}

void Animal::setY(double y){
    this->y = y;
}

void Animal::setWidth(int width){
    this->width = width;
}

void Animal::setHeight(int height){
    this->height = height;
}
