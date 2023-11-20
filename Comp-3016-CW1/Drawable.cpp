#include "Drawable.h"

// Empty constructor for when required
Drawable::Drawable() { }

// Standard constructor
Drawable::Drawable(char toDraw) {
	drawChar = toDraw;
}

// Constructor to set initial position to custom value
Drawable::Drawable(char toDraw, Vector2 _position) {
	drawChar = toDraw;
	*position = _position;
}

// Getting the character that represents this drawable object
std::string Drawable::getDrawable() {
	return std::string(1, drawChar);
}