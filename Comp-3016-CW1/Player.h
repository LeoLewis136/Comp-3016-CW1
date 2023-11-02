#pragma once

class Player : public Drawable, public Updatable {
public:
	Player(char to_draw, Vector2 start_pos) : Drawable(to_draw, start_pos) {}

	void update(std::vector<std::vector<std::string>>& map) override {
		Vector2 toMove = inputs();

		if (map[position->y + toMove.y][position->x + toMove.x] == ".") {
			*position = *position + toMove;
		}
	}

private:
	// Getting inputs 
	Vector2 inputs() {
		if (_kbhit()) {
			switch (_getch()) {
			case 'a':
				return Vector2(-1, 0);
			case 'd':
				return Vector2(1, 0);
			case 'w':
				return Vector2(0, -1);
			case 's':
				return Vector2(0, 1);
			}
		}

		return Vector2();
	}
};