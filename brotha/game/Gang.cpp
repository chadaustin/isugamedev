#include "Gang.h"
#include <algorithm>

namespace game {

   Gang::Gang( const std::string& name )
      : mGangName(name){
   }

   const std::string& Gang::getName() const{
      return mGangName;
   }

   void Gang::addPlayer(Player* player){
      PlayersListItr Itr;
      Itr = std::find(mGangPlayers.begin(),mGangPlayers.end(),player);
      
      if (Itr != mGangPlayers.end()){
         mGangPlayers.push_back(player);
      }
      else{
         std::cout<<"A player by this name already exists in this gang!" << std::endl;
      }
   }

   const Gang::GangPlayersList Gang::getPlayers() const{
      return mGangPlayers;
   }

   void Gang::addGang(Gang* gang){
      GangListItr Itr;
      Itr = std::find(mAllGangs.begin(),mAllGangs.end(),gang);
      
      if (Itr != mAllGangs.end()){
         mAllGangs.push_back(gang);
      }
      else{
         std::cout<<"A gang by this name already exists in the game!" << std::endl;
      }
   }

   const Gang::GangList Gang::getGangs() const{
      return mAllGangs;
   }

	
}