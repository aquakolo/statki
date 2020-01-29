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

typedef struct f{
	struct f *next, *last;
	int x, y;
}cell;

cell *new(int x, int y, cell *last, cell *next);
void e_remove(cell *now);
cell *e_find(cell *start,int n);