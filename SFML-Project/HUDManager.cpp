#include "HUDManager.h"


HUDManager::HUDManager()
{
	gameManager = GameManager::GetInstance();
	_font.loadFromFile("ARIAL.TTF");

	_score.setFont(_font);                // Police
	_timer.setFont(_font);                // Police
	_level.setFont(_font);                // Police
	_multiplicateur.setFont(_font);                // Police
	_fps.setFont(_font);                // Police
	_score.setCharacterSize(28);         // Taille du texte
	_timer.setCharacterSize(28);         // Taille du texte
	_level.setCharacterSize(28);         // Taille du texte
	_multiplicateur.setCharacterSize(28);         // Taille du texte
	_fps.setCharacterSize(28);         // Taille du texte
	_score.setFillColor(sf::Color::White);   // Couleur
	_timer.setFillColor(sf::Color::White);   // Couleur
	_level.setFillColor(sf::Color::White);   // Couleur
	_multiplicateur.setFillColor(sf::Color::White);   // Couleur
	_fps.setFillColor(sf::Color::White);   // Couleur
	_score.setPosition(50, 60);             // Position dans la fenêtre
	_timer.setPosition(50, 25);             // Position dans la fenêtre
	_level.setPosition(50, 95);             // Position dans la fenêtre
	_multiplicateur.setPosition(30, 550);             // Position dans la fenêtre
	_fps.setPosition(650, 550);             // Position dans la fenêtre

	_button.setFillColor(sf::Color::Blue);
	_button.setSize({200, 35});
	_button.setPosition({300, 275});

}

void HUDManager::Draw(sf::RenderWindow& window)
{
	if (!gameManager->pause)
	{
		for (int i = 0; i < gameManager->player->health; i++)
		{
			CreateLifePoint({ (9.0f + i) * 40.0f, 25.0f }, window);
		}
		_score.setString("Score : " + std::to_string(gameManager->score));
		window.draw(_score);
		_timer.setString("Time : " + std::to_string((int)gameManager->GetTime()));
		window.draw(_timer);
		if (gameManager->GetMultiplicateur() > 1)
		{
			_multiplicateur.setString("x" + std::to_string(gameManager->GetMultiplicateur()));
			window.draw(_multiplicateur);
		}
		_level.setString("Level : " + std::to_string(gameManager->GetLevel()));
		window.draw(_level);
		_fps.setString("FPS : " + std::to_string(gameManager->GetFPS()));
		window.draw(_fps);
	}
	else
	{
		_level.setPosition(320, 150);
		_level.setCharacterSize(32);  
		_level.setFillColor(sf::Color::Red);  
		_level.setString("Game Over");
		_score.setPosition(315,200);
		_score.setString("Score final : " + std::to_string(gameManager->score));
		_multiplicateur.setPosition(350, 275);
		_multiplicateur.setString("Restart");


		window.draw(_score);
		window.draw(_level);
		window.draw(_button);
		window.draw(_multiplicateur);
	}
}

void HUDManager::CreateLifePoint(CustomVector2f position, sf::RenderWindow& window)
{
	sf::CircleShape lifePointShape(10.0f);
	lifePointShape.setFillColor(sf::Color::Red);
	lifePointShape.setPosition(position);
	window.draw(lifePointShape);
}


