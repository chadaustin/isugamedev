#ifndef ASTER_GAME_BOARD
#define ASTER_GAME_BOARD

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "StopWatch.h"    // for time measurment...
#include "Grid.h"
#include "cubeGeometry.h" // for cheezy cube geometry

///////////////////////////////////////////////////////////
// A few useful math routines
///////////////////////////////////////////////////////////
namespace Math
{
   inline float deg2rad( float deg )
   {
      return (deg * 3.1459f) / 180.0f;
   }
   inline float rad2deg( float rad )
   {
      return (rad * 180.0f) / 3.1459f;
   }
   inline float abs( float a )
   {
      return (a < 0.0f) ? -a : a;
   }

   //: return a random number between 0.0f and 1.0f
   //! RETURNS: random number between 0 and 1
   inline float random()
   {
      // ::rand() returns int from  0 - RAND_MAX
      const float rand_max = RAND_MAX;
      float r = static_cast<float>( ::rand() );
      r /= rand_max;
      return r;
   }

   //: return a random number between x1 and x2
   //! RETURNS: random number between x1 and x2
   inline float random( float x1, float x2 )
   {
      float r = Math::random();
      float size = x2 - x1;
      return r * size + x1;
   }
   
   // dot product.  sqrt of this gives dist between points..
   inline float dot( float pt1[3], float pt2[3] )
   {
      float d = 0.0f;
      d += pt1[0] * pt2[0];
      d += pt1[1] * pt2[1];
      d += pt1[2] * pt2[2];
      return d;
   }
   // subtract two vectors, store result in res
   inline void sub( float res[3], float vec1[3], float vec2[3] )
   {
      res[0] = vec1[0] - vec2[0];
      res[1] = vec1[1] - vec2[1];
      res[2] = vec1[2] - vec2[2];
   }
   // add two vectors, store result in res
   inline void add( float res[3], float vec1[3], float vec2[3] )
   {
      res[0] = vec1[0] + vec2[0];
      res[1] = vec1[1] + vec2[1];
      res[2] = vec1[2] + vec2[2];
   }
   // scale a vector
   inline void mul( float res[3], float vec1[3], float scalar )
   {
      res[0] = vec1[0] * scalar;
      res[1] = vec1[1] * scalar;
      res[2] = vec1[2] * scalar;
   }
   // copy a vector
   inline void copy( float res[3], float vec1[3] )
   {
      res[0] = vec1[0];
      res[1] = vec1[1];
      res[2] = vec1[2];
   }
   // normalize a vector
   inline void norm( float vec[3] )
   {
      float d = Math::dot( vec, vec );
      if (d <= 0.0001f) // some epsillon (d should be > 0)
         return;
      
      float n = sqrtf( d );
      float n_inv = 1.0f / n;
      Math::mul( vec, vec, n_inv );
   }
   // distance
   inline float distance( float vec1[3], float vec2[3]  )
   {
      float temp[3];
      Math::sub( temp, vec1, vec2 );
      return sqrtf( Math::dot( temp, temp ) );
   }
   
   // compute perfectly elastic reflection using available vectors... 
   inline void reflect( float reflection[3], float incoming[3], float surfacenormal[3] )
   {
      Math::mul( reflection, incoming, -1.0f );
      float d = Math::dot( reflection, surfacenormal );
      Math::mul( reflection, surfacenormal, d );
      Math::mul( reflection, reflection, 2.0f );
      Math::add( reflection, reflection, incoming );
   }   
}

///////////////////////////////////////////////////////////
// a few game objects
///////////////////////////////////////////////////////////

class BaseObject
{
public:
   BaseObject() : size( 1.0f ), rotation( 0 ), angularVel( 0 ), timeToLive( -1 )
   {
      this->setPos( 0.0f, 0.0f, 0.0f );
      this->setVel( 0.0f, 0.0f, 0.0f );
   }
   void draw() 
   { 
      glPushMatrix();
      glTranslatef( position[0], position[1], position[2] );
      glRotatef( rotation, 0,1,0 );
      glScalef( size * 0.5f, size * 0.5f, size * 0.5f );
      cube.render(); 
      glPopMatrix();
   }
   void update( float dt )
   {
      position[0] += velocity[0] * dt;
      position[1] += velocity[1] * dt;
      position[2] += velocity[2] * dt;
      rotation += angularVel * dt;
      if (timeToLive != -1) 
         timeToLive -= dt;
   }
   void setPos( float x, float y, float z )
   {
      position[0] = x;
      position[1] = y;
      position[2] = z;
   }   
   void setVel( float x, float y, float z )
   {
      velocity[0] = x;
      velocity[1] = y;
      velocity[2] = z;
   }   
   float size;
   float rotation;
   float angularVel;
   float timeToLive; // -1 is infinite == don't ever die;
   float velocity[3];
   float position[3];
   cubeGeometry cube;
};

class Projectile : public BaseObject
{
public:
};
class Roid : public BaseObject
{
public:
};
class Ship : public BaseObject
{
public:
};

///////////////////////////////////////////////////////////
// the asteroids game board
///////////////////////////////////////////////////////////
class GameBoard
{
public:
   GameBoard() : width( 0 ), height( 0 ), mainWin_contextID( -1 ), 
      boardSize( 15 ), 
      projVelocity( 20.0f ), projSize( 0.1f ), projTimeToLive( 0.75f ), 
      rotVelocity( 60.0f ), shipAccel( 10.0f ), 
      roidSize( 3.0f ), roidMaxSpeed( 3.0f ), 
      mousesens( 96.0f )
   {
      Roid r; 
      r.size = roidSize;
      r.setPos( -5.0f, 0.0f, -5.0f );
      r.setVel( Math::random() * roidMaxSpeed, 0, Math::random() * roidMaxSpeed );
      roids.push_back( r );
      r.setPos( -5.0f, 0.0f, 5.0f );
      r.setVel( Math::random() * roidMaxSpeed, 0, Math::random() * roidMaxSpeed );
      roids.push_back( r );
      r.setPos(  5.0f, 0.0f, -5.0f );
      r.setVel( Math::random() * roidMaxSpeed, 0, Math::random() * roidMaxSpeed );
      roids.push_back( r );
      r.setPos(  5.0f, 0.0f, 5.0f );
      r.setVel( Math::random() * roidMaxSpeed, 0, Math::random() * roidMaxSpeed );
      roids.push_back( r );
      
      grid.setPos( 0.0f, -1.0f, 0.0f );
      grid.size = boardSize;
      
      
   }

   void init( gk::IGameKernel* kernel )
   {
      mKernel = kernel;
      
      // inputs.
      mMouseYaxis.init( "MouseLookYaxis", mKernel );
      mFire.init( "Fire", mKernel );
      mAccelerate.init( "Accelerate", mKernel );
      mBackstep.init( "Backstep", mKernel );
      mStrafeLeft.init( "StrafeLeft", mKernel );
      mStrafeRight.init( "StrafeRight", mKernel );
      mRotateLeft.init( "RotateLeft", mKernel );
      mRotateRight.init( "RotateRight", mKernel );
   }   
   
   void draw()
   {
      std::cout<<"draw"<<std::endl;
      // camera xform (this does the first person view navigation transform)
      glRotatef( -ship.rotation, 0.0f, 1.0f, 0.0f );
      glTranslatef( -ship.position[0], -ship.position[1], -ship.position[2] );
      
      unsigned int x;
      for (x = 0; x < roids.size(); ++x)
      {
         roids[x].draw();
      }  
      for (x = 0; x < projs.size(); ++x)
      {
         projs[x].draw();
      }  
      grid.draw();    
   }   
   
   void update( float dt )
   {
      mKernel->warpMouse( width / 2, height / 2 );

      ///////////
      // PHYSICS
      ///////////
      ship.update( dt );

      unsigned int x;
      for (x = 0; x < roids.size(); ++x)
      {
         roids[x].update( dt );
      }  
      for (x = 0; x < projs.size(); ++x)
      {
         projs[x].update( dt );
      }
      
      
      ///////////
      // INPUT: 
      ///////////
      
      // find out what dir, the ship is pointing.
      // - flip the x axis to support right-hand rule
      // - add 90deg so that the identity rotation faces out of the screen
      // - then negate it all because we actually face forward (in 0,0,-1)
      float shipForward[3];
      shipForward[0] = cosf( Math::deg2rad( ship.rotation + 90 ) ); 
      shipForward[1] = 0;                                           
      shipForward[2] = -sinf( Math::deg2rad( ship.rotation + 90 ) ); 
      
      float shipRight[3];
      shipRight[0] = cosf( Math::deg2rad( ship.rotation ) ); 
      shipRight[1] = 0;                                           
      shipRight[2] = -sinf( Math::deg2rad( ship.rotation ) ); 
      
      float shipUp[3] = { 0.0f, 1.0f, 0.0f };
      
      // do rotation based on a mouse axis.
      float dx = -(mMouseYaxis.getAnalogData());
      ship.rotation += dx * mousesens;
      
      // handle button input
      // poll each button state, do appropriate behaviour
      if (mRotateLeft.getDigitalData() == gk::DigitalInput::DOWN ||
          mRotateLeft.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         ship.angularVel = rotVelocity;
      else if (mRotateRight.getDigitalData() == gk::DigitalInput::DOWN ||
               mRotateRight.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         ship.angularVel = -rotVelocity;
      else
         ship.angularVel = 0;
      
      if (mFire.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
      {
         // fire in the direction ship faces
         // use flip flop to give effect of two side mounted gun turrets...
         Projectile proj;
         static float flip_flop = -1;
         flip_flop = -flip_flop;
         
         // local position on the ship
         float local_pos[3] = { 0.2f * flip_flop, -0.2f, 0.4f };
         
         // convert the local position to world coord
         float world_offset[3];
         world_offset[0] = shipRight[0] * local_pos[0] + shipUp[0] * local_pos[1] + shipForward[0] * local_pos[2];
         world_offset[1] = shipRight[1] * local_pos[0] + shipUp[1] * local_pos[1] + shipForward[1] * local_pos[2];
         world_offset[2] = shipRight[2] * local_pos[0] + shipUp[2] * local_pos[1] + shipForward[2] * local_pos[2];
         
         // set the projectile start position (relative to the ships world position)
         proj.setPos( ship.position[0] + world_offset[0], 
                      ship.position[1] + world_offset[1], 
                      ship.position[2] + world_offset[2] );
         proj.setVel( shipForward[0] * projVelocity, 
                      shipForward[1] * projVelocity, 
                      shipForward[2] * projVelocity );
         proj.size = projSize;
         proj.timeToLive = projTimeToLive;
         projs.push_back( proj );
      }
      if (mAccelerate.getDigitalData() == gk::DigitalInput::DOWN ||
          mAccelerate.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         ship.setVel( ship.velocity[0] + (shipForward[0] * shipAccel * dt), 
                      ship.velocity[1] + (shipForward[1] * shipAccel * dt), 
                      ship.velocity[2] + (shipForward[2] * shipAccel * dt) );
      
      if (mBackstep.getDigitalData() == gk::DigitalInput::DOWN ||
          mBackstep.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         ship.setVel( ship.velocity[0] - (shipForward[0] * shipAccel * dt), 
                      ship.velocity[1] - (shipForward[1] * shipAccel * dt), 
                      ship.velocity[2] - (shipForward[2] * shipAccel * dt) );
      if (mStrafeRight.getDigitalData() == gk::DigitalInput::DOWN ||
          mStrafeRight.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         ship.setVel( ship.velocity[0] + (shipRight[0] * shipAccel * dt), 
                      ship.velocity[1] + (shipRight[1] * shipAccel * dt), 
                      ship.velocity[2] + (shipRight[2] * shipAccel * dt) );
      
      if (mStrafeLeft.getDigitalData() == gk::DigitalInput::DOWN ||
          mStrafeLeft.getDigitalData() == gk::DigitalInput::EDGE_DOWN)
         ship.setVel( ship.velocity[0] - (shipRight[0] * shipAccel * dt), 
                      ship.velocity[1] - (shipRight[1] * shipAccel * dt), 
                      ship.velocity[2] - (shipRight[2] * shipAccel * dt) );
      
      //////////////
      // GAME LOGIC
      // collisions, roid bounce, removing, etc..
      //////////////


      // do asteroid bounce with the walls of the arena.
      std::vector<Roid>::iterator itr;
      //const float eps = 0.01f;
      for (itr = roids.begin(); itr != roids.end(); ++itr)
      {
         if ((*itr).position[0] > boardSize || (*itr).position[0] < -boardSize)
            (*itr).velocity[0] = -(*itr).velocity[0];
         if ((*itr).position[1] > boardSize || (*itr).position[1] < -boardSize)
            (*itr).velocity[1] = -(*itr).velocity[1];
         if ((*itr).position[2] > boardSize || (*itr).position[2] < -boardSize)
            (*itr).velocity[2] = -(*itr).velocity[2];
      }
      
      // do bounce on the ship with the edges of the arena.
      float outside = 10.0f;// ship can go this much outside the arena before bouncing
      float dampen = 0.8f;// dampen the elastic collision with wall
      if (ship.position[0] > (boardSize+outside) || ship.position[0] < -(boardSize+outside))
         ship.velocity[0] = -ship.velocity[0] * dampen;
      if (ship.position[1] > (boardSize+outside) || ship.position[1] < -(boardSize+outside))
         ship.velocity[1] = -ship.velocity[1] * dampen;
      if (ship.position[2] > (boardSize+outside) || ship.position[2] < -(boardSize+outside))
         ship.velocity[2] = -ship.velocity[2] * dampen;

      // remove projectiles that are too old
      std::vector<Projectile>::iterator pitr;
      std::vector< std::vector<Projectile>::iterator > proj_remove_queue;
      for (pitr = projs.begin(); pitr != projs.end(); ++pitr)
      {
         if ((*pitr).timeToLive != -1 && (*pitr).timeToLive <= 0)
            proj_remove_queue.push_back( pitr );
      }
      x = proj_remove_queue.size();
      while (x--)
         projs.erase( proj_remove_queue[x] );
      
      // do collision between ship and asteroids...
      for (itr = roids.begin(); itr != roids.end(); ++itr)
      {
         // get dist from ship to center of roid (treat roid as sphere for simplicity)
         float dist = Math::distance( ship.position, (*itr).position );
         float min_dist_between_ship_and_roid = ((*itr).size + ship.size);
         
         // if too close, then collision...
         if (dist < min_dist_between_ship_and_roid)
         {
            // get vector from roid to ship (normal to collision angles)
            float normal[3];
            Math::sub( normal, ship.position, (*itr).position );
            Math::norm( normal );

            // reflect velocity only if moving toward each other
            if (Math::dot( ship.velocity, normal ) < 0)
            {
               // compute perfectly elastic reflection
               float reflectionVector[3];
               Math::reflect( reflectionVector, ship.velocity, normal );

               // dampen resulting reflection
               Math::mul( ship.velocity, reflectionVector, dampen );
            }
            
            // asteroids can push the ship around... (affects position)
            float vec[3], newposition[3];
            Math::sub( vec, ship.position, (*itr).position );
            Math::norm( vec );
            Math::mul( vec, vec, min_dist_between_ship_and_roid );
            Math::add( newposition, (*itr).position, vec );
            
            // set the new ship position and velocity
            float additional_velocity_from_impact[3];
            Math::sub( additional_velocity_from_impact, newposition, ship.position );
            Math::add( ship.velocity, ship.velocity, additional_velocity_from_impact );
            Math::copy( ship.position, newposition );            
         }
      }
      
      // do collision between projectile and asteroids...
      for (itr = roids.begin(); itr != roids.end(); ++itr)
      {
         for (pitr = projs.begin(); pitr != projs.end(); ++pitr)
         {
            // get dist from bullet to center of roid (treat roid as sphere for simplicity)
            float dist = Math::distance( (*pitr).position, (*itr).position );
            
            // consider the size of the roid (smaller is harder to hit because the distance will need to be much closer)
            // the dist between object centers should be less than the sum of the two radii 
            if (dist < ((*itr).size + (*pitr).size))
            {
               Roid aster = (*itr); 
               
               // remove the hit asteroid, and the hit projectile
               roids.erase( itr );
               projs.erase( pitr );
                  
               // if it was big enough, replace it with two smaller ones...
               if (aster.size > 0.5f) // .25 is smallest size roid can break into
               {
                  Roid r; 
                  r.size = aster.size / 2.0f;
                  r.setPos( aster.position[0], aster.position[1], aster.position[2] );
                  r.setVel( Math::random() * roidMaxSpeed, 0, Math::random() * roidMaxSpeed );
                  roids.push_back( r );
                  
                  r.setPos( aster.position[0], aster.position[1], aster.position[2] );
                  r.setVel( Math::random() * roidMaxSpeed, 0, Math::random() * roidMaxSpeed );
                  roids.push_back( r );
               }
               
               return; // WARNING: don't put any code after this for loop!
            }       
         }
      }
   }   
      
   // window state
   int width, height;
   int mainWin_contextID;
   
   // game setup (configuration options)
   const int boardSize;
   const float projVelocity, projSize, projTimeToLive;
   const float rotVelocity, shipAccel;
   const float roidSize, roidMaxSpeed;
   const float mousesens;
   
   // ship state
   Ship ship;
   
   // projectile state
   std::vector<Projectile> projs;
   
   // aster-roids state
   std::vector<Roid> roids;

   // other game objects...
   Grid grid;
  
   gk::IGameKernel* mKernel;
   
   gk::AnalogInterface mMouseYaxis;
   gk::DigitalInterface mAccelerate, mBackstep, mRotateLeft, mRotateRight;
   gk::DigitalInterface mFire, mStrafeLeft, mStrafeRight;
};


#endif
