#pragma once

#include <iostream>
#include <vector>
#include "Player.h"
#include "CACEnemy.h"
#include "ShooterEnemy.h"
#include "Bullet.h"
#include "Collectible.h"

class Manager 
{
public:
    virtual void Draw(sf::RenderWindow& window);

};

