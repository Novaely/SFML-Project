#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "InputManager.h"
#include "PoolManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

const float FPS_60 = 1.0f / 60.0f;

int main()
{
	//initialisation de toutes les variables importantes
	Player player;
	float time = 0;
	int tick = 0;
	GameManager gameManager;
	InputManager inputManager;
	PoolManager poolManager;
	gameManager.player = &player;
	gameManager.poolManager = &poolManager;
	CollisionManager collisionManager(&gameManager);

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
		collisionManager.Update(deltaTime);
		gameManager.Update(deltaTime);

		//Render
		window.clear();
		gameManager.Draw(window);
		window.display();

		sf::sleep(sf::seconds(FPS_60 - deltaTime));
	}
}
