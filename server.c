#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int PORT=8080;

typedef struct{
	int x;
	int y;
	int size;
	bool dir;
}ship;

typedef struct{
	ship shipn[9];
	int field[10][10];
	int size[9];
	int ils;
}board;

int server_socket, client_socket[max_clients], new_sock, sd, sockn; 
int max_clients=30;

struct sockaddr_in serv_address;
int serv_addr_len;

fd_set readfds;
int max_sd, activity;
int valread;

int inroom[2]={-1};

char message[64];
char *name[30];

bool room_started=0;

board *p[2];

int turn=0;

void move(int player){
	int opponent=player^1;
	if(FD_ISSET(client_socket[inroom[player]], &readfds)){
		char move[3];
		read(client_socket[inroom[player]], move, 3);
		int x=move[0]-'0';
		int y=move[1]-'0';
		send(client_socket[inroom[opponent]], move, 3, 0);
		int w=p[opponent].field[y][x]
		if(w==0){
			send(client_socket[inroom[player]], "0000\n", 5, 0);
		}
		else if(w!=0 && p[opponent].size[w]>1){
			p[opponent].size[p[opponent].field[y][x]]--;
			send(client_socket[inroom[player]], "1000\n", 5, 0);
		}
		else{
			p[opponent].size[w]--;
			char odp[5]="0000\n";
			odp[0]+=p[opponent].shipn[w].x;
			odp[1]+=p[opponent].shipn[w].y;
			odp[2]+=p[opponent].shipn[w].size;
			odp[3]+=p[opponent].shipn[w].dir;
			p[opponent].ils--;
			send(client_socket[inroom[player]], odp, 5, 0);
		}
		turn=opponent;
	}
	if(p[opponent].ils==0){
		free(p[0]);
		free(p[1]);
		inroom[0]=-1;
		inroom[1]=-1;
		room_started=0;
		turn=0;
	}

}
void addtoroom(int who){
	if(inroom[0]==-1)inroom[0]=who;
	else{
		inroom[1]=who;
		room_started=1;
	}
}
void room1(){
	if(p[0]==NULL && FD_ISSET(client_socket[inroom[0]], &readfds)){
		p[0]=malloc(board);
		char shipo[33];
		read(client_socket[inroom[0]], shipo, 33);
		for(int c=1;c<=8;c++){
			p[0].shipn[c].x=shipo[(c-1)*4+0]-'0';
			p[0].shipn[c].y=shipo[(c-1)*4+1]-'0';
			p[0].shipn[c].size=shipo[(c-1)*4+2]-'0';
			p[0].shipn[c].dir=shipo[(c-1)*4+3]-'0';
			p[0].size[c]=shipo[(c-1)*4+2]-'0';
			for(int d=0;d<p[0].shipn[c].size;d++){
				field[p[0].shipn[c].y+d*(p[0].shipn[c].dir^1)][p[0].shipn[c].x+d*p[0].shipn[c].dir]=c;
			}
		}
		p[0].ils=8;
	}
	if(p[1]==NULL && FD_ISSET(client_socket[inroom[1]], &readfds)){
		p[1]=malloc(board);
		char shipo[33];
		read(client_socket[inroom[1]], shipo, 33, 0);
		for(int c=1;c<=8;c++){	
			p[1].shipn[c].x=shipo[(c-1)*4+0]-'0';
			p[1].shipn[c].y=shipo[(c-1)*4+1]-'0';
			p[1].shipn[c].size=shipo[(c-1)*4+2]-'0';
			p[1].shipn[c].dir=shipo[(c-1)*4+3]-'0';
			p[1].size[c]=shipo[(c-1)*4+2]-'0';
			for(int d=0;d<p[1].shipn[c].size;d++){
				field[p[1].shipn[c].y+d*(p[1].shipn[c].dir^1)][p[1].shipn[c].x+d*p[1].shipn[c].dir]=c;
			}
		}
		p[1].ils=8;
	}
	if(p[0]!=NULL && p[1]!=NULL){
		move(turn);
	}
}

bool notinroom(int who){
	if(inroom[0]==who)return false;
	if(inroom[1]==who)return false;
	return true;
}

void send_list(int who){
	int w=(room_started?2:0);
	if(w==0 inroom[0]!=-1)w=1;
	char mess[2]="0\n";mess[0]+=w;
	send(client_socket[who],mess, 2, 0);
	for(int c=0;c<w;c++){
		send(client_socket[who], name[inroom[c]], strlen(name[inroom[c]]), 0);
	}
}

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
					char namec[20];
					read(client_socket[c], namec, 20);
					name[c]=namec;
					break;
				}
			}
		}
		if(room_started){
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
						if(sockn==0){
							send_list(c);
						}
						if(sockn==1 && !room_started){
							addtoroom(c);
						}
						
					}
				}
			}
		}
	}
    return 0; 
} 