/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: GarageDataMessage.h,v $
 * Date modified: $Date: 2002-05-01 23:35:19 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */

#ifndef NET_GARAGE_DATA_MESSAGE_H
#define NET_GARAGE_DATA_MESSAGE_H


#include <string>
#include "Message.h"
#include "MessageTypes.h"
#include "Serialize.h"
#include "xml/Player.h"
#include "xml/CarType.h"


namespace net {

   /**
    * Server will send this for all garage data
    */
   class GarageDataMessage : public Message {
   public:
      GarageDataMessage(data::Player* player = NULL, data::CarTypeList* cartl = NULL)
         : mPlayer(player), mCarTypes(cartl) {
      }

      PRUint32 getType() const {
         return GarageData;
      }

      PRUint32 getSize() {
         PRUint32 retVal = 0;

         if(mCarTypes != NULL) {
            data::CarTypeList* ctl = mCarTypes;
            for(unsigned int x=0;x<ctl->size();++x) {
               retVal += sizes::getVarSize((*ctl)[x]->getName()) +
                        sizes::getVarSize((*ctl)[x]->getFilename());
            }
            retVal += sizes::getVarSize((PRUint32)0);
         }

         if(mPlayer != NULL) {
            data::CarList* cl = &mPlayer->getCars();
            data::StatList* sl = &mPlayer->getStats();

            for(unsigned int x=0;x<cl->size();++x) {
               data::ModList* ml = &(*cl)[x]->getMods();

               retVal += sizes::getVarSize((*cl)[x]->getName());
               for(unsigned int y=0;y<ml->size();++y) {
                  retVal += sizes::getVarSize((*ml)[x]->getName()) +
                           sizes::getVarSize((PRUint32)(*ml)[x]->getLevel());
               }
               retVal += sizes::getVarSize((PRUint32)0);
            }
            retVal += sizes::getVarSize((PRUint32)0);

            for(unsigned int x=0;x<sl->size();++x) {
               retVal += sizes::getVarSize((*sl)[x]->getName()) +
                        sizes::getVarSize((*sl)[x]->getVal());
            }
            retVal += sizes::getVarSize((PRUint32)0);
         }

         return retVal;
      }

      void serialize(OutputStream& os) {
         data::CarTypeList* ctl = mCarTypes;
         os << ctl->size();
         for(unsigned int x=0;x<ctl->size();++x) {
            os << (*ctl)[x]->getName() << (*ctl)[x]->getFilename();
         }

         // send the player info
         if(mPlayer != NULL) {
            data::CarList* cl = &mPlayer->getCars();
            os << cl->size();
            for(unsigned int x=0;x<cl->size();++x) {
               os << (*cl)[x]->getName();

               data::ModList* ml = &(*cl)[x]->getMods();
               os << ml->size();
               for(unsigned int y=0;y<ml->size();++y) {
                  os << (*ml)[y]->getName() << (PRUint32)(*ml)[y]->getLevel();
               }
            }

            data::StatList* sl = &mPlayer->getStats();
            os << sl->size();
            for(unsigned int x=0;x<sl->size();++x) {
               os << (*sl)[x]->getName() << (*sl)[x]->getVal();
            }
         }
      }

      void deserialize(InputStream& is) {
         // read in the global car list
         if(mCarTypes == NULL) {
            // create car types object if it doesn't exist
            mCarTypes = new data::CarTypeList();
         }

         PRUint32 size;
         is >> size;
         for(unsigned int x=0;x<size;++x) {
            std::string name, file;
            is >> name >> file;

            data::CarType* ct = new data::CarType(name, file);
            mCarTypes->push_back(ct);
         }

         if(mPlayer == NULL) {
            // create player object if it doesn't exist
            mPlayer = new data::Player("","");
         }

         // read the player information
         is >> size;
         data::CarList* cl = &mPlayer->getCars();
         for(unsigned int x=0;x<size;++x) {
            std::string carName;
            is >> carName;
            data::Car* c = new data::Car(carName);
            
            // read this cars mod list
            PRUint32 modSize;
            is >> modSize;
            data::ModList* ml = &c->getMods();
            for(unsigned int y=0;y<modSize;++y) {
               std::string modName;
               PRUint32 modLevel;
               is >> modName >> modLevel;

               data::Mod* m = new data::Mod(modName, modLevel);
               ml->push_back(m);
            }

            cl->push_back(c);
         }

         // read this players stat list
         is >> size;
         data::StatList* sl = &mPlayer->getStats();
         for(unsigned int x=0;x<size;++x) {
            std::string name, value;
            is >> name >> value;
            data::Stat* s = new data::Stat(name, value);
            sl->push_back(s);
         }
      }

      data::CarTypeList* getCarTypes() {
         return mCarTypes;
      }

      data::Player* getPlayer() {
         return mPlayer;
      }

   private:
      /// The player
      data::Player* mPlayer;

      /// All car types in the database.
      data::CarTypeList* mCarTypes;
   };

}

#endif
