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

// Draw the map
void GameManager::draw() {
	// Create a temporary copy of the map to add dynamic objects without affecting the original
	std::vector<std::vector<std::string>> tempMap = mapHandler->map;

	// Add all the drawable objects in the correct position in the temporary map
	for (int i = 0; i < drawables.size(); i++) {
		tempMap[drawables[i]->position->y][drawables[i]->position->x] = drawables[i]->getDrawable();
	}

	// Loop through entire map and draw to screen
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

// Function to pause the execution of the game for the correct time to manage a consistent framerate
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

// Managing the flow of the game loop
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

// Create entites that are shown on the map
void GameManager::createObjects() {
	// Unused
	std::vector<Vector2> path0 = { Vector2(1,0), Vector2(0,-1), Vector2(-1,0), Vector2(0,1) };
	
	// Add the player in the correct place
	myPlayer = new Player('P', Vector2(mapHandler->myPlayer.x, mapHandler->myPlayer.y), 100, 1, 2);
	drawables.push_back(myPlayer);
	updatables.push_back(myPlayer);

	// Check all the found enemies an place them in the correct place
	for (int i = 0; i < mapHandler->enemies.size(); i++) {
		// Place the enemies in the correct place and give them the correct attacks
		if (std::get<1>(mapHandler->enemies[i]) == "E") {
			Enemy* temp = new Enemy('E', Vector2(std::get<0>(mapHandler->enemies[i]).x, std::get<0>(mapHandler->enemies[i]).y), path0, myPlayer, 70, 1, 2);
			
			temp->availableAttacks.push_back(std::make_tuple("Punch", 20, 5, 5));
			temp->availableAttacks.push_back(std::make_tuple("Claw", 10, 1, 20));
			
			drawables.push_back(temp);
			updatables.push_back(temp);
			enemies.push_back(temp);
		}
		if (std::get<1>(mapHandler->enemies[i]) == "B") {
			Enemy* temp = new Enemy('B', Vector2(std::get<0>(mapHandler->enemies[i]).x, std::get<0>(mapHandler->enemies[i]).y), path0, myPlayer, 100, 1, 1.2);

			temp->availableAttacks.push_back(std::make_tuple("Ground Slam", 40, 0, 0));
			temp->availableAttacks.push_back(std::make_tuple("Punch", 10, 10, 4));

			drawables.push_back(temp);
			updatables.push_back(temp);
			enemies.push_back(temp);
		}
		if (std::get<1>(mapHandler->enemies[i]) == "R") {
			Enemy* temp = new Enemy('R', Vector2(std::get<0>(mapHandler->enemies[i]).x, std::get<0>(mapHandler->enemies[i]).y), path0, myPlayer, 50, 1, 4);

			temp->availableAttacks.push_back(std::make_tuple("Slash", 5, 5, 25));
			temp->availableAttacks.push_back(std::make_tuple("Thrust", 10, 10, 15));

			drawables.push_back(temp);
			updatables.push_back(temp);
			enemies.push_back(temp);
		}

			
	}
}

// Handiling the removal of an enemy object form all required locations when the enemy dies
void GameManager::deleteEnemy(Enemy* _toDelete) {
	int count = 0;
	while (count < drawables.size() || count < updatables.size()) {
		// Check if this index of drawable objects is the correct enemy
		Enemy* tempPtr = dynamic_cast<Enemy*>(drawables[count]);
		if (tempPtr && tempPtr == _toDelete) {
			drawables.erase(drawables.begin() + count);
		}

		// Check if this index of updatable objects is the correct enemy
		tempPtr = dynamic_cast<Enemy*>(updatables[count]);
		if (tempPtr && tempPtr == _toDelete) {
			updatables.erase(updatables.begin() + count);
		}

		// Increase index
		count++;
	}

	// Delete this enemy from the enemies collection
	for (int i = 0; i < enemies.size(); i++) {
		if (_toDelete == enemies[i]) {
			enemies.erase(enemies.begin() + i);
		}
	}
	
	// Delete enemy pointer
	delete _toDelete;
}

void GameManager::checkEnemies() {
	if (enemies.size() > 0) {
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
	else {
		std::cout << "You won \nPress any key to exit";
		_getch();
		exit(0);
	}
	
}