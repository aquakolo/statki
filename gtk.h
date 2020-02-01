#include<stdbool.h>
#include<gtk/gtk.h>
#include<gtk/gtkx.h>
void on_10_toggled(GtkRadioButton *b);
void on_20_toggled(GtkRadioButton *b);
void on_30_toggled(GtkRadioButton *b);
void on_40_toggled(GtkRadioButton *b);
void on_11_toggled(GtkRadioButton *b);
void on_21_toggled(GtkRadioButton *b);
void on_31_toggled(GtkRadioButton *b);
void on_41_toggled(GtkRadioButton *b);
void on_fin_clicked();
void on_ng_ent1_changed(GtkEntry* entry);
void on_lm_easy_clicked();
void on_lm_nor_clicked();
void on_lm_cheat_clicked();
void picturedel(int size,int k,int w,int h,GtkButton *button);
void on_mm_but1_clicked();
void on_backtomenu_clicked();
void on_mm_but2_clicked();
void on_mm_but3_clicked();
void on_ng_but1_clicked();
void on_lm_back_clicked();
void pictureadd(int size,int k,int w,int h);
void add(int width, int height);
void rem(int x, GtkButton *button);
void shipch();
void on_space_clicked(GtkButton *button);
void gtk_on();
void set_boards();
void fill_boards();
void on_give_up_clicked();
void on_shoot_clicked(GtkButton *but);
void opturn();
bool lose();
void on_ng_but2_clicked();