#ifndef _METRO_WORLD_H_
#define _METRO_WORLD_H_

#include "Includes.h"
#include "EntityID.h"
#include "Entity.h"
#include "EdgeState.h"
#include "Character.h"		//for the Playa'
#include "Lock.h"
#include <gmtl/Point.h>
#include "PointOps.h"		//for the gmtl::Point comparison operators

namespace metro
{
	/**
	 * The world is a mediator between each of the components contained inside
	 * the main game.
	 */
	class World
	{
	public:
		
		~World( void );

		/**
		 * This class is a Singleton; you get access to it through this function
		 *
		 * @return		the single instance of this class
		 */
		static World & instance();


		
		void draw( void ) const;
		void update( float dt );

		/**
		 * Initializes the world using the early test data?
		 */
		void initHardcoded();

		/**
		 * Adds an entity to the world.
		 *
		 * @param	entity		the entity to add
		 */
		void addEntity( boost::shared_ptr< Entity > entity );

		/**
		 * Removes an entity from the world
		 *
		 * @param	id				the id of the entity to remove
		 */
		void removeEntity( EntityID id );
		
		/**
		 * Gets an entity from the world
		 * 
		 * @param	id				the id of the entity to retrieve
		 *
		 * @return		the entity with the given id, or an empty boost::shared_ptr
		 * 			   if the id doesn't exist.
		 */
		boost::shared_ptr< Entity > getEntity( EntityID id );
		
		//access to lock and edge state information
		//TODO:  Implement these.
		EdgeState getEdgeState( const gmtl::Point2i & tile )const;
		void setEdgeState( const gmtl::Point2i & tile );
		Lock getLock( const gmtl::Point2i & tile )const;
		
		//returns the openGL world coordinates of a tile
		gmtl::Point3f getWorldCoords( const gmtl::Point2i & tile )const;
		gmtl::Point3f getWorldCoords( unsigned int x, unsigned int y )const;
		
		//keeps the entity map coordinates up to date, 
		//should be called by the move handler
		void updateEntityCoords( EntityID entity, const gmtl::Point2i & prevTile, const gmtl::Point2i & currentTile );

		//public for testing purposes
		std::map < gmtl::Point2i, EdgeState > mEdgeMap;
		std::map < gmtl::Point2i, Lock > mLockMap;
		std::multimap < gmtl::Point2i, EntityID > mEntityMap;
		std::map < EntityID, std::vector< gmtl::Point2i > > mPathMap;
	
	private:

		/**
		 * This class is a singleton; you must use instance() to access it.
		 */
		World( void );

		World( const World& src );

		World& operator=( const World& rhs );
		
		///the sole instance of this class
		static boost::shared_ptr< World > mSelf;

		//defines bottom right corner of grid + (1,1), the max size of the map
		gmtl::Point2i mMapSize;
		
		//radius size of hexagon
		float mHexRad;

		///the entities
		std::map < EntityID, boost::shared_ptr< Entity > > mEntities;
		
		///simplification
		typedef std::map< gmtl::Point2i, EdgeState >::iterator EdgeItr;
		typedef std::map< gmtl::Point2i, Lock >::iterator LockItr;
		typedef std::map< EntityID, std::vector< gmtl::Point2i > >::iterator PathItr;
		typedef std::map< EntityID, boost::shared_ptr< Entity > >::iterator EntityItr;
		typedef std::map< EntityID, boost::shared_ptr< Entity > >::const_iterator ConstEntityItr;
	};
}

#endif

