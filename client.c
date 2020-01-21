#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include<stdio.h>

GtkWidget *window1, *window2, *window3;
GtkStack *menu;
GtkBuilder *builder;
char pname[100]="Player";

void on_mm_but1_clicked(){
	gtk_stack_set_visible_child_name(menu,"newgame");
}
void on_mm_but2_clicked(){
	window2 =GTK_WIDGET(gtk_builder_get_object(builder,"window2"));
	gtk_widget_show_all(window2);
}
void on_mm_but3_clicked(){
	window3 =GTK_WIDGET(gtk_builder_get_object(builder,"window3"));
	gtk_widget_show_all(window3);
}
void on_ng_ent1_changed(GtkEntry* entry){
	sprintf(pname,"entry=%s",gtk_entry_get_text(entry));
}


int main(int argc, char *argv[]){

	gtk_init(&argc,&argv);
	builder=gtk_builder_new_from_file("client.glade");
	
	window1 = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
	menu = GTK_STACK(gtk_builder_get_object(builder,"menu"));
	g_signal_connect (G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_builder_connect_signals(builder, NULL);

	gtk_widget_show_all(window1);
	
	gtk_main();
	
	return 0;
}