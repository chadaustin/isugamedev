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
 * File:          $RCSfile: PhysicsEngine.h,v $
 * Date modified: $Date: 2002-11-03 03:49:59 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#ifndef MW_PHYSICS_ENGINE_H
#define MW_PHYSICS_ENGINE_H

#include "CollisionDetector.h"
#include "CollisionResponse.h"
#include "RigidBody.h"
#include "Scene.h"

namespace mw
{
   /**
    * @ingroup Physics
    *
    * This class is the Facade to the Physics subsystem. It is responsible for
    * knowing how to apply the physical rules to rigid bodies and their states.
    *
    * @see RigidBody
    * @see BodyState
    */
   class PhysicsEngine
   {
   public:
      /// Epsilon value for time value testing.
      const static float TIME_EPSILON;

      /// Normal gravity vector (acceleration) in meters/sec.
      const static gmtl::Vec3f GRAVITY;

   public:
      /**
       * Creates a new physics simulator that will use the given collision
       * detection algorithm for the objects in the given scene.
       */
      PhysicsEngine(CollisionDetector* collisionDetector,
                    CollisionResponse* collisionResponse,
                    Scene* scene);

      ~PhysicsEngine();

      /**
       * Applies all the forces to the given body over the given change of time.
       * The body's state is updated to reflect the changes. This is equivalent
       * to calling update(body, dt, body->getNextState()).
       *
       * @param body       the RigidBody to update
       * @param dt         the time delta in seconds
       * @param rotation   true if rotational calculations should be done
       */
      static void update(RigidBody* body, float dt, bool rotation = true);

      /**
       * Applies all the forces to the given body over the given change of time
       * and stores the result in the given state. The source body is not
       * modified.
       *
       * @param body       the RigidBody to update
       * @param dt         the time delta in seconds
       * @param state      the state to modify with the result of the update
       * @param rotation   true if rotational calculations should be done
       */
      static void update(const RigidBody* body, float dt,
                         BodyState& state, bool rotation = true);

      /**
       * Updates the dynamics of all the bodies in this physics simulator.
       *
       * @param dt         the time delta in seconds
       */
      void update(float dt);

      /// Get the collision detection algorithm used with this physics simulator
      CollisionDetector* getCollisionDetector() const;

      /// Get the scene used with this physics simulator
      Scene* getScene() const;

   private:
      /// The collision detection algorithm used
      CollisionDetector* mCollisionDetector;

      /// The collision response mapping
      CollisionResponse* mCollisionResponse;

      /// The scene that contains the rigid bodies
      Scene* mScene;
   };
}

#endif
