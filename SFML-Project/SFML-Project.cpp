#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include "InputManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "ChronoSpacer");
    // Initialise everything below
    // Game loop

    Player player;

    InputManager inputManager;

    /*Bullet bullet;
    bullet.maxInputSpeed = 50;
    bullet.position = CustomVector2f(300, 100);
    bullet.inputDirection = CustomVector2f(1, 0);
    bullet.Active();*/

    sf::Clock clock;
    float deltaTime = 0;

    while (window.isOpen()) {
        sf::Event event;
        deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            // Process any input event here
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                inputManager.OneClickInputCheck(event, player);
            }
        }
        
        inputManager.ContinuInputCheck(event, player);

        window.clear();

        //bullet.Update(deltaTime, window);
        player.Update(deltaTime, window);

        window.display();
    }
}