#include <iostream>

#include "engine.hpp"

using namespace std;

Engine::Engine() {
	quitBoolean = false;
	parser = new Parser();
	player = new Player();
	roomHandler = new RoomHandler();
}

void Engine::memHandle() {
	delete parser;
	delete player;
	delete roomHandler;
}

void Engine::printIntro() {
	cout << "You have crashed!" << endl;
	cout << "In the name of the Emperor, good luck." << endl << endl;
}

void Engine::startGameLoop() {
	printIntro();
	player->currentRoom = roomHandler->start();
	cout << player->currentRoom->description << endl;
}

void Engine::quitGame() {
	quitBoolean = true;
}

void Engine::respawn() {
	cout << "No respawns lol" << endl;
}