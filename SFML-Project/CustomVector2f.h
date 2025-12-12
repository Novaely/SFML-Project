#pragma once

#include <SFML/Graphics.hpp>

struct CustomVector2f
{
	// ===== VARIABLES ===== //

	// Transform //
	float x = 0.0f;
	float y = 0.0f;

	// Constants //
	static const CustomVector2f zero;
	static const CustomVector2f one;
	static const CustomVector2f minusOne;
	static const CustomVector2f right;
	static const CustomVector2f down;
	static const CustomVector2f left;
	static const CustomVector2f up;

	// ===== FUNCTIONS ===== //

	// Constructors
	CustomVector2f();
	CustomVector2f(float _xy);
	CustomVector2f(float _x, float _y);
	CustomVector2f(const sf::Vector2f& v);

	// Methods
	float GetSquaredMagnitude() const;
	float GetMagnitude() const;
	void SetMagnitude(float mag);
	CustomVector2f GetNormalised() const;
	void Normalise();
	float GetAngle() const;
	float AngleTo(const CustomVector2f& other) const;
	float SquaredDistanceTo(const CustomVector2f& other) const;
	float DistanceTo(const CustomVector2f& other) const;
	CustomVector2f GetNormalCounterClockWise() const;
	CustomVector2f GetNormalClockWise() const;
	CustomVector2f DirectionTo(const CustomVector2f& other) const;
	CustomVector2f Rotate(float angle) const;
	float Dot(const CustomVector2f& other) const;

	// Conversion //
	operator sf::Vector2f() const;

	// Operators with CustomVector2f //
	CustomVector2f operator+(const CustomVector2f& other) const;
	CustomVector2f operator-(const CustomVector2f& other) const;
	CustomVector2f operator-() const;
	CustomVector2f operator*(const CustomVector2f& other) const;
	CustomVector2f operator/(const CustomVector2f& other) const;

	CustomVector2f& operator+=(const CustomVector2f& other);
	CustomVector2f& operator-=(const CustomVector2f& other);
	CustomVector2f& operator*=(const CustomVector2f& other);
	CustomVector2f& operator/=(const CustomVector2f& other);

	// Operators with float //
	CustomVector2f operator+(const float& other) const;
	CustomVector2f operator-(const float& other) const;
	CustomVector2f operator*(const float& other) const;
	CustomVector2f operator/(const float& other) const;

	CustomVector2f& operator+=(const float& other);
	CustomVector2f& operator-=(const float& other);
	CustomVector2f& operator*=(const float& other);
	CustomVector2f& operator/=(const float& other);

	// Comparaisons operators //
	bool operator==(const CustomVector2f& other) const;
	bool operator!=(const CustomVector2f& other) const;
};

std::ostream& operator<<(std::ostream& os, const CustomVector2f& v);