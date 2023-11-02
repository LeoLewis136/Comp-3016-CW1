#pragma once
#include <Math.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <conio.h>

#include "MapLoader.h"
#include "Drawable.h";
#include "Vector2.h";

class GameManager {
public:
	GameManager(std::string map) {
		// Loading the map
		mapHandler = new MapLoader(map);

		gameLoop();
	}

private:
	MapLoader* mapHandler;
	bool gameRunning = true;

	/* Core game loop functions which organise 
	the calling order of all game loop functions*/

	// Funtion to update all objects that require an update function to be called
	void update() {

	}

	void draw() {
		std::vector<std::vector<std::string>> tempMap = mapHandler->map;

		for (int y = 0; y < tempMap.size(); y++) {
			for (int x = 0; x < tempMap[y].size(); x++) {
				std::cout << tempMap[y][x];
			}
			std::cout << std::endl;
		}

		std::cout << "UI test";
	}

	void gameLoop() {
		while (gameRunning) {
			system("cls");

			update();
			draw();

			Sleep(10);
		}
	}
};