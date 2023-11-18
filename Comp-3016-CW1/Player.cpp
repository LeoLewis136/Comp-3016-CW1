#include "Vector2.h"
#include "Combat.h"
#include "Player.h"


Player::Player(char to_draw, Vector2 start_pos, float health, float defense, float critMult) : Drawable(to_draw, start_pos), Combat(health, critMult, defense) {


	/* Assigning all the player attacks in the format :
	(Attack name, Damage, Miss chance, Crit chance) */
	this->availableAttacks.push_back(std::make_tuple("Punch", 15, 2, 10));
	this->availableAttacks.push_back(std::make_tuple("Claw", 10, 1, 30));

	/* Assigning all the player effects in the format :
	(Effect name, Effect amount, Duration, Effect player) */
	this->availableMoves.push_back(std::make_tuple("Fortify", 2, 2, true));
	this->availableMoves.push_back(std::make_tuple("Critical surge", 3, 1, true));
	this->availableMoves.push_back(std::make_tuple("Heal", 100, 0, true));

}

void Player::update(std::vector<std::vector<std::string>>& map) {
	Vector2 toMove = this->inputs();

	if (map[position->y + toMove.y][position->x + toMove.x] == ".") {
		*position = *position + toMove;
	}
}

// Getting inputs 
Vector2 Player::inputs() {
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

	// Ensuring that the input buffer gets cleared to stop large queues of inputs causing odd movment
	while (_kbhit()) {
		_getch();
	}

	return Vector2();
}