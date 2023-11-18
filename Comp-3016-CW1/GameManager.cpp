#include "GameManager.h"
#include "TurnBased.h"

GameManager::GameManager(std::string map) {
	// Loading the map
	mapHandler = new MapLoader(map);
	gameLoop();
}

void GameManager::startBattle(Enemy* enemy) {
	TurnBasedCombat* temp = new TurnBasedCombat(myPlayer, enemy);
	temp->mainLoop();

	delete(temp);
}

// Funtion to update all objects that require an update function to be called
void GameManager::update() {
	for (int i = 0; i < updatables.size(); i++) {
		updatables[i]->update(mapHandler->map);
	}
}

void GameManager::draw() {
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

	//std::cout << "UI testing" ;
	//std::cout << *myPlayer->position << std::endl;
	//for (Enemy* enemy : enemies) {
	//	std::cout << enemy->position->distanceTo(*myPlayer->position) << "  ";
	//}
}

std::chrono::high_resolution_clock::time_point GameManager::manageFramerate(std::chrono::high_resolution_clock::time_point _startTime, std::chrono::milliseconds _frameDuration) {
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

void GameManager::gameLoop() {
	/* Setting up required variables to keep a
	consistent framerate no matter execution time */
	const int targetFps = 5;
	const std::chrono::milliseconds frameDuration(1000 / targetFps);
	std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

	createObjects();

	while (gameRunning) {
		system("cls");

		this->update();
		checkEnemies();
		this->draw();

		startTime = manageFramerate(startTime, frameDuration);
	}

	system("cls");
	std::cout << "You Lost";
}

void GameManager::createObjects() {
	std::vector<Vector2> path0 = { Vector2(1,0), Vector2(0,-1), Vector2(-1,0), Vector2(0,1) };
	myPlayer = new Player('P', Vector2(mapHandler->myPlayer.x, mapHandler->myPlayer.y), 100, 1, 2);
	drawables.push_back(myPlayer);
	updatables.push_back(myPlayer);

	for (int i = 0; i < mapHandler->enemies.size(); i++) {
		Enemy* temp = new Enemy('E', Vector2(mapHandler->enemies[i].x, mapHandler->enemies[i].y), path0, myPlayer, 60, 1, 2);
		drawables.push_back(temp);
		updatables.push_back(temp);
		enemies.push_back(temp);
	}
}

void GameManager::deleteEnemy(Enemy* _toDelete) {
	int count = 0;
	while (count < drawables.size() || count < updatables.size()) {
		Enemy* tempPtr = dynamic_cast<Enemy*>(drawables[count]);
		if (tempPtr && tempPtr == _toDelete) {
			drawables.erase(drawables.begin() + count);
		}

		tempPtr = dynamic_cast<Enemy*>(updatables[count]);
		if (tempPtr && tempPtr == _toDelete) {
			updatables.erase(updatables.begin() + count);
		}

		count++;
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (_toDelete == enemies[i]) {
			enemies.erase(enemies.begin() + i);
		}
	}

	delete _toDelete;
}

void GameManager::checkEnemies() {
	for (Enemy* enemy : enemies) {
		if (*enemy->position == *myPlayer->position) {
			TurnBasedCombat* combat = new TurnBasedCombat(myPlayer, enemy);

			bool playerWon = combat->mainLoop();
			// Clearing the enemy if they die
			if (playerWon) {
				this->deleteEnemy(enemy);
				enemy->isDead = true;
				break;
			}
			else {
				gameRunning = false;
				break;
			}
		}
	}
}