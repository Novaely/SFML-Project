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
	InputManager inputManager;
	PoolManager poolManager;
	gameManager.poolManager = &poolManager;
	CollisionManager collisionManager(windowSize);
	HUDManager hudManager;

	sf::Clock clock;
	float deltaTime = 0;

	// Variables for FPS
	int frameCount = 0;
	float fpsElapsedTime = 0;
	const float fpsTimeToWait = 0.5f;

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
				inputManager.OneClickInputPressed(event, *(gameManager.player));
			}
			if (event.type == sf::Event::KeyReleased) {
				inputManager.OneClickInputUnpressed(event);
			}
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				Vec2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				if (gameManager.pause && hudManager.DoRestartButtonContainsPos(mousePos))
				{
					gameManager.RestartGame();
				}
			}
		}
		inputManager.ContinuInputCheck(event, *(gameManager.player));

		//Update
		if (gameManager.pause == false)
		{
			frameCount++;
			fpsElapsedTime += deltaTime;
			if (fpsElapsedTime >= fpsTimeToWait)
			{
				gameManager.fps = (float)frameCount / fpsTimeToWait;
				//std::cout << "FPS : " << gameManager.fps << std::endl;
				//std::cout << gameManager.gameObjects.size() << std::endl;
				frameCount = 0;
				fpsElapsedTime = 0;
			}

			gameManager.Update(deltaTime, windowSize);
			collisionManager.Update(deltaTime);
			gameManager.UpdateDestroyItem();
			
			//Render
			window.clear();
			gameManager.Draw(window);
			hudManager.Draw(window);
			window.display();
		}

		sf::sleep(sf::seconds(FPS_60 - deltaTime));
	}
}
