#include "ParticleSystem.h"
#include "PsOperator.h"

void GrimReaper::operator() (ParticleSystem& ps )
{
   std::vector<Particle*>& psList = ps.particles();
   std::vector<Particle*>::iterator it;
   std::list< std::vector<Particle*>::iterator > deadList;
   for (it = psList.begin(); it != psList.end(); ++it)
   {
      // age the particle
      Particle& p = *(*it);
      p.growOlder( ps.timeDelta() );

      // if the particle is dead, then queue it for removal...
      if (p.age() >= p.ageOfDeath() && p.ageOfDeath() >= 0.0f)
      {
         deadList.push_back( it );
      }
   }

   // now delete the dead ones...
   std::list< std::vector<Particle*>::iterator >::reverse_iterator deadListIt;
   for (deadListIt = deadList.rbegin(); deadListIt != deadList.rend(); ++deadListIt)
   {
      ps.remove( (*deadListIt) );
      //psList.erase( (*deadListIt) );
   }
}

void ColorWithAge::operator() (ParticleSystem& ps )
{
   std::vector<Particle*>::iterator it;
   for (it = ps.particles().begin(); it != ps.particles().end();
   ++it)
   {
      Particle& p = *(*it);
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


void GrowWithAge::operator() (ParticleSystem& ps )
{
   std::vector<Particle*>::iterator it;
   for (it = ps.particles().begin(); it != ps.particles().end(); ++it)
   {
      Particle& p = *(*it);
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
      kev::Lerp( mSizeTransitions[index], mSizeTransitions[index+1], val, result );
      
      p.setVolume( result );
   }
}
















