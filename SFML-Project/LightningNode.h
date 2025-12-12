#pragma once

#include "SingleLightning.h"

class LightningNode : public GameObject
{
	public:
        // ===== VARIABLES ===== //

        // Lightning //
        Vec2f startPoint = Vec2f::zero;
        Vec2f endPoint = Vec2f::zero;

        // ===== FUNCTIONS ===== //
        
        // Constructor //
        LightningNode();

        // Game //
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

        // Lightning //
        void StartLightning();
        void StopLightning();

	private:
        // ===== VAIRABLES ===== //

        // Lightning //
        int numLightning = 3;
        std::vector<SingleLightning*> allLightnings;
        Vec2f vecDirector = Vec2f::zero;
        Vec2f vecDirection = Vec2f::zero;
        LightningParameters parameters;

        const sf::Color allColors[3]
        {
            sf::Color::Blue, sf::Color::Cyan, sf::Color(0, 119, 255)
        };
        sf::Color innerLineColor = sf::Color::White;
};