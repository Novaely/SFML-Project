#include "SingleLightning.h"

SingleLightning::SingleLightning(LightningParameters& params, sf::Color color, sf::Color& innerColor)
{
	_parameters = &params;
	_color = color;
	_innerLineColor = &innerColor;
	rotation = _parameters->rotation;
	//startPoint = _parameters->startPoint;
	startPoint = Vec2f::zero;
	//endPoint = startPoint + _parameters->vecDirection * (_parameters->marginStart + _parameters->marginEnd);
	endPoint = startPoint + Vec2f::right * (_parameters->marginStart + _parameters->marginEnd);
	finalEndPoint = startPoint + Vec2f::right * (_parameters->endPoint - _parameters->startPoint).GetMagnitude();

	ComputeFirstPoint();
	points.push_back(endPoint);
	ClampFirstPoint();

	// Set constant segments
	firstSeg = CreateSegmentInfo();
	secondSeg = CreateSegmentInfo();
	lastSeg = CreateSegmentInfo();
	
	firstSeg.startPoint = &startPoint;
	firstSeg.endPoint = &firstPoint;
	
	secondSeg.startPoint = &firstPoint;
	secondSeg.endPoint = &points.back();

	lastSeg.startPoint = &points.front();
	lastSeg.endPoint = &endPoint;

	_currentState = &SingleLightning::Spawning;
}

void SingleLightning::Stop()
{
	_isDestroying = true;
	_currentState = &SingleLightning::Destroying;
}

void SingleLightning::Update(float deltaTime)
{
	currentLifeTime += deltaTime;

	if (_parameters->lifeTime != -1 && currentLifeTime >= _parameters->lifeTime)
	{
		_isDestroying = true;
		_currentState = &SingleLightning::Destroying;
	}
	
	(this->*_currentState)(deltaTime);
}

void SingleLightning::Draw(sf::RenderWindow& window)
{
	if (_isFinished) return;
	
	if (!_isDestroying)
	{
		DrawLine(window, firstSeg);
		DrawLine(window, secondSeg);
	}
	else
	{
		DrawLine(window, firstSeg);
		DrawLine(window, secondSeg);
	}
	
	for (SegmentInfos& seg : listSegInfos)
	{
		DrawLine(window, seg);
	}

	DrawLine(window, lastSeg);
}

void SingleLightning::DrawLine(sf::RenderWindow& window, SegmentInfos& segInfo)
{
	Vec2f startP = _parameters->startPoint + Math::RotatePoint((*segInfo.startPoint), Vec2f::zero, rotation);
	Vec2f vecDirec = _parameters->startPoint + Math::RotatePoint((*segInfo.endPoint), Vec2f::zero, rotation) - startP;
	float angle = Math::ToDegree(vecDirec.GetAngle()) + rotation;

	Vec2f recPos = startP + vecDirec * 0.5f;
	float length = vecDirec.GetMagnitude();
	
	Vec2f recSize = Vec2f(length + _parameters->linesWidth, _parameters->linesWidth);
	Vec2f recOrigin = recSize * 0.5f;
	Vec2f innerRecSize = Vec2f(length + _parameters->innerLineWidth, _parameters->innerLineWidth);
	Vec2f recInnerOrigin = innerRecSize * 0.5f;

	segInfo.recShape->setOrigin(recOrigin);
	segInfo.recShape->setPosition(recPos);
	segInfo.recShape->setRotation(angle);
	segInfo.recShape->setSize(recSize);
	window.draw((*segInfo.recShape));

	segInfo.innerRecShape->setOrigin(recInnerOrigin);
	segInfo.innerRecShape->setPosition(recPos);
	segInfo.innerRecShape->setRotation(angle);
	segInfo.innerRecShape->setSize(innerRecSize);
	window.draw((*segInfo.innerRecShape));
}

void SingleLightning::ComputeFirstPoint()
{
	float minAngle = _parameters->minAngle;
	float maxAngle = _parameters->maxAngle;
	
	float angle = RandomFloat(minAngle, maxAngle);
	angle *= sideDirection;
	sideDirection *= -1;
	float lengthRatio = RandomFloat(_parameters->randomRatioLengthMin, _parameters->randomRatioLengthMax);
	//float length = _parameters->vecDirector.GetMagnitude() / _parameters->numSegmentPerUnit * lengthRatio;
	float length = _parameters->unitSize / _parameters->numSegmentPerUnit * lengthRatio;
	firstPointVector = -(Math::Polar2Cart(Math::ToRad(angle), length));
}

void SingleLightning::ClampFirstPoint()
{
	const Vec2f& startP = startPoint;
	//firstPoint = Math::RotatePoint(points.back(), startP, -Math::ToRad(rotation)) + firstPointVector;
	firstPoint = points.back() + firstPointVector;

	// Clamp height
	if (firstPoint.y > startP.y + _parameters->width * 0.5f)
	{
		firstPoint.y = startP.y + _parameters->width * 0.5f;
	}
	else if (firstPoint.y < startP.y - _parameters->width * 0.5f)
	{
		firstPoint.y = startP.y - _parameters->width * 0.5f;
	}

	// Clamp at margin start
	if (firstPoint.x < startP.x + _parameters->marginStart)
	{
		firstPoint.x = startP.x + _parameters->marginStart;
	}
}

void SingleLightning::CreateNewPoint()
{
	//firstPoint = Math::RotatePoint(firstPoint, startPoint, Math::ToRad(rotation));
	points.push_back(firstPoint);

	ComputeFirstPoint();
	ClampFirstPoint();

	secondSeg.endPoint = &points.back();

	auto pointsIt = points.end();
	pointsIt--;

	SegmentInfos newSeg = CreateSegmentInfo();
	newSeg.startPoint = &(*pointsIt);
	pointsIt--;
	newSeg.endPoint = &(*pointsIt);
	listSegInfos.push_back(newSeg);
}

void SingleLightning::Spawning(float deltaTime)
{
	// Moving points
	for (Vec2f& point : points)
	{
		//point += _parameters->vecDirection * _parameters->spawnSpeed * deltaTime;
		point += Vec2f::right * _parameters->spawnSpeed * deltaTime;
	}
	//endPoint += _parameters->vecDirection * _parameters->spawnSpeed * deltaTime;
	endPoint += Vec2f::right * _parameters->spawnSpeed * deltaTime;

	// Compute next point
	ClampFirstPoint();

	//if (firstPoint.x > _parameters->startPoint.x + _parameters->marginStart)
	if (firstPoint.x > startPoint.x + _parameters->marginStart)
	{
		CreateNewPoint();
	}

	//firstPoint = Math::RotatePoint(firstPoint, startPoint, Math::ToRad(rotation));

	// If end reached, go in Moving state
	//if (points.size() < 1 && (points.front() - _parameters->endPoint).GetMagnitude() <= _parameters->marginEnd)
	if (points.size() > 1 && points.front().x > finalEndPoint.x + _parameters->marginEnd)
	{
		_currentState = &SingleLightning::Moving;
		//endPoint = _parameters->endPoint;
		endPoint = finalEndPoint;
	}
}

void SingleLightning::CheckLastSeg()
{
	if (points.size() < 1 || listSegInfos.size() < 1) return;

	//Vec2f rotatedLastPoint = Math::RotatePoint(points.front(), startPoint, -Math::ToRad(rotation));
	//Vec2f rotatedEndPoint = Math::RotatePoint(_parameters->endPoint, startPoint, -Math::ToRad(rotation));

	Vec2f rotatedLastPoint = points.front();
	Vec2f rotatedEndPoint = finalEndPoint;

	if (rotatedLastPoint.x < rotatedEndPoint.x) return;

	points.pop_front();
	DeleteSegment(&listSegInfos.front());
	listSegInfos.pop_front();

	lastSeg.startPoint = &points.front();
	listSegInfos.front().endPoint = &endPoint;
}

void SingleLightning::Moving(float deltaTime)
{
	// Moving points
	for (Vec2f& point : points)
	{
		//point += _parameters->vecDirection * _parameters->spawnSpeed * deltaTime;
		point += Vec2f::right * _parameters->movingSpeed * deltaTime;
	}

	// Compute next point
	ClampFirstPoint();

	//if (firstPoint.x > _parameters->startPoint.x + _parameters->marginStart)
	if (firstPoint.x > startPoint.x + _parameters->marginStart)
	{
		CreateNewPoint();
	}

	//firstPoint = Math::RotatePoint(firstPoint, startPoint, Math::ToRad(rotation));

	CheckLastSeg();
}

void SingleLightning::Destroying(float deltaTime)
{
	if (listSegInfos.size() < 2)
	{
		_isFinished = true;
		_currentState = nullptr;
		return;
	}

	// Moving points
	for (Vec2f& point : points)
	{
		//point += _parameters->vecDirection * _parameters->spawnSpeed * deltaTime;
		point += Vec2f::right * _parameters->destroyingSpeed * deltaTime;
	}
	startPoint += Vec2f::right * _parameters->destroyingSpeed * deltaTime;

	// If destroying but end not reached, go as far as possible and stop at the end
	/*if (endPoint != _parameters->endPoint)
	{
		if ((endPoint - startPoint).GetMagnitude() < (_parameters->endPoint - startPoint).GetMagnitude())
		{
			endPoint += _parameters->vecDirection * _parameters->spawnSpeed * deltaTime;
		}
		else endPoint = _parameters->endPoint;
	}*/

	if (endPoint != finalEndPoint)
	{
		if ((endPoint - startPoint).GetMagnitude() < (finalEndPoint - startPoint).GetMagnitude())
		{
			endPoint += Vec2f::right * _parameters->destroyingSpeed * deltaTime;
		}
		else endPoint = finalEndPoint;
	}

	ClampFirstPoint();

	//firstPoint = Math::RotatePoint(firstPoint, startPoint, Math::ToRad(rotation));

	CheckLastSeg();
}

void SingleLightning::DeleteSegment(SegmentInfos* seg)
{
	delete seg->recShape;
	delete seg->innerRecShape;
}

SingleLightning::SegmentInfos SingleLightning::CreateSegmentInfo()
{
	SegmentInfos seg;
	seg.recShape = new sf::RectangleShape();
	seg.innerRecShape = new sf::RectangleShape();
	seg.recShape->setFillColor(_color);
	seg.innerRecShape->setFillColor(*_innerLineColor);
	return seg;
}

SingleLightning::~SingleLightning()
{
	delete firstSeg.recShape;
	delete firstSeg.innerRecShape;

	delete secondSeg.recShape;
	delete secondSeg.innerRecShape;

	delete lastSeg.recShape;
	delete lastSeg.innerRecShape;

	for (SegmentInfos& segInfo : listSegInfos)
	{
		delete segInfo.recShape;
		delete segInfo.innerRecShape;
	}
}

bool SingleLightning::IsFinish()
{
	return _isFinished;
}

float SingleLightning::GetLightningLength()
{
	return endPoint.x - startPoint.x;
}

Vec2f SingleLightning::GetGLobalStartPoint()
{
	return _parameters->startPoint + Math::RotatePoint(startPoint, Vec2f::zero, rotation);
}