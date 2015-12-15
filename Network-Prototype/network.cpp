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
	DropMessage
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
	MessageCode code;
};

int SendInt(int num, int socket)
{
    int32_t conv = htonl(num);
    char *data = (char*)&conv;
    int left = sizeof(conv);
    int rc;
    while (left) {
        rc = write(socket, data + sizeof(conv) - left, left);
        if (rc < 0) return -1;
        left -= rc;
    }
    return 0;
}

int ReadInt(int *num, int fd)
{
    int32_t ret;
    char *data = (char*)&ret;
    int left = sizeof(ret);
    int rc;

    while (left) {
        rc = read(fd, data + sizeof(ret) - left, left);
        if (rc < 0) return -1;
        left -= rc;
    }

    int answer = data[0];
    answer += data[1] >> 8;
    answer += data[2] >> 16;
    answer += data[3] >> 24;

    *num =  ntohl(answer);
    return 0;
}

int SendString(char* str, unsigned int length, int socket) {
	if(SendInt(socket, length) != 0) {
		return -1;
	}
	int left = length;
    int rc;
    while (left) {
        rc = write(socket, str + length - left, left);
        if (rc < 0) return -1;
        left -= rc;
    }
    return 0;
}

int ReadString(char* str, int socket, int length) {
	int left = length;
    int rc;
    while (left) {
        rc = read(socket, str + length - left, left);
        if (rc < 0) return -1;
        left -= rc;
    }
}

/*
//-------------------------------------------------//
//Room info
//-------------------------------------------------//
struct RoomInfo : NetworkStruct {
	RoomInfo () {code = MessageCode::MessageMessage;}
	int id;
};

void SendRoomInfo(RoomInfo& str, int socket) {
	SendInt((unsigned int)str.code, socket); // Send the op code
	SendInt(str.requestID, socket); // Send the requestID
	SendInt(str, socket);
}

void ReceiveRoomInfo(int socket) {
	RoomInfo str;
	return str;
}


//-------------------------------------------------/
// Attack
//-------------------------------------------------//
struct AttackInfo : NetworkStruct{
	AttackInfo() {code = MessageCode::AttackMessage;}
	int attackerID;
	int enemyID;
	int targetID;
	int damage;
};

void SendAttackInfo(AttackInfo& str, int socket) {

}

AttackInfo ReceiveAttackInfo(int socket) {
	AttackInfo str;
	return str;
}

//-------------------------------------------------//
//Enemy info
//-------------------------------------------------//
struct EnemyInfo : NetworkStruct{
	EnemyInfo() {code = MessageCode::EnemyMessage;}
	int id;
	int attackPoint;
};

void SendEnemyInfo(EnemyInfo str, int socket) {
	SendInt((unsigned int)str.code, socket);
	SendInt(str.requestID, socket);
	SendInt(str.enemyID, socket);
}

EnemyInfo ReceiveEnemyInfo(int socket) {
	EnemyInfo str;
	return str;
}

//-------------------------------------------------//
//Spawn
//-------------------------------------------------//
struct SpawnInfo : NetworkStruct {
	SpawnInfo() {code = MessageCode::SpawnMessage;}
	int roomID;
	int monsterID;
};

void SendSpawnInfo(SpawnInfo& str, int socket) {
	
}

SpawnInfo ReceiveSpawn(int socket) {
	SpawnInfo str;
	return str;
}
//-------------------------------------------------//
//Player
//-------------------------------------------------//
struct PlayerInfo : NetworkStruct{
	PlayerInfo() {code = MessageCode::PlayerMessage;}
	int id;
	char* name;
	int namesize;
};
void SendPlayerInfo(PlayerInfo& str, int socket) {

}

PlayerInfo ReceivePlayerInfo(int socket) {
	PlayerInfo str;
	return str;
}

//-------------------------------------------------//
//Message
//-------------------------------------------------//
struct MessageInfo : NetworkStruct{
	MessageInfo() {code = MessageCode::MessageMessage;}
	int senderID;
	int receiverID;
	char* text;
	int textSize;
};

void SendMessage(MessageInfo& str, int socket) {

}

MessageInfo ReceiveMessage(int socket) {
	MessageInfo str;
	return str;
} 
*/
#endif