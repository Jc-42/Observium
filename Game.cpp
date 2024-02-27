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

// Function to convert axial coordinates to cube coordinates
std::vector<int> axial_to_cube(int q, int r) {
  std::vector<int> cube(3); // Use a vector of size 3 for cube coordinates (q, r, s)
  cube[0] = q; // q = hex.q
  cube[1] = r; // r = hex.r
  cube[2] = -q - r; // s = -q-r
  return cube;
}

std::vector<int> cube_to_oddr(int q, int r, int s) {
   int col = q + (r - (r & 1)) / 2;
   int row = r;
   return std::vector<int>{col, row};
}

std::vector<int> oddr_to_cube(int x, int y) {
   int q = x - (y - (y & 1)) / 2;
   int r = y;
   int s = -q - r;
   return std::vector<int>{q, r, s};
}

// Function to add two vectors (arrays)
std::vector<int> vector_add(const std::vector<int>& v1, const std::vector<int>& v2) {
  if (v1.size() != v2.size()) {
    throw std::invalid_argument("Vectors must have the same size");
  }
  std::vector<int> result(v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    result[i] = v1[i] + v2[i];
  }
  return result;
}

// Function to generate results based on center and N
std::vector<std::vector<int>> generate_results(const std::vector<int>& center, int N) {
  std::vector<std::vector<int>> results;
  std::vector<std::vector<int>> resultsFin;
  for (int q = -N; q <= N; ++q) {
    for (int r = std::max(-N, -q - N); r <= std::min(N, -q + N); ++r) {
      int s = -q - r;
      std::vector<int> new_point = {q, r, s};
      results.push_back(vector_add(center, new_point));
    }
  }

  for(int i = 0; i < results.size(); i++){
    std::cout<<results.size() << " i " << i <<std::endl;
    resultsFin.push_back(cube_to_oddr(results[i][0], results[i][1], results[i][2]));
  }
  return resultsFin;
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
    std::vector<int> center = oddr_to_cube(5, 5);
    int N = 2;
    std::vector<std::vector<int>> results = generate_results(center, N);

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
