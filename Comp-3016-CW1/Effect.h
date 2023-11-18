#pragma once

#include <string>

class Combat;

/* Class that can be used to create an object to store 
information about a current status effect on an object */
class Effect {
public:
	/* Constructor to create an effect takes parameters 
	(The value to modify, the length in turns of the effect, the value to make the effected stat)
	and then assigns the desired value to the stat */
	Effect(int _duration, std::string _effectName, float _value);

	void setParent(Combat* temp);

	bool update();

	void updateDuration(int newDuration);
	int getDuration();

	std::string name;
	int modifiedStat;

private:
	void deleteEffect();

	// Applying the desired effect of this effect object upon creation
	std::string manageEffect(int _value);

	float change;
	Combat* myParentObject;
	int duration;
};