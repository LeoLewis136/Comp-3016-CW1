#pragma once

class Player : public Drawable, public Updatable {
public:
	/* Storing the current values of each of these parameters */
	// Storing current health
	int health = 100;
	// Multiplier that determines how much extra damage crits currently do
	int critMult = 2;
	// Multiplier that is used for "defense"
	float damageMult = 1;
	// Int that stores what the current minimum miss chance is
	// Changes to allow for increased miss chance for a few turns
	int missChance = 0;

	Player() {}
	
	Player(char to_draw, Vector2 start_pos) : Drawable(to_draw, start_pos) {
		attacks.push_back(std::make_tuple("Punch", 100, 5, 100));
		attacks.push_back(std::make_tuple("Claw", 5, 1, 30));
	}

	void update(std::vector<std::vector<std::string>>& map) override {
		Vector2 toMove = inputs();

		if (map[position->y + toMove.y][position->x + toMove.x] == ".") {
			*position = *position + toMove;
		}
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
			if (value < max(std::get<2>(attacks[index]), missChance)) {
				return std::make_tuple(0, true, false, std::get<0>(attacks[index]));
			}
			// Generate a random number for crit chance
			value = rand() % 100;
			if (value < std::get<3>(attacks[index])) {
				return std::make_tuple((std::get<1>(attacks[index]) * critMult), false, true, std::get<0>(attacks[index]));
			}

			// Neither crit or miss
			return std::make_tuple(std::get<1>(attacks[index]), false, false, std::get<0>(attacks[index]));
		}

		return std::make_tuple(-1, false, false, "");
	}

	void addEffect(Effect _toAdd) {
		effects.push_back(_toAdd);
	}
	void deleteEffect(Effect _toRemove) {
		int i = 0;
		for (i = 0; i < effects.size(); i++) {
			if (effects[i].name == _toRemove.name) {
				break;
			}
		}
		effects.erase(effects.begin() + i);
	}
	void clearEffects() {
		effects.clear();

		// Also resetting all other attributes to standard before the next combat
		health = stdHealth;
		critMult = stdCritMult;
		damageMult = stdDamageMult;
		missChance = stdMissChance;
	}

	// Returns all the effects currently on the player
	std::vector<Effect> getEffects() { return effects; }
	// Returns all the attacks this player can do
	std::vector<std::tuple<std::string, int, int, int>> getAttacks() { return attacks; }
	// Methods to get the current health and add or remove health
	int getHealth() { return health; }
	void modifyHealth(int adjust) { health += adjust; }

	int getDefense() { return damageMult; }

private:

	/* Storing the default value of each of the above parameters */
	int stdHealth = 100;
	int stdCritMult = 2;
	int stdDamageMult = 1;
	int stdMissChance = 0;

	// All attacks. Format is (name, damage, miss chance, crit chance)
	std::vector<std::tuple<std::string, int, int, int>> attacks;
	// Stores all currently active effects
	std::vector<Effect> effects;

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

		// Ensuring that the input buffer gets cleared to stop large queues of inputs causing odd movment
		while (_kbhit()) {
			_getch();
		}

		return Vector2();
	}

	// Function to convert string to all lower case
	std::string toLower(std::string toConvert) {
		for (char& c : toConvert) {
			c = std::tolower(c);
		}

		return toConvert;
	}
};