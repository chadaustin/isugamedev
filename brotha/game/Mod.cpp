#include "Mod.h"
#include <algorithm>

namespace game {

   Mod::Mod( const std::string& name, int level )
      : modName(name), modLevel(level){
   }

   void Mod::addMod(Mod* mod){
      ModListItr Itr;
      Itr = std::find(mMods.begin(),mMods.end(),mod);
      
      if (Itr != mMods.end()){
         mMods.push_back(mod);
      }
      else{
         std::cout<<"A mod by this name already exists!"<<std::endl;
      }
   }

   void Mod::removeMod(Mod* mod){
      ModListItr Itr;

      // find the object to remove and set to iterator
      Itr = std::find(mMods.begin(), mMods.end(), mod);
      
      // makes sure object exists and removes if it does
      if(Itr != mMods.end()){
         mMods.erase(Itr);
      }
   }

   const Mod::ModList Mod::getMods() const{
      return mMods;
   }
	
}
