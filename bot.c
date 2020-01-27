#include"else.h"
#include<time.h>
#include<lib.h>
#include
int level;
int mf[10][10];
shipclass shipss[9];
int freeships[6]={0,0,2,3,2,1};
int live[9];
bool wrong(int x, int y, int size, bool dir){
	if(freeships[size]==0)return true;
	for(int c=0;c<size;c++){
		if(mf[y+c*(dir^1)][x+c*dir]!=0)return true;
	}
	return false;
}

void start(int _level){
	srand(clock());
	level=_level;
	for(int c=1;c<=8;c++){
		int x, y, size;
		bool dir;
		do{
			x=rand()%10;
			y=rand()%10;
			size=rand()%4+2;
			dir=rand%2;
		}while(wrong(x,y,size,dir));
		for(int d=0;d<size;d++){
			mf[y+d*(dir^1)][x+d*dir]=c;
		}
		freeships[size]--;
		shipss[c]={'A'+y,x,size,dir};
		live[c]=size;
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