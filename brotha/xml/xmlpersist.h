#ifndef XMLP_H
#define XMLP_H

#include <iostream>
#include <string>
#include <xmlpp/xmlpp.h>
#include "brothadata.h"


namespace dataxml {
   Bdata b;

   Bdata load(std::string filename) {
      //fillWithFakeData(&b);
      xmlpp::XMLContextPtr ctx( new xmlpp::XMLContext );
      xmlpp::XMLDocument doc( ctx );
      doc.load_file( filename );
      xmlpp::xmlnodeptr rootp = doc.getChild ("wbdata");
      xmlpp::xmlnodelist cursor = rootp->getChildren("gang");
      xmlpp::XMLNodeListIterator it = cursor.begin();

      while (it != cursor.end()) {
         xmlpp::XMLAttributes& attr = (*it)->get_attrmap();
         Gang* g = new Gang(attr.get("name"));
         xmlpp::xmlnodeptr info = (*it)->getChild("info");
         g->setInfo( info->get_cdata());
         b.addGang(g);
         xmlpp::xmlnodelist cursor2 = (*it)->getChildren("player");
         xmlpp::XMLNodeListIterator it2 = cursor2.begin();

         while (it2 != cursor2.end()) {
            //xmlpp::XMLAttributes& attr2 = (*it2)->get_attrmap();
            //Player* p = new Player(attr2.get("name"), attr2.get("password"));
            attr = (*it2)->get_attrmap();
            Player* p = new Player(attr.get("name"), attr.get("password"));
            g->addPlayer(p);
            xmlpp::xmlnodelist cursor3 = (*it2)->getChildren("car");
            xmlpp::XMLNodeListIterator it3 = cursor3.begin();

            while (it3 != cursor3.end()) {
               attr = (*it3)->get_attrmap();
               Car* c = new Car(attr.get("cartype"));
               p->addCar(c);
               xmlpp::xmlnodelist cursor4 = (*it3)->getChildren("mod");
               xmlpp::XMLNodeListIterator it4 = cursor4.begin();

               while (it4 != cursor4.end()) {
                  attr = (*it4)->get_attrmap();
                  Mod* m = new Mod(attr.get("name"),atoi(attr.get("level").c_str()));
                  c->addMod(m);
                  it4++;
               }
               it3++;
            }

            xmlpp::xmlnodelist cursorStat = (*it2)->getChildren("stat");
            xmlpp::XMLNodeListIterator itStat = cursorStat.begin();

            while (itStat != cursorStat.end()) {
               attr = (*itStat)->get_attrmap();
               Stat* s = new Stat(attr.get("name"),attr.get("value"));
               p->addStat(s);
               itStat++;
            }
            it2++;
         }

         it++;
         xmlpp::xmlnodelist types = rootp->getChildren("cartype");
         xmlpp::XMLNodeListIterator itTypes = types.begin();

         while (itTypes != types.end()) {
            xmlpp::XMLAttributes& attr = (*itTypes)->get_attrmap();
            Cartype* c = new Cartype(attr.get("name"),attr.get("model"));
            b.addCarType(c);
            itTypes++;
         }
      }
      return b;
   }

   fillWithFakeData(Bdata* b) {
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
}

#endif
