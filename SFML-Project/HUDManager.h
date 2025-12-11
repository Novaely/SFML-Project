#pragma once
#include "Manager.h"
#include "GameManager.h"


class HUDManager :
    public Manager
{
private:
		sf::Text _score;
		sf::Text _timer;
		sf::Text _multiplicateur;
		sf::Text _level;
		sf::Text _fps;
		sf::Font _font;
		sf::RectangleShape _button;

    public:
		HUDManager();

		GameManager* gameManager;	

		bool DoRestartButtonContainsPos(Vec2f& pos);
	    void Draw(sf::RenderWindow& window) override;
        void CreateLifePoint(const CustomVector2f& position, sf::RenderWindow& window);
};

