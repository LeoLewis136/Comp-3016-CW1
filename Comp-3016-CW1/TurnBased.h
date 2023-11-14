#pragma once

class TurnBasedCombat {
public:
	TurnBasedCombat(Player* _character, Enemy* _enemy) {
		enemy = _enemy;
		character = _character;
	}

	// Main combat loop returns true if player won and false if they lost
	bool mainLoop() {
		character->addEffect(Effect(character->critMult, 1, "Increased Crit", 5));


		bool isDead = false;

		while (!isDead) {
			drawHealth();
			drawEffects();
			drawAttacks();

			if (getAttack()) {
				character->clearEffects();
				return true;
			}

			if (enemyAttack()) {
				character->clearEffects();
				isDead = true;
				break;
			}

			std::cout << std::endl;
			
			effectsManager();
		}

		return false;
	}

private:
	Enemy* enemy;
	Player* character;

	// Function to draw the player attacks
	void drawAttacks() {
		std::vector<std::tuple<std::string, int, int, int>> attacks = character->getAttacks();

		std::cout << "ATTACKS: | ";
		for(std::tuple<std::string, int, int, int> attack : attacks) {
			std::cout << "" << std::get<0>(attack) << " | ";
		}
		std::cout << std::endl << ":";
	}

	void drawEffects() {
		std::cout << "EFFECTS: ";
		for (Effect effect : character->getEffects()) {
			std::cout << effect.name << *effect.modifiedStat <<" ";
		}
		std::cout << std::endl;
	}

	// Manage all current status effects or debuffs that are occurring
	void effectsManager() {
		for (Effect effect : character->getEffects()) {
			if (effect.update()) {
				character->deleteEffect(effect);
			}
		}
	}

	// Gettin the player attack and returning if the enemy has died
	bool getAttack() {
		std::string input;
		std::cin >> input;

		system("cls");


		std::tuple<int, bool, bool, std::string> temp = character->checkAttack(input);
		std::cout << "Player attacked with " << std::get<3>(temp) << " and ";
		if (std::get<1>(temp)) {
			std::cout << "Missed" << std::endl;
		}
		else if (std::get<2>(temp)) {
			std::cout << "Crit" << std::endl;
		}
		else {
			std::cout << "Hit" << std::endl;
		}

		// Subtract damage from enemy health
		enemy->modifyHealth(-std::get<0>(temp));

		if (enemy->getHealth() <= 0) {
			return true;
		}

		return false;
	}

	// Get the enemy to attack the player returns if the player has died
	bool enemyAttack() {
		std::tuple<int, bool, bool, std::string> temp = enemy->attack();
		std::cout << "Enemy attacked with " << std::get<3>(temp) << " and ";
		if (std::get<1>(temp)) {
			std::cout << "Missed" << std::endl;
		}
		else if (std::get<2>(temp)) {
			std::cout << "Crit" << std::endl;
		}
		else {
			std::cout << "Hit" << std::endl;
		}

		// Subtract damage from enemy health
		character->modifyHealth(-std::get<0>(temp) * character->getDefense());

		if (character->getHealth() <= 0) {
			return true;
		}

		return false;
	}

	// Function to draw the health of the player & enemy
	void drawHealth() {
		std::cout << "Player: " << character->getHealth() << std::endl;
		std::cout << "Enemy: " << enemy->getHealth() << std::endl;
	}
};