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

	void Entity::setPosition( const Coord2i & p )
	{
		//TODO: move to moveHandler
		World::instance().updateEntityCoords( mId, mPosition, p );
		mPosition = p;
	}

	Coord2i Entity::getPosition()const
	{
		return mPosition;
	}
}
