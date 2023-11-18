#pragma once

#include <ostream>

class Vector2 {
public:
	float x = 0;
	float y = 0;

	// Constructor when x and y are passed
	Vector2(float _x, float _y);

	// Empty constructor to make a vector of 0,0
	Vector2() {}

	// Overload * operator
	Vector2 operator * (float& a);
	

	// Overload / operator
	Vector2 operator / (float& a);

	// Overload + operator
	Vector2 operator + (Vector2& a);

	// Overload - operator
	Vector2 operator - (Vector2& a);

	bool operator == (Vector2& a);

	// Overload << operator
	friend std::ostream& operator << (std::ostream& output, const Vector2& a);

	// Calculate the numerical distance between two points
	float distanceTo(Vector2& to);

	// Calculate the vector that shows the distance between 2 points
	Vector2 directionTo(Vector2& to);

};