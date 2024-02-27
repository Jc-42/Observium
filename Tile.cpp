#include <SFML/Graphics.hpp>
#include "Tile.h" 

#include <iostream>

Tile::Tile(double x, double y, int width, sf::Texture& texture, std::string tag) : x(x), y(y), width(width), sprite(texture) {
    hexagon = new sf::CircleShape(width, 6);
    sprite.setScale((double)width / (double)texture.getSize().x, (double)width / (double)texture.getSize().y);
    sprite.setPosition(x, y);
    this->tag = tag;
}

Tile::Tile() : x(0), y(0), width(1) {
    hexagon = new sf::CircleShape(width, 6);
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

void Tile::setX(int x){
    this->x = x;
}

void Tile::setY(int y){
    this->y = y;
}

void Tile::setWidth(int w){
    width = w;
    sprite.setScale(sprite.getTexture()->getSize().x / width, sprite.getScale().y);
}


void Tile::draw(sf::RenderWindow& window, double offsetX, double offsetY){
    if(x + offsetX != sprite.getPosition().x || y + offsetY != sprite.getPosition().y){
        sprite.setPosition(x + offsetX, y + offsetY);
    }
    
    if((x + offsetX - 30 - (sprite.getTexture()->getSize().x * sprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (sprite.getTexture()->getSize().x * sprite.getScale().x) > 0) && (y + offsetY - 30 - (sprite.getTexture()->getSize().y * sprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (sprite.getTexture()->getSize().y * sprite.getScale().y) > 0)){
        window.draw(sprite);
    }
}