#include<gtk/gtk.h>
#include<gtk/gtkx.h>

GtkWidget *window1, *window2, *mainmenu, *mm_lab0, *mm_but1, *mm_but2, *mm_but3, *rules, *rul_lab0, *rul_lab1, *rul_lab2, *rul_lab3;
GtkBuilder *builder;


void on_mm_but2_clicked(GtkWidget* widget, gpointer user_data){
	gtk_widget_show_all(window2);
}


int main(int argc, char *argv[]){

	gtk_init(&argc,&argv);
	builder=gtk_builder_new_from_file("client.glade");
	
	window1 = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));
	window2 = GTK_WIDGET(gtk_builder_get_object(builder,"window2"));

	g_signal_connect (G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect (G_OBJECT(window2), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_builder_connect_signals(builder, NULL);

	mainmenu=GTK_WIDGET(gtk_builder_get_object(builder,"mainmenu"));
	mm_lab0	=GTK_WIDGET(gtk_builder_get_object(builder,"mm_lab0"));
	mm_but1 =GTK_WIDGET(gtk_builder_get_object(builder,"mm_but1"));
	mm_but2 =GTK_WIDGET(gtk_builder_get_object(builder,"mm_but2"));
	mm_but3 =GTK_WIDGET(gtk_builder_get_object(builder,"mm_but3"));
	rules 	=GTK_WIDGET(gtk_builder_get_object(builder,"rules"));
	rul_lab0=GTK_WIDGET(gtk_builder_get_object(builder,"rul_lab0"));
	rul_lab1=GTK_WIDGET(gtk_builder_get_object(builder,"rul_lab1"));
	rul_lab2=GTK_WIDGET(gtk_builder_get_object(builder,"rul_lab2"));


	gtk_widget_show_all(window1);
	
	gtk_main();
	
	return 0;
}