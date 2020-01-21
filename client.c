#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include<stdio.h>
#include<stdbool.h>
#include "else.h"
#include "gtk.h"

GtkWidget *window1, *rules, *about, *board;
GtkStack *menu;
GtkBuilder *builder;
GtkWidget *shipchoice[4][2];

int level;
int ship[4]={2,3,2,1};
int lship[4]={1,3,6,8};
char pname[100]="Player";
int shipn=4;
int shipk=0;
int field[10][10]={0};
bool shipfree[9];

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
void on_space_clicked(GtkButton *button){
	int c, d;bool ok=0;
	for(c=0;c<10;c++){
		for(d=0;d<10;d++){
			if(button==(GtkButton *)gtk_grid_get_child_at((GtkGrid *)board, d, c)){ok=1;break;}
		}
		if(ok)break;
	}
	if(good(c, d, shipn, shipk, field) && ship[shipn-1]!=0)
		add(d, c, shipk, shipn, field, ship, shipchoice, board, lship, shipfree);
	else if(good2(c,d, field))
		rem(field[c][d], button, shipfree,ship, field, shipchoice);
}
void on_10_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=1, shipk=0;}}
void on_20_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=2, shipk=0;}}
void on_30_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=3, shipk=0;}}
void on_40_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=4, shipk=0;}}
void on_11_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=1, shipk=1;}}
void on_21_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=2, shipk=1;}}
void on_31_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=3, shipk=1;}}
void on_41_toggled(GtkRadioButton *b){if(gtk_toggle_button_get_active((GtkToggleButton *)b)){shipn=4, shipk=1;}}

int main(int argc, char *argv[]){

	gtk_init(&argc,&argv);
	builder=gtk_builder_new_from_file("client.glade");
	
	window1 = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
	menu = GTK_STACK(gtk_builder_get_object(builder,"menu"));
	g_signal_connect (G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	rules =GTK_WIDGET(gtk_builder_get_object(builder,"rules"));
	about =GTK_WIDGET(gtk_builder_get_object(builder,"about"));
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
	shipch(shipchoice, builder);

	gtk_builder_connect_signals(builder, NULL);

	gtk_widget_show_all(window1);
	
	gtk_main();
	
	return 0;
}