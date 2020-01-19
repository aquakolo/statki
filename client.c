#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include<glade/glade.h>

GtkWidget *window, *mainmenu, *mm_lab1, *mm_but1, *mm_but2, *mm_but3, *rules, *rul_lab1;
GtkBuilder *builder;


void on_mm_but2_clicked(GtkWidget* widget, gpointer user_data){
	gtk_widget_hide(mainmenu);
	gtk_widget_show(rules);
}


int main(int argc, char *argv[]){

	gtk_init(&argc,&argv);
	builder=gtk_builder_new_from_file("client.glade");
	
	window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
	
	g_signal_connect (G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_builder_connect_signals(builder, NULL);

	mainmenu=GTK_WIDGET(gtk_builder_get_object(builder,"mainmenu"));
	mm_lab1	=GTK_WIDGET(gtk_builder_get_object(builder,"mm_lab1"));
	mm_but1 =GTK_WIDGET(gtk_builder_get_object(builder,"mm_but1"));
	mm_but2 =GTK_WIDGET(gtk_builder_get_object(builder,"mm_but2"));
	mm_but3 =GTK_WIDGET(gtk_builder_get_object(builder,"mm_but3"));
	rules 	=GTK_WIDGET(gtk_builder_get_object(builder,"rules"));
	rul_lab1=GTK_WIDGET(gtk_builder_get_object(builder,"rul_lab1"));


	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}