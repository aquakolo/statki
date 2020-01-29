#include"else.h"
#include<stdlib.h>
#include<stdbool.h>

bool good2(int c,int d, int field[][10]){
	bool goodw=(d < 10);
	goodw&=(c < 10);
	goodw&=(field[c][d]!=0);
	return goodw;
}
bool good(int c,int d, int shipn, int shipk, int field[][10]){
	if(!(d < 10-shipn*shipk))return false;
	if(c >= 10-shipn*(shipk^1))return false;
	for(int i=0;i<=shipn;i++){
		if(field[c+i*(shipk^1)][d+i*shipk]!=0)return false;
	}
	return true;
}
int find(int lship[],int shipn, bool shipfree[]){
	int p=lship[shipn-1];
	int k=(shipn==5?9:lship[shipn]);
	for(;p<k;p++){
		if(shipfree[p]==0){shipfree[p]=1;return p;} 
	}
}

cell *new(int x, int y, cell *last, cell *next){
	cell *now=malloc(sizeof(cell));
	now->x=x;
	now->y=y;
	if(last!=NULL)last->next=now;
	now->last=last;
	if(next!=NULL)next->last=now;
	now->next=next;
	return now;
}

void e_remove(cell *now){
	if(now->last!=NULL)now->last->next=now->next;
	if(now->last!=NULL)now->next->last=now->last;
	free(now);
}

cell *e_find(cell *start,int n){
	if(n==0 || start==NULL)return start;
	return e_find(start->next, n-1);
}