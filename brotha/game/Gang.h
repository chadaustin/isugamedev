#ifndef GAME_CARTYPE_H
#define GAME_CARTYPE_H

#include <vector> 
#include <string>
#include "game/Player.h"

namespace game {

   class Gang {

   public:  
      /// For creating list of gangs
      typedef std::vector<Gang*> GangList;

      /// For returning iterators to specific players
      typedef GangList::iterator GangListItr;

      /// For players in gang
      typedef std::vector<Player*> GangPlayersList;

      /// For returning iterators to specific players
      typedef GangPlayersList::iterator PlayersListItr;

   public:

      /**
       * Creates a new gang with the given name.
       */
      Gang(const std::string& name);

      /**
       * Gets the name of the gang.
       */
      const std::string& getName() const;

      /**
       * Returns a list of players in the gang
       */
      const GangPlayersList getPlayers() const;

      /**
       * Returns a list of players in the gang
       */
      const GangList getGangs() const;

      /**
       * Adds player to the gang
       */
      void addPlayer(Player* player);

      /**
       * Adds gang to the game
       */
      void addGang(Gang* gang);



   private:
      /// This player's name
      std::string mGangName;

      /// List of gang's players
      GangPlayersList mGangPlayers;

      /// List of gangs
      GangList mAllGangs;

   };

}

#endif
