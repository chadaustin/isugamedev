#include "PointOps.h"

namespace gmtl
{
	bool operator<( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b )
	{
		if(a[0]==b[0])
		{
			return a[1]<b[1];
		}
		return a[0]<b[0];
	}

	bool operator>( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b )
	{
		if(a[0]==b[0])
		{
			return a[1]>b[1];
		}
		return a[0]>b[0];
	}

	bool operator<=( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b )
	{
		return( a<b || a==b ) ;
	}

	bool operator>=( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b )
	{
		return( a>b || a==b ) ;
	}

	bool operator==( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b )
	{
		return (a[0]==b[0] && a[1]==b[1]);
	}

	bool operator!=( const gmtl::Point<int,2> &a, const gmtl::Point<int,2> &b )
	{
		return !(a==b);
	}
}
