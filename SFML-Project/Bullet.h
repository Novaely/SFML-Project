#pragma once
#include "Movable.h"

class Bullet :
    public Movable
{

    public:
        // Constructor 
        Bullet();

        float damage;

        void Active();
		void Desactive();
        
    protected:
        void Draw(sf::RenderWindow& window) override;
};

