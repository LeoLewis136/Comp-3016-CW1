#include "GameManager.h"

int main() {
	// Seed random
	std::srand((unsigned)time(NULL));
	// Create game object and pass map file name
	GameManager game = GameManager("Map.txt");

	return 0;	
}