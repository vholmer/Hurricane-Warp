#ifndef NETWORK_H
#define NETWORK_H

enum class ClientOutput : unsigned int{
	SendInt,
	SendAsciiString,
	SendMessage,
	SendPlayerAction,
	RequestRoomInfo,
	RequestPlayerInfo,
	ConnectionLost = 0xffffffff,
};

enum class ClientInput : unsigned int {
	ReceivingInteger,
	ReceivingString,
	RoomInfo,
	ItemInfo,
	PlayerInfo,
	PlayerAction,
	CloseConnection = 0xffffffff,
};

enum class MessageCode : unsigned int {
	Default,
	RoomMessage,
	AttackMessage,
	EnemyMessage,
	PlayerMessage,
	MessageMessage,
	SpawnMessage,
	DropMessage,
	ConnectionLost = 0xffffffff
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

/*
//-------------------------------------------------//
//Room info
//-------------------------------------------------//
struct RoomServerStruct : NetworkStruct {
	RoomInfo () {code = MessageCode::MessageMessage;}
	int id;
};

struct PlayerClientStruct : NetworkStruct {
	PlayerClientStruct() {code = MessageCode::PlayerMessage;}
};

void SendRoomInfo(RoomInfo& str, int socket) {
	SendInt((unsigned int)str.code, socket); // Send the op code
	SendInt(str.requestID, socket); // Send the requestID
	SendInt(str, socket);
}

RoomServerStruct ReceiveRoomInfo(int socket) {
	RoomServerStruct str;
	return str;
}


//-------------------------------------------------/
// Attack
//-------------------------------------------------//
struct AttackServerStruct : NetworkStruct{
	AttackServerStruct() {code = MessageCode::AttackMessage;}
	int attackerID;
	int enemyID;
	int targetID;
	int damage;
};

struct PlayerClientStruct : NetworkStruct {
	PlayerClientStruct() {code = MessageCode::PlayerMessage;}
};

void SendAttackInfo(AttackInfo& str, int socket) {

}

AttackServerStruct ReceiveAttackInfo(int socket) {
	AttackServerStructstr;
	return str;
}

//-------------------------------------------------//
//Enemy info
//-------------------------------------------------//
struct EnemyServerStruct : NetworkStruct{
	EnemyServerStruct() {code = MessageCode::EnemyMessage;}
	int id;
	int attackPoint;
};

struct PlayerClientStruct : NetworkStruct {
	PlayerClientStruct() {code = MessageCode::PlayerMessage;}
};

void SendEnemyInfo(EnemyInfo str, int socket) {
	SendInt((unsigned int)str.code, socket);
	SendInt(str.requestID, socket);
	SendInt(str.enemyID, socket);
}

EnemyServerStructReceiveEnemyInfo(int socket) {
	EnemyServerStruct str;
	return str;
}

//-------------------------------------------------//
//Spawn
//-------------------------------------------------//
struct SpawnServerStruct : NetworkStruct {
	SpawnInfo() {code = MessageCode::SpawnMessage;}
	int roomID;
	int monsterID;
};

struct SpawnClientStruct : NetworkStruct {
	SpawnClientStruct() {code = MessageCode::SpawnMessage;}
};

void SendSpawnInfo(SpawnInfo& str, int socket) {
	
}

SpawnServerStruct ReceiveSpawn(int socket) {
	SpawnServerStruct str;
	return str;
}
//-------------------------------------------------//
//Player
//-------------------------------------------------//
struct PlayerServerStruct : NetworkStruct{
	PlayerServerStruct() {code = MessageCode::PlayerMessage;}
	int id;
	char* name;
	int namesize;
};

struct PlayerClientStruct : NetworkStruct {
	PlayerClientStruct() {code = MessageCode::PlayerMessage;}
};
void SendPlayerInfo(PlayerInfo& str, int socket) {

}

PlayerServerStruct ReceivePlayerInfo(int socket) {
	PlayerServerStructstr;
	return str;
}

//-------------------------------------------------//
//Message
//-------------------------------------------------//
struct MessageServerStruct : NetworkStruct{
	MessageServerStruct() {code = MessageCode::MessageMessage;}
	int senderID;
	int receiverID;
	char* text;
	int textSize;
};

struct MessageClientStruct : NetworkStruct {
	MessageClientStruct() {code = MessageCode::MessageMessage;}
};

void SendMessage(MessageMessage& str, int socket) {

}

MessageServerStruct ReceiveMessage(int socket) {
	MessageServerStruct str;
	return str;
} 
*/
#endif