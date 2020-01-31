#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PORT=8080;

int server_socket, client_socket[max_clients], new_sock, sd, sockn; 
int max_clients=30;

struct sockaddr_in serv_address;
int serv_addr_len;

fd_set readfds;
int max_sd, activity;
int valread;

char message[64];

void sockets_clear(){
	for(int c=0;c<max_clients;c++){   
		client_socket[c]=0;//free   
	}
}

int main(int argc, char *argv[]){
	if(argc>1)PORT=atoi(argv[1]);

	sockets_clear();

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket == 0){
		perror("socket failed"); 
		return 0;
	}

	serv_address.sin_family=AF_INET; 
	serv_address.sin_addr.s_addr=INADDR_ANY; 
	serv_address.sin_port=htons(PORT);
	serv_addr_len=sizeof(serv_address);

	if(bind(server_socket,(struct sockaddr *)&serv_address,serv_addr_len)<0){ 
		perror("bind failed"); 
		return 0; 
	}

	if(listen(server_socket, 3) < 0){ 
		perror("listen"); 
		return 0; 
	}

	while(true){
		FD_ZERO(&readfds);

		FD_SET(server_socket, &readfds);
		max_sd = server_socket;

		for(int c=0;c<max_clients;c++){
			if(client_socket[c]!=0) FD_SET(client_socket[c], &readfds);
			if(max_sd<client_socket[c])max_sd=client_socket[c];
		}

		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
		if((activity < 0) && (errno!=EINTR)){   
			printf("select error");   
		}

		if(FD_ISSET(server_socket, &readfds)){
			new_sock=accept(server_socket, (struct sockaddr *)&serv_address, (socklen_t*)&serv_addr_len);
			if(new_sock<0){
				perror("accept");
				return 0;
			}
			for(int c=0;c<max_clients;c++){
				if(client_socket[c]==0){
					client_socket[c]=new_sock;
					break;
				}
			}
		}
		if(room_started()){
			room1();
		}
		for(int c=0;c<max_clients;c++){
			if(notinroom(c)){
				sd = client_socket[c];
				if(FD_ISSET(sd, &readfds)){
					valread=read(cd, message, 64);
					if(valread==0){
						close(sd);
						client_socket[c]=0;
					}
					else{
						sockn=atoi(message);
						if(sockn==-1){
							send(list);
						}
						else if(sockn==-2){
								}
						else{
							addroom(sockn);
						}
					}
				}
			}
		}
	}
    return 0; 
} 