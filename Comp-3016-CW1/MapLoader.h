#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class MapLoader {
public:
	// Variable to store the map
	std::vector<std::vector<std::string>> map;
	std::vector<std::vector<Vector2>> paths;

	std::vector<std::tuple<Vector2, std::string>> enemies;
	Vector2 myPlayer;

	// Constructor that takes a location to load the map from
	MapLoader(std::string& mapLocation);

private:
	// Method to split a string at a delimiter
	std::vector<std::string> stringSplit(std::string input, char delimiter);

	// Method to load the map file and store it in the map variable
	void mapLoader(std::string mapLocation);

	// Load required info for the game
	void mapInfo(std::string mapInfoLocation);

	// Looking for any special objects defined within the map file
	void finalPass();
};