#pragma once

#include <tuple>
#include <vector>
#include <string>
#include <conio.h>

#include "Drawable.h"
#include "Updatable.h"
#include "Combat.h"

class Player : public Drawable, public Updatable, public Combat {
public:
	/* Storing the current values of each of these parameters */
	// Storing current health
	int health = 100;
	// Multiplier that determines how much extra damage crits currently do
	int critMult = 2;
	// Multiplier that is used for "defense"
	int damageMult = 1;
	// Int that stores what the current minimum miss chance is
	// Changes to allow for increased miss chance for a few turns
	int missChance = 0;
	
	Player(char to_draw, Vector2 start_pos, float health, float defense, float critMult);

	void update(std::vector<std::vector<std::string>>& map);

protected:
	// Getting inputs 
	Vector2 inputs();
};