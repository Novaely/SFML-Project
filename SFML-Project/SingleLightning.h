#pragma once

#include "Utils.h"
#include "GameObject.h"
#include <list>

using Vec2f = CustomVector2f;

struct LightningParameters
{
    // Parameters to change before play
    float unitSize = 75;

    float minAngle = 30.0f;
    float maxAngle = 80.0f;

    int numSegmentPerUnit = 2;

    float spawnSpeed = 150;
    float movingSpeed = 150;
    float destroyingSpeed = 150;

    int marginStart = 10;
    int marginEnd = 10;
    int width = 15;

    float randomRatioLengthMin = 0.75f;
    float randomRatioLengthMax = 2.0f;

    float linesWidth = 2.0f;
    float innerLineWidth = 1.0f;

    float lifeTime = 2.5f;

    // Parameters automatically updated
    float rotation = 0;
    Vec2f startPoint = Vec2f::zero;
    Vec2f endPoint = Vec2f::zero;
    Vec2f vecDirection = Vec2f::zero;
    Vec2f vecDirector = Vec2f::zero;
};

class SingleLightning : public GameObject
{
	public:
        SingleLightning(LightningParameters& params, sf::Color color, sf::Color& innerColor);
        ~SingleLightning();

        int sideDirection = 1;

		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;

        void Stop();

        bool IsFinish();

	private:
        struct SegmentInfos
        {
            Vec2f* startPoint;
            Vec2f* endPoint;
            sf::RectangleShape* recShape;
            sf::RectangleShape* innerRecShape;
        };

        void (SingleLightning::* _currentState)(float) = nullptr;

        bool _isFinished = false;
        bool _isDestroying = false;

        std::list<SegmentInfos> listSegInfos;
        std::list<Vec2f> points;
        LightningParameters* _parameters;

        SegmentInfos firstSeg;
        SegmentInfos secondSeg;
        SegmentInfos lastSeg;

        Vec2f startPoint;
        Vec2f endPoint;
        Vec2f finalEndPoint;

        Vec2f firstPoint;
        Vec2f firstPointVector;

        float currentLifeTime = 0.0f;

        sf::Color _color;
        sf::Color* _innerLineColor;

		void Spawning(float deltaTime);
		void Moving(float deltaTime);
		void Destroying(float deltaTime);

        void CreateNewPoint();
		void ClampFirstPoint();
		void ComputeFirstPoint();

        SegmentInfos CreateSegmentInfo();
        void DeleteSegment(SegmentInfos* seg);

        void CheckLastSeg();

        void DrawLine(sf::RenderWindow& window, SegmentInfos& segInfo);
};