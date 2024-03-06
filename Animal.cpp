#include <SFML/Graphics.hpp>
#include "Animal.h" 
#include "Game.h"

#include <iostream>
#include <cmath>
#include <random>

Animal::Animal(double x, double y, int width, int height, sf::Texture& texture) : x(x), y(y), width(width), height(height), rect(x, y, width, height), sprite(texture), isWalking(false){
    sprite.setOrigin(width / 2, height / 2);
    sprite.setScale((double)width / (double)texture.getSize().x, (double)height / (double)texture.getSize().y);
    sprite.setPosition(x,y);
    health = 100;
    //Needs
    energyNeed = 0;
    foodNeed = 0;
    waterNeed = 0;
    sight = 2;
}

Animal::Animal(){

}


void Animal::draw(sf::RenderWindow& window, double& deltaTime, double offsetX, double offsetY, Tile (&map)[35][35]){
    sf::CircleShape target(20);
    /*target.setOrigin(20, 20);
    target.setPosition(targetX + offsetX, targetY + offsetY);
    target.setFillColor(sf::Color().Red);
    window.draw(target);
    */
    
    

    if(isWalking){
       move(deltaTime, map);
    }
    /*
    if(nextTile != nullptr){
        sf::CircleShape target2(4);
        target2.setPosition(nextTile->getX() + offsetX, nextTile->getY() + offsetY);
        target2.setFillColor(sf::Color().White);
        window.draw(target2);
    }
    */

    if(!doingAction && !isWalking){
        std::cout<<"energy: " << energyNeed << " food: " << foodNeed << " water: " << waterNeed<<std::endl;
        //TODO make this much more simplified and less spagetti.
        std::random_device rd;
        std::mt19937 gen(rd());  
        std::uniform_int_distribution<int>  needDistribution(0, 100);  
        int needRolls[3]; 
        int needValues[3];
        bool oneRollSuccessfull = false;
        std::fill_n(needValues, 3, -1);

        for(int i = 0; i < 3; i++){
            needRolls[i] = needDistribution(gen); 
        }

        if(needRolls[0] < energyNeed){
            needValues[0] = energyNeed - needRolls[0];
            oneRollSuccessfull = true;
        }
        if(needRolls[1] < foodNeed){
            needValues[1] = foodNeed - needRolls[1];
            oneRollSuccessfull = true;
        }
        if(needRolls[2] < waterNeed){
            needValues[2] = waterNeed - needRolls[2];
            oneRollSuccessfull = true;
        }

        if(oneRollSuccessfull){
            int max = INT32_MIN;
            for(int i = 0; i < 3; i++){
                if(needValues[i] > max) max = needValues[i];
            }
            
            if(max == needValues[0]){
                //Take energy action
                std::cout<<"ENERGY ACTION"<<std::endl;
                energyNeed = 0;
            }
            else if(max == needValues[1]){
                //Take food action
                std::cout<<"FOOD ACTION"<<std::endl;
                foodNeed = 0;
            }
            else if(max == needValues[2]){
                //Take water action
                std::cout<<"WATER ACTION"<<std::endl;
                drink(map);
            }
        }
    }
    

    if(x + offsetX != sprite.getPosition().x || y + offsetY != sprite.getPosition().y){
        sprite.setPosition(x + offsetX, y + offsetY);
    }
    
    if((x + offsetX - 30 - (sprite.getTexture()->getSize().x * sprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (sprite.getTexture()->getSize().x * sprite.getScale().x) > 0) && (y + offsetY - 30 - (sprite.getTexture()->getSize().y * sprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (sprite.getTexture()->getSize().y * sprite.getScale().y) > 0)){
        window.draw(sprite);
    }

    //std::vector<int> test = Game::pixel_to_hex((double)x, (double)y, (double)width);
}

void Animal::move(double& deltaTime, Tile (&map)[35][35]){
    if(!betweenHex){
        std::vector<int> animalHexPos = Game::pixel_to_hex((double)x, (double)y, 32);
        std::vector<int> center = Game::oddr_to_cube(animalHexPos[0], animalHexPos[1]);
        std::vector<std::vector<int>> results = Game::generate_results(center, 1);
        double min = std::numeric_limits<double>::max();
        double distance;

        //Get the ajacent tile that is closest to the target but skip water tiles as they shouldent be walkable
        for(int i = 0; i < results.size(); i++){
            if(results[i][0] >= 0 && results[i][0] < 35 && results[i][1] >= 0 && results[i][1] < 35){
                if(map[results[i][0]][results[i][1]].tag.compare("water") == 0){
                    if(action.compare("drinking") == 0){
                        isWalking = false;
                        betweenHex = false;
                        waterNeed = 0;
                        action = "idle";
                        doingAction = false;
                        std::cout<< "drank water" << std::endl;
                        return;
                    }
                    continue;    
                }
                if(results[i][0] == animalHexPos[0] && results[i][1] == animalHexPos[1]) continue; //Skip the tile the animal is on
                distance = sqrt(pow(map[results[i][0]][results[i][1]].getX() - targetX, 2) + pow(map[results[i][0]][results[i][1]].getY() - targetY, 2)); //Pythagorean Theorem! who ever said it would'nt be useful in real life?
                if(distance < min){
                    min = distance;
                    nextTile = &map[results[i][0]][results[i][1]];
                }
            }            
        }

        if(min == std::numeric_limits<double>::max()){
            std::cout<< "No Path Found" <<std::endl; //If this is called you done fucked up
        }   
        else{
            betweenHex = true;
        }
    }


        if(nextTile->getX() > x){
            x += stepSize * deltaTime;
        }
        else if(nextTile->getX() < x){            
            x -= stepSize * deltaTime;
        }
        if(nextTile->getY() > y){
            y += stepSize * deltaTime;
        }
        else if(nextTile->getY() < y){
            y -= stepSize * deltaTime;
        }

        waterNeed += .015 * stepSize * deltaTime;
        foodNeed += .0075 * stepSize * deltaTime;
        energyNeed += .002 * stepSize * deltaTime;

        
        //Check if the animal has moved to the target
        if(sqrt(pow(targetX - x, 32) + pow(targetY - y, 2)) <= 10 * stepSize * deltaTime){
            isWalking = false;
            betweenHex = false;
        }

        //Check if the animal has moved to the next tile in its path
        else if(sqrt(pow(nextTile->getX() - x, 2) + pow(nextTile->getY() - y, 2)) <= 5 * stepSize * deltaTime){
            betweenHex = false;
        }
}

//TODO implement a memory for the animal so that it knows where its been
void Animal::moveTo(double x, double y){
    targetX = x; 
    targetY = y;
    isWalking = true;
}

void Animal::drink(Tile (&map)[35][35]){
//TODO pregenerate this as a vecotr centered on 0,0 then add vector values to current values
    
    //convert the animal pos to hex, then search all surrounding hexs in a range of sight for water if found navigate to it.
    std::vector<int> animalHexPos = Game::pixel_to_hex((double)x, (double)y, 32);
    std::vector<int> center = Game::oddr_to_cube(animalHexPos[0], animalHexPos[1]);
    std::vector<std::vector<int>> results = Game::generate_results(center, sight);

    std::cout<<"Center: " << animalHexPos[0] << ", " << animalHexPos[1] <<std::endl;
    for(int i = 0; i < results.size(); i++){
        if(results[i][0] >= 0 && results[i][1] >= 0 && results[i][0] < 35 && results[i][1] < 35){
            Tile& current = map[results[i][0]][results[i][1]];
            if(current.tag.compare("water") == 0){
                action = "drinking";
                std::cout<<"water at: " << (double)current.getX() << ", " << (double)current.getY() << std::endl;
                doingAction = true;
                moveTo((double)current.getX(), (double)current.getY());
                return;
            }
        }
        else{
           std::cout<<"this tile is out of bounds"<<std::endl;
        }
        
    }
  //TODO implement somthing to do when the animal cannot find water in its vacity, maybe roll again with a +10 bonus
  // to keep searching for water. Also maybe implement a system where it makes slighly informed decision about where
  // to go ie less random wandering
}

