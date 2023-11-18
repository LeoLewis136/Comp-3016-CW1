#pragma once

#include <vector>
#include <tuple>

class Effect;

class Combat {
public:
	// Default empty constructor
	Combat();
	// Constructor that assigns all the required attributes to passed values
	Combat(float _health, float _critMult, float _defense);

	/* interacting with any private attributes with get/set methods */

	/* Get / Set for all required paremeters */
	// Getting all the attacks that this object is able to use
	std::vector<std::tuple<std::string, float, float, float>> getAvailableAttacks();
	// Gettinf all the non-damaging moves that this object is able to use
	std::vector<std::tuple<std::string, float, int, bool>> getAvailableMoves();
	// Getting any status effects currently effecting this object
	std::vector<Effect*> getActiveEffects();
	// Health get/set and function to + or - health while keeping within the max and min
	float getHealth();
	void setHealth(float _health);
	void modifyHealth(float change);
	// Defense functions
	void setDefense(float toSet);
	void resetDefense();
	float getDefense();
	// Crit mutiplier functions
	void setCritMult(float toSet);
	void resetCritMult();
	// Miss chance funstions
	void setMissChance(float toSet);
	void resetMissChance();


	

	// Adding a new effect to this object
	bool addStatusEffect(Effect* toAdd);
	// Delete a pre existing status effect
	void deleteStatusEffect(Effect* toRemove);
	// Clear the list of active effects and reset all the values changed by the effects
	void clearStatusEffects();

	// Checking if the attack exists and if it does then return the correct value
	std::tuple<float, bool, bool, std::string>* getAttack(std::string toCheck);

	// Check if the effect exists and working out what to do with the effect
	// Returns the format: (Effect object, Apply to player)
	std::tuple<Effect> getMove(std::string toCheck);

	// All attacks. Format is (name, damage, miss chance, crit chance)
	std::vector<std::tuple<std::string, float, float, float>> availableAttacks;
	// All available non attack moves. Format is (name, effect amount, duration, effectOnPlayer)
	std::vector<std::tuple<std::string, float, int, bool>> availableMoves;
	// Stores all currently active effects
	std::vector<Effect*> activeEffects;

protected:
	// Combat object stats
	float health;
	float critMult;
	float defense;
	float missChance;

	// Storing the default value of each stat of this object
	float stdHealth;
	float stdCritMult;
	float stdDefense;
	float stdMissChance;

	// Function to convert string to all lower case
	std::string toLower(std::string toConvert);
};