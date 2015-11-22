#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <chrono>
#include <future>   
#include <thread>
#include <iostream>
#include <list>

#include <unistd.h>

#include <atomic>

#include "clientHandler.hpp"

using namespace std;

class Server {
	private:
		int sockfd;
		int portn;

		struct sockaddr_in serv_addr;
		future<void> thread_starter;
		future<void> admin_input;
		future<void> game_logic;

		list<ClientHandler*> client_list;

		atomic<bool> kill_everythread;

		mutex list_mutex;

		void client_listener();


		public:
		Server();

		bool start(char* c);


		bool stop();

};
#endif

