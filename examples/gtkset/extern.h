/* Author: Daniel E. Shipton <dshipton@iastate.edu> */
#ifndef EXTERN_H
#define EXTERN_H

/***	extern.h
**** Variables shared to everyone for drawing shapes,
**** computing scores and what not.
***/
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
#define VERSION "0.1"
	
	extern int cardsleft;
	extern int playscore;
	extern int computscore;
	extern GdkDrawable *card_pixmap[27], *card_bkg;
	extern GtkWidget *window, *drawing_area, *playerscore;
	extern GtkWidget *computerscore, *cards_remain;
#endif
