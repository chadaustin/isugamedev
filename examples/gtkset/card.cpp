/* Author: Daniel E. Shipton <dshipton@iastate.edu> */
#include "card.h"

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

/***	Card()
**** Makes a new card with default shape, color, etc...
***/
Card::Card()
{
	color=0;
	shape=0;
	number=1;
	shading=0;
	selected=FALSE;
}

/***	Card(int colr, int shp, int num, int shding)
**** Makes a new unselected card with specified attributes.
***/
Card::Card(int colr, int shp, int num, int shdng)
{
	color=colr;
	shape=shp;
	number=num;
	shading=shdng;
	selected=FALSE;
}

/***	getColor()
**** Returns the color of the card.
***/
int Card::getColor()
{
	return color;
}

/***	getShape()
**** Returns the shape of the card.
***/
int Card::getShape()
{
        return shape;
}

/***	getNumber()
**** Returns the number of shapes on the card.
***/
int Card::getNumber()
{
        return number;
}

/***	getShading()
**** Returns the shading of the card.
***/
int Card::getShading()
{
        return shading;
}

/***	Select()
**** Set the selected attribute to true.
***/
void Card::Select()
{
	if(selected)
	{selected = FALSE;}
	else
	{selected = TRUE;}
}

/***	bool isSelected()
**** Returns if it is selected or not.
***/
bool Card::isSelected()
{
	return selected;
}
	
/***	void draw(......)
**** This function has the card draw itself to an area
**** that the program passes it. It's coordinates are
**** specified by bx and by.
***/
void Card::draw(GdkDrawable *drawable, GdkDrawable *card_pixmap[27], GdkDrawable *card_bkg, GdkGC *gc, int bx, int by)
{
int basex = SPACE_INTER+CARD_WS*bx;
  int basey = SPACE_INTER+CARD_HS*by;
  int basex2 = basex + SPACE_OUTER;
  int basey2 = basey + SPACE_OUTER;
  gdk_draw_pixmap(drawable, gc, card_bkg, 0, 0,
    SPACE_INTER+CARD_WS*bx, SPACE_INTER+CARD_HS*by, CARD_W, CARD_H);
  switch (number) {
    case 0:
      gdk_draw_pixmap(drawable, gc,
        card_pixmap[shape*9 + shading*3 + color],
        0, 0, basex2, basey2+PAD_1, SHAPE_W, SHAPE_H);
      break;
    case 1:
      gdk_draw_pixmap(drawable, gc,
        card_pixmap[shape*9 + shading*3 + color],
        0, 0, basex2, basey2+PAD_2, SHAPE_W, SHAPE_H);
      gdk_draw_pixmap(drawable, gc,
        card_pixmap[shape*9 + shading*3 + color],
        0, 0, basex2, basey2+2*PAD_2+SHAPE_H, SHAPE_W, SHAPE_H);
      break;
    case 2:
      gdk_draw_pixmap(drawable, gc,
        card_pixmap[shape*9 + shading*3 + color],
        0, 0, basex2, basey2, SHAPE_W, SHAPE_H);
      gdk_draw_pixmap(drawable, gc,
        card_pixmap[shape*9 + shading*3 + color],
        0, 0, basex2, basey2+PAD_1, SHAPE_W, SHAPE_H);
      gdk_draw_pixmap(drawable, gc,
        card_pixmap[shape*9 + shading*3 + color],
        0, 0, basex2, basey2+2*PAD_1, SHAPE_W, SHAPE_H);
      break;
    default: ;
  }
  if (selected) {
    gdk_draw_rectangle(drawable, gc, 1, basex, basey, CARD_W, SEL_W);
    gdk_draw_rectangle(drawable, gc, 1, basex, basey, SEL_W, CARD_H);
    gdk_draw_rectangle(drawable, gc, 1, basex+CARD_W-SEL_W, basey,
      SEL_W, CARD_H);
    gdk_draw_rectangle(drawable, gc, 1, basex, basey+CARD_H-SEL_W,
      CARD_W, SEL_W);
  }

}
