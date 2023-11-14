#pragma once

/* Class that can be used to create an object to store 
information about a current status effect on an object */
class Effect {
public:
	/* Constructor to create an effect takes parameters 
	(The value to modify, the length in turns of the effect, the value to make the effected stat)
	and then assigns the desired value to the stat */
	Effect(int &_modified, int _duration, std::string _effectName, int _value) {
		modifiedStat = &_modified;
		duration = _duration;
		defaultValue = *modifiedStat;
		*modifiedStat = _value;

		name = _effectName;
	}

	bool update() {
		duration--;

		// When this effect is over reset stat
		if (duration <= 0) {
			*modifiedStat = defaultValue;
			return true;
		}
		return false;
	}

	std::string name;
	int* modifiedStat = nullptr;

private:
	
	int duration;
	int defaultValue;
};