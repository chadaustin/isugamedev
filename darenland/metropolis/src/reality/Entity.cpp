#include "Entity.h"
#include "World.h"

namespace metro
{
	Entity::Entity( const EntityID& id )
		: mId( id )
	{}

	Entity::Entity( const Entity &src )
	{}

	Entity::~Entity( void )
	{}

	EntityID Entity::getID( void ) const
	{
		return mId;
	}

	void Entity::setPos( const Coord2i & p )
	{
		//TODO: move to moveHandler
		World::instance().updateEntityCoords( mId, pos, p );
		pos=p;
	}

	Coord2i Entity::getPos()const
	{
		return pos;
	}
}
