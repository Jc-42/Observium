#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Tile.h"
#include "Animal.h"
#include <iostream>
#include <random>

using namespace sf;
using namespace std;

Game::Game(int sizeX, int sizeY) : window(VideoMode(sizeX, sizeY), "Observium", Style::Titlebar | Style::Close), tileTexture(), animalTexture(){
    double cameraOffsetX;
    double cameraOffsetY;
    tileTexture.loadFromFile("RotatedHexagon.png");
    animalTexture.loadFromFile("Rabbit.png");
    rabbit = Animal(50, 50, 20, 20, animalTexture);
    for(int i = 0; i < 35; i++){
        for(int j = 0; j < 35; j++){
            map[i][j] = Tile(i * 64 + (32 * (j % 2)), (double)j * 64.0 * (.75), 64, tileTexture);
        }
    }
    rabbit.moveTo(500, 500);  

    
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
    
    
    deltaTime = clock.restart().asSeconds();
    
    if(rabbit.moving == false){ 
        std::random_device rd;
        std::mt19937 gen(rd());  
        std::uniform_int_distribution<int> distributionX( rabbit.getX() - 150,  rabbit.getX() + 150);
        std::uniform_int_distribution<int> distributionY( rabbit.getY() - 150,  rabbit.getY() + 150);
        int randX = distributionX(gen);     
        int randY = distributionY(gen);  
        if(randX < 20) randX = 20;           
        if(randX > window.getSize().x - 20) randX = window.getSize().x - 20;              
        if(randY < 20) randY = 20;
        if(randY > window.getSize().y- 20) randY = window.getSize().y- 20;   
        rabbit.moveTo(randX, randY);
        std::cout << "rabbit moving to " << randX << " " << randY << std::endl;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        cameraOffsetX -= 200 * deltaTime;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        cameraOffsetX += 200 * deltaTime;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        cameraOffsetY -= 200 * deltaTime;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        cameraOffsetY += 200 * deltaTime;
    }

    Game::window.clear();
    //Game::window.draw(shape);
    //Game::window.draw(text);
    for(int i = 0; i < 34; i++){
        for(int j = 0; j < 35; j++){
            map[i][j].draw(window, -cameraOffsetX, -cameraOffsetY);
        }
    }
    rabbit.draw(window, deltaTime, -cameraOffsetX, -cameraOffsetY);
    Game::window.display();
}
