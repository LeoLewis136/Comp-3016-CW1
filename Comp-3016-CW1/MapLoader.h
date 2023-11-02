#pragma once

class MapLoader {
public:
	// Variable to store the map
	std::vector<std::vector<std::string>> map;

	// Constructor that takes a location to load the map from
	MapLoader(std::string& mapLocation) {
		mapLoader(mapLocation);
	}

private:
	// Method to split a string at a delimiter
	std::vector<std::string> stringSplit(std::string input, char delimiter) {
		// Temporary storage variables
		std::vector<std::string> finalLine;
		std::stringstream stream(input);
		std::string temp;

		// Read each line and split using the delimiter
		while (getline(stream, temp, delimiter)) {
			finalLine.push_back(temp);
		}

		// Return the new line with the correct splits
		return finalLine;
	}

	// Method to load the map file and store it in the map variable
	void mapLoader(std::string mapLocation) {
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
			map.push_back(stringSplit(tempMap[i], ','));
		}

	}
};