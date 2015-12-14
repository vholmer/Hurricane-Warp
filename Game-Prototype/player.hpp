#include <vector>

using namespace std;

struct Player {
	Room currentRoom;
	vector<Item> inventory;
	int hitPoints;

	Player();
};