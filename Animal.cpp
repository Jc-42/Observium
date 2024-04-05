#include <SFML/Graphics.hpp>
#include "Animal.h" 
#include "Game.h"

#include <iostream>
#include <cmath>
#include <random>
//TODO add a stack or queue based system for processing actions where the actions are processed from first to last. Stack may be better because it allows for new actions to override old ones which is more simmilar to real life. 
//optionally could use a priority queue but at first glance it seems funky



Animal::Animal(double x, double y, int width, int height, sf::Texture& lTexture, sf::Texture& rTexture, sf::Texture& lSleepTexture, sf::Texture& rSleepTexture) : x(x), y(y), width(width), height(height), rect(x, y, width, height), lSprite(lTexture), rSprite(rTexture), lSleepingSprite(lSleepTexture), rSleepingSprite(rSleepTexture), isWalking(false){
    lSprite.setOrigin(width / 2, height / 2);
    lSprite.setScale((double)width / (double)lTexture.getSize().x, (double)height / (double)lTexture.getSize().y);
    lSprite.setPosition(x,y);

    rSprite.setOrigin(width / 2, height / 2);
    rSprite.setScale((double)width / (double)rTexture.getSize().x, (double)height / (double)rTexture.getSize().y);
    rSprite.setPosition(x,y);

    lSleepingSprite.setOrigin(width / 2, height / 2);
    lSleepingSprite.setScale((double)width / (double)lSleepTexture.getSize().x, (double)height / (double)lSleepTexture.getSize().y);
    lSleepingSprite.setPosition(x,y);

    rSleepingSprite.setOrigin(width / 2, height / 2);
    rSleepingSprite.setScale((double)width / (double)rSleepTexture.getSize().x, (double)height / (double)rSleepTexture.getSize().y);
    rSleepingSprite.setPosition(x,y);

    health = 100;
    //Needs
    energyNeed = 0;
    foodNeed = 0;
    waterNeed = 0;
    sight = 2;
    directionFacing = 1;
    animalHexPos = Game::pixel_to_hex((double)x, (double)y, 48);
}

Animal::Animal(){

}

void Animal::draw(sf::RenderWindow& window, double offsetX, double offsetY){
    sf::CircleShape target(20);
    target.setOrigin(20, 20);
    target.setPosition(targetX + offsetX, targetY + offsetY);
    target.setFillColor(sf::Color().Red);
    window.draw(target);
    
    if(nextTile != nullptr){
        sf::CircleShape target2(4);
        target2.setPosition(nextTile->getX() + offsetX, nextTile->getY() + offsetY);
        target2.setFillColor(sf::Color().White);
        window.draw(target2);
    }
    
    if(directionFacing == 1){
        if(actionQueue.back().compare("sleeping") == 0){
            if((x + offsetX - 30 - (rSleepingSprite.getTexture()->getSize().x * rSleepingSprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (rSleepingSprite.getTexture()->getSize().x * rSleepingSprite.getScale().x) > 0) && (y + offsetY - 30 - (rSleepingSprite.getTexture()->getSize().y * rSleepingSprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (rSleepingSprite.getTexture()->getSize().y * rSleepingSprite.getScale().y) > 0)){
                rSleepingSprite.setPosition(x + offsetX, y + offsetY);
                window.draw(rSleepingSprite);
            }
        }
        //else if(action.compare("idle") == 0){
            else if((x + offsetX - 30 - (rSprite.getTexture()->getSize().x * rSprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (rSprite.getTexture()->getSize().x * rSprite.getScale().x) > 0) && (y + offsetY - 30 - (rSprite.getTexture()->getSize().y * rSprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (rSprite.getTexture()->getSize().y * rSprite.getScale().y) > 0)){
                rSprite.setPosition(x + offsetX, y + offsetY);
                window.draw(rSprite);
            }
        //}
    }
    else if(directionFacing == -1){
        if(actionQueue.back().compare("sleeping") == 0){
            if((x + offsetX - 30 - (lSleepingSprite.getTexture()->getSize().x * lSleepingSprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (lSleepingSprite.getTexture()->getSize().x * lSleepingSprite.getScale().x) > 0) && (y + offsetY - 30 - (lSleepingSprite.getTexture()->getSize().y * lSleepingSprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (lSleepingSprite.getTexture()->getSize().y * lSleepingSprite.getScale().y) > 0)){
                lSleepingSprite.setPosition(x + offsetX, y + offsetY);
                window.draw(lSleepingSprite);
            }
        }
        //else if(action.compare("idle") == 0){ 
            else if((x + offsetX - 30 - (lSprite.getTexture()->getSize().x * lSprite.getScale().x)  < window.getSize().x && x + offsetX + 30 + (lSprite.getTexture()->getSize().x * lSprite.getScale().x) > 0) && (y + offsetY - 30 - (lSprite.getTexture()->getSize().y * lSprite.getScale().y) < window.getSize().y && y + offsetY + 30 + (lSprite.getTexture()->getSize().y * lSprite.getScale().y) > 0)){
                lSprite.setPosition(x + offsetX, y + offsetY);
                window.draw(lSprite);
            }
        //}
    }

    
    if(!actionQueue.empty()){
        sf::Text text;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);

        for(std::string s : actionQueue){
            text.setString(text.getString() + s + " ");
        }

        text.setPosition(x + offsetX, y + offsetY - 20);

        text.setCharacterSize(12); // in pixels

        text.setFillColor(sf::Color::Red);

        window.draw(text);
    }

   
}

void Animal::update(sf::RenderWindow& window, double& deltaTime, double offsetX, double offsetY, Tile (&map)[35][35]){
    actionTime -= 1 * deltaTime;
    //if(isWalking){
       //move(deltaTime, map);
    //}
    if(/*!doingAction && !isWalking &&*/ actionTime <= 0 || foodNeed > 60 || waterNeed > 60 || energyNeed > 60 || (foodNeed + waterNeed + energyNeed) / 3 > 40){ //If rest 
        std::cout<<"energy: " << energyNeed << " food: " << foodNeed << " water: " << waterNeed<<std::endl;
        actionTime = 5;
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
                //doingAction = true;
                //action = "sleeping";
                //direNeeds.push_back("sleep action");
                //sleep(deltaTime);
            }
            else if(max == needValues[1]){
                //Take food action
                std::cout<<"FOOD ACTION"<<std::endl;
                if (std::count(direNeeds.begin(), direNeeds.end(), "food action") == 0) {
                    direNeeds.push_back("food action");
                    actionQueue.push_back("eating");
                }
                //foodNeed = 0;
            }
            else if(max == needValues[2]){
                //Take water action
                std::cout<<"WATER ACTION"<<std::endl;
                if (std::count(direNeeds.begin(), direNeeds.end(), "water action") == 0) {
                    actionQueue.push_back("looking for water");
                    direNeeds.push_back("water action");
                }
                //findWater(map, window);
            }
        }
    }
    
    //Process actions all logic of actions should be done here
    //This is the ONLY place that actionQueue or completeAction should ever be used
    if(energyNeed > 100){
        //doingAction = true;
        //action = "sleeping";
        actionQueue.push_back("sleep");
        //sleep(deltaTime);
    }

    if(!actionQueue.empty()){
        std::string currentAction = actionQueue.back();
        if(currentAction.compare("sleep") == 0){
            sleep(deltaTime);
            if(energyNeed <= 0){
                energyNeed = 0;
                completeAction();
                direNeeds.erase(std::remove(direNeeds.begin(), direNeeds.end(), "energy action"), direNeeds.end());
                //doingAction = false;
                //idle = true;
            }
        } 
        else if(currentAction.compare("looking for water") == 0){
            Tile* waterTile = findWater(map, window);
            
            
            if(waterTile != nullptr){ //If a water tile was found
                completeAction();
                //action = "drinking";
                //doingAction = true;
                //idle = false;
                setMoveTarget((double)waterTile->getX(), (double)waterTile->getY());
                
                actionQueue.push_back("moving to water");
                std::cout<<"water found"<<std::endl;
            }
            else{ //If a water tile wasnt found
                std::cout<<"no water found"<<std::endl;
                //Check if water need is higher than all other needs exept energy because energy is much less dangerous than thirst
                if(waterNeed > foodNeed){ //Basicly used to check if its worth it to search
                    std::vector<int> random;
                    std::cout<<"searching for water"<<std::endl;
                    do{ //Move to a random position in the animal sight.
                        std::random_device rd;
                        std::mt19937 gen(rd());
                        std::uniform_int_distribution<int> distributionX(x - (sqrt(3) * 48 * 0.5 * sight), x + (sqrt(3) * 48 * 0.5 * sight));
                        std::uniform_int_distribution<int> distributionY(y - (sqrt(3) * 48 * 0.5 * sight), y + (sqrt(3) * 48 * 0.5 * sight)); //Using inner radius for both so that the random area in entirely within the hexagon
                        int randX = distributionX(gen);
                        int randY = distributionY(gen);
                        if (randX < 20) randX = 20;
                        if (randX > window.getSize().x - 20) randX = window.getSize().x - 20;
                        if (randY < 20)  randY = 20;
                        if (randY > window.getSize().y - 20) randY = window.getSize().y - 20;
                        random = Game::pixel_to_hex(randX, randY, 48);
                        if(map[random[0]][random[1]].tag.compare("water") != 0){ //Avoid walking on water
                            //TODO make a function to do this called hex_to_pixel
                            setMoveTarget(random[0] * (48 * sqrt(3)) + (((sqrt(3) * 48.0) / (2.0)) * (random[1] % 2)), (double)random[1] * ((3.0 / 2.0) * 48));
                            actionQueue.push_back("moving");
                            std::cout<<"new spot found"<<std::endl;
                        }
                    } while(map[random[0]][random[1]].tag.compare("water") == 0);
                }
                else{
                    completeAction(); //No longer looking for water
                    std::cout<<"no longer looking for water"<<std::endl;
                }
                //TODO implement somthing to do when the animal cannot find water in its vacity, maybe roll again with a +10 bonus
                // to keep searching for water. Also maybe implement a system where it makes slighly informed decision about where
                // to go ie less random wandering
            }  
        }
        //moving to water is different from moving because the animal most be within one tile of the water when 
        //moving to water. 
        //If the animal is going exactly to the target use moving
        else if(currentAction.compare("moving to water") == 0){
            bool doneMoving = move(deltaTime, map, "water");
            if(doneMoving){
                completeAction();
                actionQueue.push_back("drinking water");
            }
        }
        else if(currentAction.compare("moving") == 0){
            bool doneMoving = move(deltaTime, map, "target");
            if(doneMoving){
                completeAction();
            }
        }
        else if(currentAction.compare("resting") == 0){
           energyNeed -= .002 * stepSize * deltaTime * 2.5; //Slightly lower energyNeed
           if(energyNeed < 0){
            energyNeed = 0;
           }
        }
        else if(currentAction.compare("drinking water") == 0){
            drink(deltaTime);
        }
        else if(currentAction.compare("eating") == 0){
            foodNeed -= .0075 * stepSize * deltaTime * 20;
            if(foodNeed <= 0){
                foodNeed = 0;
                completeAction();
                direNeeds.erase(std::remove(direNeeds.begin(), direNeeds.end(), "food action"), direNeeds.end());
            }
            
            
        }
    }
    else{
        actionQueue.push_back("resting");
    }


    //std::vector<int> test = Game::pixel_to_hex((double)x, (double)y, (double)width);
    
    //I dont know why stepSize is here?
    waterNeed += .015 * stepSize * deltaTime;
    foodNeed += .0075 * stepSize * deltaTime;
    energyNeed += .002 * stepSize * deltaTime;

    if(foodNeed > 100 || waterNeed > 100){
        health -= .02 * stepSize * deltaTime;
    }
    

    draw(window, offsetX, offsetY);
}

//Increments the animal to the target, returns true if the animal is done moving and false if its not 
bool Animal::move(double& deltaTime, Tile (&map)[35][35], std::string destination){
    if(!betweenHex){
        std::vector<std::vector<int>> tiles = getTilesWithinRange(1);
        double min = std::numeric_limits<double>::max();
        double distance;
        int nextTileX;
        int nextTileY;

        //Get the ajacent tile that is closest to the target but skip water tiles as they shouldent be walkable
        for(int i = 0; i < tiles.size(); i++){ 
            if(map[tiles[i][0]][tiles[i][1]].tag.compare("water") == 0){
                if(destination.compare("water") == 0){
                    //If the animal is going to water and is ajacent to a water tile return true.
                    isWalking = false;
                    betweenHex = false;
                    //idle = true;
                    return true;
                }

                continue; //skip water 
            }
            if(tiles[i][0] == animalHexPos[0] && tiles[i][1] == animalHexPos[1]) continue; //Skip the tile the animal is on
            if(std::find(pathMemory.begin(), pathMemory.end(), tiles[i]) != pathMemory.end()) continue; //Skip if the animal has moved over that tile in its current walk

            distance = sqrt(pow(map[tiles[i][0]][tiles[i][1]].getX() - targetX, 2) + pow(map[tiles[i][0]][tiles[i][1]].getY() - targetY, 2)); //Pythagorean Theorem! who ever said it wouldnt be useful in real life?
            if(distance < min){ // Find the closest tile to the target
                min = distance;
                nextTile = &map[tiles[i][0]][tiles[i][1]];
                nextTileX = tiles[i][0];
                nextTileY = tiles[i][1];
            }         
        }

        
        if(min == std::numeric_limits<double>::max()){
            //Animal is stuck since the map should never create an enclosed area this means the animal has hit a dead end therefor it must backtrack
            std::cout<< "dead end" <<std::endl;
            backtrackStep++;
            if(pathMemory.size() - backtrackStep < 0){
                //You done fucked up
            }
            else{
                pathMemory.push_back({pathMemory[pathMemory.size() - backtrackStep][0], pathMemory[pathMemory.size() - backtrackStep][1]}); //Add new tile to pathMemory
                backtrackStep++; //Increment again to account for push_back in above line
                nextTile = &map[pathMemory[pathMemory.size() - backtrackStep][0]][pathMemory[pathMemory.size() - backtrackStep][1]];
                betweenHex = true;
            }
        }   
        else{
            betweenHex = true;
            pathMemory.push_back({nextTileX, nextTileY}); //Add next tile to the memory
            backtrackStep = 0; //Reset the backtrackStep because the animal does not need to chain any more backtracks
        }
    }

    sf::Vector2f targetPosition = sf::Vector2f(nextTile->getX(), nextTile->getY());
    sf::Vector2f currentPosition = sf::Vector2f(x, y);

    sf::Vector2f direction = targetPosition - currentPosition;
    direction = Game::normalize(direction); // Function to normalize the vector (make its length 1)

    if(direction.x > 0) directionFacing = 1;
    else if(direction.x < 0) directionFacing = -1;
    
    x += direction.x * stepSize * deltaTime;
    y += direction.y * stepSize * deltaTime;

    animalHexPos = Game::pixel_to_hex((double)x, (double)y, 48);
    



    //Check if the animal has moved to the target if so stop walking, clear the path memory, and reset the backtrackStep
    if(sqrt(pow(targetX - x, 2) + pow(targetY - y, 2)) <= 10 * stepSize * deltaTime){
        isWalking = false;
        betweenHex = false;
        pathMemory.clear();
        backtrackStep = 0;
        //idle = true;
        return true;
    }
    //Check if the animal has moved to the next tile in its path
    else if(sqrt(pow(nextTile->getX() - x, 2) + pow(nextTile->getY() - y, 2)) <= 5 * stepSize * deltaTime){
        betweenHex = false;
    }
    
    return false;
}

//TODO implement a memory for the animal so that it knows where its been

//Sets the target to move to. The animal will not actually move intil Animal::move() is called
void Animal::setMoveTarget(double x, double y){
    targetX = x; 
    targetY = y;
    isWalking = true;
}

//Checks if any water tiles are within sight returns a pointer to the water tile
Tile* Animal::findWater(Tile (&map)[35][35], sf::RenderWindow& window){
    //TODO pregenerate this as a vecotr centered on 0,0 then add vector values to current values
    
    //convert the animal pos to hex, then search all surrounding hexs in a range of sight for water if found navigate to it.
    std::cout<<"get tiles"<<std::endl;
    std::vector<std::vector<int>> tiles = getTilesWithinRange(sight);

    std::cout<<"Center: " << animalHexPos[0] << ", " << animalHexPos[1] <<std::endl;
    for(int i = 0; i < tiles.size(); i++){
        std::cout<<"find WATER"<<std::endl;
        Tile* current = &map[tiles[i][0]][tiles[i][1]];
        if(current->tag.compare("water") == 0){
            std::cout<<"found"<<std::endl;
            return current;
        }   
    }

    std::cout<<"not found"<<std::endl;
    //No water found

    return nullptr;
    
}

void Animal::sleep(double& deltaTime){
    energyNeed -= .002 * stepSize * deltaTime * 3; //Deplete 3 times faster than it fills
}

void Animal::drink(double& deltaTime){
    std::cout << "drinking water" << std::endl;
    waterNeed -= .015 * stepSize * deltaTime * 35; //Deplete 35 times faster than it fills
    if(waterNeed <= 0){
        waterNeed = 0;
        completeAction();
        direNeeds.erase(std::remove(direNeeds.begin(), direNeeds.end(), "water action"), direNeeds.end());
        //action = "idle";
        //doingAction = false;
    }
}

std::vector<std::vector<int>> Animal::getTilesWithinRange(int range){
    std::vector<int> center = Game::oddr_to_cube(animalHexPos[0], animalHexPos[1]);
    std::vector<std::vector<int>> results = Game::generate_results(center, range, 35);
    return results;
}

//Completes the last action in actionQueue
void Animal::completeAction(){
    if(!actionQueue.empty()){
        std::string action = actionQueue.back();

        for(int i = actionQueue.size() - 2; i >= 0; i--){
            if(actionQueue[i].compare(action) == 0){
                actionQueue.erase(std::next(actionQueue.begin(), i));
                i++;
            }
        }
        if(actionQueue.back().compare("resting") != 0){
            for(std::string s : actionQueue) std::cout << s << std::endl;
            std::cout << "Removing " << actionQueue.back() <<std::endl;
            for(std::string s : actionQueue) std::cout << s << std::endl;
        }
        actionQueue.pop_back();
    }
}