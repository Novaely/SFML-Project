#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "InputManager.h"
#include "PoolManager.h"
#include "GameManager.h"
#include "CollisionManager.h"
#include "HUDManager.h"

const float FPS_60 = 1.0f / 60.0f;

int main()
{
	CustomVector2f windowSize = {800, 600};
	//initialisation de toutes les variables importantes
	GameManager gameManager;
	Player player;
	int tick = 0;
	int boucle = 1;
	InputManager inputManager;
	PoolManager poolManager;
	gameManager.player = &player;
	player.position = { 400,300 };
	gameManager.poolManager = &poolManager;
	CollisionManager collisionManager(&gameManager, windowSize);
	HUDManager hudManager;

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
		tick++;
		if (gameManager.GetTime() >= boucle) {
			//std::cout << "FPS : " << tick << std::endl;
			gameManager.fps = tick;
			boucle++;
			tick = 0;
		}
		gameManager.Update(deltaTime, windowSize);
		gameManager.UpdateDestroyItem();
		collisionManager.Update(deltaTime);
		gameManager.UpdateDestroyItem();

		//Render
		window.clear();
		gameManager.Draw(window);
		hudManager.Draw(window);
		window.display();

		sf::sleep(sf::seconds(FPS_60 - deltaTime));
	}
}
