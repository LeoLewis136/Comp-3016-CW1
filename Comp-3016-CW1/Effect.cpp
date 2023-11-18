#include "Effect.h"
#include "Combat.h"

/* Define all the methods that the Effect class requires */
Effect::Effect(int _duration, std::string _effectName, float _value) {
	duration = _duration;
	change = _value;
	name = _effectName;
}

void Effect::setParent(Combat* temp) {
	myParentObject = temp;
	manageEffect(change);
}

bool Effect::update() {
	duration--;

	// When this effect is over reset stat
	if (duration <= 0) {
		deleteEffect();
		return true;
	}
	return false;
}

int Effect::getDuration() { return duration; }
void Effect::updateDuration(int newDuration) {
	duration = newDuration;
}


void Effect::deleteEffect() {
	if (name == "Fortify") {
		myParentObject->resetDefense();
	}
	else if (name == "Critical surge") {
		myParentObject->resetCritMult();
	}
}

// Applying the desired effect of this effect object upon creation
std::string Effect::manageEffect(int _value) {
	if (name == "Fortify") {
		return "";
	}
	else if (name == "Critical surge") {
		myParentObject->setCritMult(_value);
	}
	else if (name == "Heal") {
		myParentObject->modifyHealth(_value);
	}
	return "";
}