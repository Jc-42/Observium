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

std::vector<int> cube_to_axial(const std::vector<int> &cube){
    std::vector<int> axial(2); // Use a vector of size 2 for axial coordinates (q, r)
    axial[0] = cube[0];        // q = cube.q
    axial[1] = cube[1];        // r = cube.r
    return axial;
}

Game::Game(int sizeX, int sizeY) : window(VideoMode(sizeX, sizeY), "Observium", Style::Titlebar | Style::Close){
    cameraOffsetX = 0;
    cameraOffsetY = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distributionWater(1, 100);
    grassTexture1.loadFromFile("Grass1.png");
    altGrassTexture1.loadFromFile("Grass1f.png");
    grassTexture2.loadFromFile("Grass2.png");
    altGrassTexture2.loadFromFile("Grass2f.png");
    grassTexture3.loadFromFile("Grass3.png");
    altGrassTexture3.loadFromFile("Grass3f.png");
    grassTexture4.loadFromFile("Grass4.png");
    altGrassTexture4.loadFromFile("Grass4f.png");
    grassTexture5.loadFromFile("Grass5.png");
    waterTexture.loadFromFile("RotatedWater.png");
    animalTextureL.loadFromFile("RabbitLNew.png");
    animalTextureR.loadFromFile("RabbitRNew.png");
    animalTextureSleepingL.loadFromFile("RabbitLSleeping.png");
    animalTextureSleepingR.loadFromFile("RabbitRSleeping.png");
    rabbit = Animal(50, 50, 25, 25, animalTextureL, animalTextureR, animalTextureSleepingL, animalTextureSleepingR);
    int rWater;
    int rGrass;
    for (int i = 0; i < 35; i++){
        for (int j = 0; j < 35; j++){
            rWater = distributionWater(gen);
            rGrass = distributionWater(gen);
            if (rWater <= 50){
                map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, waterTexture, "water");
            }
            else{
                if(rGrass < 10) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, grassTexture1, "grass");
                else if(rGrass >= 10 && rGrass < 20) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, altGrassTexture1, "grass");
                else if(rGrass >= 20 && rGrass < 30) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, grassTexture2, "grass");
                else if(rGrass >= 30 && rGrass < 40) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, altGrassTexture2, "grass");
                else if(rGrass >= 40 && rGrass < 50) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, grassTexture3, "grass");
                else if(rGrass >= 50 && rGrass < 60) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, altGrassTexture3, "grass");
                else if(rGrass >= 60 && rGrass < 70) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, grassTexture4, "grass");
                else if(rGrass >= 70 && rGrass < 80) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, altGrassTexture4, "grass");
                else if(rGrass >= 80) map[i][j] = Tile(i * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (j % 2)), (double)j * ((3.0 / 2.0) * 48), 48, grassTexture5, "grass");
            }
        }
    }
    //rabbit.moveTo(500, 500);

    // Example usage
    std::vector<int> center = Game::oddr_to_cube(5, 5);
    int N = 2;
    std::vector<std::vector<int>> results = Game::generate_results(center, N);

    // Print the results
    for (const auto &point : results){
        std::cout << "[" << point[0] << ", " << point[1] << ", "
                  << "]" << std::endl;
    }
}

RenderWindow &Game::getWindow(){
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        cameraOffsetX -= 200 * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        cameraOffsetX += 200 * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        cameraOffsetY -= 200 * deltaTime;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        cameraOffsetY += 200 * deltaTime;
    }
/*
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    std::vector<int> hexPos = Game::pixel_to_hex(mousePosition.x, mousePosition.y, 32);

    sf::CircleShape hoverPos(5);
    hoverPos.setPosition(hexPos[0] * (32 * sqrt(3)) + (((sqrt(3) * 32.0) / (2.0)) * (hexPos[1] % 2)), (double)hexPos[1] * ((3.0 / 2.0) * 32));
    hoverPos.setFillColor(sf::Color().Black);
*/
    Game::window.clear();
    // Game::window.draw(shape);
    // Game::window.draw(text);
    for (int i = 0; i < 34; i++){
        for (int j = 0; j < 35; j++){
            map[i][j].draw(window, -(int)cameraOffsetX, -(int)cameraOffsetY);
        }
    }
    if(rabbit.health > 0) rabbit.draw(window, deltaTime, -(int)cameraOffsetX, -(int)cameraOffsetY, map);
    //window.draw(hoverPos);
    Game::window.display();

    if (rabbit.isWalking == false && rabbit.doingAction == false){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distributionX(rabbit.x - 350, rabbit.x + 350);
        std::uniform_int_distribution<int> distributionY(rabbit.y - 350, rabbit.y + 350);
        int randX = distributionX(gen);
        int randY = distributionY(gen);
        if (randX < 20) randX = 20;
        if (randX > window.getSize().x - 20) randX = window.getSize().x - 20;
        if (randY < 20)  randY = 20;
        if (randY > window.getSize().y - 20) randY = window.getSize().y - 20;
        std::vector<int> random = Game::pixel_to_hex(randX, randY, 48);
        if(map[random[0]][random[1]].tag.compare("water") != 0){
            //TODO make a function to do this called hex_to_pixel
            rabbit.moveTo(random[0] * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (random[1] % 2)), (double)random[1] * ((3.0 / 2.0) * 48));
        }
    }

}
