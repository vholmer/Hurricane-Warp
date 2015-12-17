#ifndef SOCK_H
#define SOCK_H

#include <cstdint> 
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>

namespace Socket {
    
    //
    int SendInt(int i, int socket);

    int ReadInt(int* i, int socket);

    int SendString(char* string, int length, int sock);

    int ReadString(char* string, int length, int sock);
}

#endif