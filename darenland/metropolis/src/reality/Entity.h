#ifndef _METRO_ENTITY_H_
#define _METRO_ENTITY_H_

#include "Includes.h"
#include "EntityID.h"
#include "boost/shared_ptr.hpp"
#include "Coord2i.h"

namespace metro
{
	class World;
	class Entity
	{
	public:
		/**
		 * Default Ctor
		 */
		Entity( const EntityID& id );

		/**
		 * Copy Ctor
		 */
		Entity( const Entity &src );

		/**
		 * Dtor
		 */
		virtual ~Entity();

		/**
		 * Returns the pointer to a newly created Entity
		 * 
		 * @return 	(Entity*)(new ChildClass(*this));
		 */
		virtual boost::shared_ptr< Entity > clone( void ) const = 0;

		/**
		 * openGL calls to display the object in local coordinates
		 */
		virtual void draw( void ) const = 0;

		/**
		 * called in preframe, gets a delta time in seconds
		 *
		 * @param	dt	delta time in seconds
		 */
		virtual void update( float dt ) = 0;

		/**
		 * returns a string describing the type of the entity class.
		 *
		 * @return  i.e. string("Enemy")
		 */
		virtual std::string getType( void ) const = 0;

		EntityID getID( void ) const;

		//TODO: this should probably go into a 'movable' or 'locational' class
		virtual Coord2i getPos()const;
		virtual void setPos(const Coord2i & p);

	protected:
		Coord2i pos;
		///the unique identifier of this entity
		EntityID mId;
	};
}

#endif
