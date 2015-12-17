#ifndef SOCKET_H
#define SOCKET_H

#include "socket.hpp"

namespace Socket {

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

    int ReadInt(int *num, int socket)
    {
        int32_t ret;
        char *data = (char*)&ret;
        int left = sizeof(ret);
        int rc;

        while (left) {
            rc = read(socket, data + sizeof(ret) - left, left);
            if (rc < 0) return -1;
            left -= rc;
        }

        int answer = data[0];
        answer += data[1] << 8;
        answer += data[2] << 16;
        answer += data[3] << 24;

        *num =  ntohl(answer);
        return 0;
    }

    int SendString(char* str, int length, int socket) {
        
        int n = SendInt(length, socket);
        
        if(n != 0) {
    		return -1;
    	}
        std::cout << "In Send string" << std::endl;
        std::cout << "Sending: " << str << std::endl;

    	int left = length;
        int rc;
        while (left) {
            std::cout << "In loop" << std::endl;
            rc = write(socket, str + length - left, left);
            std::cout << "We're done here" << std::endl;
            if (rc < 0) return -1;
            left -= rc;
        }
        return 0;
    }

    int ReadString(char* str, int length, int socket) {
    	int left = length;
        int rc;
        std::cout << "IN Read string" << std::endl;
        while (left) {
            std::cout << "IN loop" << std::endl;
            rc = read(socket, str + length - left, left);
            std::cout << "yo" << std::endl;
            if (rc < 0)  {
                std::cout << "Something went realy wrong" << std::endl;
                return -1;
            }
            left -= rc;
        }
        std::cout << "We're read this string" << str << std::endl;
        return 0;
    }
}
#endif