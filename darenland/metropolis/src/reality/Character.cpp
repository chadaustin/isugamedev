#include "Character.h"
#include "World.h"	//here to prevent circular includes

namespace metro
{
	Character::Character( const EntityID& id ) :
		Entity( id )
	{
	}

	Character::Character( const Character& src ) :
		Entity( src )
	{
	}

	Character::~Character( void )
	{
	}

	void Character::draw( void ) const
	{
		glColor4f( 1, 0, 0, 0.5 );
		glutSolidTeapot( 1 );
	}

	void Character::update( float dt )
	{
		//  0.5% of chance to move
		if( float(rand())/RAND_MAX * 1000 < 5 )
		{
			setPos( Coord2i( pos + Coord2i( 1 , 1 ) ) );
		}
	}

	boost::shared_ptr< Entity > Character::clone( void ) const
	{
		return boost::shared_ptr< Entity >( new Character( *this ) );
	}

	std::string Character::getType( void ) const
	{
		return std::string( "Character" );
	}

}
