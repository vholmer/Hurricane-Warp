#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "item.hpp"
#include "actor.hpp"
#include "player.hpp"

using namespace std;

struct Item;
struct Actor;
struct Player;

const string NORTH = "north";
const string EAST = "east";
const string SOUTH = "south";
const string WEST = "west";
const string UP = "up";
const string DOWN = "down";

struct Room {

private:
	string description;
	vector<Item*> itemsInRoom;
	vector<Actor*> charsInRoom;
	vector<Player*> playersInRoom;

public:

	unordered_map<string, Room*> exits;
	
	Room(string description);

	string getDescription() const;

	vector<Item*>& getItemsInRoom();

	vector<Actor*>& getCharsInRoom();

	vector<Player*>& getPlayersInRoom();

	vector<string> getExits();

	void addItem(Item* item);

	void addChar(Actor* actor);

	void addPlayer(Player* p);

	void removeItem(Item* item);

	void removeChar(Actor* actor);

	void removePlayer(Player* p);
};

#endif
