#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

#include "Vector2.h"
#include "MapLoader.h"
#include "Combat.h"
#include "Enemy.h"
#include "Player.h"

class GameManager {
public:
	GameManager(std::string map);

	void startBattle(Enemy* enemy);

private:
	MapLoader* mapHandler;
	Player* myPlayer;
	bool gameRunning = true;

	std::vector<Updatable*> updatables;
	std::vector<Drawable*> drawables;
	std::vector<Enemy*> enemies;

	/* Core game loop functions which organise 
	the calling order of all game loop functions*/

	// Funtion to update all objects that require an update function to be called
	void update();

	void draw();

	std::chrono::high_resolution_clock::time_point manageFramerate(std::chrono::high_resolution_clock::time_point _startTime, std::chrono::milliseconds _frameDuration);

	void gameLoop();

	void createObjects();

	void deleteEnemy(Enemy* _toDelete);

	void checkEnemies();
};