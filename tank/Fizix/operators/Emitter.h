#ifndef EMITTERS
#define EMITTERS

#include "Defines.h"
#include "Fizix/Operator.h"
#include "Fizix/DynamicSystem.h"

namespace ani
{
   
template<class __EntityType>
class Emitter : public ani::Operator<__EntityType>
{
public:
   Emitter() : mAgeOfDeath( 2 ), mRate( 0.1 ) {}
   virtual ~Emitter() {}
   void setEmissionRate( const float& rate ) { mRate = rate; }      
   void setAgeOfDeath( float aod )
   {
      mAgeOfDeath = aod;
   }

   float mAgeOfDeath;
   float mRate;
};

template<class __EntityType>
class FlameEmitter : public Emitter<__EntityType>
{
public:
   FlameEmitter() : kRandMax( RAND_MAX ), x(0), velocitizer(0), Emitter<__EntityType>(), mSize( 8 ) { srand( 2); }
   virtual ~FlameEmitter() {}
   void setPos( const Vec3<float>& pos )
   {
      mPos = pos;  
   }   
   void setSize( float size ) { mSize = size; }
   virtual void exec( DynamicSystem<__EntityType>& sys, float timeDelta )
   {
      for (x += sys.timeDelta(); x > mRate; x -= mRate )
      {
         __EntityType* p = new __EntityType;
         p->ref();
         p->setMass( 1.0f ); // 1 kilogram
         float r1 = rand(), r2 = rand(), r3, r4 = rand(), r5 = rand();
         r1 /= kRandMax;
         r2 /= kRandMax;
         r4 /= kRandMax;
         r5 /= kRandMax;
         r3 = (r1 + r2) * 0.5f;

         // compute random position within the space.
         float posx = -mSize * 0.5f + r4 * mSize;
         float posz = -mSize * 0.5f + r5 * mSize;

         // make the velocity increase in the middle.
         float vely = 1.0f - kev::MIN( kev::ABS(posx / mSize), kev::ABS(posz / mSize) );
         const float multifactor = 3.0f;

         float velx = r1 * 2.0f - 1.0f;
         float velz = r2 * 2.0f - 1.0f;
         Vec3<float> velocity( velx, (r3 * 1.0f + 3.8f) * (vely * multifactor), velz );

         Vec3<float> position( posx + mPos[0], 0.0f + mPos[1], posz + mPos[2] );
         ColorRGBA color( 0.0f, 0.0f, 0.0f, 1.0f );
         p->setVelocity( velocity );
         p->setPosition( position );
         p->setColor( color );
         p->setAgeOfDeath( mAgeOfDeath );
         sys.add( p );
         p->unrefDelete(); // give up responsibility of this object.
      }

      if (x < 0) x = 0;
   }

   float x;
   float velocitizer;
   const float kRandMax;
   float mSize;
   Vec3<float> mPos;
};

template<class __EntityType>
class SpiralEmitter : public Emitter<__EntityType>
{
public:
   SpiralEmitter() : velocitizer(0), Emitter<__EntityType>(), x(0), pos( 0,0,0 ) {}
   virtual ~SpiralEmitter() {}
   void setPosition( float x, float y, float z )
   {
      pos.set( x, y, z );
   }   

   virtual void exec( DynamicSystem<__EntityType>& sys )
   {
      for (x += sys.timeDelta(); x > mRate; x -= mRate )
      {
   velocitizer += 0.75f * ps.timeDelta();
   if (velocitizer > 1.0f || velocitizer <= 0)
      velocitizer = 0.0f;
   __EntityType* p = new __EntityType;
   p->ref();
   p->setMass( 1.0f ); // 1 kilogram
   Vec3<float> velocity( kev::SIN( velocitizer * TWO_PI_F ) * 5.0f, 19.6f, kev::COS( velocitizer * TWO_PI_F ) * 5.0f );
         ColorRGBA color( 0.3f, 0.2f, 1.0f, 1.0f );
         p->setVelocity( velocity );
         p->setPosition( pos );
         p->setColor( color );
   p->setAgeOfDeath( 10 );
         sys.add( p );
   p->unrefDelete(); // give up responsibility of this object.
      }

      if (x < 0) x = 0;
   }

   float x;
   float velocitizer;
   Vec3<float> pos;
};


} // end namespace

#endif
