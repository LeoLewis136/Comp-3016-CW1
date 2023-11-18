#include "Drawable.h"

Drawable::Drawable() { }

Drawable::Drawable(char toDraw) {
	drawChar = toDraw;
}

Drawable::Drawable(char toDraw, Vector2 _position) {
	drawChar = toDraw;
	*position = _position;
}

std::string Drawable::getDrawable() {
	return std::string(1, drawChar);
}