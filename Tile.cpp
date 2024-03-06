#include <SFML/Graphics.hpp>
#include "Tile.h" 
#include <cmath>

#include <iostream>

Tile::Tile(double x, double y, int radius, sf::Texture& texture, std::string tag) : x(x), y(y), radius(radius), sprite(texture) {
    hexagon = new sf::CircleShape(radius, 6);
    hexagon->setOutlineThickness(1);
    hexagon->setOutlineColor(sf::Color().Cyan);
    hexagon->setFillColor(sf::Color().Transparent);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setScale(((double)radius * sqrt(3)) / (double)texture.getSize().x, ((double)radius * 2) / (double)texture.getSize().y);
    sprite.setPosition(x, y);
    hexagon->setOrigin(radius, radius);
    hexagon->setPosition(x, y);
    this->tag = tag;
}

Tile::Tile() : x(0), y(0), radius(1) {
    hexagon = new sf::CircleShape(radius, 6);
}



void Tile::draw(sf::RenderWindow& window, double offsetX, double offsetY){
    if(x + offsetX != sprite.getPosition().x || y + offsetY != sprite.getPosition().y){
        sprite.setPosition(x + offsetX, y + offsetY);
    }
    
    if((x + offsetX - 30 - (sprite.getTexture()->getSize().x * sprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (sprite.getTexture()->getSize().x * sprite.getScale().x) > 0) && (y + offsetY - 30 - (sprite.getTexture()->getSize().y * sprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (sprite.getTexture()->getSize().y * sprite.getScale().y) > 0)){
        window.draw(sprite);
        //window.draw(*hexagon);
    }
}