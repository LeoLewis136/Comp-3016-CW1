#include "Vector2.h"
#include "MapLoader.h"

// Constructor that takes a location to load the map from
MapLoader::MapLoader(std::string& mapLocation) {
	mapLoader(mapLocation);
	finalPass();
}

// Method to split a string at a delimiter
std::vector<std::string> MapLoader::stringSplit(std::string _input, char delimiter) {
	// Temporary storage variables
	std::vector<std::string> finalLine;
	std::stringstream stream(_input);
	std::string temp;

	// Read each line and split using the delimiter
	while (getline(stream, temp, delimiter)) {
		finalLine.push_back(temp);
	}

	// Return the new line with the correct splits
	return finalLine;
}

// Method to load the map file and store it in the map variable
void MapLoader::mapLoader(std::string mapLocation) {
	// Create readable map file
	std::ifstream mapFile(mapLocation);

	// Variables that can be used to temporarily store parts of the map pduring loading
	std::vector<std::string> tempMap;
	std::string line;

	// Read each line of the file line by line and store in tempMap
	if (mapFile.is_open()) {
		while (getline(mapFile, line)) {
			tempMap.push_back(line);
		}
	}
	// Throw an error if the map file is unable to be read from
	else {
		std::cerr << "Map file cannot be opened";
		std::exit(0);
	}

	// Split each line of the map file into a vector so that each map position is separate
	for (int i = 0; i < tempMap.size(); i++) {
		map.push_back(this->stringSplit(tempMap[i], ','));
	}

}

// Looking for any special objects defined within the map file
void MapLoader::finalPass() {
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			// Storing the position of any enemies on the map te be created later
			// Standard enemy
			if (map[y][x] == "E") {
				enemies.push_back(std::make_tuple(Vector2(x, y), "E"));
				map[y][x] = ".";
			}
			// Brute enemy
			if (map[y][x] == "B") {
				enemies.push_back(std::make_tuple(Vector2(x, y), "B"));
				map[y][x] = ".";
			}
			// Rogue enemy
			if (map[y][x] == "R") {
				enemies.push_back(std::make_tuple(Vector2(x, y), "R"));
				map[y][x] = ".";
			}

			// Storing the position of the player on the map to be loaded later
			else if (map[y][x] == "P") {
				myPlayer = Vector2(x, y);
				map[y][x] = ".";
			}
		}
	}
}