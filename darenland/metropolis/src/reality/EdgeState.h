#ifndef _METRO_HEX_H_
#define _METRO_HEX_H_

#include "Includes.h"

namespace metro
{
 	//bit flags for defining which hex edges are blocked for movement
	//when EDGE_NORTH is 1, passage to north is closed
	enum EdgeFlag
	{
		EDGE_NONE = 0,
		EDGE_NORTH = 1,
		EDGE_SOUTH = 2,
		EDGE_NORTH_EAST = 4,
		EDGE_NORTH_WEST = 8,
		EDGE_SOUTH_EAST = 16,
		EDGE_SOUTH_WEST = 32,
		EDGE_ALL = 63
	};

	//bit field for all the edge flags
	typedef char EdgeState;
}

#endif
