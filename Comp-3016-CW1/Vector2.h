#pragma once

class Vector2 {
public:
	float x = 0;
	float y = 0;

	// Constructor when x and y are passed
	Vector2(float _x, float _y) {
		x = _x;
		y = _y;
	}

	// Empty constructor to make a vector of 0,0
	Vector2() {}

	// Overload * operator
	Vector2 operator * (float& a) {
		return Vector2(x * a, y * a);
	}

	// Overload / operator
	Vector2 operator / (float& a) {
		return Vector2(x / a, y / a);
	}

	// Overload + operator
	Vector2 operator + (Vector2& a) {
		return Vector2(x + a.x, y + a.y);
	}

	// Overload - operator
	Vector2 operator - (Vector2& a) {
		return Vector2(x - a.x, y - a.y);
	}

	bool operator == (Vector2& a) {
		return (x == a.x) && (y == a.y);
	}

	// Overload << operator
	friend std::ostream& operator << (std::ostream& output, const Vector2& a) {
		output << "(" << a.x << " ," << a.y << " )";
		return output;
	}

	// Calculate the numerical distance between two points
	float distanceTo(Vector2& to) {
		float dx = x - to.x;
		float dy = y - to.y;

		return sqrt(dx * dx + dy * dy);
	}

	// Calculate the vector that shows the distance between 2 points
	Vector2 directionTo(Vector2& to) {
		return Vector2(to.x - x, to.y - y);
	}

};