#include "HUDManager.h"


HUDManager::HUDManager()
{
	_gameManager = GameManager::GetInstance();
	_font.loadFromFile("ARIAL.TTF");

	SetGameHUDValues();
	_wasGamePause = false;

	_button.setFillColor(sf::Color::Blue);
	_button.setSize({200, 35});
	_button.setPosition({300, 275});

}

void HUDManager::SetGameHUDValues()
{
	// Police
	_score.setFont(_font);                
	_timer.setFont(_font);
	_level.setFont(_font);
	_multiplicateur.setFont(_font);
	_fps.setFont(_font);

	// Taille du texte
	_score.setCharacterSize(28);
	_timer.setCharacterSize(28);
	_level.setCharacterSize(28);
	_multiplicateur.setCharacterSize(28);
	_fps.setCharacterSize(28);

	// Couleur
	_score.setFillColor(sf::Color::White);
	_timer.setFillColor(sf::Color::White);
	_level.setFillColor(sf::Color::White);
	_multiplicateur.setFillColor(sf::Color::White);
	_fps.setFillColor(sf::Color::White);

	// Position dans la fenêtre
	_score.setPosition(50, 60);
	_timer.setPosition(50, 25);
	_level.setPosition(50, 95);
	_multiplicateur.setPosition(30, 550);
	_fps.setPosition(650, 550);
}

void HUDManager::SetPauseHUDValues()
{
	_level.setPosition(320, 150);
	_level.setCharacterSize(32);
	_level.setFillColor(sf::Color::Red);
	_level.setString("Game Over");
	_score.setPosition(315, 200);
	_score.setString("Score final : " + std::to_string(_gameManager->score));
	_multiplicateur.setPosition(350, 275);
	_multiplicateur.setString("Restart");
}

void HUDManager::Draw(sf::RenderWindow& window)
{
	if (!_gameManager->pause)
	{
		if (_wasGamePause)
		{
			_wasGamePause = false;
			SetGameHUDValues();
		}

		for (int i = 0; i < _gameManager->player->health; i++)
		{
			CreateLifePoint({ (9.0f + i) * 40.0f, 25.0f }, window);
		}
		_score.setString("Score : " + std::to_string(_gameManager->score));
		window.draw(_score);
		_timer.setString("Time : " + std::to_string((int)_gameManager->GetTime()));
		window.draw(_timer);
		if (_gameManager->GetMultiplicateur() > 1)
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
		if (!_wasGamePause)
		{
			_wasGamePause = true;
			SetPauseHUDValues();
		}

		window.draw(_score);
		window.draw(_level);
		window.draw(_button);
		window.draw(_multiplicateur);
	}
}

void HUDManager::CreateLifePoint(const CustomVector2f& position, sf::RenderWindow& window)
{
	float radius = 7.5f;

	sf::CircleShape circLeft(radius);
	circLeft.setOrigin(Vec2f(radius));
	circLeft.setFillColor(sf::Color::Red);
	circLeft.setPosition(position - Vec2f(radius, 0));

	sf::CircleShape circRight(radius);
	circRight.setOrigin(Vec2f(radius));
	circRight.setFillColor(sf::Color::Red);
	circRight.setPosition(position + Vec2f(radius, 0));

	sf::ConvexShape convexBot(3);
	convexBot.setFillColor(sf::Color::Red);
	convexBot.setPoint(0, Vec2f(0, -radius * 3));
	convexBot.setPoint(1, Vec2f(radius * 2.125f, 0));
	convexBot.setPoint(2, Vec2f(-radius * 2.125f, 0));
	convexBot.setRotation(180);
	convexBot.setPosition(position);

	window.draw(circLeft);
	window.draw(circRight);
	window.draw(convexBot);
}

bool HUDManager::DoRestartButtonContainsPos(Vec2f& pos) 
{
	return _button.getGlobalBounds().contains(pos);
}