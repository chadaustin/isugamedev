#ifndef XMLP_H
#define XMLP_H

#include <iostream>
#include <string>



class XMLPersistory{

  public:
    bool open(std::string filename);
    void close();
    bool save(std::string filename);

};
     


bool XMLPersistory::open(std::string filename){
   std::cout << filename;
   return true;
}

#endif
