#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <chrono>
#include <future>   
#include <thread>
#include <iostream>
#include <queue>
#include <unistd.h>
#include <atomic>

using namespace std;

class ClientHandler {

	private:
		string id;
		string ip_adress;

		atomic<int> socket;

		future<void> out_thr; // Future objects which referenses the output thread
		future<void> in_thr; // Future objects which referenses the input thread

		bool started; // set to true when connection is established

		atomic<bool> kill_everythread; // set to true when we want all processes to end themselves

		/*
		Calculate the ip with the help of a socket struct
		*/
		string calculateIP(struct sockaddr_in &cli_addr) const;


		void outProcess(int sock); // process which handles the input

		void inProcess(int sock); // process which handles the output

	public:

		queue<string> input; // queue which holds all the input 
		queue<string> output; // queue which holds all the ouput

		/*
		Create a client which listens to the socket
		(the socket needs to have been accepted)
		*/
		ClientHandler();

		/*
		Returns true if the connections has been established
		*/
		bool isStarted() const;

		/*
		Initiate the connection with the client
		*/
		bool start(int, struct sockaddr_in&);

		/*
		End the current client connection and closes all the sockets
		returns true if connection was properly closed
		*/
		bool endConnection();

		/*
		Returns true if the client handler can be endd
		*/
		bool canBeEnded() const;

		/*
		Returns the IP of the client
		*/
		string getIP() const;

		/*
		Returns the id of the client
		*/
		string getID() const;
};
#endif