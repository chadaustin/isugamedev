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
 * File:          $RCSfile: SnowSystem.cpp,v $
 * Date modified: $Date: 2002-11-14 09:31:47 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <gmtl/Math.h>
#include <SDL_opengl.h>
#include "SnowSystem.h"

namespace mw
{
   const int BASE_HEIGHT = 25;

   SnowSystem::SnowSystem()
   {
      Particle* p = mParticles;
      for (int i = 0; i < SNOWFLAKE_COUNT; ++i)
      {
         p->x = gmtl::Math::rangeRandom(-100, 100);
         p->y = gmtl::Math::unitRandom() * BASE_HEIGHT;
         p->z = gmtl::Math::rangeRandom(-100, 300);
         p->velocity = gmtl::Math::unitRandom() * 2 + 2;
         ++p;
      }
   }

   SnowSystem::~SnowSystem()
   {}

   void
   SnowSystem::draw()
   {
      glEnable(GL_POINT_SMOOTH);
      glPointSize(4);
      glDepthMask(GL_FALSE);

      glColor3f(1.0f, 1.0f, 1.0f);
      Particle* p = mParticles;

      glBegin(GL_POINTS);
      for (int i = 0; i < SNOWFLAKE_COUNT; ++i)
      {
         glVertex3f(p->x, p->y, p->z);
         ++p;
      }
      glEnd();

      glDepthMask(GL_TRUE);
   }

   void
   SnowSystem::update(float dt)
   {
      Particle* p = mParticles;
      for (int i = 0; i < SNOWFLAKE_COUNT; ++i)
      {
         p->y -= dt * p->velocity;

         if (p->y < 0)
         {
            p->y = BASE_HEIGHT;
         }

         ++p;
      }
   }
}
