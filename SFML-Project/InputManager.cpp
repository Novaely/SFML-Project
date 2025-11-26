#include "InputManager.h"
#include <iostream>
#include "Utils.h"

InputManager::InputManager() {}

void InputManager::OneClickInputCheck(sf::Event event, Player& player)
{
    switch (event.key.code) {
        case sf::Keyboard::LShift:
            player.SwitchColor();
            break;
    }
}

void InputManager::ContinuInputCheck(sf::Event event, Player & player) {
    bool keyUp = (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    bool keyDown = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    bool keyLeft = (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    bool keyRight = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
    CustomVector2f inputDirection = { (float)keyRight - (float)keyLeft, (float)keyDown - (float)keyUp };
    player.inputDirection = inputDirection.GetNormalised();

    bool keyRotLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool keyRotRight = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    player.rotationDirection = keyRotRight - keyRotLeft;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        player.Shoot();
        std::cout << "Shoot (not implement)" << std::endl;
    }
}