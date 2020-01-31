#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h>
#include "else.h"

int socket;
struct sockaddr_in server;

bool setsocet(){
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){ 
        printf("\n Socket creation error \n");
        return 0;
    } 
}