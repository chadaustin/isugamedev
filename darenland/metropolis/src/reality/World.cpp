#include "World.h"

namespace metro
{
	boost::shared_ptr< World > World::mSelf;

	World & World::instance()
	{
		if( mSelf == 0 )
		{
			mSelf = boost::shared_ptr< World >( new World );
		}
		return *mSelf;
	}

	void World::initHardcoded()
	{
		mHexRad = 2;
		//the map is a 21x21 grid
		mMapSize.set(21, 21);

		//go through all the grid points and change stuff
		for( unsigned int i = 0; i < mMapSize[0]; i ++ )
		{
			for( unsigned int j = 0; j < mMapSize[1]; j ++ )
			{
				if(i%2==0 && j%2==0)
				{
					//if coordinates are even, lock the tile
					Lock L;
					L.requestStaticLock(4);
					mLockMap[ Coord2i( i, j ) ] = L ;
				}

				if( i%3==0 && j%3==0 )
				{
					//if coordinates are multiples of 3,
					//lock all edges except the south and north edges
					mEdgeMap[ Coord2i( i, j ) ] = EDGE_ALL ^ EDGE_NORTH ^ EDGE_SOUTH;
				}
			}
		}

		Entity * c = new Character(4);

		c->setPosition(Coord2i(0,0));
		EntityID id = c->getID();
		mEntities[id] = boost::shared_ptr< Entity >(c);
	}

	World::World( void )
	{
	}

	World::~World( void )
	{
	}

	void
	World::addEntity(boost::shared_ptr< Entity > entity)
	{
		gmtl::Point2i position = entity->getPosition();
		EntityID id = entity->getID();
		mEntities[id] = entity;
		mEntityMap.insert(std::make_pair< gmtl::Point2i, EntityID >( position, id ));
	}

	void
	World::removeEntity(EntityID id)
	{
		boost::shared_ptr< Entity > e = mEntities[id];
		mEntityMap.erase(e->getPosition());
		mPathMap.erase(id);
		mEntities.erase(id);
	}

	boost::shared_ptr< Entity >
	World::getEntity(EntityID id)
	{
		if (mEntities.find(id) != mEntities.end())
		{
			return mEntities[id];
		}
		boost::shared_ptr< Entity > empty;
		return empty;
	}
	
	void
	World::cleanup()
	{
		///de-allocate boost::shared_ptrs
		for (EntityItr itr = mEntities.begin(); itr != mEntities.end(); ++itr)
		{
			itr->second.reset();
		}
	}
	
	//draws a hexagon outline, given an edge state, colors open edges green,
	//closed ones red
	//north is negative Z axis, East is positive X axis
	void drawHexEdges( float x, float y, float z, float r, 
			             const EdgeState &edge )
	{
		float cs30 = cos( 30 * DEG_TO_RAD );
		float sn30 = sin( 30 * DEG_TO_RAD );


		glBegin( GL_LINES );

		if( edge & EDGE_SOUTH_EAST )
			glColor4f( 1, 0, 0, 1 );
		else
			glColor4f( 0, 1, 0, 1 );

		glVertex3f( x + r, y, z );
		glVertex3f( x + r * sn30, y, z + r * cs30 );


		if( edge & EDGE_SOUTH )
			glColor4f( 1, 0, 0, 1 );
		else
			glColor4f( 0, 1, 0, 1 );

		glVertex3f( x + r * sn30, y, z + r * cs30 );
		glVertex3f( x - r * sn30, y, z + r * cs30 );


		if( edge & EDGE_SOUTH_WEST )
			glColor4f( 1, 0, 0, 1 );
		else
			glColor4f( 0, 1, 0, 1 );

		glVertex3f( x - r * sn30, y, z + r * cs30 );
		glVertex3f( x - r, y, z );


		if( edge & EDGE_NORTH_WEST )
			glColor4f( 1, 0, 0, 1 );
		else
			glColor4f( 0, 1, 0, 1 );

		glVertex3f( x - r, y, z );
		glVertex3f( x - r * sn30, y, z - r * cs30 );


		if( edge & EDGE_NORTH )
			glColor4f( 1, 0, 0, 1 );
		else
			glColor4f( 0, 1, 0, 1 );

		glVertex3f( x - r * sn30, y, z - r * cs30 );
		glVertex3f( x + r * sn30, y, z - r * cs30 );


		if( edge & EDGE_NORTH_EAST )
			glColor4f( 1, 0, 0, 1 );
		else
			glColor4f( 0, 1, 0, 1 );

		glVertex3f( x + r * sn30, y, z - r * cs30 );
		glVertex3f( x + r, y, z );
		glEnd();
	}

	//just draws a hexagon outline if no edge state is specified
	void drawHexEdges( float x, float y, float z, float r )
	{
		float cs30 = cos( 30 * DEG_TO_RAD );
		float sn30 = sin( 30 * DEG_TO_RAD );


		glBegin( GL_LINE_LOOP );

		glColor4f( 0, 1, 0, 1 );
		glVertex3f( x + r, y, z );
		glVertex3f( x + r * sn30, y, z + r * cs30 );
		glVertex3f( x - r * sn30, y, z + r * cs30 );
		glVertex3f( x - r, y, z );
		glVertex3f( x - r * sn30, y, z - r * cs30 );
		glVertex3f( x + r * sn30, y, z - r * cs30 );

		glEnd();
	}

	//draws a filled hexagon without a lock
	void drawHexFan( float x, float y, float z, float r )
	{
		float cs30 = cos( 30 * DEG_TO_RAD );
		float sn30 = sin( 30 * DEG_TO_RAD );


		glBegin( GL_TRIANGLE_FAN );

		glVertex3f( x, y, z );
		glVertex3f( x + r, y, z );
		glVertex3f( x + r * sn30, y, z + r * cs30 );
		glVertex3f( x - r * sn30, y, z + r * cs30 );
		glVertex3f( x - r, y, z );
		glVertex3f( x - r * sn30, y, z - r * cs30 );
		glVertex3f( x + r * sn30, y, z - r * cs30 );
		glVertex3f( x + r, y, z );

		glEnd();
	}

	//draws filled hexagon, red if locked, grey if open
	void drawHexFan( float x, float y, float z, float r, const Lock &l )
	{
		float cs30 = cos( 30 * DEG_TO_RAD );
		float sn30 = sin( 30 * DEG_TO_RAD );

		if( l.getLockState() != Lock::NO_LOCK )
		{
			glColor4f(0.5,0,0,1);
		}
		else
		{
			glColor4f(0.4,0.4,0.4,1);
		}
		drawHexFan( x, y, z, r );
	}

	void World::updateEntityCoords( EntityID entity, const Coord2i & prevTile, const Coord2i & currentTile )
	{
		//update world's entity map
		std::multimap< Coord2i, EntityID >::iterator prev;

		prev = mEntityMap.find( prevTile );

		if( prev != mEntityMap.end() )
		{
			//make prev point to our location-ID pair
			while( prev->second == entity )
			{
				//if the key changes we've gone too far
				if( prev->first != prevTile )
				{
					prev = mEntityMap.end();
					break;
				}
				++prev;
			}
		}

		if( prev != mEntityMap.end() )
		{
			mEntityMap.erase(prev);
		}

		World::instance().mEntityMap.insert( std::pair< Coord2i, EntityID > ( currentTile, entity ) );
	}

	gmtl::Point3f World::getWorldCoords( const Coord2i & tile )const
	{
		return getWorldCoords( tile[0], tile[1] );
	}
	
	gmtl::Point3f World::getWorldCoords( unsigned int x, unsigned int y )const
	{
		float cs30 = cos( 30 * DEG_TO_RAD );
		float sn30 = sin( 30 * DEG_TO_RAD );
		gmtl::Point3f p( x * ( mHexRad + mHexRad * sn30 ), 0, y * 2 * mHexRad * cs30 );

		//every other collumn is lower
		if( x % 2 == 0 )
		{
			p[ 2 ] -= mHexRad * cs30;
		}
		return p;
	}

	void World::draw( void ) const
	{
		gluLookAt( 5, 80, 10, 5, 0, 5, 0, 1, 0 );
		glColor4f( 0, 1, 0, 1 );
		float cs30 = cos( 30 * DEG_TO_RAD );
		float sn30 = sin( 30 * DEG_TO_RAD );

		glBegin( GL_LINES );
		glColor4f( 1, 0, 0, 1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f( 100, 0, 0 );

		glColor4f( 0, 1, 0, 1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f( 0, 100, 0 );

		glColor4f( 0, 0, 1, 1 );
		glVertex3f( 0, 0, 0 );
		glVertex3f( 0, 0, 100 );
		glEnd();

		//go through all coordinates to draw the grid
		for( unsigned int i = 0; i < mMapSize[0]; ++i )
		{
			for( unsigned int j = 0; j < mMapSize[1]; ++j )
			{

				gmtl::Point3f p=getWorldCoords( i, j );
				//if a lock is found at these coordinates draw a colored hexFan
				std::map< Coord2i, Lock >::const_iterator lock = mLockMap.find( Coord2i( i, j ) );
				if( lock != mLockMap.end() )
				{
					drawHexFan(p[ 0 ],p[ 1 ],p[ 2 ], mHexRad * 0.75, lock->second );
				}
				//otherwise a normal grey hex will do
				else
				{
					glColor4f(0.4,0.4,0.4,1);
					drawHexFan(p[ 0 ],p[ 1 ],p[ 2 ], mHexRad * 0.75);
				}


				//draw on top of the hexFan
				glDisable(GL_DEPTH_TEST);
				//if an edge state is present, draw with all the pretty colors
				std::map< Coord2i, EdgeState >::const_iterator edge = mEdgeMap.find( Coord2i( i, j ) );
				if( edge != mEdgeMap.end() )
				{
					drawHexEdges(p[ 0 ],p[ 1 ],p[ 2 ], mHexRad * 0.75, edge->second );
				}
				//otherwise all green will do
				else
				{
					drawHexEdges(p[ 0 ],p[ 1 ],p[ 2 ], mHexRad * 0.75);
				}
				glEnable(GL_DEPTH_TEST);
			}
		}

	  for( ConstEntityItr itr = mEntities.begin(); itr != mEntities.end(); ++itr)
		{
			gmtl::Point3f p = getWorldCoords(itr->second->getPosition() );
			glTranslatef( p[0], p[1], p[2] );
			itr->second->draw();
		}
	}

	void World::update( float dt )
	{
		for( EntityItr itr = mEntities.begin(); itr != mEntities.end(); ++itr)
		{
			itr->second->update( dt );
		}
	}
}
