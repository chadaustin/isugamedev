#ifndef BDATA_CARTYPE_H
#define BDATA_CARTYPE_H


#include <iostream>
#include <string>
#include <vector>

namespace dataxml{


class Cartype{
private:

  std::string name;
  std::string filename;

public:

  Cartype(){
    name = "none!";
	filename = "car.model";
  }

  Cartype(std::string iname){
	  name = iname;
	  filename = "car.model";
  }

  Cartype(std::string in_name, std::string imodl){
    name = in_name;
    filename = imodl;
  }

  std::string getFileName(){
    return filename;
  }

  std::string getName(){
    return name;
  }

  void xMLify(std::ostream& out){
	  out << "  <cartype name=\"" << name << "\" file=\"" << filename<< "\" />" << std::endl;
  }
};




typedef std::vector<Cartype*> cartypelist;

}
#endif