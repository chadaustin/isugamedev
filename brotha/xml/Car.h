#ifndef BDATA_CAR_H
#define BDATA_CAR_H

#include <iostream.h>
#include <string.h>
#include <vector>

#include "Cartype.h"
#include "brothadata.h"

namespace dataxml{

class Car{
private:

  modlist mods;

public:
  std::string name;
  Car(std::string iname){
    name = iname;
  }

  std::string getName(){
    return name;
  }

  modlist getMods(){
    return mods;
  }

  void addMod(Mod* m){
    mods.push_back(m);
  }

  void xMLify(std::ostream& out){
	  out << "      <car cartype=\"" << name << "\">" << std::endl;
    for(unsigned int i = 0; i < mods.size(); i++){
      mods[i]->xMLify(out);
    }
	out << "      </car>" << std::endl;
  }
};





typedef std::vector<Car*> carlist;

}
#endif
