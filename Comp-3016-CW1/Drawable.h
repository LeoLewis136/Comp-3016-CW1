#pragma once

#include <string>

#include "Vector2.h"

class Drawable {
public:
	Vector2* position = new Vector2(1, 1);
	
	Drawable();

	Drawable(char toDraw);

	Drawable(char toDraw, Vector2 _position);

	virtual std::string getDrawable();

private:
	char drawChar;
};