#ifndef _METRO_WORLD_H_
#define _METRO_WORLD_H_

#include "Includes.h"
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
		static World & instance();
		~World( void );
		void draw( void ) const;
		void update( float dt );
		void initHardcoded();

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
		World( void );
		static boost::shared_ptr< World > mSelf;

		//defines bottom right corner of grid + (1,1), the max size of the map
		gmtl::Point2i mMapSize;
		
		//radius size of hexagon
		float mHexRad;


		//or however we want to store the entities
		std::vector < Entity * > mEntityList;
	};
}

#endif

