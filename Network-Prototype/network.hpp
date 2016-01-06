#ifndef NETWORK_H
#define NETWORK_H

#include "socket.hpp"
#include <vector>

using namespace Socket;

namespace Network {

enum class MessageCode : unsigned int {
	Default,
	RoomMessage,
	AttackMessage,
	EnemyMessage,
	MoveMessage,
	DeathMessage,
	PlayerMessage,
	MessageMessage,
	SpawnMessage,
	DropMessage,
	ItemMessage,
	StillThere,
	StillHere, 
	ConnectionLost
};

enum class PlayerAction : unsigned int {
	MoveEast,
	MoveWest,
	MoveNorth,
	MoveSouth,
	Drop,
	Hurt
};

enum class SpawnCodes : unsigned int {
	Player,
	Wizard,
	Troll
};

// Set requestID to any non-zeronummer to make the struct 
//act as a request
struct NetworkStruct {
	unsigned int requestID = 0;
	unsigned int timestamp = 0;
	MessageCode code;
	virtual ~NetworkStruct() {};
};


//-------------------------------------------------//
//Room info
//-------------------------------------------------//
struct RoomStruct : NetworkStruct {
	RoomStruct ();
	virtual ~RoomStruct() override;
	int id;
	//std::vector<PlayerStruct*> players;
	//std::vector<EnemyStruct*> enemies;
	//std::vector<unsigned int> items;
};

int SendRoomStruct(RoomStruct& strc, int socket);

int ReadRoomStruct(RoomStruct& strc, int socket);


//-------------------------------------------------/
// Attack
//-------------------------------------------------//
struct AttackStruct : NetworkStruct{
	AttackStruct();
	virtual ~AttackStruct() override;
	int attackerID;
	int targetID;
	int damage;
};


int ReadAttackStruct(AttackStruct& strc, int socket) ;

int SendAttackStruct(AttackStruct& strc, int socket);

//-------------------------------------------------//
//Enemy info
//-------------------------------------------------//
struct EnemyStruct : NetworkStruct{
	EnemyStruct();
	virtual ~EnemyStruct() override;
	int id;
	int attackPoint;
};


int SendEnemyStruct(EnemyStruct& strc, int socket);

int ReadEnemyStruct(EnemyStruct& strc, int socket);

//-------------------------------------------------//
//Spawn
//-------------------------------------------------//
struct SpawnStruct : NetworkStruct {
	SpawnStruct();
	virtual ~SpawnStruct() override;
	int roomID;
	int monsterID;
};


int SendSpawnStruct(SpawnStruct& strc, int socket);

int ReadSpawnStruct(SpawnStruct& strc, int socket);

//-------------------------------------------------//
//Player
//-------------------------------------------------//
/**
 * Content:
 *
 * int requestID : Id for the request, should be set to zero if a call to the server
 * should not be 
 * 
 * int time stamp :
 *
 * MessageCode code : Automatically set to MessageCode::PlayerMessage, should not be changed
 *
 * char * name : name of the player
 *
 * int namebufferSize : The size of the buffer which contains the name
 *
 * int nameSize : Size of the name string
 *
 * A struct which contains all the necissary information about a player
 * inherits from NetworksStruct
 */
struct PlayerStruct : NetworkStruct{
	int id;
	int namesize;
	int nameBufferSize;
	char* name;
	PlayerStruct(int size = 1024);
	virtual ~PlayerStruct() override;
};


int SendPlayerStruct(PlayerStruct& strc, int socket);

int ReadPlayerStruct(PlayerStruct& strc, int socket);
//-------------------------------------------------//
//Message
//-------------------------------------------------//
struct MessageStruct : NetworkStruct{
	int textSize;
	int textBufferSize;
	char* text;
	MessageStruct(int size = 1024);
	virtual ~MessageStruct() override;
};

int ReadMessageStruct(MessageStruct& strc, int socket);

int SendMessageStruct(MessageStruct& strc, int socket);


//----------------------------------------------------

struct ItemStruct : NetworkStruct {
	unsigned int type;
	unsigned int id;
	ItemStruct();
	virtual ~ItemStruct() override;
};

int ReadItemStruct(ItemStruct& strc, int socket);

int SendItemStruct(ItemStruct& strc, int socket);


/**
 * string source : The string to be copied
 * 
 * char * copytarget : The target buffer to copy the string to
 *
 * int targetSize : The size of the buffer
 *
 * Copies the string to the buffer from index 0 to source.size, returns -1
 * if size of copytarget is not larger than source.size + 1 and does not copy, otherwise 
 * returns 0
 */
int SetContentCharArray(std::string source, char * copytarget, int targetSize);

}
#endif