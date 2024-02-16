#include "Game.h"
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <string>
#include <vector>


using namespace std; 
int main() {
    sf::Event event;
    Game observium(1000, 1000);
    int i = 0;

    while (observium.getWindow().isOpen()) {
        observium.paint(i);
        i++;
        while (observium.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                observium.getWindow().close();
                return 0;
            }
        }
    }

    return 0;
}
