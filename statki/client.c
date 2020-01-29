#include<gtk/gtk.h>
#include<gtk/gtkx.h>
#include<stdio.h>
#include<stdbool.h>
#include "else.h"
#include "gtk.h"


int main(int argc, char *argv[]){
	if(argc>=2){
		if(argv[1]=="-t"){/*text_on();*/}
	}
	else 
		gtk_on();
	return 0;
}