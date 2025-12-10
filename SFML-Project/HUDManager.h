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
		sf::Font _font;

    public:
		HUDManager();

		GameManager* gameManager;	

	    void Draw(sf::RenderWindow& window) override;
        void CreateLifePoint(CustomVector2f position, sf::RenderWindow& window);
};

