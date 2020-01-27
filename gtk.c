#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include"gtk.h"
#include"else.h"

GtkWidget *window1, *board, *buttonres, *fin;
GtkStack *menu;
GtkBuilder *builder;
GtkWidget *shipchoice[4][2];

typedef struct{
	char y;
	int x;
	int size;
	bool dir;
}shipclass;


int level;
int ship[4]={2,3,2,1};
int lship[4]={1,3,6,8};
char pname[100]="Player";
int shipn=4;
int shipk=1;
int howmanyships=8;
int field[10][10]={0};
bool shipfree[9];
shipclass ships[9];
const int ay=7, m0=3, o0=17;

void on_fin_clicked(){
	gtk_stack_set_visible_child_name(menu,"boards_game");
	set_boards();
	fill_boards();
}
void on_mm_but1_clicked(){
	gtk_stack_set_visible_child_name(menu,"newgame");
}
void on_backtomenu_clicked(){
	gtk_stack_set_visible_child_name(menu,"main");
}
void on_mm_but2_clicked(){
	gtk_stack_set_visible_child_name(menu,"rules");
}
void on_mm_but3_clicked(){
	gtk_stack_set_visible_child_name(menu,"about");
}
void on_ng_but1_clicked(){
	gtk_stack_set_visible_child_name(menu,"level");
}
void on_lm_back_clicked(){
	gtk_stack_set_visible_child_name(menu,"newgame");
}
void on_give_up_clicked(){
	howmanyships=8;
	for(int c=0;c<10;c++)for(int d=0;d<10;d++)field[c][d]=0;
	for(int c=0;c<9;c++)shipfree[c]=0;
	ship[0]=2;ship[1]=3;ship[2]=2;ship[3]=1;
	shipn=4; shipk=1;
	on_backtomenu_clicked();
}

void set_boards(){
	board =GTK_WIDGET(gtk_builder_get_object(builder,"boards_game"));
	GtkWidget *text;
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">A</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)board,text,m0-1,ay+c,1,1);
	}
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">0</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)board,text,m0+c,ay-1,1,1);
	}
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">A</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)board,text,o0-1,ay+c,1,1);
	}
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">0</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)board,text,o0+c,ay-1,1,1);
	}
}

void fill_boards(){
	GtkWidget *see;
	char name[]="see.png";
	for(int c=0;c<10;c++){
		for(int d=0;d<10;d++){
			if(field[c][d]==0){
				see=gtk_image_new_from_file(name);
				gtk_widget_show(see);
				gtk_grid_attach((GtkGrid *)board,see,m0+d,ay+c,1,1);
			}
		}
	}
	GtkWidget *ship;
	char name2[]="statek0pozi.png";
	for(int c=1;c<=8;c++){
		name2[6]='0'+ships[c].size;
		if(ships[c].dir==0){name2[8]='i';name2[9]='o';name2[10]='n';}
		ship=gtk_image_new_from_file(name2);
		gtk_widget_show(ship);
		gtk_grid_attach((GtkGrid *)board,ship,m0+ships[c].x,ay+ships[c].y-'A',1+(ships[c].size-1)*ships[c].dir,1+(ships[c].size-1)*(ships[c].dir^1));
	}
}

void pictureadd(int size,int k,int w,int h){
	howmanyships--;
	if(k==0){
		GtkWidget *but;
		for(int c=h;c<h+size;c++){
			but=gtk_grid_get_child_at((GtkGrid *)board, w, c);
			gtk_widget_destroy(but);
		}
	}
	else{
		GtkWidget *but;
		for(int c=w;c<w+size;c++){
			but=gtk_grid_get_child_at((GtkGrid *)board, c, h);
			gtk_widget_destroy(but);
		}
	}
	GtkWidget *but=gtk_button_new();
	char name[]="statek0pozi.png";
	name[6]+=size;
	if(k==0){name[8]='i';name[9]='o';name[10]='n';}
	GtkWidget *image=gtk_image_new_from_file(name);
	gtk_button_set_image ((GtkButton *)but,image);size--;
	g_signal_connect (G_OBJECT(but), "clicked", G_CALLBACK(on_space_clicked), NULL);
	gtk_grid_attach((GtkGrid *)board,but,w,h,1+size*k,1+size*(k^1));
	gtk_widget_show(but);
	if(howmanyships==0){gtk_widget_show(fin);}
}
void picturedel(int size,int k,int w,int h,GtkButton *button){
	if(howmanyships==0){gtk_widget_hide(fin);}
	howmanyships++;
	gtk_widget_destroy((GtkWidget *)button);
	if(k==0){
		for(int c=h;c<h+size;c++){
			GtkWidget *but;
			char t[2]={c+'A',w+'0'};
			but=gtk_button_new();
			g_signal_connect (G_OBJECT(but), "clicked", G_CALLBACK(on_space_clicked), NULL);
			gtk_button_set_label((GtkButton *)but,t);
			gtk_widget_show(but);
			gtk_grid_attach((GtkGrid *)board,(GtkWidget *)but,w,c,1,1);
		}
	}
	else{
		for(int c=w;c<w+size;c++){
			GtkWidget *but;
			char t[2]={h+'A',c+'0'};
			but=gtk_button_new();
			g_signal_connect (G_OBJECT(but), "clicked", G_CALLBACK(on_space_clicked), NULL);
			gtk_button_set_label((GtkButton *)but,t);
			gtk_widget_show(but);
			gtk_grid_attach((GtkGrid *)board,(GtkWidget *)but,c,h,1,1);
		}
	}
}
void add(int width, int height){
	int p;
	if(shipk==0){
		p=find(lship,shipn, shipfree);
		for(int c=height;c<=height+shipn;c++){
			field[c][width]=p;
		}
	}
	else{
		p=find(lship,shipn, shipfree);
		for(int c=width;c<=width+shipn;c++){
			field[height][c]=p;
		}
	}
	ships[p].y='A'+height;ships[p].x=width;ships[p].size=shipn+1;ships[p].dir=shipk;
	ship[shipn-1]--;
	char w[]="0"; w[0]+=ship[shipn-1];
	gtk_button_set_label((GtkButton *)shipchoice[shipn-1][0], w);
	gtk_button_set_label((GtkButton *)shipchoice[shipn-1][1], w);
	pictureadd(shipn+1, shipk,width, height);
}
void rem(int x, GtkButton *button){
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
	picturedel(s,(possy2-possy)^1,possx, possy, button);
	ship[s-2]++;
	char w[]="0"; w[0]+=ship[s-2];
	gtk_button_set_label((GtkButton *)(shipchoice[s-2][0]), w);
	gtk_button_set_label((GtkButton *)(shipchoice[s-2][1]), w);
}
void shipch(){
	shipchoice[0][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib2pi"));
	shipchoice[0][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib2po"));
	shipchoice[1][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib3pi"));
	shipchoice[1][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib3po"));
	shipchoice[2][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib4pi"));
	shipchoice[2][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib4po"));
	shipchoice[3][0]=GTK_WIDGET(gtk_builder_get_object(builder,"shib5pi"));
	shipchoice[3][1]=GTK_WIDGET(gtk_builder_get_object(builder,"shib5po"));
}

void on_ng_ent1_changed(GtkEntry* entry){
	sprintf(pname,"entry=%s",gtk_entry_get_text(entry));
}
void on_lm_easy_clicked(){
	level=1;
	gtk_stack_set_visible_child_name(menu,"board");
}
void on_lm_nor_clicked(){
	level=2;
	gtk_stack_set_visible_child_name(menu,"board");
}
void on_lm_cheat_clicked(){
	level=3;
	gtk_stack_set_visible_child_name(menu,"board");
}

void on_10_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=1, shipk=0;}}
void on_20_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=2, shipk=0;}}
void on_30_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=3, shipk=0;}}
void on_40_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=4, shipk=0;}}
void on_11_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=1, shipk=1;}}
void on_21_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=2, shipk=1;}}
void on_31_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=3, shipk=1;}}
void on_41_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=4, shipk=1;}}


void on_space_clicked(GtkButton *button){
	int c, d;bool ok=0;
	for(c=0;c<10;c++){
		for(d=0;d<10;d++){
			if(button==(GtkButton *)gtk_grid_get_child_at((GtkGrid *)board, d, c)){ok=1;break;}
		}
		if(ok)break;
	}
	if(good(c, d, shipn, shipk, field) && ship[shipn-1]!=0)
		add(d, c);
	else if(good2(c,d, field))
		rem(field[c][d], button);
}
void gtk_on(){
	gtk_init(NULL, NULL);
	builder=gtk_builder_new_from_file("client.glade");
	
	window1 = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
	menu = GTK_STACK(gtk_builder_get_object(builder,"menu"));
	fin = GTK_WIDGET(gtk_builder_get_object(builder,"fin"));
	g_signal_connect (G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	board =GTK_WIDGET(gtk_builder_get_object(builder,"board"));
	for(char i='A';i<='J';i++){
		for(char j='0';j<='9';j++){
			char t[3]={i,j,'\0'};
			GtkWidget *but=gtk_button_new();
			g_signal_connect (G_OBJECT(but), "clicked", G_CALLBACK(on_space_clicked), NULL);
			gtk_button_set_label((GtkButton *)but,t);
			gtk_grid_attach((GtkGrid *)board,(GtkWidget *)but,j-'0',i-'A',1,1);
		}
	}
	g_signal_connect (G_OBJECT(buttonres), "clicked", G_CALLBACK(on_space_clicked), NULL);
	shipch(shipchoice, builder);

	gtk_builder_connect_signals(builder, NULL);

	gtk_widget_show_all(window1);
	
	gtk_main();
}