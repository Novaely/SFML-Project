#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "InputManager.h"
#include "PoolManager.h"
#include "GameManager.h"
#include "CollisionManager.h"
#include "LightningNode.h"

const float FPS_60 = 1.0f / 60.0f;

int main()
{
	CustomVector2f windowSize = {800, 600};
	//initialisation de toutes les variables importantes
	Player player;
	float time = 0;
	int tick = 0;
	GameManager gameManager;
	InputManager inputManager;
	PoolManager poolManager;
	gameManager.player = &player;
	gameManager.poolManager = &poolManager;
	CollisionManager collisionManager(&gameManager, windowSize);

	sf::Clock clock;
	float deltaTime = 0;

	float fpsTimer = 0.0f;
	int frameCount = 0;

	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML-Project");
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
				inputManager.OneClickInputPressed(event, player);
			}
			if (event.type == sf::Event::KeyReleased) {
				inputManager.OneClickInputUnpressed(event);
			}
		}
		inputManager.ContinuInputCheck(event, player);

		//Update
		gameManager.Update(deltaTime, windowSize);
		gameManager.UpdateDestroyItem();
		collisionManager.Update(deltaTime);
		gameManager.UpdateDestroyItem();

		//Render
		window.clear();
		gameManager.Draw(window);
		window.display();

		fpsTimer += deltaTime;
		frameCount++;

		if (fpsTimer >= 1.0f) {
			std::cout << "FPS: " << frameCount << std::endl;
			fpsTimer = 0.0f;
			frameCount = 0;
		}

		sf::sleep(sf::seconds(FPS_60 - deltaTime));
	}
}
