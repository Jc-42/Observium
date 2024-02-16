#include <SFML/Graphics.hpp>
#include "Tile.h" 

Tile::Tile(int x, int y, int width, int height, sf::Texture& texture) : x(x), y(y), width(width), height(height), rect(x, y, width, height), sprite(texture){
    sprite.setScale(1,1);
    sprite.setPosition(x,y);
}

int Tile::getX(){
    return x;
} 

int Tile::getY(){
    return y;
}

int Tile::getWidth(){
    return width;
}

int Tile::getHeight(){
    return height;
}

void Tile::setX(int x){
    this->x = x;
    sprite.setPosition(x,y);
}

void Tile::setY(int y){
    this->y = y;
    sprite.setPosition(x,y);
}

void Tile::setWidth(int w){
    width = w;
}

void Tile::setHeight(int h){
    height = h;
}

void Tile::draw(sf::RenderWindow& window){
    window.draw(sprite);
}