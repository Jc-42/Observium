#include <SFML/Graphics.hpp>
#include "Tile.h" 

#include <iostream>

Tile::Tile(int x, int y, int width, int height, sf::Texture& texture) : x(x), y(y), width(width), height(height), rect(x, y, width, height), sprite(texture){
    sprite.setScale((double)width / (double)texture.getSize().x, (double)height / (double)texture.getSize().y);
    sprite.setPosition(x,y);
}

Tile::Tile(){

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
    sprite.setScale(sprite.getTexture()->getSize().x / width, sprite.getScale().y);
}

void Tile::setHeight(int h){
    height = h;
    sprite.setScale(sprite.getScale().x, sprite.getTexture()->getSize().y / height);
}

void Tile::draw(sf::RenderWindow& window){
    window.draw(sprite);
}