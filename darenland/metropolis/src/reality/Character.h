#ifndef _METRO_CHARACTER_H_
#define _METRO_CHARACTER_H_

#include "Includes.h"
#include "Entity.h"		//for inheritance
#include "EntityID.h"

namespace metro
{
	class World;	//prevent circular includes
	class Character : public Entity
	{
	public:
		Character( const EntityID& id );
		Character( const Character &src );
		virtual ~Character( void );

		//draws a teapot for now
		virtual void draw( void ) const;
		virtual void update( float dt );
		virtual boost::shared_ptr< Entity > clone( void ) const;
		virtual std::string getType( void ) const;
	};
}
#endif
