#ifndef XMLP_H
#define XMLP_H

#include <iostream>
#include <string>
#include "brothadata.h"



namespace dataxml{
	Bdata b;

	fillWithFakeData(Bdata* b){
		  Gang* g = new Gang("emigia");
          Player* p = new Player("ama","kuriyama");
          Car* c = new Car("tercel");
          Mod* m = new Mod("breaks",4);
          Cartype* ct = new Cartype("tercel");
          b->addGang(g);
          b->addCarType(ct);
          c->addMod(m);
          p->addCar(c);
          g->addPlayer(p);
	}

	Bdata load(std::string filename){
		fillWithFakeData(&b);
		return b;
	}
}

#endif
