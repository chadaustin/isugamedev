#ifndef DATA_BROTHA_DATA_H
#define DATA_BROTHA_DATA_H

#include <iostream>
#include <string.h>
#include <vector>

#include "Car.h"
#include "Gang.h"
#include "CarType.h"
#include "Player.h"

namespace data {

   class BrothaData {
   private:
      GangList gangs;
      CarTypeList cars;

   public:
      GangList& getGangList() {
         return gangs;
      }

      CarTypeList& getCarTypes() {
         return cars;
      }

      void addCarType(CarType* c) {
         cars.push_back(c);
      }

      void addGang(Gang* g) {
         gangs.push_back(g);
      }

      void xMLify(std::ostream& out) {
         out << "<wbdata>" << std::endl;
         for (unsigned int i = 0; i < gangs.size(); ++i) {
            gangs[i]->xMLify(out);
         }
         for (unsigned int i = 0; i < cars.size(); ++i) {
            cars[i]->xMLify(out);
         }
         out << "</wbdata>";
      }

      Gang* getGang(const std::string& name) {
         for (unsigned int i = 0; i < gangs.size(); ++i) {
            if (gangs[i]->getName() == name) {
               return gangs[i];
            }
         }
         throw "not found";
         return gangs[0];  //should never be reached.
      }

      Player* getPlayer(const std::string& name) {
         GangList::iterator itr;
         for (itr = gangs.begin(); itr != gangs.end(); ++itr) {
            if (Player* p = (*itr)->getPlayer(name)) {
               return p;
            }
         }
         return NULL;
      }
   };
}

#endif
