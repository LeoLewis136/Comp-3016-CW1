#include "Effect.h"
#include "Combat.h"

/* Defining all methods that the combat class requires */

// Constructor that assigns all the required attributes to passed values
Combat::Combat(float _health, float _critMult, float _defense) {
	stdHealth = health = _health;
	stdCritMult = critMult = _critMult;
	stdDefense = defense = _defense;
	stdMissChance = missChance = 0;
}

/* Get / Set for all required paremeters */
	// Getting all the attacks that this object is able to use
std::vector<std::tuple<std::string, float, float, float>> Combat::getAvailableAttacks() { return availableAttacks; }
// Gettinf all the non-damaging moves that this object is able to use
std::vector<std::tuple<std::string, float, int, bool>> Combat::getAvailableMoves() { return availableMoves; }
// Getting any status effects currently effecting this object
std::vector<Effect*> Combat::getActiveEffects() { return activeEffects; }
// Health get/set and function to + or - health while keeping within the max and min
float Combat::getHealth() { return health; }
void Combat::setHealth(float _health) { health = _health; }
void Combat::modifyHealth(float change) {
	health = std::min(health + change, stdHealth);
}
// Defense functions
void Combat::setDefense(float toSet) { defense = toSet; }
void Combat::resetDefense() { defense = stdDefense; }
float Combat::getDefense() { return defense; }
// Crit mutiplier functions
void Combat::setCritMult(float toSet) { critMult = toSet; }
void Combat::resetCritMult() { critMult = stdCritMult; }
// Miss chance funstions
void Combat::setMissChance(float toSet) { missChance = toSet; }
void Combat::resetMissChance() { missChance = stdMissChance; }


// Adding a new effect to this object
bool Combat::addStatusEffect(Effect* toAdd) {
	// Check the effect doesn't already exist and if it does then update the duration of that effect
	for (Effect* effect : activeEffects) {
		if (effect->name == toAdd->name) {
			effect->updateDuration(toAdd->getDuration());
			return false;
		}
	}

	// If the effect doesn't exist add the new effect
	activeEffects.push_back(toAdd);
	return true;
}
// Delete a pre existing status effect
void Combat::deleteStatusEffect(Effect* toRemove) {
	// Find the index of the status effect then remove it
	for (int i = 0; i < activeEffects.size(); i++) {
		if (activeEffects[i]->name == toRemove->name) {
			activeEffects.erase(activeEffects.begin() + i);
			break;
		}
	}
}
// Clear the list of active effects and reset all the values changed by the effects
void Combat::clearStatusEffects() {
	activeEffects.clear();

	health = stdHealth;
	critMult = stdCritMult;
	defense = stdDefense;
	missChance = stdMissChance;
}

// Checking if the attack exists and if it does then return the correct value
std::tuple<float, bool, bool, std::string>* Combat::getAttack(std::string toCheck) {
	int index = -1;
	for (int i = 0; i < availableAttacks.size(); i++) {
		// Check the names both in all lower case
		if (toLower(toCheck) == toLower(std::get<0>(availableAttacks[i]))) {
			index = i;
			break;
		}
	}
	// Return early if the attack does not exist
	if (index == -1) { return nullptr; }

	// If the attack exists
	if (index >= 0) {
		// Generate a random number for miss chance 
		int value = rand() % 100;
		if (value < std::max(std::get<2>(availableAttacks[index]), missChance)) {
			return new std::tuple<float, bool, bool, std::string>(0, true, false, std::get<0>(availableAttacks[index]));
		}
		// Generate a random number for crit chance
		value = rand() % 100;
		if (value < std::get<3>(availableAttacks[index])) {
			return new std::tuple<float, bool, bool, std::string>((std::get<1>(availableAttacks[index]) * critMult), false, true, std::get<0>(availableAttacks[index]));
		}

		// Neither crit or miss
		return new std::tuple<float, bool, bool, std::string>(std::get<1>(availableAttacks[index]), false, false, std::get<0>(availableAttacks[index]));
	}
}

// Check if the effect exists and working out what to do with the effect
// Returns the format: (Effect object, Apply to player)
std::tuple<Effect> Combat::getMove(std::string toCheck) {
	// Working out what the index of the selected effect is in the myEffects vector
	int index = -1;
	for (int i = 0; i < availableMoves.size(); i++) {
		if (toLower(toCheck) == toLower(std::get<0>(availableMoves[i]))) {
			index = i;
		}
	}

	// Creating an effect and returning the effect along with where it should go
	if (std::get<2>(availableMoves[index]) > 0) {
		Effect* temp = new Effect(std::get<2>(availableMoves[index]), std::get<0>(availableMoves[index]), std::get<1>(availableMoves[index]));
		return *temp;
	}
}

// Function to convert string to all lower case
std::string Combat::toLower(std::string toConvert) {
	for (char& c : toConvert) {
		c = std::tolower(c);
	}

	return toConvert;
}