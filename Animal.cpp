#include <SFML/Graphics.hpp>
#include "Animal.h" 
#include "Game.h"

#include <iostream>
#include <cmath>
#include <random>

Animal::Animal(double x, double y, int width, int height, sf::Texture& texture) : x(x), y(y), width(width), height(height), rect(x, y, width, height), sprite(texture), moving(false){
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
  
    
    if(moving){
        if(targetX > x){
            x += stepSize * deltaTime;
        }
        else if(targetX < x){            
            x -= stepSize * deltaTime;
        }
        if(targetY > y){
            y += stepSize * deltaTime;
        }
        else if(targetY < y){
            y -= stepSize * deltaTime;
        }

        waterNeed += .015 * stepSize * deltaTime;
        foodNeed += .0075 * stepSize * deltaTime;
        energyNeed += .002 * stepSize * deltaTime;

        if(abs(targetX - x) <= 10 * stepSize * deltaTime && abs(targetY - y) <= 10 * stepSize * deltaTime){
            moving = false;
            doingAction = false;
            if(action.compare("drinking") == 0){
                waterNeed = 0;
                action = "idle";
            }
        }
    }

    if(!doingAction){
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
        
        doingAction = true;
    }
    

    if(x + offsetX != sprite.getPosition().x || y + offsetY != sprite.getPosition().y){
        sprite.setPosition(x + offsetX, y + offsetY);
    }
    
    if((x + offsetX - 30 - (sprite.getTexture()->getSize().x * sprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (sprite.getTexture()->getSize().x * sprite.getScale().x) > 0) && (y + offsetY - 30 - (sprite.getTexture()->getSize().y * sprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (sprite.getTexture()->getSize().y * sprite.getScale().y) > 0)){
        window.draw(sprite);
    }

   
}


//TODO implement a memory for the animal so that it knows where its been
void Animal::moveTo(double x, double y){
    targetX = x; 
    targetY = y;
    moving = true;
    doingAction = true;
}

void Animal::drink(Tile (&map)[35][35]){
//TODO pregenerate this as a vecotr centered on 0,0 then add vector values to current values
  std::vector<int> center = Game::oddr_to_cube((int)(x / 35), (int)(y / 35));
  std::vector<std::vector<int>> results = Game::generate_results(center, sight);
  for(int i = 0; i < results.size(); i++){
    if(results[i][0] >= 0 && results[i][1] >= 0 && results[i][0] < 35 && results[i][1] < 35){
        Tile& current = map[results[0][0]][results[0][1]];
        if(current.tag.compare("water") == 0){
            action = "drinking";
            moveTo((double)current.getX() + current.getWidth() / 2.0, (double)current.getY() + current.getWidth() / 2.0);
            return;
        }
    }
  }
  //TODO implement somthing to do when the animal cannot find water in its vacity, maybe roll again with a +10 bonus
  // to keep searching for water. Also maybe implement a system where it makes slighly informed decision about where
  // to go
}

