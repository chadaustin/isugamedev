#ifndef PS_OPERATOR_H
#define PS_OPERATOR_H

#include "ParticleSystemMemory.h"
#include <ColorRGBA.h>
#include <vector>

// using the time to live, kill the particle when expired
class GrimReaper : public PsOperator
{
public:
   GrimReaper() : PsOperator() {}
   virtual ~GrimReaper() {}
   virtual void operator() (ParticleSystem& ps );
};

// as it gets older, color it
class ColorWithAge : public PsOperator
{
public:
   ColorWithAge() : PsOperator()
   {
      // set some default colors to cycle through
      ColorRGBA a;
      a.set( 1.0f, 0.0f, 0.0f, 1.0f );
      mColorTransitions.push_back( a );
      
      a.set( 0.0f, 1.0f, 0.0f, 0.7f );
      mColorTransitions.push_back( a );

      a.set( 0.0f, 0.0f, 1.0f, 0.3f );
      mColorTransitions.push_back( a );
   }
   virtual ~ColorWithAge() {}
   
   // colors to interpolate between
   void setColors( std::vector<ColorRGBA>& colorTransitions ) { mColorTransitions = colorTransitions; }
   virtual void operator() (ParticleSystem& ps );

   std::vector<ColorRGBA> mColorTransitions;
};

// change size as it grows older
class GrowWithAge : public PsOperator
{
public:
   GrowWithAge() : PsOperator()
   {
      mSizeTransitions.push_back( 1.0f );
      mSizeTransitions.push_back( 0.75f );
      mSizeTransitions.push_back( 0.50f );
      mSizeTransitions.push_back( 0.0f );
   }
   virtual ~GrowWithAge() {}
   void setVolumes( std::vector<float> sizeTransitions ) { mSizeTransitions = sizeTransitions; }
   virtual void operator() ( ParticleSystem& ps );

   std::vector<float> mSizeTransitions;
};
#endif
