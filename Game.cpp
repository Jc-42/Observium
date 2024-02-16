#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Tile.h"
#include <iostream>

using namespace sf;
using namespace std;

Game::Game(int sizeX, int sizeY) : window(VideoMode(sizeX, sizeY), "Observium", Style::Titlebar | Style::Close), texture(), tile(40, 40, 100, 100, texture) {
    texture.loadFromFile("Grass.png");
    tile = Tile(40, 40, 100, 100, texture);
}


RenderWindow& Game::getWindow(){
    return window; 
}

void Game::paint(int frame){
    /*
    sf::Text text;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font); 

    text.setString("Frame Number: " + std::to_string(frame));

    text.setCharacterSize(24); // in pixels

    text.setFillColor(sf::Color::Red);

    CircleShape shape(10.f);
    shape.setFillColor(Color::Green);
    */
    
    

    Game::window.clear();
    //Game::window.draw(shape);
    //Game::window.draw(text);
    tile.draw(window);
    Game::window.display();
}
