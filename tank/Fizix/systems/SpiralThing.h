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
         solver->deref();

         // operations
         SpiralEmitter* se = new SpiralEmitter;
         se->setEmissionRate( 0.08 );
         this->add( se );
         Gravity* gravity = new Gravity;
         this->add( gravity );
         GrimReaper* reaper = new GrimReaper;
         this->add( reaper );
         ColorWithAge* cwa = new ColorWithAge;
         cwa->setColors( colorTransitions );
         this->add( cwa );

         GrowWithAge* gwa = new GrowWithAge;
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

         gwa->deref();
         gravity->deref();
         reaper->deref();
         cwa->deref();
         se->deref();
      }
   
};



