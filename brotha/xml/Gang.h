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

  std::string getName(){
    return name;
  }

  void xMLify(std::ostream& out){
   out << "  <gang name=\"" << name << "\">" << std::endl;
   for(int i = 0; i < players.size(); i++){
      players[i]->xMLify(out);
    }
   out << "  </gang>" <<endl;
  }
};


typedef std::vector<Gang*> ganglist;
}
#endif