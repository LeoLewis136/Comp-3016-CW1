#include "Vector2.h"
#include "Combat.h"
#include "Player.h"
#include "Enemy.h"



Enemy::Enemy(char to_draw, Vector2 start_pos, std::vector<Vector2> _path, Player* _character, float health, float defense, float critMult) : Updatable(), Drawable(to_draw, start_pos), Combat(health, critMult, defense) {
	path = _path;
	character = _character;

	this->availableAttacks.push_back(std::make_tuple("Punch", 10, 5, 5));
	this->availableAttacks.push_back(std::make_tuple("Claw", 5, 1, 20));
}

// Enemy update code
void Enemy::update(std::vector<std::vector<std::string>>& map) {
	// Move along specified path
	//pathIndex = (pathIndex + 1) % path.size();
	//*position = *position + path[pathIndex];
}

