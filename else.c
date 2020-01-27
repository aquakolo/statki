#include"else.h"
#include<stdbool.h>

bool good2(int c,int d, int field[][10]){
	bool goodw=(d < 10);
	goodw&=(c < 10);
	goodw&=(field[c][d]!=0);
	return goodw;
}
bool good(int c,int d, int shipn, int shipk, int field[][10]){
	bool goodw=(d < 10-shipn*shipk);
	goodw&=(c < 10-shipn*(shipk^1));
	goodw&=(field[c][d]==0);
	return goodw;
}
int find(int lship[],int shipn, bool shipfree[]){
	int p=lship[shipn-1];
	int k=(shipn==5?9:lship[shipn]);
	for(;p<k;p++){
		if(shipfree[p]==0){shipfree[p]=1;return p;}
	}
}