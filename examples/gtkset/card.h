/* Author: Daniel E. Shipton <dshipton@iastate.edu> */
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <iostream>
#ifndef CARD_H
#define CARD_H

class Card
{

      public:
	
	/***	Card()
	**** Makes a new card with default shape, color, etc...
	***/
	Card ();
	
	/***	Card(int colr, int shp, int num, int shding)
	**** Makes a new unselected card with specified attributes.
	***/
	Card (int colr, int shp, int num, int shdng);
	
	/***	void draw(......)
	**** This function has the card draw itself to an area
	**** that the program passes it. It's coordinates are
	**** specified by bx and by.
	***/
	void draw (GdkDrawable * drawable, GdkDrawable * pixmap[27],
		   GdkDrawable * card_bkg, GdkGC * gc, int bx, int by);
		   
	/***	getColor()
	**** Returns the color of the card.
	***/
	int getColor ();
	
	/***	getShape()
	**** Returns the shape of the card.
	***/
	int getShape ();
	
	/***	getNumber()
	**** Returns the number of shapes on the card.
	***/
	int getNumber ();
	
	/***	getShading()
	**** Returns the shading of the card.
	***/
	int getShading ();
	
	/***	Select()
	**** Set the selected attribute to true.
	***/
	void Select ();
	
	/***	bool isSelected()
	**** Returns if it is selected or not.
	***/
	bool isSelected ();

      private:
	int color, shape, number, shading;
	bool selected;
};
#endif
