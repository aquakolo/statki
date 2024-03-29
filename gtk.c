#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include"gtk.h"
#include"bot.h"
#include"socket.h"

GtkWidget *window1, *board, *buttonres, *fin, *message, *give_up, *m_board, *o_board, *info, *refresh, *join;
GtkStack *menu;
GtkBuilder *builder;
GtkWidget *shipchoice[4][2];
GtkWidget *mboard[10][10], *oboard[10][10];
bool multi=0;
bool ot=0;
bool set=0;
int level;
int ship[4]={2,3,2,1};
int lship[4]={1,3,6,8};
char pname[100]="Player";
int shipn=4;
int shipk=1;
int howmanyships=8;
int hmships=8;
int field[10][10]={0};
int livep[9]={0,2,2,3,3,3,4,4,5};
bool shipfree[9];
shipclass ships[9];
int lp=26;
int port;
bool finish;
bool rp=0;
const int ay=7, m0=3, o0=19;

void on_fin_clicked(){
	gtk_stack_set_visible_child_name(menu,"boards_game");
	if(!set)set_boards();
	fill_boards();
	if(multi){
		send_ships(ships);
	}
	if(ot){
		while(gtk_events_pending()) gtk_main_iteration();
		gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Ruch przeciwnika.</span>");
		rp=1;
		opturn();
		rp=0;
		if(finish)return;
		gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Przeciwnik spudłował!\nTwój ruch.</span>");
	}
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
void on_ng_but2_clicked(){
	multi=1;
	gtk_stack_set_visible_child_name(menu,"login");
}
void on_lm_back_clicked(){
	gtk_stack_set_visible_child_name(menu,"newgame");
}
void on_give_up_clicked(){
	on_backtomenu_clicked();
}
void back_login(){
	if(socket_e())close_s();
	multi=0;
	gtk_stack_set_visible_child_name(menu,"newgame");
}


void set_boards(){
	board =GTK_WIDGET(gtk_builder_get_object(builder,"boards_game"));
	m_board =GTK_WIDGET(gtk_builder_get_object(builder,"m_board"));
	o_board =GTK_WIDGET(gtk_builder_get_object(builder,"o_board"));
	GtkWidget *text;
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">A</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)m_board,text,0,c+1,1,1);
	}
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">0</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)m_board,text,c+1,0,1,1);
	}
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">A</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)o_board,text,0,c+1,1,1);
	}
	for(int c=0;c<10;c++){
		char t[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 11\">0</span>";t[59]+=c;
		text=gtk_label_new(NULL);
		gtk_label_set_markup (GTK_LABEL(text), t);
		gtk_widget_show(text);
		gtk_grid_attach((GtkGrid *)o_board,text,c+1,0,1,1);
	}
	set=1;
}

void fill_boards(){
	gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Twój ruch.</span>");
	GtkWidget *see;
	for(int c=0;c<10;c++){
		for(int d=0;d<10;d++){
			see=mboard[c][d];
			if(see!=NULL)gtk_widget_destroy(see);
			if(field[c][d]==0){
				see=gtk_image_new_from_file("see.png");
				gtk_widget_show(see);
				gtk_grid_attach((GtkGrid *)m_board,see,d+1,c+1,1,1);
				mboard[c][d]=see;
			}
			else{
				int p=field[c][d];
				if(d>0 && field[c][d-1]==p && d<9 && field[c][d+1]==p)see=gtk_image_new_from_file("sl.png");
				else if(d<9 && field[c][d+1]==p)see=gtk_image_new_from_file("ll.png");
				else if(d>0 && field[c][d-1]==p)see=gtk_image_new_from_file("pl.png");
				else if(c>0 && field[c-1][d]==p && c<9 && field[c+1][d]==p)see=gtk_image_new_from_file("slo.png");
				else if(c<9 && field[c+1][d]==p)see=gtk_image_new_from_file("gl.png");
				else if(c>0 && field[c-1][d]==p)see=gtk_image_new_from_file("dl.png");
				gtk_widget_show(see);
				gtk_grid_attach((GtkGrid *)m_board,see,d+1,c+1,1,1);
				mboard[c][d]=see;
			}
		}
	}

	for(int i=0;i<=9;i++){
		for(int j=0;j<=9;j++){
			see=oboard[i][j];
			if(see!=NULL)gtk_widget_destroy(see);
			GtkWidget *but=gtk_button_new();
			GtkWidget *image=gtk_image_new_from_file("dot.png");
			gtk_button_set_image ((GtkButton *)but,image);
			g_signal_connect (G_OBJECT(but), "clicked", G_CALLBACK(on_shoot_clicked), NULL);
			gtk_widget_show(but);
			gtk_grid_attach((GtkGrid *)o_board,but,j+1,i+1,1,1);
			oboard[i][j]=but;
		}
	}
	int temp[9]={0,2,2,3,3,3,4,4,5};
	for(int c=0;c<9;c++)livep[c]=temp[c];
	hmships=8;
	lp=26;
	start_bot(level, field);
	finish=0;
}
void on_shoot_clicked(GtkButton *but){
	if(finish)return;
	if(rp)return;
	int c, d;bool ok=false;
	for(c=ay;c<ay+10;c++){
		for(d=o0;d<o0+10;d++){
			if((GtkWidget *)but==oboard[c-ay][d-o0]){
				ok=true;
				break;
			}
		}
		if(ok)break;
	}
	int result=(!multi?shoot(d-o0, c-ay):sends(d-o0, c-ay));
	gtk_widget_destroy((GtkWidget *)but);
	if(result<2){
		GtkWidget *image;
		if(result==0)image=gtk_image_new_from_file("see.png");
		if(result==1)image=gtk_image_new_from_file("hit.png");
		gtk_widget_show(image);
		gtk_grid_attach((GtkGrid *)o_board,image,d-o0+1,c-ay+1,1,1);
		oboard[c-ay][d-o0]=image;
		if(result==0)gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Pudło!\nRuch przeciwnika.</span>");
		if(result==1)gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Trafiony!\nTwój ruch.</span>");
		while(gtk_events_pending()) gtk_main_iteration();
		if(result==0){
			rp=1;
			opturn();
			rp=0;
			if(finish)return;
			gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Przeciwnik spudłował!\nTwój ruch.</span>");
		}
	}
	else{
		gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Trafiony, Zatopiony!\nTwój ruch.</span>");
		int x, y, size;
		int dir=result/1000;result-=dir*1000;
		size=result/100;result-=size*100;
		y=result/10;result-=y*10;
		x=result;
		GtkWidget *was;
		for(int c=0;c<size;c++){
			was=oboard[y+c*(dir^1)][x+c*dir];
			if(was!=NULL)gtk_widget_destroy(was);
		}
		char t[]="s0pod.png";t[1]+=size;if(dir==0){t[3]='i';}
		GtkWidget *image=gtk_image_new_from_file(t);
		gtk_widget_show(image);
		gtk_grid_attach((GtkGrid *)o_board, image, x+1, y+1, 1+(size-1)*dir, 1+(size-1)*(dir^1));
		oboard[y][x]=image;
		hmships--;
	}
	if(hmships==0){
		gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Wygrałeś!!!</span>");
		gtk_button_set_label((GtkButton *)give_up, "Koniec");
		finish=1;
	}
}

void opturn(){
	int opshoot,x,y,p;
	GtkWidget *image;
	do{
		while(gtk_events_pending()) gtk_main_iteration(); 
		opshoot=(!multi?turn():ans());
		x=opshoot%10;
		y=opshoot/10;
		p=field[y][x];
		if(p!=0){
			livep[p]--;
			lp--;
			if(livep[p]!=0){
				if(!multi)answer(x, y, 1);
				gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Zostałeś trafiony!\nRuch przeciwnika.</span>");
			}
			else{
				if(!multi)answer(ships[p].x, ships[p].y-'A', (int)(ships[p].dir)*10+ships[p].size);
				gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Zostałeś zniszczony!\nRuch przeciwnika.</span>");
			}
			if(x>0 && field[y][x-1]==p && x<9 && field[y][x+1]==p)image=gtk_image_new_from_file("sd.png");
			else if(x<9 && field[y][x+1]==p)image=gtk_image_new_from_file("ld.png");
			else if(x>0 && field[y][x-1]==p)image=gtk_image_new_from_file("pd.png");
			else if(y>0 && field[y-1][x]==p && y<9 && field[y+1][x]==p)image=gtk_image_new_from_file("sdo.png");
			else if(y<9 && field[y+1][x]==p)image=gtk_image_new_from_file("gd.png");
			else if(y>0 && field[y-1][x]==p)image=gtk_image_new_from_file("dd.png");
		}
		else{if(!multi)answer(x, y, 0);image=gtk_image_new_from_file("miss.png");}
		gtk_widget_show(image);
		if(mboard[y][x]!=NULL)gtk_widget_destroy(mboard[y][x]);
		gtk_grid_attach((GtkGrid *)m_board,image, x+1, y+1, 1, 1);
		mboard[y][x]=image;
	}while(p!=0 && !lose());
	if(lose()){
		gtk_label_set_markup((GtkLabel *)message, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 14\">Przegrałeś!!!</span>");
		gtk_button_set_label((GtkButton *)give_up, "Koniec");
		finish=1;
	}
}

bool lose(){
	if(lp==0)return true;
	return false;
}

void pictureadd(int size,int k,int w,int h){
	howmanyships--;
	if(k==0){
		GtkWidget *but;
		for(int c=h;c<h+size;c++){
			but=gtk_grid_get_child_at((GtkGrid *)board, w, c);
			if(but!=NULL)gtk_widget_destroy(but);
		}
	}
	else{
		GtkWidget *but;
		for(int c=w;c<w+size;c++){
			but=gtk_grid_get_child_at((GtkGrid *)board, c, h);
			if(but!=NULL)gtk_widget_destroy(but);
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
	if(x<=2)s=2;
	else if(x<=5)s=3;
	else if(x<=7)s=4;
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
	sprintf(pname,"%s",gtk_entry_get_text(entry));
}

void port_changed(GtkEntry* entry){
	char portt[8];
	sprintf(portt,"%s",gtk_entry_get_text(entry));
	port=atoi(portt);
}

void connect_clicked(){
	if(socket_e())close_s();
	if(setsocket(port)){
		send_name(pname);
		gtk_widget_show(info);
		gtk_widget_show(refresh);
		refresh_clicked();
	}
}
void refresh_clicked(){
	int s=slist();
	char buff[]="<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 13\">Ilość zajętych miejsc w pokoju: 0/2";
	buff[95]+=s;
	for(int c=0;c<s;c++){
		strcat(buff, "\n");
		strcat(buff, names());
	}
	strcat(buff, "</span>");
	gtk_label_set_markup((GtkLabel *)info, buff);
	if(s<2){
		gtk_widget_show(join);
	}
}

void join_clicked(){
	int ok=sendjoin();
	if(ok==0){refresh_clicked();return;}
	if(ok==1){
		ot=0;
		gtk_label_set_markup((GtkLabel *)info, "<span foreground=\"black\" font_desc=\"FreeSans Semi-Bold 13\">Czekanie na przeciwnika!</span>");
		while(gtk_events_pending()) gtk_main_iteration();
		wait();
	}
	else{ot=1;}
	gtk_stack_set_visible_child_name(menu,"board");
}

void on_lm_easy_clicked(){
	level=1;
	multi=0;
	gtk_stack_set_visible_child_name(menu,"board");
}
void on_lm_nor_clicked(){
	level=2;
	multi=0;
	gtk_stack_set_visible_child_name(menu,"board");
}
void on_lm_cheat_clicked(){
	level=3;
	multi=0;
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
	if(good(c, d, shipn, shipk, field) && ship[shipn-1]!=0){
		add(d, c);
	}else if(good2(c,d, field)){
		rem(field[c][d], button);
	}
}
void gtk_on(){
	gtk_init(NULL, NULL);
	builder=gtk_builder_new_from_file("client.glade");
	window1 = GTK_WIDGET(gtk_builder_get_object(builder,"window1"));	
	menu = GTK_STACK(gtk_builder_get_object(builder,"menu"));			
	fin = GTK_WIDGET(gtk_builder_get_object(builder,"fin"));			
	message = GTK_WIDGET(gtk_builder_get_object(builder,"message"));	
	give_up = GTK_WIDGET(gtk_builder_get_object(builder,"give_up"));
	info = GTK_WIDGET(gtk_builder_get_object(builder,"info"));
	refresh = GTK_WIDGET(gtk_builder_get_object(builder,"refresh"));
	join = GTK_WIDGET(gtk_builder_get_object(builder,"join"));
	
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
	
	shipch(shipchoice, builder);
	
	gtk_builder_connect_signals(builder, NULL);
	
	gtk_widget_show_all(window1);
	
	gtk_main();
}