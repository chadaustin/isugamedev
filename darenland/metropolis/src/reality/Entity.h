#ifndef _METRO_ENTITY_H_
#define _METRO_ENTITY_H_

#include "Includes.h"
#include "EntityID.h"
#include "boost/shared_ptr.hpp"
#include "gmtl/Point.h"
#include "PointOps.h"		///For the gmtl::Point comparison operators.

namespace metro
{
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

		/**
		 * Returns the Unique ID of this entity
		 *
		 * @return	the UID of this entity
		 */
		EntityID getID( void ) const;

		/**
		 * Returns the current position of this entity
		 *
		 * @return	the current position of this entity
		 */
		virtual gmtl::Point2i getPosition()const;

		/**
		 * Sets the current position of this entity
		 *
		 * @param	pos		the new position for the entity
		 */
		virtual void setPosition(const gmtl::Point2i & p);

	protected:

		///the current position of this entity
		gmtl::Point2i mPosition;
		
		///the unique identifier of this entity
		EntityID mId;
	};
}

#endif
