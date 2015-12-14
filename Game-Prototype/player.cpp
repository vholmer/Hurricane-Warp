#include "player.hpp"

Player::Player() {
	currentRoom = Room.start();
	hitPoints = 10;
}