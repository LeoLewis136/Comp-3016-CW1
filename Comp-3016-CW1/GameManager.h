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
#include "Vector2.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Player.h"

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

	std::vector<Updatable*> updatables;
	std::vector<Drawable*> drawables;

	/* Core game loop functions which organise 
	the calling order of all game loop functions*/

	// Funtion to update all objects that require an update function to be called
	void update() {
		for (int i = 0; i < updatables.size(); i++) {
			updatables[i]->update(mapHandler->map);
		}
	}

	void draw() {
		std::vector<std::vector<std::string>> tempMap = mapHandler->map;

		for (int i = 0; i < drawables.size(); i++) {
			tempMap[drawables[i]->position->y][drawables[i]->position->x] = drawables[i]->getDrawable();
		}
		
		for (int y = 0; y < tempMap.size(); y++) {
			for (int x = 0; x < tempMap[y].size(); x++) {
				std::cout << tempMap[y][x];
			}
			std::cout << std::endl;
		}

		std::cout << "UI testing" << std::endl;
	}

	void gameLoop() {
		Player* character = new Player('P', Vector2(3, 3));
		updatables.push_back(character);
		drawables.push_back(character);

		Drawable* test = new Drawable('E');
		drawables.push_back(test);

		while (gameRunning) {
			system("cls");

			update();
			draw();

			Sleep(10);
		}
	}
};