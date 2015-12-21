#include "network.hpp"
//-------------------------------------------------//
//Message
//-------------------------------------------------//

namespace Network {

int SendRoomStruct(RoomStruct& strc, int socket) {
	int n = SendInt((int)strc.code, socket);
	n = SendInt(strc.id, socket);
	return n;
}

int ReadRoomStruct(RoomStruct& strc, int socket) {
	int n = ReadInt(&(strc.id), socket);
	return n;
}

//-------------------------------------------------//
//Message
//-------------------------------------------------//


int ReadAttackStruct(AttackStruct& strc, int socket) {
	int n = ReadInt(&(strc.attackerID), socket);
	n = ReadInt(&(strc.targetID), socket);
	n = ReadInt(&(strc.damage), socket);
	return n;
}

int SendAttackStruct(AttackStruct& strc, int socket) {
	int n = SendInt((int)strc.code, socket);
	n = SendInt(strc.attackerID, socket);
	n = SendInt(strc.targetID, socket);
	n = SendInt(strc.damage, socket);
	return n;
}


//-------------------------------------------------//
//Message
//-------------------------------------------------//

int SendEnemyStruct(EnemyStruct& strc, int socket) {
	int n = SendInt((unsigned int)strc.code, socket);
	n = SendInt(strc.id, socket);
	n = SendInt(strc.attackPoint, socket);
	return n;
}

int ReadEnemyStruct(EnemyStruct& strc, int socket) {
	int n = ReadInt(&(strc.id), socket);
	n = ReadInt(&(strc.attackPoint), socket);
}

//-------------------------------------------------//
//Message
//-------------------------------------------------//

int SendSpawnStruct(SpawnStruct& strc, int socket) {
	int n = SendInt((int)strc.code, socket);
	n = SendInt(strc.roomID, socket);
	n = SendInt(strc.monsterID, socket);
	return n;
}

int ReadSpawnStruct(SpawnStruct& strc, int socket) {
	int n = ReadInt(&(strc.roomID), socket);
	n = ReadInt(&(strc.monsterID), socket); 
	return n;
}

//-------------------------------------------------//
//Message
//-------------------------------------------------//

PlayerStruct::PlayerStruct() {
	code = MessageCode::PlayerMessage;
	nameBufferSize = size;
	name = new char[nameBufferSize]();
}

PlayerStruct::~PlayerStruct() {
	delete [] name;
}

int SendPlayerStruct(PlayerStruct& strc, int socket) {
	int n = SendInt((int)strc.code, socket);
	n = SendInt(strc.id, socket);
	n = SendString(strc.name, strc.namesize, socket);
	return n;
}

int ReadPlayerStruct(PlayerStruct& strc, int socket) {
	int n = ReadInt(&(strc.id), socket);
	n = ReadInt(&(strc.namesize), socket);
	n =ReadString(strc.name, strc.namesize, socket);
	return n;
}


//-------------------------------------------------//
//Message
//-------------------------------------------------//
MessageStruct::MessageStruct(int size = 1024) {
		code = MessageCode::MessageMessage;
		requestID = 0;
		textBufferSize = size;
		text = new char[textBufferSize]();
}

MessageStruct::~MessageStruct() {
	delete [] text;
}

int ReadMessageStruct(MessageStruct& strc, int socket) {
	int n = ReadInt(&(strc.senderID), socket);
	n = ReadInt(&(strc.receiverID), socket);
	n = ReadInt(&(strc.textSize), socket);
	n = ReadString(strc.text, strc.textSize, socket);
	return n;
}

int SendMessageStruct(MessageStruct& strc, int socket) {
	int n = SendInt((int) strc.code, socket);
	
	n = SendInt(strc.senderID, socket);
	n = SendInt(strc.receiverID, socket);
	n = SendString(strc.text, strc.textSize, socket);
	return n;
}

//---//
int SetContentCharArray(std::string source, char * copytarget, int targetSize) {
	if(source.size() >= targetSize) {
		return -1;
	}
	std::copy(source.begin(), source.end(), copytarget);
	copytarget[source.size()]=0;
	return 0;
}


}