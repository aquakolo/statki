#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h> 

#include "else.h"

int server_socket;
struct sockaddr_in server_address;

bool setsocket(int PORT){
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket < 0){ 
        perror("\n Socket creation error \n");
        return 0;
    } 

    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(PORT);
    server_address.sin_addr.s_addr=INADDR_ANY;

    if(connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){ 
        perror("\nConnection Failed \n"); 
        return 0; 
    }
    return 1;
}

int sends(int x, int y){
	char mess[]="00\0";mess[1]+=x;mess[0]+=y;
	send(server_socket,mess,3,0);
    int res=ans();
    return res;
}

int ans(){
	char answ[5];
	read(server_socket,answ,5);
	int res=answ[0]-'0'+(answ[1]-'0')*10+(answ[2]-'0')*100+(answ[3]-'0')*1000;//x, y, size, dir
}


void close_s(){
	close(server_socket);
}
