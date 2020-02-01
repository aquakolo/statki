#include<stdbool.h>
bool good(int c,int d, int shipn, int shipk, int field[][10]);
bool good2(int c,int d, int field[][10]);
int find(int lship[],int shipn, bool shipfree[]);

typedef struct{
	char y;
	int x;
	int size;
	bool dir;
}shipclass;
