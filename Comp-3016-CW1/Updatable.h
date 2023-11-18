#pragma once

#include <vector>
#include <string>

class Updatable {
public:
	// Creating update method for child classes to inherit and modify 
	virtual void update(std::vector<std::vector<std::string >> &map) {}
};