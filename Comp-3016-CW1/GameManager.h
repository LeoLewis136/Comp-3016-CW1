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
#include <chrono>
#include <thread>

#include "MapLoader.h"
#include "Vector2.h"
#include "Updatable.h"
#include "Drawable.h"
#include "Player.h"
#include "Enemy.h"

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

	std::chrono::high_resolution_clock::time_point manageFramerate(std::chrono::high_resolution_clock::time_point _startTime, std::chrono::milliseconds _frameDuration) {
		// Calculate elapsed time
		auto endTime = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - _startTime);

		// Sleep to maintain desired FPS
		if (elapsedTime < _frameDuration) {
			std::this_thread::sleep_for(_frameDuration - elapsedTime);
		}

		// Reset start_time for next frame
		return std::chrono::high_resolution_clock::now();
	}

	void gameLoop() {
		/* Setting up required variables to keep a 
		consistent framerate no matter execution time */
		const int targetFps = 5;
		const std::chrono::milliseconds frameDuration(1000 / targetFps);
		std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();


		Player* character = new Player('P', Vector2(3, 3));
		updatables.push_back(character);
		drawables.push_back(character);

		std::vector<Vector2> path0 = { Vector2(1,1), Vector2(1,2), Vector2(2,2), Vector2(2,1) };
		Enemy* test = new Enemy('E', Vector2(1,1), path0, *character);
		drawables.push_back(test);
		updatables.push_back(test);

		while (gameRunning) {
			system("cls");

			update();
			draw();

			startTime = manageFramerate(startTime, frameDuration);
		}

	}
};