#include "GameManager.h"

int main() {
	std::srand((unsigned)time(NULL));
	GameManager game = GameManager("Map.txt");

	return 0;	
}