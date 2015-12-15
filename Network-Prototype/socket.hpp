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
    
    int SendInt(int, int);

    int ReadInt(int*, int);

    int SendString(char*, int length, int sock);

    int ReadString(char*, int length, int sock);
}

#endif