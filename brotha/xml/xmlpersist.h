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
 * File:          $RCSfile: xmlpersist.h,v $
 * Date modified: $Date: 2002-04-29 08:23:46 $
 * Version:       $Revision: 1.10 $
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
#ifndef XMLP_H
#define XMLP_H

#include <iostream>
#include <string>
#include <xmlpp/xmlpp.h>
#include "BrothaData.h"


namespace data {
   BrothaData b;

   BrothaData load(std::string filename) {
      //fillWithFakeData(&b);
      xmlpp::XMLContextPtr ctx( new xmlpp::XMLContext );
      xmlpp::XMLDocument doc( ctx );
      doc.load_file( filename );
      xmlpp::xmlnodeptr rootp = doc.getChild ("wbdata");
      xmlpp::xmlnodelist cursor = rootp->getChildren("gang");
      xmlpp::XMLNodeListIterator it = cursor.begin();

      while (it != cursor.end()) {
         xmlpp::XMLAttributes& attr = (*it)->get_attrmap();
         Gang* g = new Gang(attr.get("name"));
         xmlpp::xmlnodeptr info = (*it)->getChild("info");
         g->setInfo( info->get_cdata());
         b.addGang(g);
         xmlpp::xmlnodelist cursor2 = (*it)->getChildren("player");
         xmlpp::XMLNodeListIterator it2 = cursor2.begin();

         while (it2 != cursor2.end()) {
            //xmlpp::XMLAttributes& attr2 = (*it2)->get_attrmap();
            //Player* p = new Player(attr2.get("name"), attr2.get("password"));
            attr = (*it2)->get_attrmap();
            Player* p = new Player(attr.get("name"), attr.get("password"));
            g->addPlayer(p);
            xmlpp::xmlnodelist cursor3 = (*it2)->getChildren("car");
            xmlpp::XMLNodeListIterator it3 = cursor3.begin();

            while (it3 != cursor3.end()) {
               attr = (*it3)->get_attrmap();
               Car* c = new Car(attr.get("cartype"));
               p->addCar(c);
               xmlpp::xmlnodelist cursor4 = (*it3)->getChildren("mod");
               xmlpp::XMLNodeListIterator it4 = cursor4.begin();

               while (it4 != cursor4.end()) {
                  attr = (*it4)->get_attrmap();
                  Mod* m = new Mod(attr.get("name"),atoi(attr.get("level").c_str()));
                  c->addMod(m);
                  it4++;
               }
               it3++;
            }

            xmlpp::xmlnodelist cursorStat = (*it2)->getChildren("stat");
            xmlpp::XMLNodeListIterator itStat = cursorStat.begin();

            while (itStat != cursorStat.end()) {
               attr = (*itStat)->get_attrmap();
               Stat* s = new Stat(attr.get("name"),attr.get("value"));
               p->addStat(s);
               itStat++;
            }
            it2++;
         }

         it++;
         xmlpp::xmlnodelist types = rootp->getChildren("cartype");
         xmlpp::XMLNodeListIterator itTypes = types.begin();

         while (itTypes != types.end()) {
            xmlpp::XMLAttributes& attr = (*itTypes)->get_attrmap();
            Cartype* c = new Cartype(attr.get("name"),attr.get("model"));
            b.addCarType(c);
            itTypes++;
         }
      }
      return b;
   }

   void fillWithFakeData(BrothaData* b) {
      Gang* g = new Gang("emigia");
      Player* p = new Player("ama","kuriyama");
      Car* c = new Car("tercel");
      Mod* m = new Mod("breaks",4);
      Cartype* ct = new Cartype("tercel");
      b->addGang(g);
      b->addCarType(ct);
      c->addMod(m);
      p->addCar(c);
      g->addPlayer(p);
   }
}

#endif
