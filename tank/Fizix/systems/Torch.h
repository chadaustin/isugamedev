

#include "ParticleSystem.h"
#include "EulerODEsolver.h"
#include "ModifiedEulerODEsolver.h"
#include "RungeKuttaODEsolver.h"
#include "HeunODEsolver.h"
#include "Force.h"
#include "Emitter.h"

#include "stdlib.h"
#include <vector>


class Torch : public ParticleSystem
{
public:
      Torch() : ParticleSystem()
      {
         // colors
         std::vector<ColorRGBA> colorTransitions;
         ColorRGBA a;
         a.setInteger( 0, 0, 181, 255 );
         colorTransitions.push_back( a );
      
         a.setInteger( 249, 188, 0, 255 );
         colorTransitions.push_back( a );

         a.setInteger( 249, 188, 0, 255 );
         colorTransitions.push_back( a );

         a.setInteger( 249, 117, 10, 255 );
         colorTransitions.push_back( a );

         a.setInteger( 155, 29, 29, 255 );
         colorTransitions.push_back( a );
         
         a.setInteger( 155, 29, 29, 255 );
         colorTransitions.push_back( a );
         
         a.setInteger( 131, 129, 155, 255 );
         colorTransitions.push_back( a );

         a.setInteger( 131, 129, 155, 255 );
         colorTransitions.push_back( a );

         a.setInteger( 131, 129, 155, 200 );
         colorTransitions.push_back( a );

         a.setInteger( 131, 129, 155, 128 );
         colorTransitions.push_back( a );

         a.setInteger( 131, 129, 155, 0 );
         colorTransitions.push_back( a );

         /*
         SpritesRenderer<glRenderParticleAsSprite>* psr = new SpritesRenderer<glRenderParticleAsSprite>;
         psr->mapName = "fire.tga";
         this->setRenderFunc( psr );
         psr->deref();
         */

         //////////////////
         ODEsolver* solver = new EulerODEsolver;
         this->setSolver( solver );
         solver->deref();

         // operations
         ViscousDrag* drag = new ViscousDrag;
         drag->setDrag( 0.40f ); // ??
         this->add( drag );
         
         FlameEmitter* fe = new FlameEmitter;
         fe->setSize( 2.5f );
         fe->setAgeOfDeath( 2.3f );
         fe->setEmissionRate( 0.014 );
         this->add( fe );
         
         GrimReaper* reaper = new GrimReaper;
         this->add( reaper );
         
         Current* cur = new Current;
         cur->setSpeed( Vec3<float>( -1,0,0 ) );
         this->add( cur );

         ColorWithAge* cwa = new ColorWithAge;
         cwa->setColors( colorTransitions );
         this->add( cwa );

         GrowWithAge* gwa = new GrowWithAge;
         std::vector<float> sizes;
         sizes.push_back( 2.5f );
         sizes.push_back( 5.0f );
         sizes.push_back( 10.0f );
         gwa->setVolumes( sizes );
         this->add( gwa );

         //drag->deref();
         cur->deref();
         gwa->deref();
         reaper->deref();
         cwa->deref();
         fe->deref();
      }

      std::vector<std::string> texname;
      std::vector<Texture>     texture;
};
