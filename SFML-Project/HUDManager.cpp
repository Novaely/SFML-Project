#include "HUDManager.h"


HUDManager::HUDManager()
{
	gameManager = GameManager::GetInstance();
	font.loadFromFile("ARIAL.TTF");

	score.setFont(font);                // Police
	timer.setFont(font);                // Police
	multiplicateur.setFont(font);                // Police
	score.setString("Bonjour SFML !");  // Contenu
	timer.setString("Bonjour SFML !");  // Contenu
	multiplicateur.setString("Bonjour SFML !");  // Contenu
	score.setCharacterSize(28);         // Taille du texte
	timer.setCharacterSize(28);         // Taille du texte
	multiplicateur.setCharacterSize(28);         // Taille du texte
	score.setFillColor(sf::Color::White);   // Couleur
	timer.setFillColor(sf::Color::White);   // Couleur
	multiplicateur.setFillColor(sf::Color::White);   // Couleur
	score.setPosition(50, 60);             // Position dans la fenêtre
	timer.setPosition(50, 25);             // Position dans la fenêtre
	multiplicateur.setPosition(170, 60);             // Position dans la fenêtre

}

void HUDManager::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < gameManager->player->health; i++)
	{
		CreateLifePoint({ (9.0f + i) * 40.0f, 25.0f }, window);
	}
	score.setString("Score : " + std::to_string(gameManager->score));
	window.draw(score);
	timer.setString("Time : " + std::to_string((int)gameManager->GetTime()));
	window.draw(timer);
	if ( gameManager->GetMultiplicateur() > 1)
	{
		multiplicateur.setString("x" + std::to_string(gameManager->GetMultiplicateur()));
		window.draw(multiplicateur);
	}
}

void HUDManager::CreateLifePoint(CustomVector2f position, sf::RenderWindow& window)
{
	sf::CircleShape lifePointShape(10.0f);
	lifePointShape.setFillColor(sf::Color::Red);
	lifePointShape.setPosition(position);
	window.draw(lifePointShape);
}


