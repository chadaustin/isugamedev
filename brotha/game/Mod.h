#ifndef GAME_MOD_H
#define GAME_MOD_H

#include <iostream.h>
#include <string>
#include "Object.h"
#include <vector>

namespace game {

   //modifications to the car.
   class Mod {
   public:
      typedef std::vector<Mod*> ModList;

      typedef ModList::iterator ModListItr;

   public:
      /**
       * Creates a new mod with the given name and level.
       */
      Mod(const std::string& name, int level);

      /**
       * Returns the name of the mod
       */
      const std::string getName() const{
         return modName;
      }
  
      /**
       * Returns the level of the mod
       */
      int getLevel() {
         return modLevel;
      }

      /**
       * Adds a mod to the mod list
       */
      void addMod(Mod* mod);
  
      /**
       * Removes a mod from the list
       */
      void removeMod(Mod* mod);

      /**
       * Returns list of all mods
       */
      const ModList getMods() const;

   private:

      /// Name of mod
      std::string modName;

      /// Level of Mod
      int modLevel;

      /// List of Mods
      ModList mMods;

   };
}

#endif
