#include "HUDManager.h"


HUDManager::HUDManager()
{
	_gameManager = GameManager::GetInstance();
	_font.loadFromFile("ARIAL.TTF");

	SetGameHUDValues();
	_wasGamePause = false;

	_button.setFillColor(sf::Color::Blue);
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
	_score.setPosition(Vec2f(50, 60) * _ratio);
	_timer.setPosition(Vec2f(50, 25) * _ratio);
	_level.setPosition(Vec2f(50, 95) * _ratio);
	_multiplicateur.setPosition(Vec2f(30, 550) * _ratio);
	_fps.setPosition(Vec2f(650, 550) * _ratio);
}

void HUDManager::SetPauseHUDValues()
{
	_level.setPosition(Vec2f(320, 150) * _ratio);
	_level.setCharacterSize(32);
	_level.setFillColor(sf::Color::Red);
	_level.setString("Game Over");
	_score.setPosition(Vec2f(315, 200) * _ratio);
	_score.setString("Score final : " + std::to_string(_gameManager->score));
	_multiplicateur.setPosition(Vec2f(350, 275) * _ratio);
	_multiplicateur.setString("Restart");
	_button.setSize(Vec2f(200, 35) * _ratio);
	_button.setPosition(Vec2f(300, 275) * _ratio);
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

		Vec2f heartPos = Vec2f::zero;
		Vec2f heartSpacing = Vec2f(50, 0) * _ratio;
		for (int i = 0; i < _gameManager->player->health; i++)
		{
			heartPos = Vec2f(300, 25.0f) * _ratio + heartSpacing * i;
			CreateLifePoint(heartPos, window);
		}
		_score.setString("Score : " + std::to_string(_gameManager->score));
		window.draw(_score);
		_timer.setString("Time : " + std::to_string((int)_gameManager->GetTime()));
		window.draw(_timer);
		if (_gameManager->GetMultiplicateur() > 1)
		{
			_multiplicateur.setString("x" + std::to_string(_gameManager->GetMultiplicateur()));
			window.draw(_multiplicateur);
		}
		_level.setString("Level : " + std::to_string(_gameManager->GetLevel()));
		window.draw(_level);
		_fps.setString("FPS : " + std::to_string(_gameManager->GetFPS()));
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
	float radius = 7.5f * _ratio.GetMagnitude();

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

void HUDManager::SetWindowRatio(const Vec2f& windowSize)
{
	_ratio = windowSize / _baseSize;
	std::cout << _ratio << std::endl;
	if (_gameManager->pause)
	{
		SetPauseHUDValues();
	}
	else
	{
		SetGameHUDValues();
	}
}

Vec2f HUDManager::GetRatio()
{
	return _ratio;
}