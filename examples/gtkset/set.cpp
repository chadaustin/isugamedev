/* Author: Daniel E. Shipton <dshipton@iastate.edu> */
#include <gtk/gtk.h>
#include <gnome.h>
#include "card.h"
#include "table.h"
#include <iostream.h>
#include <gdk/gdkkeysyms.h>
#include <time.h>

#include "bean_e.xbm"
#include "bean_s.xbm"
#include "bean_f.xbm"
#include "blob_e.xbm"
#include "blob_s.xbm"
#include "blob_f.xbm"
#include "diamond_e.xbm"
#include "diamond_s.xbm"
#include "diamond_f.xbm"

#define SHAPE_W 90
#define SHAPE_H 30
#define SPACE_OUTER 15
#define SPACE_INNER 15
#define SPACE_INTER 10
#define CARD_W (SHAPE_W+2*SPACE_OUTER)
#define CARD_H (3*SHAPE_H+2*SPACE_INNER+2*SPACE_OUTER)
#define CARD_WS (CARD_W+SPACE_INTER)
#define CARD_HS (CARD_H+SPACE_INTER)
#define ARC_SIZE 15
#define SEL_W 3
#define PAD_3 0
#define PAD_2 ((2*SPACE_INNER+SHAPE_H)/3)
#define PAD_1 (SPACE_INNER+SHAPE_H)


#define VERSION "Set Game 0.1"

	GdkDrawable *card_pixmap[27], *card_bkg;
	GtkWidget *window, *drawing_area, *playerscore;
	GtkWidget *computerscore, *cards_remain;
	Table mytable;
	int cardsleft = 81;
	int playscore = 0;
	int computscore = 0;
	int pleasewait = 0;
	time_t waittime = (time_t)12;

static int expose_event(GtkWidget *wid, GdkEventExpose *ev) {
  mytable.numSelected();
  return TRUE;
}


static int myidle(gpointer data)
{
	static time_t lasttime=0;
	static time_t lastgot = 0;
	int computer_tries = 150;
	
	if(cardsleft<=0)
	{
		// sleep(5);
		return 1;
	}
	
	if(pleasewait==0)
	{
		pleasewait++;
		lasttime=time(NULL);
		// sleep(2);
		return 1;
	}
	
	if((mytable.numSel ==2 || mytable.numSel ==3))
	{
		// sleep(1);
		return 1;
	}
	
	if((lasttime!=0 && (time(NULL) - lasttime) < waittime) || (lastgot!=0 && (time(NULL) - lastgot) < waittime))
	{
		// sleep(2);
		return 1;
	}
	
	int i, j, k;
	cout << "computer searching....." << endl;
	for(int m =0; m<computer_tries; m++)
	{
		i=rand()%12;
		
		for(j=lrand48()%12;j==i;j=lrand48()%11);
			
		for(k=lrand48()%12;j==k || i==k; k=lrand48()%11);

		if(mytable.isaSet(mytable.mycards[i],mytable.mycards[j],mytable.mycards[k]))
		{
			cout << "Computer found one!... ";
			cout << i << "," << j << "," << k << endl;
			char remain[10];
			computscore++;
			sprintf(remain, "%d", computscore);
			gtk_label_set_text(GTK_LABEL(computerscore), remain);
			if(cardsleft!=0)
			{
				mytable.mycards[i]=mytable.mydeck.Deal();
				cardsleft--;
			}

			
			if(cardsleft!=0)
			{
				mytable.mycards[j]=mytable.mydeck.Deal();
				cardsleft--;
				}

			
			if(cardsleft!=0)
			{
				mytable.mycards[k]=mytable.mydeck.Deal();
				cardsleft--;
				}
			mytable.numSelected();
			mytable.makeSet();
			lastgot = time(NULL);
			return 1;
		}	

	}
	lasttime = time(NULL);
	cout << "computer didn't find one" << endl;
	return 1;
}

void newgame( GtkWidget *widget, gpointer   data )
{
    mytable.reset();
}

static int button_event(GtkWidget *wid, GdkEventButton *ev) {
  int cardx = (int)(ev->x - SPACE_INTER)/CARD_WS;
  int cardy = (int)(ev->y - SPACE_INTER)/CARD_HS;
	cout << cardx << " " << cardy << endl;
  if (ev->type != GDK_BUTTON_PRESS)
    return FALSE;
  if (3*cardx+cardy <= -1)
    return FALSE;
  if (ev->x < (cardx+1)*CARD_WS && ev->y < (cardy+1)*CARD_HS) {
    mytable.mycards[cardx+4*cardy].Select();
	mytable.numSelected();
  }
  return TRUE;
}

void main(int argc, char *argv[])
{
	gnome_init(VERSION, VERSION, argc, argv);

	/* Set up to draw from card class */
	GtkWidget *vbox, *vbox1, *vbox2, *vbox3;
	GtkWidget *tbar;
	GtkWidget *setbutton, *nosetbutton;
	GdkColor white, black, blue;
	/* Done setting up */

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Set Game");
	gtk_window_set_policy(GTK_WINDOW(window), FALSE, FALSE, TRUE);
	gtk_container_border_width(GTK_CONTAINER(window), 0);

	vbox= gtk_vbox_new(FALSE, 0);
	vbox1 = gtk_vbox_new(FALSE, 0);
	vbox2 = gtk_vbox_new(FALSE, 0);
	vbox3 = gtk_vbox_new(FALSE, 0);

	drawing_area = gtk_drawing_area_new();
  gtk_widget_set_events(drawing_area,
    GDK_EXPOSURE_MASK|GDK_BUTTON_PRESS_MASK);
  gtk_widget_set_events(window, GDK_KEY_PRESS_MASK);
  gtk_signal_connect(GTK_OBJECT(drawing_area), "expose_event",
    GTK_SIGNAL_FUNC(expose_event), 0);
  gtk_signal_connect(GTK_OBJECT(drawing_area), "button_press_event",
    GTK_SIGNAL_FUNC(button_event), 0);
	GnomeUIInfo toolbar[ ] = {
GNOMEUIINFO_ITEM_STOCK ("New Game", "Start new Game", newgame, GNOME_STOCK_PIXMAP_NEW),
GNOMEUIINFO_ITEM_STOCK ("High Scores", "Shows High scores", gtk_main_quit, GNOME_STOCK_PIXMAP_SCORES),
GNOMEUIINFO_ITEM_STOCK ("End Game", "Ends Current Game", gtk_main_quit, GNOME_STOCK_PIXMAP_STOP),
GNOMEUIINFO_ITEM_STOCK ("Exit", "Exit the application", gtk_main_quit, GNOME_STOCK_PIXMAP_EXIT),
GNOMEUIINFO_END
};
	tbar = gtk_toolbar_new(GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS);
	gnome_app_fill_toolbar(GTK_TOOLBAR(tbar), toolbar, gtk_accel_group_new());
	gtk_box_pack_start(GTK_BOX(vbox1), tbar, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), vbox1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), vbox2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), vbox3, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox2), drawing_area, TRUE, TRUE, 5);
	gtk_drawing_area_size(GTK_DRAWING_AREA(drawing_area), SPACE_INTER+CARD_WS*4, SPACE_INTER+CARD_HS*3);
	gtk_box_pack_start(GTK_BOX(vbox3), gtk_label_new("Player"), TRUE, TRUE, 1);
	playerscore = gtk_label_new("0");
	gtk_box_pack_start(GTK_BOX(vbox3), playerscore, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(vbox3), gtk_label_new("Computer"), TRUE, TRUE, 1);
	computerscore = gtk_label_new("0");
	gtk_box_pack_start(GTK_BOX(vbox3), computerscore, TRUE, TRUE, 1);
	gtk_box_pack_start(GTK_BOX(vbox3), gtk_label_new("Cards Remaining"), TRUE, TRUE, 1);
	cards_remain = gtk_label_new("81");
	gtk_box_pack_start(GTK_BOX(vbox3), cards_remain, TRUE, TRUE, 1);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show_all(window);

	gtk_idle_add( myidle, NULL);


/************************ Start Deck Setup *************************/
unsigned char *pixmap_data[] = {
    bean_e_bits,
    bean_s_bits,
    bean_f_bits,
    blob_e_bits,
    blob_s_bits,
    blob_f_bits,
    diamond_e_bits,
    diamond_s_bits,
    diamond_f_bits
  };
  int i, j;
  GdkWindow *wn = window->window;
  GdkColor col[4];
  GdkColormap *cmap = gdk_window_get_colormap(wn);
  GdkGC *gc;
  GtkStyle *style = gtk_widget_get_style(window);
  col[0].red = 54000; col[0].green = col[0].blue = 0;
  col[1].green = 40000; col[1].red = col[1].blue = 0;
  col[2].red = col[2].blue = 32000; col[2].green = 0;
  gdk_color_white(cmap, &white);
  gdk_color_black(cmap, &black);
  blue.red = blue.green = 0; blue.blue = 48000;
  gdk_color_alloc(cmap, &blue);
  for (i=0; i<3; i++)
    gdk_color_alloc(cmap, &col[i]);
  for (i=0; i<9; i++)
    for (j=0; j<3; j++)
      card_pixmap[i*3+j] = gdk_pixmap_create_from_data(wn, (gchar*) pixmap_data[i],
        SHAPE_W, SHAPE_H, -1, &col[j], &white);
  /* free colors? !! */

  gc = gdk_gc_new(wn);

  /*** cards in normal state ***/
  card_bkg = gdk_pixmap_new(wn, CARD_W, CARD_H, -1);
  /* clear the card */
  gdk_gc_set_foreground(gc, &style->bg[GTK_STATE_NORMAL]);
  gdk_draw_rectangle(card_bkg, gc, 1, 0, 0, CARD_W, CARD_H);
  /* draw corner arcs */
  gdk_gc_set_foreground(gc, &white);
  gdk_draw_arc(card_bkg, gc, 1, 0,                 0,
    2*ARC_SIZE, 2*ARC_SIZE, 90*64,  90*64);
  gdk_draw_arc(card_bkg, gc, 1, CARD_W-2*ARC_SIZE, 0,
    2*ARC_SIZE, 2*ARC_SIZE, 0,      90*64);
  gdk_draw_arc(card_bkg, gc, 1, 0,                 CARD_H-2*ARC_SIZE,
    2*ARC_SIZE, 2*ARC_SIZE, 180*64, 90*64);
  gdk_draw_arc(card_bkg, gc, 1, CARD_W-2*ARC_SIZE,
    CARD_H-2*ARC_SIZE, 2*ARC_SIZE, 2*ARC_SIZE, 270*64, 90*64);
  /* draw the rest */
  gdk_draw_rectangle(card_bkg, gc, 1, ARC_SIZE, 0, CARD_W-2*ARC_SIZE, CARD_H);
  gdk_draw_rectangle(card_bkg, gc, 1, 0, ARC_SIZE, CARD_W, CARD_H-2*ARC_SIZE);
	  gdk_gc_destroy(gc);

/************************ End Deck Setup *************************/



  /* done setting up for once 
	  to draw
	  wn = drawing_area->window;
	  gc-gdk_gc_new(wn);
	  card1.draw();
	  .............draw();
	  gdk_gc_destroy();
	  
	  
	  Card(int colr, int shp, int num, int shdng);
  */
 

		mytable.Draw();
	gtk_main();
	return 0;
}	
