#ifndef _METRO_WORLD_H_
#define _METRO_WORLD_H_

#include "Includes.h"
#include "EdgeState.h"
#include "Character.h"		//for the Playa'
#include "Lock.h"
#include "Coord2i.h"

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
		EdgeState getEdgeState( const Coord2i & tile )const;
		void setEdgeState( const Coord2i & tile );
		Lock getLock( const Coord2i & tile )const;
		
		//returns the openGL world coordinates of a tile
		gmtl::Point3f getWorldCoords( const Coord2i & tile )const;
		gmtl::Point3f getWorldCoords( unsigned int x, unsigned int y )const;
		
		//keeps the entity map coordinates up to date, 
		//should be called by the move handler
		void updateEntityCoords( EntityID entity, const Coord2i & prevTile, const Coord2i & currentTile );

		//public for testing purposes
		std::map < Coord2i, EdgeState > mEdgeMap;
		std::map < Coord2i, Lock > mLockMap;
		std::multimap < Coord2i, EntityID > mEntityMap;
		std::map < EntityID, std::vector< Coord2i > > mPathMap;

	private:
		World( void );
		static boost::shared_ptr< World > mSelf;

		//defines bottom right corner of grid + (1,1), the max size of the map
		Coord2i mMapSize;
		
		//radius size of hexagon
		float mHexRad;


		//or however we want to store the entities
		std::vector < Entity * > mEntityList;
	};
}

#endif

