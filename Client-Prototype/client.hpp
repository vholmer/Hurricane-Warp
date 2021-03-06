#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>

#include <chrono>
#include <future>   
#include <thread>
#include <iostream>
#include <queue>
#include <mutex>

#include "../Game-Prototype/room.hpp"
#include "../Network-Prototype/socket.hpp"
#include "../Network-Prototype/network.hpp"

#include <signal.h>


using namespace std;

using namespace Socket;

using namespace Network;

//volatile atomic<std::queue<std::string>> input_queue(std::queue<std::string>());
//volatile atomic<std::queue<std::string>> output_queue(std::queue<std::string>());

int sock;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


void OnExit(int s) {
	std::cout << "Exiting" << std::endl;
	close(sock);
	exit(1);
}

class Client {
	private:
		atomic<bool> kill_everythread;

		char buffer [500];

		int sockfd;
		int portno;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		
		future<void> input_thread;
		future<void> output_thread;

		vector<int> requestList;
		queue<NetworkStruct*> incoming;
		queue<NetworkStruct*> outgoing;

		void read_process(int socket);
		void sendProcess(int socket);
		void client_process(int socket);
		void send(int socket, std::string s);

		mutex output_mutex;

		unsigned int requestNumber;

	public:
		/*
			
		*/
		Client();

		unsigned int getNextRequestID();
		
		void HandleInput(int socket);

		void endConnection(int socket);

		void quitConnection(int socket);

		
		//Start client
		bool start(int argc, char* argv[]);

		//End client
		bool end();

		// Room requestRoom(int roomID);

		NetworkStruct* getNextServerMessage();

		void sendMessage(std::string str);

		//void sendAttack();

		//void sendAction();

};
#endif