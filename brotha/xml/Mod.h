#ifndef BDATA_MOD_H
#define BDATA_MOD_H

#include <iostream.h>
#include <string.h>
#include <vector>


namespace dataxml{



//modifications to the car.
class Mod {

private:

  std::string type;
  int level;

public:

  Mod(std::string in_type, int in_level){
    type = in_type;
    level = in_level;
  }

  std::string getType(){
    return type;
  }
  
  int getLevel(){
    return level;
  }
  
  void xMLify(std::ostream& out){
    out <<"        <mod name=\"" << type << "\" level=\"" << level << "\" />" << std::endl;
  }
};





typedef std::vector<Mod*> modlist;

}



#endif