#pragma once

#include "Utils.h"
#include "GameObject.h"
#include <list>

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

        // ===== VARIABLES ===== //

        // Others //
        int sideDirection = 1;

        // ===== FUNCTIONS ===== //

        // Constructor //
        SingleLightning(LightningParameters& params, sf::Color color, sf::Color& innerColor);

        // Destructor //
        ~SingleLightning();

        // Getter / Setters //
        bool IsFinish();
        float GetLightningLength();
        Vec2f GetGLobalStartPoint();

        // Game //
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        void Active() override;

        // Lightning control //
        void Stop();        

	private:
        struct SegmentInfos
        {
            Vec2f* startPoint;
            Vec2f* endPoint;
            sf::RectangleShape* recShape;
            sf::RectangleShape* innerRecShape;
        };

        // ===== VARIABLES ===== //

        // Lightning infos //
        bool _isFinished = false;
        bool _isDestroying = false;
        float currentLifeTime = 0.0f;
        LightningParameters* _parameters;

        sf::Color _color;
        sf::Color* _innerLineColor;

        // Lightning statics infos //

        SegmentInfos firstSeg;
        SegmentInfos secondSeg;
        SegmentInfos lastSeg;

        // Lightning Points / Segments //

        std::list<SegmentInfos> listSegInfos;
        std::list<Vec2f> points;

        Vec2f endPoint;
        Vec2f finalEndPoint;
        Vec2f startPoint;

        Vec2f firstPoint;
        Vec2f firstPointVector;

        // ===== FUCNTIONS ===== //

        // State machine //
        void (SingleLightning::* _currentState)(float) = nullptr;

		void Spawning(float deltaTime);
		void Moving(float deltaTime);
		void Destroying(float deltaTime);

        // Lightning points //
        void CreateNewPoint();
		void ClampFirstPoint();
		void ComputeFirstPoint();

        // Lightning segments //
        SegmentInfos CreateSegmentInfo();
        void DeleteSegment(SegmentInfos* seg);
        void CheckLastSeg();

        void DrawLine(sf::RenderWindow& window, SegmentInfos& segInfo);
};