
//////////////////////////////////////////////////////////////////
//
//                         -=     Vec2<type>     =-
//
// Definition: "a 3D 32 bit vector"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Vec2.h,v $
//    $Date: 2002-01-11 16:18:25 $
//    $Revision: 1.3 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////

////
#ifndef VEC2__INCLUDED
#define VEC2__INCLUDED

//#include "Defines.h"

template <class _dataType>
class Vec2
{
protected:

	_dataType _v[2];

public:

	Vec2(){ _v[0] = 0.0f; _v[1] = 0.0f; }
	Vec2( const Vec2<_dataType>& vec );
	Vec2( const _dataType vec[2] );
	Vec2( const _dataType& v0, const _dataType& v1 );

	void				absolute();
	Vec2<_dataType>		absolute ( const Vec2<_dataType>& vec );

	Vec2<_dataType>			cross ( const Vec2<_dataType>& vec ) const;

	_dataType				dot ( const Vec2<_dataType>& vec ) const;

	bool				equals ( const Vec2<_dataType>& vec, const _dataType& tolerence ) const;

	Vec2<_dataType>				getAbs() const;
	void				getAbs ( Vec2<_dataType>& vec ) const;
	_dataType				getAngle ( const Vec2<_dataType>& vec ) const;
	_dataType				getDistance ( const Vec2<_dataType>& vec ) const;
	_dataType				getDistanceSquared ( const Vec2<_dataType>& vec ) const;
	_dataType				getRealDistance ( const Vec2<_dataType>& vec ) const;
	_dataType				getRealDistanceSquared ( const Vec2<_dataType>& vec ) const;
	void				get( _dataType &v0, _dataType &v1, _dataType &v2 ) const;

	_dataType				length() const;
	_dataType				lengthSquared() const;
	
	// Linear Interpolation between two vectors.
         void            lerp(const _dataType& lerpVal,
                              const Vec2<_dataType>& from, 
                              const Vec2<_dataType>& to );
		    
	_dataType			normalize();

	inline _dataType* 			data() { return _v; }
	inline const _dataType* 		data() const { return _v; }
	inline _dataType &		operator[]( int i ) { return _v[i]; }
	inline const _dataType &		operator[]( int i ) const { return _v[i]; }
	Vec2<_dataType>& 		operator*=( const _dataType& value );
	Vec2<_dataType>& 		operator/=( const _dataType& value );
	Vec2<_dataType>& 		operator+=( const Vec2<_dataType>& vec );
	Vec2<_dataType>& 		operator+=( const _dataType v[4] );
	Vec2<_dataType>& 		operator-=( const Vec2<_dataType>& vec );
	Vec2<_dataType>& 		operator=( const Vec2<_dataType>& vec );
	Vec2<_dataType>& 		operator=( const _dataType v[4] );
	Vec2<_dataType>& 		operator=( const _dataType& value );
	Vec2<_dataType>		operator-() const;
	Vec2<_dataType>		operator*( const _dataType& value ) const;
	Vec2<_dataType>		operator/( const _dataType& value ) const;
	Vec2<_dataType>		operator+( const Vec2<_dataType>& vecB ) const;
	Vec2<_dataType>		operator-( const Vec2<_dataType>& vecB ) const;
	bool				operator==( const Vec2<_dataType>& vecB ) const;
	bool				operator!=( const Vec2<_dataType>& vecB ) const;
	//friend ostream &		operator<<( ostream& out, const Vec2<_dataType>& vec );
	//friend istream &		operator>>( istream& in, Vec2<_dataType>& vec );

	void				setLength( const _dataType& value );

	void				set( const Vec2<_dataType>& vec );
	void				set( const _dataType vec[4] );
	void				set( const _dataType& v0, const _dataType& v1, const _dataType& v2 );
};

//  Constructor.
template<class _dataType>
inline Vec2<_dataType>::Vec2( const Vec2<_dataType>& vec )
{
	_v[0] = vec[0];
	_v[1] = vec[1];
}

//  Constructor.
template<class _dataType>
inline Vec2<_dataType>::Vec2( const _dataType v[2] )
{
	_v[0] = v[0];
	_v[1] = v[1];
}

//  Constructor.
template<class _dataType>
inline Vec2<_dataType>::Vec2( const _dataType& v0, const _dataType& v1 )
{
	_v[0] = v0;
	_v[1] = v1;
}

//  Set the value.
template<class _dataType>
inline void Vec2<_dataType>::set( const Vec2<_dataType>& vec )
{
	_v[0] = vec[0];
	_v[1] = vec[1];
}

//  Set the value.
template<class _dataType>
inline void Vec2<_dataType>::set( const _dataType v[2] )
{
	_v[0] = v[0];
	_v[1] = v[1];
}

//  Set the value.
template<class _dataType>
inline void Vec2<_dataType>::set( const _dataType& v0, const _dataType& v1, const _dataType& v2 )
{
	_v[0] = v0;
	_v[1] = v1;
}


//  Make all the vector's components positive.
template<class _dataType>
inline void Vec2<_dataType>::absolute()
{
	_v[0] = abs( _v[0] );
	_v[1] = abs( _v[1] );
}


//  Return the cross product.
template<class _dataType>
inline Vec2<_dataType> Vec2<_dataType>::cross ( const Vec2<_dataType>& vec ) const
{
	return Vec2<_dataType>( _v[0] * vec[1] - _v[1] * vec[0],
				_v[1] * vec[0] - _v[0] * vec[1] );
}

//  Return the dot product.
template<class _dataType>
inline _dataType Vec2<_dataType>::dot ( const Vec2<_dataType>& vec ) const
{
	return _v[0] * vec[0] + 
	    _v[1] * vec[1];
}

//  See if the vectors are equal within the given tolerance.
template<class _dataType>
inline bool Vec2<_dataType>::equals ( const Vec2<_dataType>& vec, const _dataType& tolerance ) const
{
	return ( abs ( _v[0] - vec._v[0] ) <= tolerance &&
		  abs ( _v[1] - vec._v[1] ) <= tolerance );
}

//  Return the absolute value.
template<class _dataType>
inline Vec2<_dataType> Vec2<_dataType>::getAbs() const
{
	return Vec2<_dataType>(	abs ( _v[0] ),
				abs ( _v[1] ) );
}

//  Return the absolute value.
template<class _dataType>
inline void Vec2<_dataType>::getAbs ( Vec2<_dataType>& vec ) const
{
	vec.set( abs ( _v[0] ),
		abs ( _v[1] ) );
}

//  Get the value.
template<class _dataType>
inline void Vec2<_dataType>::get( _dataType &v0, _dataType &v1, _dataType &v2 ) const
{
	v0 = _v[0];
	v1 = _v[1];
}

//  Return the angle between the two vectors in radians
template<class _dataType>
inline _dataType Vec2<_dataType>::getAngle ( const Vec2<_dataType>& vec ) const
{
    // This is: theta = acosf ( A dot B / |A||B| ).

    return acosf( ( _v[0] * vec[0] + _v[1] * vec[1] ) / 
		( sqrt ( _v[0] * _v[0] + _v[1] * _v[1] ) * 
		  sqrt ( vec[0] * vec[0] + vec[1] * vec[1] ) ) );
}

//  Get the distance.
template<class _dataType>
inline _dataType Vec2<_dataType>::getDistance ( const Vec2<_dataType>& vec ) const
{
	return sqrt ( ( _v[0] - vec[0] ) * ( _v[0] - vec[0] ) +
				   ( _v[1] - vec[1] ) * ( _v[1] - vec[1] ) );
}

//  Get the squared distance.
template<class _dataType>
inline _dataType Vec2<_dataType>::getDistanceSquared ( const Vec2<_dataType>& vec ) const
{
	return ( _v[0] - vec[0] ) * ( _v[0] - vec[0] ) +
		   ( _v[1] - vec[1] ) * ( _v[1] - vec[1] );
}

//  Return the length.
template<class _dataType>
inline _dataType Vec2<_dataType>::length() const
{
	return sqrt ( _v[0] * _v[0] + 
				   _v[1] * _v[1] );
}

//  Return the length squared.
template<class _dataType>
inline _dataType Vec2<_dataType>::lengthSquared() const
{
	return _v[0] * _v[0] + _v[1] * _v[1];
}

//  Normalize, return the length prior to normalization.
template<class _dataType>
inline _dataType Vec2<_dataType>::normalize()
{
	_dataType length = sqrt ( _v[0] * _v[0] + 
				_v[1] * _v[1] );

	_dataType invLength = 1.0f / length;

	_v[0] *= invLength;
	_v[1] *= invLength;

	return length;
}

//  Multiply all the components by the value.
template<class _dataType>
inline Vec2<_dataType>& Vec2<_dataType>::operator*=( const _dataType& value )
{
	_v[0] *= value;
	_v[1] *= value;

	return *this;
}

//  Divide all the components by the value.
template<class _dataType>
inline Vec2<_dataType>& Vec2<_dataType>::operator/=( const _dataType& value )
{
	_dataType invValue = 1.0f / value;

	_v[0] *= invValue;
	_v[1] *= invValue;

	return *this;
}

//  Add the vector to this one.
template<class _dataType>
inline Vec2<_dataType>& Vec2<_dataType>::operator+=( const Vec2<_dataType>& vec )
{
	_v[0] += vec[0];
	_v[1] += vec[1];

	return *this;
}

//  Subtract the vector from this one.
template<class _dataType>
inline Vec2<_dataType>& Vec2<_dataType>::operator-=( const Vec2<_dataType>& vec )
{
	_v[0] -= vec[0];
	_v[1] -= vec[1];

	return *this;
}

//  Assign this vector.
template<class _dataType>
inline Vec2<_dataType>& Vec2<_dataType>::operator=( const Vec2<_dataType>& vec )
{
	_v[0] = vec[0];
	_v[1] = vec[1];

	return *this;
}

//	Assign this vector.
template<class _dataType>
inline Vec2<_dataType>& Vec2<_dataType>::operator=( const _dataType v[2] )
{
	_v[0] = v[0];
	_v[1] = v[1];

	return *this;
}

//  Return the negative of this vector.
template<class _dataType>
inline Vec2<_dataType> Vec2<_dataType>::operator-() const
{
	return Vec2<_dataType>( -_v[0], -_v[1] );
}

//  Return the component-wise product with the given value.
template<class _dataType>
inline Vec2<_dataType> Vec2<_dataType>::operator*( const _dataType& value ) const
{
    return Vec2<_dataType>( _v[0]*value, _v[1]*value );
}

//  Return the component-wise division with the given value.
template<class _dataType>
inline Vec2<_dataType> Vec2<_dataType>::operator/( const _dataType& value ) const
{
	_dataType invValue = static_cast<_dataType>(1.0) / value;
	return Vec2<_dataType> ( _v[0] * invValue, 
					 _v[1] * invValue );
}

//  Return the vector sum.
template<class _dataType>
inline Vec2<_dataType> Vec2<_dataType>::operator+( const Vec2<_dataType>& vecB ) const
{
	return Vec2<_dataType> ( _v[0] + vecB[0], 
				_v[1] + vecB[1] );
}

//  Return the vector difference.
template<class _dataType>
inline Vec2<_dataType> Vec2<_dataType>::operator-( const Vec2<_dataType>& vecB ) const
{
	return Vec2<_dataType>( _v[0] - vecB._v[0], 
				_v[1] - vecB._v[1] );
}

//  See if they're equal.
template<class _dataType>
inline bool Vec2<_dataType>::operator==( const Vec2<_dataType>& vecB ) const
{
	return ( _v[0] == vecB._v[0] && 
		 _v[1] == vecB._v[1] );
}

//  See if they're not equal.
template<class _dataType>
inline bool Vec2<_dataType>::operator!=( const Vec2<_dataType>& vecB ) const
{
	return ( _v[0] != vecB._v[0] || 
		_v[1] != vecB._v[1] );
}
/*
//  Output operator.
template<class _dataType>
inline ostream &operator<<( ostream &out, const Vec2<_dataType>& vec )
{
	out << vec[0] << " " 
		<< vec[1];

	return out;
}

//  Input operator.
template<class _dataType>
inline istream &operator>>( istream &in, Vec2<_dataType>& vec )
{
	in >> vec[0] 
	   >> vec[1];

	return in;
}
*/
//  Set the length.
template<class _dataType>
inline void Vec2<_dataType>::setLength( const _dataType& newLength )
{
	_dataType oldLength = sqrt( _v[0] * _v[0] + 
				_v[1] * _v[1] );
	
	_dataType factor = newLength / oldLength;

	_v[0] *= factor;
	_v[1] *= factor;
}

// Linear Interpolation between two vectors.
template<class _dataType>
inline void Vec2<_dataType>::lerp(const _dataType &lerpVal,
                        const Vec2<_dataType>& from, 
                        const Vec2<_dataType>& to )
{
   Vec2<_dataType> offset = to - from;
   (*this) = from + offset*lerpVal;
}

//Typedef some commonly used vector types
typedef Vec2<float>  Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<int>    Vec2i;
typedef Vec2<long>   Vec2l;

#endif
