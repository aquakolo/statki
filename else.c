#include"else.h"
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
	return 0;
}
