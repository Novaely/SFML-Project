#include "LightningNode.h"

LightningNode::LightningNode() : allLightnings(numLightning, nullptr) {}

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
}

void LightningNode::Draw(sf::RenderWindow& window)
{
	auto singleLightIt = allLightnings.begin();
	while (singleLightIt != allLightnings.end())
	{
		(*singleLightIt)->Draw(window);
		singleLightIt++;
	}
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