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
 * File:          $RCSfile: SpreadGun.h,v $
 * Date modified: $Date: 2002-07-07 03:50:01 $
 * Version:       $Revision: 1.8 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_SPREADGUN_H
#define MW_SPREADGUN_H

#include <gmtl/Math.h>
#include <gmtl/AxisAngle.h>
#include "BaseProjectileWeapon.h"
#include "BaseBullet.h"

namespace mw
{
   /*PISTOL,a basic weapon*/
   class SpreadGun : public BaseProjectileWeapon
   {
   public:
      SpreadGun()
         : BaseProjectileWeapon( Weapon::AUTOMATIC, "SpreadGun" )
         , mSpinning( 0.0f )
      {
         mCockRate = 0.1f;
         mReloadRate = 0.5f;
      }

      /** render the weapon using opengl calls. */
      virtual void draw() const 
      {
         glPushMatrix();
            glMultMatrixf( this->matrix().getData() );
            glScalef( 0.3f, 0.3f, 0.4f );
            glRotatef( mSpinning, 0, 0, 1 );
            cubeGeometry().render();
         glPopMatrix();
      }
      
      virtual void update( GameState& g, float dt )
      {
         BaseProjectileWeapon::update( g, dt );
         if (mFiring)
         {
            mSpinning += 5.0f * 360.0f * dt; // 5 Revs per sec
         }
      }
      
   protected:
      void discharge(GameState& g)
      {
         // define the spread
         float angle = gmtl::Math::deg2Rad( 15.0f );
         gmtl::Quatf r0( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( angle, 0.0f, 1.0f, 0.0f ) ) ),
                     r1, 
                     r2( gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( -angle, 0.0f, 1.0f, 0.0f ) ) );
         
         // define the 3 bullets in the spread weapon.
         BaseBullet* bullet0 = this->createBullet();
         bullet0->setRot( this->getRot() * r0 );
         bullet0->setPos( this->getPos() );
         bullet0->setVel( this->getRot() * r0 * bullet0->getVel() );
         
         BaseBullet* bullet1 = this->createBullet();
         bullet1->setRot( this->getRot() * r1 );
         bullet1->setPos( this->getPos() );
         bullet1->setVel( this->getRot() * r1 * bullet1->getVel() );
         
         BaseBullet* bullet2 = this->createBullet();
         bullet2->setRot( this->getRot() * r2 );
         bullet2->setPos( this->getPos() );
         bullet2->setVel( this->getRot() * r2 * bullet2->getVel() );
         
         // add the three bullets to the game
         // bullet is not mine anymore, belongs to GameState
         g.add( bullet0 ); 
         g.add( bullet1 ); 
         g.add( bullet2 ); 
      }

      void ejectCasing(GameState& g)
      {
         /// @todo eject a casing into the game
      }
      
      float mSpinning;
   };
}

#endif
