#pragma once

class Enemy : public Drawable, public Updatable{
public:
	bool isDead = false;

	Enemy(){}

	Enemy(char to_draw, Vector2 start_pos, std::vector<Vector2> _path, Player* _character) : Drawable(to_draw, start_pos) {
		path = _path;
		character = _character;

		attacks.push_back(std::make_tuple("Punch", 10, 5, 5));
		attacks.push_back(std::make_tuple("Claw", 5, 1, 20));
	}

	// Enemy update code
	void update(std::vector<std::vector<std::string>>& map) override {
		// Move along specified path
		//pathIndex = (pathIndex + 1) % path.size();
		//*position = *position + path[pathIndex];
	}

	// Returns all the attacks this enemy can do
	std::vector<std::tuple<std::string, int, int, int>> getAttacks() {
		return attacks;
	}

	// Function to handle enemy attacks
	std::tuple<int, bool, bool, std::string> attack() {
		// Pick a random attack
		std::tuple<std::string, int, int, int> attack = attacks[rand() % (attacks.size() - 1)];

		// Generate a random number for miss chance 
		int value = rand() % 100;
		if (value < std::get<2>(attack)) {
			return std::make_tuple(0, true, false, std::get<0>(attack));
		}
		// Generate a random number for crit chance
		value = rand() % 100;
		if (value < std::get<3>(attack)) {
			return std::make_tuple(std::get<1>(attack) * 2, false, true, std::get<0>(attack));
		}

		// Neither crit or miss
		return std::make_tuple(std::get<1>(attack), false, false, std::get<0>(attack));
		
	}

	void death() {

	}

	// Methods to get the current health and add or remove health
	int getHealth() { return health; }
	void modifyHealth(int adjust) { health += adjust; }

private:
	int health = 100;

	Player* character;

	std::vector<Vector2> path;
	// All attacks format is (name, damage, miss chance, crit chance)
	std::vector<std::tuple<std::string, int, int, int>> attacks;
	int pathIndex = 0;
};