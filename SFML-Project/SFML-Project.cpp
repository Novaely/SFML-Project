#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "InputManager.h"

const float FPS_60 = 1.0f / 60.0f;

int main()
{
	//initialisation de toutes les variables importantes
	Player player;
	float time = 0;
	int tick = 0;
	InputManager inputManager;
	PoolManager poolManager;
	player.poolManager = &poolManager;

	sf::Clock clock;
	float deltaTime = 0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML-Project");
	// Initialise everything below
	// 
	 // Game loop
	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		 time += deltaTime;

		 //CHeck Input
		sf::Event event;
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

		//Update


		//Render
		window.clear();
		player.Update(deltaTime,window);
		window.display();

		sf::sleep(sf::seconds(FPS_60 - deltaTime));
	}
}
