#include "Vector2.h"
#include "Combat.h"
#include "Player.h"
#include "Enemy.h"


// Enemy constructor
Enemy::Enemy(char to_draw, Vector2 start_pos, std::vector<Vector2> _path, Player* _character, float health, float defense, float critMult) : Updatable(), Drawable(to_draw, start_pos), Combat(health, critMult, defense) {
	path = _path;
	character = _character;
}

// Enemy update code
void Enemy::update(std::vector<std::vector<std::string>>& map) {
	//pathIndex = (pathIndex + 1) % path.size();
	//*position = *position + path[pathIndex];
}

