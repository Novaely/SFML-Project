#pragma once
#include "Manager.h"
#include "GameManager.h"


class HUDManager :
    public Manager
{

    public:
		HUDManager();

		GameManager* gameManager;	

	    void Draw(sf::RenderWindow& window) override;
        void CreateLifePoint(CustomVector2f position, sf::RenderWindow& window);

		sf::Text score;
		sf::Text timer;
		sf::Text multiplicateur;
		sf::Font font;
};

