#include"else.h"
#include<time.h>
#include<stdlib.h>
int level;
int mf[10][10];
shipclass shipss[9];
int sssize[9]={0,2,2,3,3,3,4,4,5};
int freeships[6]={0,0,2,3,2,1};
int live[9];
bool wrong(int x, int y, int size, bool dir){
	if(!(x < 11-size*dir))return true;
	if(!(y < 11-size*(dir^1)))return true;
	if(freeships[size]==0)return true;
	for(int c=0;c<size;c++){
		if(mf[y+c*(dir^1)][x+c*dir]!=0)return true;
	}
	return false;
}

void start(int _level){
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