/* Author: Daniel E. Shipton <dshipton@iastate.edu> */
#include "table.h"

/***	Table()
**** Sets up the table class by drawing 12 cards
**** from its deck. Need to call Draw() to 
**** display the cards on the screen.
***/
Table::Table()
{
	for(int i=0; i<12; i++)
	{
		mycards[i] = mydeck.Deal();
		cardsleft--;
		}
	makeSet();
}

/***	void makeSet()
**** Makes sure that out of the 12 cards on the
**** table there is a set.  If not it discards
**** top-left card for another(want that random).
***/
void Table::makeSet()
{
	int i =0;
	int j = 0;
	int k = 0;
	bool isOne=false;
	while(!isOne && cardsleft !=0)
	{
		for(i=0;i<12;i++)
		{
			for(j=0;j<12;j++)
			{
				for(k=0;k<12;k++)
				{
					if(!((i==j) || (i==k) || (j==k)))
					{		
						if(isaSet(mycards[i],mycards[j],mycards[k]))
							{isOne=true;}
						}
					}
				}
			}
		if(!isOne)
		{
			mycards[lrand48()%12]=mydeck.Deal();
			cardsleft--;
		}
	}
	return;
}

/***	void numSelected()
**** This counts how many are selected on the
**** the table and if 2 are selected shuts off
**** the computer. If 3 are selected it checks
**** for a set and corrects the score. It also
**** calls Draw after completion.
***/
void Table::numSelected()
{
	int x=0;
	int cn1, cn2, cn3;
	char remain[3];
	Card c1, c2, c3;
	int i=0;
	for(i=0; i<12; i++)
	{
		if(mycards[i].isSelected())
		{x++;}
	}
	numSel = x;
	if(x==3)
	{
		i=0;
		while(!mycards[i].isSelected())
		{i++;}
		c1 = mycards[i];
		cn1 = i;
		i++;
		while(!mycards[i].isSelected())
		{i++;}
		c2= mycards[i];
		cn2 = i;
		i++;
		while(!mycards[i].isSelected())
		{i++;}
		c3 = mycards[i];
		cn3 = i;
		if(!isaSet(c1, c2, c3))
		{ 
			playscore--;
			sprintf(remain, "%d", playscore);
			gtk_label_set_text(GTK_LABEL(playerscore), remain);
			for(i=0; i<12; i++)
			{
				if(mycards[i].isSelected())
				{ mycards[i].Select();}
			}
			numSel=0;
		}
		else
		{
			playscore++;
			sprintf(remain, "%d", playscore);
			gtk_label_set_text(GTK_LABEL(playerscore), remain);
			if(cardsleft!=0)
			{mycards[cn1]=mydeck.Deal();
				cardsleft--;}
			else
			{mycards[cn1].Select();}
			
			if(cardsleft!=0)
			{mycards[cn2]=mydeck.Deal();
				cardsleft--;}
			else
			{mycards[cn2].Select();}
			
			if(cardsleft!=0)
			{mycards[cn3]=mydeck.Deal();
				cardsleft--;}
			else
			{mycards[cn3].Select();}
			numSel = 0;
		}
	}
	sprintf(remain, "%d", cardsleft);
	gtk_label_set_text(GTK_LABEL(cards_remain), remain);
	// if(x==2)
	// turn computer off
	Draw();
	return;
}

/***	void reset()
**** Resets the table to start a new game.
***/
void Table::reset()
{
	mydeck.reset();
	for(int i=0; i<12; i++)
	{mycards[i] = mydeck.Deal();}
	makeSet();
	Draw();
}

/***	bool isaSet(Card card1, Card card2, Card card3)
**** Takes 3 cards as an argument and checks to see if it
**** is a set.  numSelected, makeSet as well as the computer player
**** use this function to check if there is a set.
***/
bool Table::isaSet(Card card1, Card card2, Card card3)
{
	if(!(card1.getNumber() == card2.getNumber() && card2.getNumber() == card3.getNumber()) &&
		!(card1.getNumber() != card2.getNumber() && card2.getNumber() != card3.getNumber() && card1.getNumber() != card3.getNumber()))
	{return false;}
	if(!(card1.getShape() == card2.getShape() && card2.getShape() == card3.getShape()) &&
		!(card1.getShape() != card2.getShape() && card2.getShape() != card3.getShape() && card1.getShape() != card3.getShape()))
	{return false;}
		if(!(card1.getColor() == card2.getColor() && card2.getColor() == card3.getColor()) &&
		!(card1.getColor() != card2.getColor() && card2.getColor() != card3.getColor() && card1.getColor() != card3.getColor()))
	{return false;}
		if(!(card1.getShading() == card2.getShading() && card2.getShading() == card3.getShading()) &&
		!(card1.getShading() != card2.getShading() && card2.getShading() != card3.getShading() && card1.getShading() != card3.getShading()))
	{return false;}
	
	return true;
}

/***	void Draw()
**** Uses extern.h to get the neccessary gdk
**** information to tell each card to draw itself.
***/
void Table::Draw()
{
	for(int i =0; i<12; i++)
	{
	  mycards[i].draw(wn(), card_pixmap, card_bkg, gc(), i%4, i/4);
	}
	 gdk_gc_destroy(gc());
	char remain[3];
	sprintf(remain, "%d", cardsleft);
	gtk_label_set_text(GTK_LABEL(cards_remain), remain);
	return;
}
