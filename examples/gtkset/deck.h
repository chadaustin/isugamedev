/* Author: Daniel E. Shipton <dshipton@iastate.edu> */
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>
#include "card.h"
#include <time.h>
#ifndef DECK_H
#define DECK_H

class Deck {

	public:
	
		/***	Deck()
		**** Deck just initializes all the cards with
		**** all the different values they can have.
		***/
		Deck();
	
		/***	Card Deal()
		**** Picks a random number and checks to see
		**** if the corresponding card has been used.
		**** If it has it just keeps picking random
		**** numbers till it finds one.
		***/
		Card Deal();
		
		/***	void reset()
		**** Resets the deck by setting all of gone
		**** to true.
		***/
		void reset();
		
	private:
	Card mycards[81];
	bool gone[81];
	int cardsleft;
};
#endif
