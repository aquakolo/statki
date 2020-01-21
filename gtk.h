#include<stdbool.h>
void picturedel(int size,int k,int w,int h,GtkButton *button);
void on_mm_but1_clicked(GtkButton *button,GtkStack *menu);
void on_ng_back_clicked(GtkButton *button,GtkStack *menu);
void on_mm_but2_clicked(GtkButton *button, GtkWidget *rules);
void on_mm_but3_clicked(GtkButton *button, GtkWidget *about);
void on_ng_but1_clicked(GtkButton *button,GtkStack *menu);
void on_lm_back_clicked(GtkButton *button,GtkStack *menu);
void pictureadd(int size,int k,int w,int h,GtkWidget *board);
void add(int width, int height,int shipk, int shipn, int field[][10], int ship[], GtkWidget *shipchoice[][2], GtkWidget *board, int lship[], bool shipfree[]);
void rem(int x, GtkButton *button, bool shipfree[],int ship[], int field[][10], GtkWidget *shipchoice[][2]);
void shipch(GtkWidget *shipchoice[][2], GtkBuilder *builder);