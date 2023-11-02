#pragma once

class Drawable {
public:
	Vector2* position = new Vector2(1, 1);
	
	Drawable() {}

	Drawable(char toDraw) {
		drawChar = toDraw;
	}

	Drawable(char toDraw, Vector2 _position) {
		drawChar = toDraw;
		*position = _position;
	}

	std::string getDrawable() {
		return std::string(1, drawChar);
	}

private:
	char drawChar;
};