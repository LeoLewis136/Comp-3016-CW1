#pragma once

class Player : public Drawable, public Updatable {
public:
	Player() {}
	
	Player(char to_draw, Vector2 start_pos) : Drawable(to_draw, start_pos) {
		attacks.push_back(std::make_tuple("Punch", 10, 5, 10));
		attacks.push_back(std::make_tuple("Claw", 5, 1, 30));
	}

	void update(std::vector<std::vector<std::string>>& map) override {
		Vector2 toMove = inputs();

		if (map[position->y + toMove.y][position->x + toMove.x] == ".") {
			*position = *position + toMove;
		}
	}

	// Returns all the attacks this player can do
	std::vector<std::tuple<std::string, int, int, int>> getAttacks() {
		return attacks;
	}

	// Check if attack exists and if it does return the damage to deal
	std::tuple<int, bool, bool, std::string> checkAttack(std::string attack) {
		// Check if the attack exists in the player's attacks
		int index = -1;
		for (int i = 0; i < attacks.size(); i++) {
			// Check the names both in all lower case
			if (toLower(attack) == toLower(std::get<0>(attacks[i]))) {
				index = i;
				break;
			}
		}

		// If the attack exists
		if (index >= 0) {
			// Generate a random number for miss chance 
			int value = rand() % 100;
			if (value < std::get<2>(attacks[index])) {
				return std::make_tuple(0, true, false, std::get<0>(attacks[index]));
			}
			// Generate a random number for crit chance
			value = rand() % 100;
			if (value < std::get<3>(attacks[index])) {
				return std::make_tuple(std::get<1>(attacks[index]) * 2, false, true, std::get<0>(attacks[index]));
			}

			// Neither crit or miss
			return std::make_tuple(std::get<1>(attacks[index]), false, false, std::get<0>(attacks[index]));
		}

		return std::make_tuple(-1, false, false, "");
	}

	// Function to convert string to all lower case
	std::string toLower(std::string toConvert) {
		for (char& c : toConvert) {
			c = std::tolower(c);
		}

		return toConvert;
	}

	// Methods to get the current health and add or remove health
	int getHealth() { return health; }
	void modifyHealth(int adjust) { health += adjust; }

private:
	int health = 100;

	// All attacks. Format is (name, damage, miss chance, crit chance)
	std::vector<std::tuple<std::string, int, int, int>> attacks;

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