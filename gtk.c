#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include"gtk.h"
#include"else.h"
void on_mm_but1_clicked(GtkButton *button,GtkStack *menu){
	gtk_stack_set_visible_child_name(menu,"newgame");
}
void on_ng_back_clicked(GtkButton *button,GtkStack *menu){
	gtk_stack_set_visible_child_name(menu,"main");
}
void on_mm_but2_clicked(GtkButton *button, GtkWidget *rules){
	gtk_widget_show_all(rules);
}
void on_mm_but3_clicked(GtkButton *button, GtkWidget *about){
	gtk_widget_show_all(about);
}
void on_ng_but1_clicked(GtkButton *button,GtkStack *menu){
	gtk_stack_set_visible_child_name(menu,"level");
}
void on_lm_back_clicked(GtkButton *button,GtkStack *menu){
	gtk_stack_set_visible_child_name(menu,"newgame");
}
void pictureadd(int size,int k,int w,int h,GtkWidget *board){
	GtkButton *but=(GtkButton *)gtk_button_new();
	char name[]="statek0pozi.png";
	name[6]+=size;
	if(k==0){name[8]='i';name[9]='o';name[10]='n';}
	GtkWidget *image=gtk_image_new_from_file(name);
	gtk_button_set_image (but,image);size--;
	gtk_grid_attach((GtkGrid *)board,(GtkWidget *)but,w,h,1+size*k,1+size*(k^1));
}
void picturedel(int size,int k,int w,int h,GtkButton *button){
	gtk_widget_destroy((GtkWidget *)button);
}
void add(int width, int height,int shipk, int shipn, int field[][10], int ship[], GtkWidget *shipchoice[][2], GtkWidget *board, int lship[], bool shipfree[]){
	if(shipk==0){
		int p=find(lship,shipn, shipfree);
		for(int c=height;c<=height+shipn;c++){
			field[c][width]=p;
		}
	}
	else{
		int p=find(lship,shipn, shipfree);
		for(int c=width;c<=width+shipn;c++){
			field[height][c]=p;
		}
	}
	ship[shipn-1]--;
	char w[]="0"; w[0]+=ship[shipn-1];
	gtk_button_set_label((GtkButton *)shipchoice[shipn-1][0], w);
	gtk_button_set_label((GtkButton *)shipchoice[shipn-1][1], w);
	pictureadd(shipn+1, shipk,width, height, board);
}
void rem(int x, GtkButton *button, bool shipfree[],int ship[], int field[][10], GtkWidget *shipchoice[][2]){
	printf("rem\n");
	shipfree[x]=0;
	int s=0, possx, possy, possy2;
	for(int c=9;c>=0;c--){
		for(int d=9;d>=0;d--){
			if(field[c][d]==x){field[c][d]=0;possx=d;possy2=possy; possy=c;}
		}
	}
	if(x<2)s=2;
	else if(x<5)s=3;
	else if(x<7)s=4;
	else s=5;
	picturedel(s,possy2-possy,possx, possy, button);
	ship[s-2]++;
	char w[]="0"; w[0]+=ship[s-2];
	gtk_button_set_label((GtkButton *)(shipchoice[s-2][0]), w);
	gtk_button_set_label((GtkButton *)(shipchoice[s-2][1]), w);
}
void shipch(GtkWidget *shipchoice[][2], GtkBuilder *builder){
	shipchoice[0][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib2pi"));
	shipchoice[0][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib2po"));
	shipchoice[1][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib3pi"));
	shipchoice[1][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib3po"));
	shipchoice[2][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib4pi"));
	shipchoice[2][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib4po"));
	shipchoice[3][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib5pi"));
	shipchoice[3][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib5po"));
}