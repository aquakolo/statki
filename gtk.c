#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include"gtk.h"
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