#ifndef PARTICLE_SYSTEM_RENDER
#define PARTICLE_SYSTEM_RENDER

#include <string>

#include <list>
#include <algorithm>
#include <functional>
#include <boost/smart_ptr.hpp>
template <class __Entity>
class RenderDynamicSystem
{
public:
   typedef boost::shared_ptr<__Entity> EntityPtr;

public:
   RenderDynamicSystem() : pr( NULL ) {}

   class EntityRender
   {
   public:
      virtual void render( const __Entity& p, bool uselocalXform, const Matrix4f& localXform, int context = 0 ) const = 0;
   };
   
   // Allows for the comparison of projected point distances
   // onto a given vector
   // NOTE: For use with std::sort or std::stable_sort
   struct ComparePointProjectionsAlongDirection
   {
   public:
      ComparePointProjectionsAlongDirection() : sortDir() {}
   
      bool operator()(const EntityPtr& x, const EntityPtr& y)
      {
         float xVal = sortDir.dot(x->position());
         float yVal = sortDir.dot(y->position());

         return (xVal < yVal); // true if x precedes y in back-to-front sortDir rendering order.
      }

      Vec3<float> sortDir;       // Direction to sort by
   };

   inline void render( const ani::DynamicSystem<__Entity>& dyns, const Matrix4f& cameraMat, bool sort, bool uselocalXform, int context = 0 ) const
   {
      std::vector<EntityPtr> ds = dyns.entities();
      if (sort)
      {
         // get camera's direction
         ComparePointProjectionsAlongDirection particle_sorter;
         Matrix4f camera_rot;
         cameraMat.getRotScale( camera_rot );
         particle_sorter.sortDir = camera_rot * Vec3<float>( 0.0f, 0.0f, 1.0f );
         particle_sorter.sortDir.normalize();
         
         // sort the particles (which could be transparent) based on projection information
         std::sort( ds.begin(), ds.end(), particle_sorter );
      }

      // render the sprites (which are now in back-to-front order)
      std::vector<EntityPtr>::const_iterator particleIt;
      Matrix4f localXform;
      localXform.makeIdent();
      for (particleIt = ds.begin(); particleIt != ds.end(); ++particleIt)
      {
         __Entity& p = *(*particleIt);
         
         // set the position/orientation of the sprite
         // offset == sprite xform...
         if (uselocalXform)
         {
            //offset.setTrans( p.position() );
            localXform.setRot( cameraMat );
         }

         assert( pr != NULL && "you must call RenderDynamicSystem::setRender() before calling render" );
         pr->render( p, uselocalXform, localXform, context );
      }
   }

   // you must set this!
   void setRender( EntityRender* r )
   {
      if (pr != NULL) delete pr;
      pr = r;
   }
   EntityRender* pr; 
};



#endif


