/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_UPDATE_PLAYER_MESSAGE_H
#define NET_UPDATE_PLAYER_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"
#include "game/Player.h"


namespace net {

   /**
    * Server will send this to notify that clients should update a player
    */
   class UpdatePlayerMessage : public Message {
   public:
      UpdatePlayerMessage(game::Player* player = NULL)
         : m_player(player)
      {}

      PRUint32 getType() const {
         return UpdatePlayer;
      }

      PRUint32 getSize() {
         if (m_player != NULL) {
            return m_player->getSize();
         } else {
            return 0;
         }
      }

      game::Player* getPlayer() {
         return m_player;
      }

      void serialize(OutputStream& os) {
         if(m_player != NULL) {
            m_player->serialize(os);
         }
      }

      void deserialize(InputStream& is) {
         if(m_player != NULL) {
            m_player->deserialize(is);
         }
      }
   private:
      game::Player* m_player;
   };

}

#endif
