#include"else.h"
#include<time.h>
#include<stdlib.h>
int level;
int mf[10][10];
shipclass shipss[9];
int sssize[9]={0,2,2,3,3,3,4,4,5};
int freeships[6]={0,0,2,3,2,1};
int live[9];
int ip=100;
cell *start;
cell *bfs=NULL;
cell *moves;
int board[10][10];
int sbfs=0;

bool wrong(int x, int y, int size, bool dir){
	if(!(x < 11-size*dir))return true;
	if(!(y < 11-size*(dir^1)))return true;
	if(freeships[size]==0)return true;
	for(int c=0;c<size;c++){
		if(mf[y+c*(dir^1)][x+c*dir]!=0)return true;
	}
	return false;
}

void start_bot(int _level, int _board[][10]){
	srand(clock());
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
		freeships[size]--;
		shipss[c].y='A'+y;
		shipss[c].x=x;
		shipss[c].size=size;

		shipss[c].dir=dir;
		live[c]=size;
	}
	if(level<3){
		cell *last=start=new(-1, -1, NULL, NULL);
		for(int c=0;c<100;c++){
			last=new(c%10, c/10, last, NULL);
		}
	}
	if(level==3){
		for(int c=9;c>=0;c--){
			for(int d=9;d>=0;d--){
				if(_board[c][d]!=0)moves=new(d, c, NULL,moves);
			}
		}
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
	if(level==1){
		cell *r=e_find(start, rand()%ip+1);
		if(r==NULL)r=start->next;
		int x=r->x, y=r->y;
		e_remove(r);
		ip--;
		return y*10+x;
	}
	if(level==2){
		if(bfs==NULL){
			int x, y;
			cell *r;
			do{
				r=e_find(start, rand()%ip+1);
				if(r==NULL)r=start->next;
				x=r->x; y=r->y;
				e_remove(r);
				ip--;
			}while(board[y][x]!=0);
			return y*10+x;
		}
		else{
			cell *r=bfs;
			int x=r->x, y=r->y;
			bfs=bfs->next;
			e_remove(r);
			sbfs--;
			return y*10+x;
		}
	}
	if(level==3){
		cell *r=moves;
		int x=r->x, y=r->y;
		moves=moves->next;
		e_remove(r);
		return y*10+x;
	}
}

void answer(int x, int y, int ans){
	if(ans==0)board[y][x]=-1;
	else if(ans==1)board[y][x]=1;
	else{
		bool dir=ans/10;
		int size=ans%10;
		for(int c=0;c<size;c++){
			board[y+c*(dir^1)][x+c*dir]=2;
		}
	}
	if(level==2 && ans>0){
		if(x>0 && board[y][x-1]==0){
			if(bfs==NULL)bfs=new(x-1, y, NULL, NULL);
			else new(x-1, y, e_find(bfs, sbfs-1), NULL);
			sbfs++;
		}
		if(y>0 && board[y-1][x]==0){
			if(bfs==NULL)bfs=new(x, y-1, NULL, NULL);
			else new(x, y-1, e_find(bfs, sbfs-1), NULL);
			sbfs++;
		}
		if(x<9 && board[y][x+1]==0){
			if(bfs==NULL)bfs=new(x+1, y, NULL, NULL);
			else new(x+1, y, e_find(bfs, sbfs-1), NULL);
			sbfs++;
		}
		if(y<9 && board[y+1][x]==0){
			if(bfs==NULL)bfs=new(x, y+1, NULL, NULL);
			else new(x, y+1, e_find(bfs, sbfs-1), NULL);
			sbfs++;
		}
	}
}