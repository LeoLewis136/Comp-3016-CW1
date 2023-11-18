#include "Vector2.h"

// Constructor when x and y are passed
Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

// Overload * operator
Vector2 Vector2::operator * (float& a) {
	return Vector2(x * a, y * a);
}

// Overload / operator
Vector2 Vector2::operator / (float& a) {
	return Vector2(x / a, y / a);
}

// Overload + operator
Vector2 Vector2::operator + (Vector2& a) {
	return Vector2(x + a.x, y + a.y);
}

// Overload - operator
Vector2 Vector2::operator - (Vector2& a) {
	return Vector2(x - a.x, y - a.y);
}

bool Vector2::operator == (Vector2& a) {
	return (x == a.x) && (y == a.y);
}

// Overload << operator
std::ostream& operator << (std::ostream & output, const Vector2 & a) {
	output << "(" << a.x << " ," << a.y << " )";
	return output;
}

// Calculate the numerical distance between two points
float Vector2::distanceTo(Vector2& to) {
	float dx = x - to.x;
	float dy = y - to.y;

	return sqrt(dx * dx + dy * dy);
}

// Calculate the vector that shows the distance between 2 points
Vector2 Vector2::directionTo(Vector2& to) {
	return Vector2(to.x - x, to.y - y);
}