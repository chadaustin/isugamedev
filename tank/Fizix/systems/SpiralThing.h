#include "Emitter.h"

class SpiralThing : public ParticleSystem
{
public:
      SpiralThing() : ParticleSystem()
      {
         // colors
         std::vector<ColorRGBA> colorTransitions;
         ColorRGBA a;
         a.setInteger( 255, 255, 255, 255 );
         colorTransitions.push_back( a );
      
         a.setInteger( 0, 0, 255, 255 );
         colorTransitions.push_back( a );

         a.setInteger( 100, 255, 100, 255 );
         colorTransitions.push_back( a );

         a.setInteger( 131, 129, 155, 189 );
         colorTransitions.push_back( a );


         // solver
         ODEsolver* solver = new EulerODEsolver;         // 1st order
         this->setSolver( solver );

         // operations
         SpiralEmitterPtr se( new SpiralEmitter );
         se->setEmissionRate( 0.08 );
         this->add( se );
         GravityPtr gravity( new Gravity );
         this->add( gravity );
         GrimReaperPtr reaper( new GrimReaper );
         this->add( reaper );
         ColorWithAgePtr cwa( new ColorWithAge );
         cwa->setColors( colorTransitions );
         this->add( cwa );

         GrowWithAgePtr gwa( new GrowWithAge );
         std::vector<float> v;
         v.push_back( 1.0f );
         v.push_back( 5.0f );
         v.push_back( 10.0f );
         v.push_back( 12.5f );
         v.push_back( 15.0f );
         v.push_back( 17.5f );
         v.push_back( 20.0f );
         v.push_back( 100.0f );
         gwa->setVolumes( v );
         this->add( gwa );
      }
   
};



