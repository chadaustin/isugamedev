#ifndef BDATA_STAT_H
#define BDATA_STAT_H

#include <iostream.h>
#include <string.h>
#include <vector>


namespace dataxml{



//modifications to the car.
class Stat {

private:

  std::string name;
  std::string value;

public:

  Stat(std::string iname, std::string ival){
		name=iname;
		value=ival;
  }

  std::string getName(){
    return name;
  }
  
  std::string getVal(){
    return value;
  }
  
  void xMLify(std::ostream& out){
    out <<"        <stat name=\"" << name << "\" value=\"" << value << "\" />" << std::endl;
  }
};





typedef std::vector<Stat*> statlist;

}



#endif