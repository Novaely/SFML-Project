#include "HUDManager.h"


HUDManager::HUDManager()
{
	gameManager = GameManager::GetInstance();
	_font.loadFromFile("ARIAL.TTF");

	_score.setFont(_font);                // Police
	_timer.setFont(_font);                // Police
	_level.setFont(_font);                // Police
	_multiplicateur.setFont(_font);                // Police
	_score.setCharacterSize(28);         // Taille du texte
	_timer.setCharacterSize(28);         // Taille du texte
	_level.setCharacterSize(28);         // Taille du texte
	_multiplicateur.setCharacterSize(28);         // Taille du texte
	_score.setFillColor(sf::Color::White);   // Couleur
	_timer.setFillColor(sf::Color::White);   // Couleur
	_level.setFillColor(sf::Color::White);   // Couleur
	_multiplicateur.setFillColor(sf::Color::White);   // Couleur
	_score.setPosition(50, 60);             // Position dans la fenêtre
	_timer.setPosition(50, 25);             // Position dans la fenêtre
	_level.setPosition(50, 95);             // Position dans la fenêtre
	_multiplicateur.setPosition(30, 550);             // Position dans la fenêtre

}

void HUDManager::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < gameManager->player->health; i++)
	{
		CreateLifePoint({ (9.0f + i) * 40.0f, 25.0f }, window);
	}
	_score.setString("Score : " + std::to_string(gameManager->score));
	window.draw(_score);
	_timer.setString("Time : " + std::to_string((int)gameManager->GetTime()));
	window.draw(_timer);
	if ( gameManager->GetMultiplicateur() > 1)
	{
		_multiplicateur.setString("x" + std::to_string(gameManager->GetMultiplicateur()));
		window.draw(_multiplicateur);
	}
	_level.setString("Level : " + std::to_string(gameManager->GetLevel()));
	window.draw(_level);
}

void HUDManager::CreateLifePoint(CustomVector2f position, sf::RenderWindow& window)
{
	sf::CircleShape lifePointShape(10.0f);
	lifePointShape.setFillColor(sf::Color::Red);
	lifePointShape.setPosition(position);
	window.draw(lifePointShape);
}


