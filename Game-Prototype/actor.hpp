#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <vector>

#include "room.hpp"
#include "player.hpp"
#include "item.hpp"
#include "engine.hpp"
#include "../Network-Prototype/clientHandler.hpp"

using namespace std;

struct Room;
struct Player;
struct Engine;
struct ClientHandler;

struct Actor {

protected:

	Room* currentRoom;

	string name;
	string description;

	int health;
	int damageBase;

public:

	void setDamageBase(int damageBase); //in actor.cpp

	virtual ~Actor() = default;

	virtual void act(Engine* engine) = 0;

	virtual void die(Engine* engine);

	string getName() const;

	string getDescription() const;

	int getHealth() const;

	Room* getRoom();

	void takeDamage(int toSubtract);

	void setRoom(Room* newRoom);

protected:

	void walk(Engine* engine); //in actor.cpp

	void printActor();

	int fight(Actor* a); //in actor.cpp

	int fight(Player* p); //in actor.cpp

	Player* playerInRoom(); // in actor.cpp
};

#endif