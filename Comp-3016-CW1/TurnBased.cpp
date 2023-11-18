#include "Effect.h"
#include "Player.h"
#include "Enemy.h"
#include "Combat.h"
#include "TurnBased.h"

/* defining all required methods by the TurnBasedCombat object */
TurnBasedCombat::TurnBasedCombat(Player* _character, Enemy* _enemy) {
	enemy = _enemy;
	character = _character;
}

// Main combat loop returns true if player won and false if they lost
bool TurnBasedCombat::mainLoop() {
	bool isDead = false;

	while (!isDead) {
		drawHealth();
		drawEffects();
		drawAttacks();

		if (getAttack()) {
			character->clearStatusEffects();
			return true;
		}

		if (enemyAttack()) {
			character->clearStatusEffects();
			isDead = true;
			break;
		}

		effectsManager();

		std::cout << std::endl;
	}
	
	return false;
}

// Function to draw the player attacks
void TurnBasedCombat::drawAttacks() {
	std::vector<std::tuple<std::string, float, float, float>> attacks = character->getAvailableAttacks();
	std::vector<std::tuple<std::string, float, int, bool>> effects = character->getAvailableMoves();

	std::cout << "AVAILABLE MOVES: | ";
	for (std::tuple<std::string, int, int, int> attack : attacks) {
		std::cout << "" << std::get<0>(attack) << " | ";
	}
	for (std::tuple<std::string, int, int, bool> effect : effects) {
		std::cout << "" << std::get<0>(effect) << " | ";
	}
	std::cout << std::endl << ":";
}

// Gettin the player attack and returning if the enemy has died
bool TurnBasedCombat::getAttack() {
	std::string input;
	getline(std::cin, input);

	system("cls");

	std::tuple<float, bool, bool, std::string>* tempAttack = character->getAttack(input);
	Effect* tempEffect = character->getMove(input);
	if (tempAttack) {
		std::cout << "Player attacked with " << std::get<3>(*tempAttack) << " and ";
		if (std::get<1>(*tempAttack)) {
			std::cout << "Missed" << std::endl;
		}
		else if (std::get<2>(*tempAttack)) {
			std::cout << "Crit" << std::endl;
		}
		else {
			std::cout << "Hit" << std::endl;
 		}

		// Subtract damage from enemy health
		enemy->modifyHealth(-std::get<0>(*tempAttack));

		if (enemy->getHealth() <= 0) {
			return true;
		}
	}
	else if (tempEffect) {

	}



	return false;
}

// Get the enemy to attack the player returns if the player has died
bool TurnBasedCombat::enemyAttack() {
	std::vector<std::tuple<std::string, float, float, float>> allAttacks = enemy->getAvailableAttacks();
	if (allAttacks.size() > 0) {
		std::tuple<float, bool, bool, std::string>* temp = enemy->getAttack(std::get<0>(allAttacks[rand() % allAttacks.size()]));

		std::cout << "Enemy attacked with " << std::get<3>(*temp) << " and ";
		if (std::get<1>(*temp)) {
			std::cout << "Missed" << std::endl;
		}
		else if (std::get<2>(*temp)) {
			std::cout << "Crit" << std::endl;
		}
		else {
			std::cout << "Hit" << std::endl;
		}
		
		// Subtract damage from enemy health
		character->modifyHealth(-std::get<0>(*temp) / character->getDefense());

		if (character->getHealth() <= 0) {
			return true;
		}
	}
	
	return false;
}

// Function to draw the health of the player & enemy
void TurnBasedCombat::drawHealth() {
	std::cout << "Player: " << character->getHealth() << std::endl;
	std::cout << "Enemy: " << enemy->getHealth() << std::endl;
}

void TurnBasedCombat::drawEffects() {
	int i = 0;

	std::cout << "EFFECT:";
	for (i = 0; i < character->getActiveEffects().size(); i++) {
		std::cout << " | " << character->getActiveEffects()[i]->name;
	}
	if (i > 0) {
		std::cout << " | ";
	}
	std::cout << std::endl;
	
}

void TurnBasedCombat::effectsManager() {
	for (Effect* effect : character->getActiveEffects()) {
		if (effect->update()) {
			character->deleteStatusEffect(effect);
		}
	}
}