#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include<time.h>
#include <math.h>
#include <ctype.h>
#include"dict-header.h"
#include "dict-soundex.h"

trieNode *root = NULL;
char dict[] = "dict-main-million.db";
BTA *dictionary;
const gchar *engWord;
const gchar *vietWord;
int dsize = 256;
int rsize;
int check;
int scheck;
//gtk3
GtkWidget *window;
GtkBuilder *builder;
GtkWidget *frame;
// gtk3-pg1
GtkButton *button11, *button12, *button13;
GtkLabel *label12,*label14;
// gtk3-pg2
GtkEntry *entry21,*entry22;
GtkButton *button21;
GtkLabel *label23,*label24;
// gtk3-pg3
GtkEntry *entry31;
GtkButton *button3;
GtkButton *button31[10];
 //gtk3-pg3-stk1
 GtkLabel *label33,*label34;
 //gtk3-pg3-stk2
 GtkEntry *entry32;
 GtkLabel *label38;
 GtkButton *button32;
 //gtk3-pg3-stk3
 GtkButton *button33;
 GtkLabel *label42;
 
//window1
GtkWidget *window1;
GtkBuilder *builder1;
GtkButton *b11,*b12;

//window2
GtkWidget *window2;
GtkBuilder *builder2;
GtkButton *b21,*b22;

//window3
GtkWidget *window3;
GtkBuilder *builder3;
GtkButton *b32;

//START
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv); // init Gtk
    btinit();
	dictionary = dictOpen(dictionary, dict);
    //activate window from gtk3.glade
    builder = gtk_builder_new_from_file("gtk3.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //get widget
    //page1
    gtk_builder_connect_signals(builder, NULL);
    frame = GTK_WIDGET(gtk_builder_get_object(builder, "frame"));
    button11 = GTK_BUTTON(gtk_builder_get_object(builder, "button11"));
    button12 = GTK_BUTTON(gtk_builder_get_object(builder, "button12"));
    button13 = GTK_BUTTON(gtk_builder_get_object(builder, "button13"));
    label12 = GTK_LABEL(gtk_builder_get_object(builder, "label12"));
    label14 = GTK_LABEL(gtk_builder_get_object(builder, "label14"));
    //page2
    entry21 = GTK_ENTRY(gtk_builder_get_object(builder,"entry21"));
    entry22 = GTK_ENTRY(gtk_builder_get_object(builder,"entry22"));
    button21 = GTK_BUTTON(gtk_builder_get_object(builder, "button21"));
    label23 = GTK_LABEL(gtk_builder_get_object(builder, "label23"));
    label24 = GTK_LABEL(gtk_builder_get_object(builder, "label24"));
    //page3
    entry31 = GTK_ENTRY(gtk_builder_get_object(builder,"entry31"));
    button3 = GTK_BUTTON(gtk_builder_get_object(builder, "button3"));
    button31[0]=GTK_BUTTON(gtk_builder_get_object(builder,"button311"));
    button31[1]=GTK_BUTTON(gtk_builder_get_object(builder,"button312"));
    button31[2]=GTK_BUTTON(gtk_builder_get_object(builder,"button313"));
    button31[3]=GTK_BUTTON(gtk_builder_get_object(builder,"button314"));
    button31[4]=GTK_BUTTON(gtk_builder_get_object(builder,"button315"));
    button31[5]=GTK_BUTTON(gtk_builder_get_object(builder,"button316"));
    button31[6]=GTK_BUTTON(gtk_builder_get_object(builder,"button317"));
    button31[7]=GTK_BUTTON(gtk_builder_get_object(builder,"button318"));
    button31[8]=GTK_BUTTON(gtk_builder_get_object(builder,"button319"));
    button31[9]=GTK_BUTTON(gtk_builder_get_object(builder,"button310"));
     //page3-stk1
     label33 = GTK_LABEL(gtk_builder_get_object(builder, "label33"));
     label34 = GTK_LABEL(gtk_builder_get_object(builder, "label34"));
     //page3-stk2
     entry32 = GTK_ENTRY(gtk_builder_get_object(builder,"entry32"));
     button32 = GTK_BUTTON(gtk_builder_get_object(builder, "button32"));
     label38 = GTK_LABEL(gtk_builder_get_object(builder, "label38"));
     //page3-stk3
     button33 = GTK_BUTTON(gtk_builder_get_object(builder, "button33"));
     label42 = GTK_LABEL(gtk_builder_get_object(builder, "label42"));
    //RUN
    GdkColor color;
    color.red=0x8686;
    color.green=0xafaf;
    color.blue=0xc7c7;
    gtk_widget_modify_bg(frame,GTK_STATE_NORMAL,&color);
    gtk_widget_show(window);
    gtk_widget_hide(GTK_WIDGET(label12));
    gtk_widget_hide(GTK_WIDGET(label14));
    gtk_main();
    return EXIT_SUCCESS;
}
//Page1
// Clicked Exit Program
void on_button11_clicked(GtkButton *b){
    //ceate window 1
    builder1 = gtk_builder_new_from_file("window1.glade");
    window1 = GTK_WIDGET(gtk_builder_get_object(builder1, "window1"));
    gtk_builder_connect_signals(builder1, NULL);
    b11 = GTK_BUTTON(gtk_builder_get_object(builder1, "b11"));
    b12 = GTK_BUTTON(gtk_builder_get_object(builder1, "b12"));
    gtk_widget_show(window1);
}

void on_b11_clicked(GtkButton *b){
    dictDeleteAll(dictionary, dsize, &rsize);
    remove("dict-main-million.db");
    gtk_main_quit();
}

void on_b12_clicked(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window1));
}
// Clicked Download Dictionary
void on_button13_clicked(GtkButton *b){
    gtk_widget_hide(GTK_WIDGET(label14));
    check=readFile(dictionary,&root, dsize);
    if(check==0){
    builder3 = gtk_builder_new_from_file("window3.glade");
    window3 = GTK_WIDGET(gtk_builder_get_object(builder3, "window3"));
    gtk_builder_connect_signals(builder3, NULL);
    b32 = GTK_BUTTON(gtk_builder_get_object(builder3, "b32"));
    gtk_widget_show(window3);
    }
    else gtk_widget_show(GTK_WIDGET(label12));
}
void on_b32_clicked(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window3));
}
// Clicked Upload Dictionary
void on_button12_clicked(GtkButton *b){
    gtk_widget_hide(GTK_WIDGET(label12));
    dictPrint(dictionary, dsize, &rsize);
    gtk_widget_show(GTK_WIDGET(label14));
}

//Page2
void on_button21_clicked(GtkButton *b){
    char tmpe[256], tmpv[256];
    //Insert English word
    engWord=gtk_entry_get_text(entry21);
    //Insert Vietnamese word
    vietWord=gtk_entry_get_text(entry22);
    strcpy(tmpe,(char*)engWord);
    strcpy(tmpv,(char*)vietWord);
    check=dictInsert(dictionary,&root, dsize,tmpe,tmpv);
    if(check==1){
    gtk_label_set_text(GTK_LABEL(label24),tmpv);
    gtk_label_set_text(GTK_LABEL(label23),tmpe);
    } else {
    gtk_label_set_text(GTK_LABEL(label24),"");
    gtk_label_set_text(GTK_LABEL(label23),"Some things're wrong...");
    }
}
void on_entry21_backspace(){
    gtk_label_set_text(GTK_LABEL(label23),"");
    gtk_label_set_text(GTK_LABEL(label24),"");
}
void on_entry22_backspace(){
    gtk_label_set_text(GTK_LABEL(label23),"");
    gtk_label_set_text(GTK_LABEL(label24),"");
}
//Page3
void on_button311_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[0]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button312_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[1]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button313_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[2]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button314_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[3]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button315_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[4]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button316_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[5]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button317_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[6]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button318_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[7]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button319_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[8]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
void on_button310_clicked(GtkButton *b){
    engWord=gtk_button_get_label(button31[9]);
    gtk_entry_set_text(GTK_ENTRY(entry31),engWord);
}
//stk1
void on_entry31_activate(){
    char tmpe[256], tmpv[256];
    engWord=gtk_entry_get_text(entry31);
    strcpy(tmpe,(char*)engWord);
    char engword[256], vietword[256];
	// Check tu dien co dang trong hay khong
	btpos(dictionary, 1);
	if (btseln(dictionary, engword, vietword, dsize, &rsize) != 0)
	{
        scheck=0;
        gtk_label_set_text(GTK_LABEL(label33),"The dictionary is blank!");
    }
	else{
        btpos(dictionary, 1);
        if (btsel(dictionary, tmpe, tmpv, dsize, &rsize) == 0) // Tim trong tu dien
		{
			scheck=1;
            gtk_label_set_text(GTK_LABEL(label33),tmpe);
            gtk_label_set_text(GTK_LABEL(label34),tmpv);
        }
	    else
	    {   	// Tim nhung tu co lien quan bang soundex
		char dictWord[256];
		char a[256];
		strcpy(a, soundex(tmpe));
		int i = 0;
        data cache[256];
		while (btseln(dictionary, dictWord, vietword, dsize, &rsize) == 0)
		{	
			char b[256];
			strcpy(b, soundex(dictWord));
			if (strcmp(a, b) == 0 )
			{	
				strcpy(cache[i].completeText, dictWord);
				i++;
			}
			
		}
        int j;
		// Kiem tra mang du lieu "cacheStorage" lay tu soundex co rong hay khong
		if(i!=0) {
			for(j=0;j<i;j++){
                if(j>=10) {break;}
            gtk_button_set_label(button31[j],cache[j].completeText);
            }
		}else{
            gtk_label_set_text(GTK_LABEL(label33),"Cant find this word!");
        }
	}
    }
}

void on_clear(){
    gtk_entry_set_text(entry31,"");
    gtk_label_set_text(GTK_LABEL(label33),"");
    gtk_label_set_text(GTK_LABEL(label34),"");
    for(int i=0;i<10;i++)
    gtk_button_set_label(button31[i],"");
    gtk_label_set_text(GTK_LABEL(label42),"");
    gtk_label_set_text(GTK_LABEL(label38),"");
    scheck=0;
}
void on_backspace(){
    gtk_label_set_text(GTK_LABEL(label33),"");
    gtk_label_set_text(GTK_LABEL(label34),"");
    for(int i=0;i<10;i++)
    gtk_button_set_label(button31[i],"");
    gtk_label_set_text(GTK_LABEL(label42),"");
    gtk_label_set_text(GTK_LABEL(label38),"");
    scheck=0;
}
void on_entry31_move_cursor(){
    char tmpe[256];
    data array[256];
     engWord=gtk_entry_get_text(entry31);
     strcpy(tmpe,(char*)engWord);
     autocomplete(root,tmpe,array);
     if(strcmp(array[0].completeText,"") != 0){
        gtk_entry_set_text(entry31,array[0].completeText);
        int i;
        for(i=1;i<11;i++){
                if(strcmp(array[i].completeText,"") == 0 ) break;
                gtk_button_set_label(button31[i-1],array[i].completeText);
            }
     }
}
//stk2
void on_button32_clicked(GtkButton *b){
    char tmpe[256], tmpv[256];
     if(scheck!=1) gtk_label_set_text(GTK_LABEL(label38),"Cant find this word!");
    else{vietWord=gtk_entry_get_text(entry32);
    strcpy(tmpe,(char*)engWord);
    strcpy(tmpv,(char*)vietWord);
    dictUpdate(dictionary, dsize, &rsize,tmpe,tmpv);
    gtk_label_set_text(label38,"Update successfully!");
    gtk_label_set_text(GTK_LABEL(label33),"");
    gtk_label_set_text(GTK_LABEL(label34),"");}
}
//stk3
void on_button33_clicked(GtkButton *b){
    if(scheck!=1) gtk_label_set_text(GTK_LABEL(label42),"Cant find this word!");
    else{
    builder2 = gtk_builder_new_from_file("window2.glade");
    window2 = GTK_WIDGET(gtk_builder_get_object(builder2, "window2"));
    gtk_builder_connect_signals(builder2, NULL);
    b21 = GTK_BUTTON(gtk_builder_get_object(builder2, "b21"));
    b22 = GTK_BUTTON(gtk_builder_get_object(builder2, "b22"));
    gtk_widget_show(window2);
    }
}
void on_b21_clicked(GtkButton *b){
    char tmpe[256];
    strcpy(tmpe,(char*)engWord);
    lowercase(tmpe);
    dictDeleteNode(dictionary,dsize, &rsize,tmpe);
    deletestr(&root,tmpe);
    gtk_label_set_text(GTK_LABEL(label42),"Remove Successfully!");
    gtk_widget_destroy(GTK_WIDGET(window2));
    gtk_label_set_text(GTK_LABEL(label33),"");
    gtk_label_set_text(GTK_LABEL(label34),"");
}
void on_b22_clicked(GtkButton *b){
    gtk_widget_destroy(GTK_WIDGET(window2));
}