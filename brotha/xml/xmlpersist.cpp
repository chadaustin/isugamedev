#include <iostream>
#include <string>
#include <vector>


#include "xmlpersist.h"
#include "brothadata.h"

void main(){
  Bdata b;
  Gang g("emigia");
  Player p("ama","kuriyama");
  Car c("tercel");
  Mod m("breaks",4);
  Cartype ct("tercel");
  b.addGang(g);
  b.addCarType(ct);
  c.addMod(m);
  p.addCar(c);
  g.addPlayer(p);
  b.xMLify(cout);
}