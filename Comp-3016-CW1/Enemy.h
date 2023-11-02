#pragma once

class Enemy : public Drawable, public Updatable{
public:
	Enemy(char to_draw, Vector2 start_pos, std::vector<Vector2> _path, Player& _character) : Drawable(to_draw, start_pos) {
		path = _path;
		character = _character;
	}

	void update(std::vector<std::vector<std::string>>& map) override {
		pathIndex = (pathIndex + 1) % path.size();

		*position = path[pathIndex];

		if (*character.position == *position) {
			exit(0);
		}
	}

private:
	Player character;

	std::vector<Vector2> path;
	int pathIndex = 0;
};