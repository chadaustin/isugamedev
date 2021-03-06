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
 * File:          $RCSfile: PhysicsEngine.cpp,v $
 * Date modified: $Date: 2002-12-21 19:25:49 $
 * Version:       $Revision: 1.17 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <iostream>
#include <gmtl/Generate.h>
#include <gmtl/Intersection.h> // for debugging only
#include "BaseBullet.h"
#include "PhysicsEngine.h"

namespace mw
{
   const float PhysicsEngine::TIME_EPSILON = 0.0001f;

   const gmtl::Vec3f PhysicsEngine::GRAVITY(0, -9.81f, 0);

   PhysicsEngine::PhysicsEngine(CollisionDetector* collisionDetector,
                                CollisionResponse* collisionResponse,
                                Scene* scene)
      : mCollisionDetector(collisionDetector)
      , mCollisionResponse(collisionResponse)
      , mScene(scene)
   {}

   PhysicsEngine::~PhysicsEngine()
   {}

   void
   PhysicsEngine::update(RigidBody* body, float dt, bool rotation)
   {
      update(body, dt, body->getNextState(), rotation);
   }

   void
   PhysicsEngine::update(const RigidBody* body, float dt, BodyState& state, bool rotation)
   {
      // Ensure the mass is not zero
      float mass = body->getMass();
      if (mass < 0.0001f)
      {
         std::cout<<"Mass too small: "<<mass<<" - Setting to 1.0"<<std::endl;
         mass = 1.0f;
      }

      const BodyState& last_state = body->getCurrentState();

      const gmtl::Point3f& pos      = last_state.getPos();
      const gmtl::Vec3f&   vel      = last_state.getVel();
      const gmtl::Quatf&   rot      = last_state.getRot();
      const gmtl::Vec3f&   rotVel   = last_state.getRotVel();
      const gmtl::Vec3f&   force    = body->getForce();
      const gmtl::Vec3f&   torque   = body->getTorque();

      // change in position over time (first order)
      // x' = v = P(t)/M
      gmtl::Vec3f pos_delta = vel * dt;

      // change in lin momentum over time (second order)
      // P'(t) = F(t)
      gmtl::Vec3f linear_momentum_delta = force * dt;

      // add the derivitives to the current rigidbody state
      state.setPos(pos + pos_delta);
      state.setVel(vel + (linear_momentum_delta / mass));

      // Only calculate rotational changes if requested
      if (rotation)
      {
         // change in rotation over time (first order)
         // R'(t) = w(t)*' R(t)   (matrix version)
         // q'(t) = 1/2 w(t) q(t) (quaternion version)
         gmtl::Quatf rot_delta, temp;
         gmtl::Quatf one_half_wt = gmtl::makePure( gmtl::Vec3f( rotVel * 0.5f ) );
         gmtl::mult( temp, one_half_wt, rot );
         gmtl::mult( rot_delta, temp, dt );  // scale by time...

         // change in ang momentum over time (second order)
         // L'(t) = T(t)
         gmtl::Vec3f ang_momentum_delta = torque;

         state.setRot(rot + rot_delta);
         gmtl::normalize(state.getRot()); // rot quats always normalized
         state.setRotVel(rotVel + ang_momentum_delta); // @todo this is wrong (needs inertia tensor)
      }
   }

   void
   PhysicsEngine::update(float dt)
   {
      for (Scene::EntitySetItr itr = mScene->begin(); itr != mScene->end(); ++itr)
      {
         RigidBody* body = *itr;

         // Apply gravity to every body
         if (0 == dynamic_cast<BaseBullet*>(body))
         {
            body->addForce(GRAVITY * body->getMass());
         }

         // Update the body for the remaining time differential
         update(body, dt);
         
         // Check if the body collided with anything
         gmtl::Vec3f path = body->getNextState().getPos() - body->getCurrentState().getPos();
         std::auto_ptr<CollisionDesc> desc(mCollisionDetector->checkCollision(body, path, *mCollisionResponse));

         // No collisions, let the body update for the remaining distance
         if (!desc.get())
         {
            // Make sure entities never go below the ground.
            // XXX: This is such a hack. We need to get ground collision
            // detection to be done in the collision detector.
            float& y = body->getNextState().getPos()[1];
            y = std::max(y, 0.0f);

            body->moveToNextState();
         }
         // There was a collision!
         else
         {
            // Figure out how much time passed to get to the collision. We do this
            // by scaling back the remaining dt by the % of the distance that was
            // travelled.
            float time_to_collision = dt * desc->getDistance();
/*
            std::cout << "Collision: " << ((Entity*)body)->getUID() << " => "
                      << ((Entity*)desc->getCollidee())->getUID()
                      << ", Time to collision: " << time_to_collision << std::endl;
*/
            time_to_collision = std::max(0.0f, time_to_collision - 0.01f);

            // Update the body to the point of the collision
            PhysicsEngine::update(body, time_to_collision);

            // Make sure entities never go below the ground.
            // XXX: This is such a hack. We need to get ground collision
            // detection to be done in the collision detector.
            float& y = body->getNextState().getPos()[1];
            y = std::max(y, 0.0f);

            body->moveToNextState();

            // body                == collider
            // desc->getCollidee() == collidee
            mCollisionResponse->collide(body, desc->getCollidee());
         }
      }
   }

   CollisionDetector*
   PhysicsEngine::getCollisionDetector() const
   {
      return mCollisionDetector;
   }

   Scene*
   PhysicsEngine::getScene() const
   {
      return mScene;
   }
}
