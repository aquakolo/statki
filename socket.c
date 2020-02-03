#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "socket.h"
#include <unistd.h>

char a[100];
int server_socket;
struct sockaddr_in server_address;
bool socket_is=0;

bool setsocket(int PORT){
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket < 0){ 
        printf("\n Socket creation error \n");
        return 0;
    } 

    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(PORT);
    server_address.sin_addr.s_addr=INADDR_ANY;

    if(connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){ 
        printf("\nConnection Failed \n"); 
        return 0; 
    }
    socket_is=1;
    return 1;
}

void send_name(char *name){
    char tosend[strlen(name)+1];
    strcpy(tosend, name);
    strcat(tosend, "\0");
    send(server_socket, tosend, strlen(name)+1, 0);
}

void send_ships(shipclass *ships){
    char tosend[33]="00000000000000000000000000000000\0";
    for(int c=0;c<8;c++){
        tosend[0+c*4]+=ships[c+1].x;
        tosend[1+c*4]+=ships[c+1].y-'A';
        tosend[2+c*4]+=ships[c+1].size;
        tosend[3+c*4]+=ships[c+1].dir;
    }
    send(server_socket, tosend, 33, 0);
}

bool socket_e(){
    return socket_is;
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
    return res;
}

void close_s(){
    socket_is=0;
	close(server_socket);
}

int slist(){
    send(server_socket, "0\0", 2, 0);
    char aa[2];
    read(server_socket, aa, 2);
    return atoi(aa);
}
char *names(){
    int valread=read(server_socket, a, 100);
    a[valread]='\0';
    return a;
}
int sendjoin(){
    send(server_socket, "1\0", 2, 0);
    char ans[2];
    read(server_socket, ans, 2);
    return ans[0]-'0';
}
void wait(){
    char ans[2];
    read(server_socket, ans, 2);
}