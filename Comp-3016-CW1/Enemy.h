#pragma once

#include <tuple>
#include <vector>
#include <string>

#include "Drawable.h"
#include "Updatable.h"
#include "Combat.h"

class Player;

class Enemy : public Drawable, public Updatable, public Combat{
public:
	bool isDead = false;

	Enemy() { }

	Enemy(char to_draw, Vector2 start_pos, std::vector<Vector2> _path, Player* _character, float health, float defense, float critMult);

	// Enemy update code
	void update(std::vector<std::vector<std::string>>& map);
		// Move along specified path
		//pathIndex = (pathIndex + 1) % path.size();
		//*position = *position + path[pathIndex];

private:
	int health = 100;

	Player* character;

	std::vector<Vector2> path;
	// All attacks format is (name, damage, miss chance, crit chance)
	std::vector<std::tuple<std::string, int, int, int>> attacks;
	int pathIndex = 0;
};