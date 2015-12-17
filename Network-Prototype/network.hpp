#ifndef NETWORK_H
#define NETWORK_H

#include "socket.hpp"

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
	ConnectionLost
};

enum class PlayerAction : unsigned int {
	MoveEast,
	MoveWest,
	MoveNorth,
	MoveSouth,
	Drop,
	Attack,
};

// Set requestID to any non-zeronummer to make the struct 
//act as a request
struct NetworkStruct {
	unsigned int requestID = 0;
	unsigned int timestamp = 0;
	MessageCode code;
};


//-------------------------------------------------//
//Room info
//-------------------------------------------------//
struct RoomStruct : NetworkStruct {
	RoomStruct () {code = MessageCode::RoomMessage;}
	int id;
};

struct RoomClientStruct : NetworkStruct {
	RoomClientStruct() {code = MessageCode::PlayerMessage;}
};

int SendRoomStruct(RoomStruct& strc, int socket);

int ReadRoomStruct(RoomStruct& strc, int socket);


//-------------------------------------------------/
// Attack
//-------------------------------------------------//
struct AttackStruct : NetworkStruct{
	AttackStruct() {code = MessageCode::AttackMessage;}
	int attackerID;
	int targetID;
	int damage;
};

struct AttackClientStruct : NetworkStruct {
	AttackClientStruct() {code = MessageCode::PlayerMessage;}
};

int ReadAttackStruct(AttackStruct& strc, int socket) ;

int SendAttackStruct(AttackStruct& strc, int socket);

//-------------------------------------------------//
//Enemy info
//-------------------------------------------------//
struct EnemyStruct : NetworkStruct{
	EnemyStruct() {code = MessageCode::EnemyMessage;}
	int id;
	int attackPoint;
};

struct EnemyClientStruct : NetworkStruct {
	EnemyClientStruct() {code = MessageCode::PlayerMessage;}
};

int SendEnemyStruct(EnemyStruct& strc, int socket);

int ReadEnemyStruct(EnemyStruct& strc, int socket);

//-------------------------------------------------//
//Spawn
//-------------------------------------------------//
struct SpawnStruct : NetworkStruct {
	SpawnStruct() {code = MessageCode::SpawnMessage;}
	int roomID;
	int monsterID;
};

struct SpawnClientStruct : NetworkStruct {
	SpawnClientStruct() {code = MessageCode::SpawnMessage;}
};

int SendSpawnStruct(SpawnStruct& strc, int socket);

int ReadSpawnStruct(SpawnStruct& strc, int socket);

//-------------------------------------------------//
//Player
//-------------------------------------------------//
struct PlayerStruct : NetworkStruct{
	PlayerStruct() {code = MessageCode::PlayerMessage;}
	int id;
	int namesize;
	char* name;
};

struct PlayerClientStruct : NetworkStruct {
	PlayerClientStruct() {code = MessageCode::PlayerMessage;}
};

int SendPlayerStruct(PlayerStruct& strc, int socket);

int ReadPlayerStruct(PlayerStruct& strc, int socket);
//-------------------------------------------------//
//Message
//-------------------------------------------------//
struct MessageStruct : NetworkStruct{
	MessageStruct() {code = MessageCode::MessageMessage;}
	int senderID;
	int receiverID;
	int textSize;
	char* text;
};

struct MessageClientStruct : NetworkStruct {
	MessageClientStruct() {code = MessageCode::MessageMessage;}
};

int ReadMessageStruct(MessageStruct& strc, int socket);

int SendMessageStruct(MessageStruct& strc, int socket);


//----------------------------------------------------

}
#endif