#include "Vector2.h"
#include "Combat.h"
#include "Player.h"

// Player constructor
Player::Player(char to_draw, Vector2 start_pos, float health, float defense, float critMult) : Drawable(to_draw, start_pos), Combat(health, critMult, defense) {
	/* Assigning all the player attacks in the format :
	(Attack name, Damage, Miss chance, Crit chance) */
	this->availableAttacks.push_back(std::make_tuple("Punch", 15, 5, 15));
	this->availableAttacks.push_back(std::make_tuple("Claw", 8, 3, 40));

	/* Assigning all the player effects in the format :
	(Effect name, Effect amount, Duration, Effect player) */
	this->availableMoves.push_back(std::make_tuple("Fortify", 2, 2, true));
	this->availableMoves.push_back(std::make_tuple("Critical surge", 3, 3, true));
	this->availableMoves.push_back(std::make_tuple("Heal", 100, 0, true));

}

// This players update method
void Player::update(std::vector<std::vector<std::string>>& map) {
	// Get current movement input
	Vector2 toMove = this->inputs();

	// Move player if the map tile is empty
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