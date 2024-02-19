#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Tile.h"
#include <iostream>

using namespace sf;
using namespace std;

Game::Game(int sizeX, int sizeY) : window(VideoMode(sizeX, sizeY), "Observium", Style::Titlebar | Style::Close), texture(){
    texture.loadFromFile("Grass.png");
    for(int i = 0; i < 35; i++){
        for(int j = 0; j < 35; j++){
            map[i][j] = Tile(i * 32, j * 32, 32, 32, texture);
        }
    }
}


RenderWindow& Game::getWindow(){
    return window; 
}

void Game::paint(){
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
    for(int i = 0; i < 35; i++){
        for(int j = 0; j < 35; j++){
            map[i][j].draw(window);
        }
    }
    Game::window.display();
}
