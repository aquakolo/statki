#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include<stdio.h>

GtkWidget *window1, *rules, *about, *board;
GtkStack *menu;
GtkBuilder *builder;

int level;
int ship[4]={2,3,2,1};
int lship[4]={0,2,5,7};
char pname[100]="Player";
int shipn=4;
int shipk=0;
int field[10][10]={0};

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
	//if(field[int(button->width)][int(button->height)]==0 && ship[shipn]!=0)add(shipn, shipk, int(button->width), int(botton->height));
	//else if(field[int(button->width)][int(button->height)]!=0)remove(field[int(button->width)][int(button->height)]);
}

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

	gtk_builder_connect_signals(builder, NULL);

	gtk_widget_show_all(window1);
	
	gtk_main();
	
	return 0;
}