#include "deck.h"

/***	Deck()
**** Deck just initializes all the cards with
**** all the different values they can have.
***/
Deck::Deck()
{
	int i =0;
	int j = 0;
	int k = 0;
	int l = 0;
	int x = 0;
	
	for(i=0; i<81; i++)
	{
		gone[i]=false;
	}
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				for(l=0;l<3;l++)
				{
					mycards[x]=Card(i, j, k, l);
					x++;
				}
			}
		}
	}
	cardsleft = x+1;
}

/***	Card Deal()
**** Picks a random number and checks to see
**** if the corresponding card has been used.
**** If it has it just keeps picking random
**** numbers till it finds one.
***/
Card Deck::Deal()
{
	//if(cardsleft==0)
	// endgame
	int cardnum;
	bool cond=true;
	srand48(time(NULL));
	while(cond)
	{
//		srand48(time(NULL));
		cardnum = lrand48()%81;
		if(!gone[cardnum])
		{
			cond=false;
			gone[cardnum]=true;
		}
	}
	return mycards[cardnum];
}

/***	void reset()
**** Resets the deck by setting all of gone
**** to true.
***/
void Deck::reset()
{
	int i =0;
	int j = 0;
	int k = 0;
	int l = 0;
	int x = 0;
	
	for(i=0; i<81; i++)
	{
		gone[i]=false;
	}
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			for(k=0;k<3;k++)
			{
				for(l=0;l<3;l++)
				{
					mycards[x]=Card(i, j, k, l);
					x++;
				}
			}
		}
	}
	cardsleft = x+1;
}

	
