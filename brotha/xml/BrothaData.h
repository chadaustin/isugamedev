#ifndef DATA_BROTHA_DATA_H
#define DATA_BROTHA_DATA_H

#include <iostream>
#include <string.h>
#include <vector>

#include "Car.h"
#include "Gang.h"
#include "Cartype.h"
#include "Player.h"

namespace data {

   class BrothaData {
   private:
      ganglist gangs;
      cartypelist cars;

   public:
      ganglist getGangList() {
         return gangs;
      }

      cartypelist getcartypes() {
         return cars;
      }

      void addCarType(Cartype* c) {
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

      Gang* getGangByName(std::string name) {
         for (unsigned int i = 0; i < gangs.size(); ++i) {
            if (gangs[i]->getName() == name) {
               return gangs[i];
            }
         }
         throw "not found";
         return gangs[0];  //should never be reached.
      }
   };
}

#endif
