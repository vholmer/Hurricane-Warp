
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

using namespace std;

volatile atomic<std::queue<std::string>> input_queue(std::queue<std::string>());
volatile atomic<std::queue<std::string>> output_queue(std::queue<std::string>());

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

class Client {
	private:
		atomic<bool> kill_everythread;

		int sockfd;
		int portno;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		
		future<void> input_thread;
		future<void> output_thread;

		queue<string> incoming;
		queue<string> outgoing;

		void send_process(int socket);
		void client_process(int socket);
		void send(int socket, std::string s);

		mutex mtx;



	public:
		/*
			
		*/
		Client();

		/*
			Start client
		*/
		bool start(int argc, char* argv[]);

		/*
			End client
		*/
		bool end();

};
#endif