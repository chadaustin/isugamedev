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










template <class __EntityType>
void GrimReaper<__EntityType>::exec(  DynamicSystem<__EntityType>& ps, float timeDelta )
{
   std::vector<__EntityType*>& psList = ps.entities();
   std::vector<__EntityType*>::iterator it;
   std::list< std::vector<__EntityType*>::iterator > deadList;
   for (it = psList.begin(); it != psList.end(); ++it)
   {
      // age the particle
      __EntityType& p = *(*it);
      p.growOlder( ps.timeDelta() );

      // if the particle is dead, then queue it for removal...
      if (p.age() >= p.ageOfDeath() && p.ageOfDeath() >= 0.0f)
      {
         deadList.push_back( it );
      }
   }

   // now delete the dead ones...
   std::list< std::vector<__EntityType*>::iterator >::reverse_iterator deadListIt;
   for (deadListIt = deadList.rbegin(); deadListIt != deadList.rend(); ++deadListIt)
   {
      //ps.remove( (*deadListIt) );

      __EntityType* p = *(*deadListIt);
      p->isInSystem( false );
      ps.system().erase( (*deadListIt) );
      p->unrefDelete();
   }
}

template <class __EntityType>
void ColorWithAge<__EntityType>::exec(  DynamicSystem<__EntityType>& ps, float timeDelta )
{
   std::vector<__EntityType*>::iterator it;
   for (it = ps.entities().begin(); it != ps.entities().end();
   ++it)
   {
      __EntityType& p = *(*it);
      float age__zero_to_one = p.age() / p.ageOfDeath();

      // find the range that we'll examine... range = {0...(size-1)} so that we can always check i and i+1
      // NOTE: range will at least be 0, since size >= 1
      assert( mColorTransitions.size() > 0 && "to use this operator, you must define some colors" );
      float range = (float)mColorTransitions.size() - 1.0f; 
      
      // the indices of the two colors to interpolate between 
      float indexf = age__zero_to_one * range;
      int index = indexf;
      int next_index = (index+1 != mColorTransitions.size()) ? index+1 : (mColorTransitions.size() - 1);
      assert( index >= 0 && next_index < mColorTransitions.size() && "out of bounds" );
      
      // find the value to interpolate this color with the next color (should be 0..1)
      float val = indexf - (float)index;

      ColorRGBA color;
      color.Lerp( mColorTransitions[index], mColorTransitions[next_index], val );
      
      //color.setHSV( rel, 0.8f, 1.0f );
      p.setColor( color );
   }
}


template <class __EntityType>
void GrowWithAge<__EntityType>::exec(  DynamicSystem<__EntityType>& ps, float timeDelta )
{
   std::vector<__EntityType*>::iterator it;
   for (it = ps.entities().begin(); it != ps.entities().end(); ++it)
   {
      __EntityType& p = *(*it);
      float age__zero_to_one = p.age() / p.ageOfDeath();

      // find the range that we'll examine... range = {0...(size-1)} so that we can always check i and i+1
      // NOTE: range will at least be 0, since size >= 1
      assert( mSizeTransitions.size() > 0 && "to use this operator, you must define some colors" );
      float range = (float)mSizeTransitions.size() - 1.0f; 
      
      // the indices of the two colors to interpolate between 
      float indexf = age__zero_to_one * range;
      int index = indexf;
      int next_index = (index+1 != mSizeTransitions.size()) ? index+1 : (mSizeTransitions.size() - 1);
      assert( index >= 0 && next_index < mSizeTransitions.size() && "out of bounds" );
      
      // find the value to interpolate this color with the next color (should be 0..1)
      float val = indexf - (float)index;

      float result;
      kev::lerp( mSizeTransitions[index], mSizeTransitions[index+1], val, result );
      
      p.setVolume( Vec3<float>( result, result, result ) );
   }
}


} // end namespace

#endif
