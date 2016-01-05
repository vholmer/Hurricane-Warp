#include <time.h>

#include "engine.hpp"

int main(void) {
	srand(time(NULL));
	Engine game;
	game.startGameLoop();
	return 0;
}