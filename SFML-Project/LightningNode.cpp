#include "LightningNode.h"

LightningNode::LightningNode() : allLightnings(numLightning, nullptr)
{
	characterType = CharaType::Lighting;
	sf::RectangleShape* pShape = new sf::RectangleShape;
	shape = pShape;
}

void LightningNode::Update(float deltaTime)
{
	auto singleLightIt = allLightnings.begin();
	while (singleLightIt != allLightnings.end())
	{		
		(*singleLightIt)->Update(deltaTime);
		if ((*singleLightIt)->IsFinish())
		{
			delete *singleLightIt;
			singleLightIt = allLightnings.erase(singleLightIt);
			if (allLightnings.size() <= 0)
			{
				pDie(this);
			}
		}
		else
		{
			singleLightIt++;
		}
	}

	if (allLightnings.size() > 0)
	{
		sf::RectangleShape* pShape = (sf::RectangleShape*)shape;
		pShape->setSize(Vec2f(allLightnings.front()->GetLightningLength(), parameters.width));
		Vec2f pos = allLightnings.front()->GetGLobalStartPoint();

		Vec2f direction = Math::Polar2Cart(parameters.rotation, 1);
		Vec2f normal = direction.GetNormalClockWise();

		pos += normal * parameters.width * 0.5f;

		pShape->setPosition(pos);
		pShape->setRotation(Math::ToDegree(parameters.rotation));
		pShape->setFillColor(sf::Color::White);
	}
}

void LightningNode::Draw(sf::RenderWindow& window)
{
	auto singleLightIt = allLightnings.begin();
	while (singleLightIt != allLightnings.end())
	{
		(*singleLightIt)->Draw(window);
		singleLightIt++;
	}

	//window.draw(*shape);
}

void LightningNode::StartLightning()
{
	parameters.startPoint = startPoint;
	parameters.endPoint = endPoint;

	position = startPoint;

	vecDirection = (endPoint - startPoint).GetNormalised();
	vecDirector = vecDirection * parameters.unitSize;

	parameters.vecDirector = vecDirector;
	parameters.vecDirection = vecDirection;
	parameters.rotation = vecDirection.GetAngle();


	SingleLightning* newLighting = nullptr;
	for (int i = 0; i < numLightning; i++)
	{
		newLighting = new SingleLightning(parameters, allColors[i % sizeof(allColors)], innerLineColor);
		newLighting->sideDirection = i % 2 == 0 ? 1 : -1;
		
		allLightnings[i] = newLighting;
	}
}

void LightningNode::StopLightning()
{
	for (SingleLightning* singleLightning : allLightnings)
	{
		singleLightning->Stop();
	}
}