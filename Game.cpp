#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Tile.h"
#include "Animal.h"
#include <iostream>
#include <random>
using namespace sf;
using namespace std;
#include <tuple>
#include <vector>
#include <limits>

std::vector<int> cube_to_axial(const std::vector<int>& cube) {
  std::vector<int> axial(2); // Use a vector of size 2 for axial coordinates (q, r)
  axial[0] = cube[0]; // q = cube.q
  axial[1] = cube[1]; // r = cube.r
  return axial;
}

Game::Game(int sizeX, int sizeY) : window(VideoMode(sizeX, sizeY), "Observium", Style::Titlebar | Style::Close), tileTexture(), animalTexture(){
  double cameraOffsetX;
  double cameraOffsetY;
  std::random_device rd;
  std::mt19937 gen(rd());  
  std::uniform_int_distribution<int> distributionWater(1, 100);   
  tileTexture.loadFromFile("RotatedHexagon.png");
  waterTexture.loadFromFile("RotatedWater.png");
  animalTexture.loadFromFile("Rabbit.png");
  rabbit = Animal(50, 50, 20, 20, animalTexture);
  int rWater;
  for(int i = 0; i < 35; i++){
      for(int j = 0; j < 35; j++){
          rWater = distributionWater(gen); 
          if(rWater <= 5){
              map[i][j] = Tile(i * 64 + (32 * (j % 2)), (double)j * 64.0 * (.75), 64, waterTexture, "water");
          } 
          else{ 
              map[i][j] = Tile(i * 64 + (32 * (j % 2)), (double)j * 64.0 * (.75), 64, tileTexture, "grass");
          }
      }
  }
  rabbit.moveTo(500, 500);  

  // Example usage
  std::vector<int> center = Game::oddr_to_cube(5, 5);
  int N = 2;
  std::vector<std::vector<int>> results = Game::generate_results(center, N);

  // Print the results
  for (const auto& point : results) {
      std::cout << "[" << point[0] << ", " << point[1] << ", " << "]" << std::endl;
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
    
    
    deltaTime = clock.restart().asSeconds();
    
    

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
    rabbit.draw(window, deltaTime, -cameraOffsetX, -cameraOffsetY, map);
    Game::window.display();

    if(rabbit.moving == false){ 
      std::random_device rd;
      std::mt19937 gen(rd());  
      std::uniform_int_distribution<int> distributionX( rabbit.x - 150,  rabbit.x + 150);
      std::uniform_int_distribution<int> distributionY( rabbit.y - 150,  rabbit.y + 150);
      int randX = distributionX(gen);     
      int randY = distributionY(gen);  
      if(randX < 20) randX = 20;           
      if(randX > window.getSize().x - 20) randX = window.getSize().x - 20;              
      if(randY < 20) randY = 20;
      if(randY > window.getSize().y- 20) randY = window.getSize().y- 20;   
      rabbit.moveTo(randX, randY);
    }
}
