#pragma once

#include <vector>
#include <string>
#include <iostream>

class Player;
class Enemy;

class TurnBasedCombat {
public:
	TurnBasedCombat(Player* _character, Enemy* _enemy);

	// Main combat loop returns true if player won and false if they lost
	bool mainLoop();

private:
	Enemy* enemy;
	Player* character;

	// Function to draw the player attacks
	void drawAttacks();

	void drawEffects();
	//	std::cout << "EFFECTS: ";
	//	for (Effect* effect : character->getActiveEffects()) {
	//		std::cout << effect->name << effect->modifiedStat <<" ";
	//	}
	//	std::cout << std::endl;

	// Manage all current status effects or debuffs that are occurring
	void effectsManager();
	//	for (Effect* effect : character->getActiveEffects()) {
	//		if (effect->update()) {
	//			character->deleteStatusEffect(effect);
	//		}
	//	}
	

	// Gettin the player attack and returning if the enemy has died
	bool getAttack();

	// Get the enemy to attack the player returns if the player has died
	bool enemyAttack();

	// Function to draw the health of the player & enemy
	void drawHealth();
};