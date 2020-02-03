#include"bot.h"
#include"else.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>

int level;
int mf[10][10];
shipclass shipss[9];
int sssize[9]={0,2,2,3,3,3,4,4,5};
int live[9];
int ip=100;
int start[100][2];
int dfs[100][2];
int moves[26][2];
int board[10][10];
int sdfs=0;
bool ts[10][10]={false};
int osst=0;

bool wrong(int x, int y, int size, bool dir){
	if(!(x < 11-size*dir))return true;
	if(!(y < 11-size*(dir^1)))return true;
	for(int c=0;c<size;c++){
		if(mf[y+c*(dir^1)][x+c*dir]!=0)return true;
	}
	return false;
}

void start_bot(int _level, int _board[][10]){
	srand(clock());ip=100;
	sdfs=0;
	for(int c=0;c<10;c++){for(int d=0;d<10;d++){mf[c][d]=0;ts[c][d]=false;}}
	level=_level;
	for(int c=8;c>=1;c--){
		int x, y, size=sssize[c];
		bool dir;
		do{
			x=rand()%10;
			y=rand()%10;
			dir=rand()%2;
		}while(wrong(x,y,size,dir));
		for(int d=0;d<size;d++){
			mf[y+d*(dir^1)][x+d*dir]=c;
		}
		shipss[c].y='A'+y;
		shipss[c].x=x;
		shipss[c].size=size;

		shipss[c].dir=dir;
		live[c]=size;
	}
	if(level<3){
		for(int c=0;c<100;c++){
			start[c][0]=c%10;
			start[c][1]=c/10;
		}
	}
	if(level==3){
		int ost=0;
		for(int c=0;c<=9;c++){
			for(int d=0;d<=9;d++){
				if(_board[c][d]!=0){moves[ost][0]=d, moves[ost][1]=c;ost++;}
			}
		}
		osst=0;
	}
}

int shoot(int x, int y){
	if(mf[y][x]==0)return 0;
	else if(live[mf[y][x]]==1){
		live[mf[y][x]]--;
		int r=shipss[mf[y][x]].dir*1000;
		r+=shipss[mf[y][x]].size*100;
		r+=(shipss[mf[y][x]].y-'A')*10;
		r+=shipss[mf[y][x]].x;
		return r;
	}
	else{
		live[mf[y][x]]--;
		return 1;
	}
}

int turn(){
	sleep(0.5);
	if(level==1){
		int s=rand()%ip, temp, y, x;
		ip--;
		temp=start[s][0];
		start[s][0]=start[ip][0];
		start[ip][0]=temp;
		temp=start[s][1];
		start[s][1]=start[ip][1];
		start[ip][1]=temp;
		y=start[ip][1];
		x=start[ip][0];
		return y*10+x;
	}
	if(level==2){
		int x, y;
		if(sdfs==0){
			int s, temp;
			do{
				s=rand()%ip;
				ip--;
				temp=start[s][0];
				start[s][0]=start[ip][0];
				start[ip][0]=temp;
				temp=start[s][1];
				start[s][1]=start[ip][1];
				start[ip][1]=temp;
				y=start[ip][1];
				x=start[ip][0];
			}while(board[y][x]!=0);
			return y*10+x;
		}
		else{
			y=dfs[sdfs-1][1];
			x=dfs[sdfs-1][0];
			sdfs--;
			return y*10+x;
		}
	}
	if(level==3){
		osst++;
		return moves[osst-1][0]+10*moves[osst-1][1];
	}
	return 0;
}

void answer(int x, int y, int ans){
	if(ans==0)board[y][x]=-1;
	else if(ans==1)board[y][x]=1;
	else{
		int dir=ans/10;
		int size=ans%10;
		for(int c=0;c<size;c++){
			board[y+c*(dir^1)][x+c*dir]=2;
		}
	}
	if(level==2 && ans>0){
		if(x>0 && board[y][x-1]==0 && !ts[y][x-1]){
			dfs[sdfs][0]=x-1;
			dfs[sdfs][1]=y;
			ts[y][x-1]=true;
			sdfs++;
		}
		if(y>0 && board[y-1][x]==0 && !ts[y-1][x]){
			dfs[sdfs][0]=x;
			dfs[sdfs][1]=y-1;
			ts[y-1][x]=true;
			sdfs++;
		}
		if(x<9 && board[y][x+1]==0 && !ts[y][x+1]){
			dfs[sdfs][0]=x+1;
			dfs[sdfs][1]=y;
			ts[y][x+1]=true;
			sdfs++;
		}
		if(y<9 && board[y+1][x]==0 && !ts[y+1][x]){
			dfs[sdfs][0]=x;
			dfs[sdfs][1]=y+1;
			ts[y+1][x]=true;
			sdfs++;
		}
	}
}