

#include <ColorRGBA.h>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr_dyncast.hpp>

#include "Fizix/Particle.h"
#include "Fizix/Body.h"
#include "Fizix/DynamicSystem.h"

#include "Fizix/Operator.h"
#include "Fizix/operators/Emitter.h"
#include "Fizix/operators/Force.h"
#include "Fizix/operators/Operations.h"

#include "stdlib.h"
#include <vector>

namespace ani
{
   
// TODO: change to particle, not body
class FireParticle : public ani::Body//ani::Particle
{
public:
   FireParticle() : mAge(0), mAgeOfDeath(0)
   {
      this->setParticle( true );
   }
   
   const ColorRGBA& color() const { return mColor; }
   void setColor( const ColorRGBA& color ) { mColor = color; }
   void setAgeOfDeath( float age ) { mAgeOfDeath = age; }
   float ageOfDeath() const { return mAgeOfDeath; }
   float age() const { return mAge; }
   void growOlder( float age ) { mAge += age; }
   float mAge, mAgeOfDeath;
   ColorRGBA mColor;
};

template<class __EntityType = FireParticle>
class Torch : public ani::DynamicSystem<__EntityType>
{
public:
      Torch() : ani::DynamicSystem<__EntityType>()
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
         psr->unrefDelete();
         */

         this->setSolver( "euler" );

         // operations
         boost::shared_ptr< ViscousDrag<__EntityType> > drag( new ViscousDrag<__EntityType> );
         drag->setDrag( 0.40f ); // ??
         this->add( sp_dynamic_cast< ani::Operator<__EntityType> >( drag ) );
         
         fe.reset( new FlameEmitter<__EntityType> );
         fe->setSize( 2.5f );
         fe->setAgeOfDeath( .3f );
         fe->setEmissionRate( 0.014 );
         this->add( sp_dynamic_cast< ani::Operator<__EntityType> >( fe ) );
         
         boost::shared_ptr< GrimReaper<__EntityType> > reaper( new GrimReaper<__EntityType> );
         this->add( sp_dynamic_cast< ani::Operator<__EntityType> >( reaper ) );
         
         boost::shared_ptr< Current<__EntityType> > cur( new Current<__EntityType> );
         cur->setSpeed( Vec3<float>( -1,0,0 ) );
         this->add( sp_dynamic_cast< ani::Operator<__EntityType> >( cur ) );

         boost::shared_ptr< ColorWithAge<__EntityType> > cwa( new ColorWithAge<__EntityType> );
         cwa->setColors( colorTransitions );
         this->add( sp_dynamic_cast< ani::Operator<__EntityType> >( cwa ) );

         boost::shared_ptr< GrowWithAge<__EntityType> > gwa( new GrowWithAge<__EntityType> );
         std::vector<float> sizes;
         sizes.push_back( 2.5f );
         sizes.push_back( 5.0f );
         sizes.push_back( 10.0f );
         gwa->setVolumes( sizes );
         this->add( sp_dynamic_cast< ani::Operator<__EntityType> >( gwa ) );
      }
      
      void setPos( const Vec3<float>& pos )
      {
         fe->setPos( pos );
      }      
      
      boost::shared_ptr< FlameEmitter<__EntityType> > fe;
};


} // end of namespace..
