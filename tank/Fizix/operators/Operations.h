#ifndef _OPERATIONS_H
#define _OPERATIONS_H

#include <ColorRGBA.h>
#include <vector>

namespace ani
{


// using the time to live, kill the particle when expired
template<class __EntityType>
class GrimReaper : public ani::Operator<__EntityType>
{
public:
   GrimReaper() : ani::Operator<__EntityType>() {}
   virtual ~GrimReaper() {}
   virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta );
};

// as it gets older, color it
template<class __EntityType>
class ColorWithAge : public ani::Operator<__EntityType>
{
public:
   ColorWithAge() : ani::Operator<__EntityType>()
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
   virtual void exec( DynamicSystem<__EntityType>& ps, float timeDelta );

   std::vector<ColorRGBA> mColorTransitions;
};

// change size as it grows older
template<class __EntityType>
class GrowWithAge : public ani::Operator<__EntityType>
{
public:
   GrowWithAge() : ani::Operator<__EntityType>()
   {
      mSizeTransitions.push_back( 1.0f );
      mSizeTransitions.push_back( 0.75f );
      mSizeTransitions.push_back( 0.50f );
      mSizeTransitions.push_back( 0.0f );
   }
   virtual ~GrowWithAge() {}
   void setVolumes( std::vector<float> sizeTransitions ) { mSizeTransitions = sizeTransitions; }
   virtual void exec(  DynamicSystem<__EntityType>& ps, float timeDelta );

   std::vector<float> mSizeTransitions;
};

} // end namespace

#endif
