#ifndef BDATA_GANG_H
#define BDATA_GANG_H

#include <iostream>
#include <string>
#include <vector>


#include "Player.h"


namespace dataxml{

class Gang{
private:
  std::string name;
  std::string info;
  playerlist players;
public:
  Gang(std::string iname){
    name = iname;
  }
  void addPlayer(Player* i){
    players.push_back(i);
  }

  playerlist getPlayerList(){
    return players;
  }

  void setInfo(std::string in){
    info = in;
  }

  std::string getInfo(){
	  return info;
  }

  std::string getName(){
    return name;
  }

  void xMLify(std::ostream& out){
   out << "  <gang name=\"" << name << "\">" << std::endl;
   out << "    <info>" << info << "</info>" <<std::endl;
   for(int i = 0; i < players.size(); i++){
      players[i]->xMLify(out);
    }
   out << "  </gang>" <<std::endl;
  }
};


typedef std::vector<Gang*> ganglist;
}
#endif