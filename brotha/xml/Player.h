
#ifndef BDATA_PLAYER_H
#define BDATA_PLAYER_H

#include <iostream>
#include <string>
#include <vector>

namespace dataxml{


class Player{
private:
  std::string name;
  std::string password; //look, it's private so it's secure :)
  carlist cars;

public:
  Player(std::string iname, std::string ipasswd){
    name = iname;
    password = ipasswd;
  }

  void changePassword(std::string npw){
     password = npw;
  }

  std::string getName(){
    return name;
  }

  std::string getPassword(){
    return password;
  }

  carlist getCars(){
    return cars;
  }

  void addCar(Car* c){
    cars.push_back(c);
  }

  void xMLify(std::ostream& out){
    out << "    <player name=\"" << name << "\" password=\"" << password << "\">" << std::endl;
    for(int i = 0; i < cars.size(); i++){
      cars[i]->xMLify(out);
    }
	out << "   </player>" << std::endl;
  }
  
};

typedef std::vector<Player*> playerlist;
}

#endif