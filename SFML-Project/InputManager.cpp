#include "InputManager.h"
#include <iostream>

InputManager::InputManager() {}

void InputManager::InputCheck(sf::Event event, Player& player)
{
    switch (event.key.code) {
        case sf::Keyboard::Space : 
            std::cout << "SPACE press detected once!" << std::endl; 
            //futur tire
            break;
        case sf::Keyboard::A :
            player.SwitchColor();
            break;
    }
}