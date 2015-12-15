#include "engine.hpp"

int main(void) {
	Engine* game = new Engine();
	game->startGameLoop();
	return 0;
}