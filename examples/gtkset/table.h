/* Author: Daniel E. Shipton <dshipton@iastate.edu> */
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdio.h>
//#include <iostream>
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "extern.h"
#ifndef TABLE_H
#define TABLE_H

class Table {

	public:
	
		/***	Table()
		**** Sets up the table class by drawing 12 cards
		**** from its deck. Need to call Draw() to 
		**** display the cards on the screen.
		***/
		Table();
		
		/***	void makeSet()
		**** Makes sure that out of the 12 cards on the
		**** table there is a set.  If not it discards
		**** top-left card for another(want that random).
		***/
		void makeSet();
	
		/***	void numSelected()
		**** This counts how many are selected on the
		**** the table and if 2 are selected shuts off
		**** the computer. If 3 are selected it checks
		**** for a set and corrects the score. It also
		**** calls Draw after completion.
		***/
		void numSelected();
		
		/***	void reset()
		**** Resets the table to start a new game.
		***/
		void reset();
		
		/***	void Draw()
		**** Uses extern.h to get the neccessary gdk
		**** information to tell each card to draw itself.
		***/
		void Draw();
		
		/***	bool isaSet(Card card1, Card card2, Card card3)
		**** Takes 3 cards as an argument and checks to see if it
		**** is a set.  numSelected, makeSet as well as the computer player
		**** use this function to check if there is a set.
		***/
		bool isaSet(Card card1, Card card2, Card card3);
		
		Card mycards[12];
		GdkWindow *wn(){return drawing_area->window;}
		GdkGC *gc() {return gdk_gc_new(wn());}
		int numSel;
		Deck mydeck;

};
#endif
