/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * -----------------------------------------------------------------
 * File:          $RCSfile: LevelLoader.cpp,v $
 * Date modified: $Date: 2002-11-13 07:35:28 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <fstream>
#include <stdexcept>

#include "LevelLoader.h"
#include "GameState.h"
#include "EntityFactory.h"

#include "AmmoCrate.h"
#include "Enemy.h"
#include "Droid.h"
#include "GunPickup.h"
#include "NavNodeTree.h"
#include "StaticEntity.h"
#include "Turret.h"

namespace mw
{
   void
   LevelLoader::load(const std::string& level, GameState* gameState)
   {
      std::ifstream in(level.c_str());
      if (!in.is_open())
      {
         throw std::runtime_error("Could not open level file: " + level);
      }

      std::string type;
      while (in >> type)
      {
         if (type == "#")
         {
            std::string dummy;
            std::getline(in, dummy);
            continue;
         }
         
         double x, y, z;
         double h, p, r;
         if (!(in >> x >> y >> z >> h >> p >> r))
         {
            break;
         }
       
         // THIS SUCKS ASS
         // VC++ 7 does not compile this right unless it's static
         // Internal Compiler Error
         // this is not threadsafe
         static Entity* e;
         e = 0;

         if (type == "droid")
         {
            std::string name, parent;
            int maxChild, level;
            if(in >> name >> parent >> maxChild >> level)
            {
               Entity* en;
               en = gameState->setupDroid(name, parent, maxChild, level, *gameState->getNavNodeTree());
               en->setModel("security_droid");
               e = en;
            }
         }
         else if (type == "navNode")
         {
            Node* node;
            node = new Node;
            if(in >> node->name)
            {
               node->loc[0] = x;
               node->loc[1] = y;
               node->loc[2] = z;
               gameState->addNavNode(node);
            }
         }
         else if (type == "navLink")
         {
            std::string n1, n2;
            if(in >> n1 >> n2)
            {
               gameState->addNavNodeLink(n1, n2);
            }
         }  
         else if (type == "turret")
         {
            std::string name, parent;
            int maxChild, level;
            if (in >> name >> parent >> maxChild >> level)
            {
               Entity* t;
               t = gameState->setupTurret(name, parent, maxChild, level);
               t->setModel("turret");
               e = t;
            }
         }
         else if (type == "ammo")
         {
            e = EntityFactory::instance().create<AmmoCrate>();
            e->setModel("ammo_crate");
         }
         else if (type == "gun")
         {
            std::string guntype;
            if (in >> guntype)
            {
               e = EntityFactory::instance().create<GunPickup>(guntype);
               e->setModel("ammo_crate");
            }
         }
         else if (type == "static")
         {
            std::string model;
            if (in >> model)
            {
               e = EntityFactory::instance().create<StaticEntity>();
               e->setModel(model);
            }

            float sx, sy, sz;
            if (in >> sx >> sy >> sz)
            {
               e->setScale(gmtl::Vec3f(sx, sy, sz));
            }
         }
         else
         {
            throw std::runtime_error("Unknown entity type: " + type);
         }

         // Only setup the entity if it is not null
         if (e != 0)
         {
            gmtl::Point3f pos(x, y, z);
            gmtl::Quatf rot(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(
               gmtl::Math::deg2Rad(p),
               gmtl::Math::deg2Rad(h),
               gmtl::Math::deg2Rad(r))));

            e->setPos(pos);
            e->setRot(rot);
            gameState->add(e);
         }
      }
   }
}
