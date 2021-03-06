#ifndef _METRO_POINT_OPS_H_
#define _METRO_POINT_OPS_H_

#include <gmtl/Point.h>

namespace gmtl
{
	bool operator<( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b );
	bool operator>( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b );
	bool operator<=( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b );
	bool operator>=( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b );
	bool operator==( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b );
	bool operator!=( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b );
}

namespace metro
{
	typedef gmtl::Point<int,2> Coord2i;
}

#endif


