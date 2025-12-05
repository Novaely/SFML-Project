#include "HUDManager.h"


HUDManager::HUDManager()
{
	gameManager = GameManager::GetInstance();
	font.loadFromFile("ARIAL.TTF");

	text.setFont(font);                // Police
	text.setString("Bonjour SFML !");  // Contenu
	text.setCharacterSize(28);         // Taille du texte
	text.setFillColor(sf::Color::White);   // Couleur
	text.setPosition(50, 25);             // Position dans la fenêtre
}

void HUDManager::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < gameManager->player->health; i++)
	{
		CreateLifePoint({ (9.0f + i) * 40.0f, 25.0f }, window);
	}
	text.setString("Score : " + std::to_string(gameManager->score));
	window.draw(text);
}

void HUDManager::CreateLifePoint(CustomVector2f position, sf::RenderWindow& window)
{
	sf::CircleShape lifePointShape(10.0f);
	lifePointShape.setFillColor(sf::Color::Red);
	lifePointShape.setPosition(position);
	window.draw(lifePointShape);
}


