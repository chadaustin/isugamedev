/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil; c-basic-offset: 3 -*- */
// vim:cindent:ts=3:et:sw=3:

#ifndef NET_ADD_OBJ_MESSAGE_H
#define NET_ADD_OBJ_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"
#include "game/Object.h"


namespace net {

   /**
    * Server will send this to notify that clients should add an object
    */
   class AddObjMessage : public Message {
   public:
      AddObjMessage(game::Object* obj = NULL) {
         m_object = obj;
      }

      PRUint32 getType() const {
         return AddObj;
      }

      PRUint32 getSize() {
         if(m_object != NULL) {
            return m_object->getSize();
         } else {
            return 0;
         }
      }

      game::Object* getObject() {
         return m_object;
      }

      void serialize(OutputStream& os) {
         if(m_object != NULL) {
            m_object->serialize(os);
         }
      }

      void deserialize(InputStream& is) {
         if(m_object == NULL) {
            m_object = new game::Object();
         }
         m_object->deserialize(is);
      }
   private:
      game::Object* m_object;
   };

}

#endif
