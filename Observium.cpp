#include "Game.h"
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <string>
#include <vector>


using namespace std; 
int main() {
    sf::Event event;
    Game observium(1120, 1120); //35x35 tiles
    sf::RenderWindow& window = observium.getWindow();

    while (window.isOpen()) {
        observium.paint();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }
        }
    }

    return 0;
}
