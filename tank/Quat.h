
//////////////////////////////////////////////////////////////////
//
//                         -=     Quat<dataType> class     =-
//
// Definition: "quaternion"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Quat.h,v $
//    $Date: 2001-09-06 15:21:24 $
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

#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include "Defines.h"
#include "Vec3.h"
#include "Vec4.h"

//: Quaternion
//  A quaternion is a data structure that can be used to store arbitrary 
//  rotation in 3space.  It is useful in robotics and animation, and is much 
//  faster to use than a rotation matrix when doing product or quotient 
//  operations (i.e. multiply or divide).
//
//    On quaternions; or on a new system of imaginaries in algebra,    <br>
//       Sir William Rowan Hamilton, Philosophical Magazine, xxv,      <br>
//       pp. 10-13 (July 1844)                                         <br>
//    Quaternion Calculus for Animation,  Ken Shoemake SIGGRAPH course notes 1989  <br>
//    Advanced Animation and Rendering Techniques: pp363-365           <br>
template <class dataType>
class Quat
{
//: Constructors
public:
   enum
   {
      QUAT_W = 3, QUAT_X = 0, QUAT_Y = 1, QUAT_Z = 2
   };
   
   //: Default constructor
   Quat();

   //: copy constructor
   Quat( const Quat<dataType>& quat );

   //: construct from raw quat data
   Quat( dataType w, dataType x, dataType y, dataType z );
   
   //: copy the quaternion data from scalar: [w]  vec: [x y z]
   //!POST: self = {w,x,y,z}
   void copy( dataType w, dataType x, dataType y, dataType z );
   
   //: copy the quaternion to self
   //!POST: self = quat
   void copy( const Quat<dataType>& quat );

   //: multiplication identity 
   // So any quaternion multiplied with this identity quaternion will 
   // not be changed.
   // sets self to multiplication identity quat: 0 rotation [1,0,0,0]
   // NOTE: addition identity is [0,0,0,0]
   void makeIdent();
   
   //: multiplication identity 
   // So any quaternion multiplied with this identity quaternion will 
   // not be changed.
   // returns a rot quaternion set to 0 rotation [1,0,0,0]
   // NOTE: addition identity is [0,0,0,0]
   static const Quat<dataType>& identity();
   
   //: Copy a pure quaternion to self
   //!POST: self = [0,p]
   void makePure( const Vec3<dataType>& p );
   
   //: returns the quaternion's norm (dot product)
   // defined as sum of squares of all quat components
   dataType norm() const;
     
   //: returns the quaternion's magnitude (also called absolute)
   // defined as the square root of the norm
   dataType length() const;
   
   //: set self to the complex conjugate of self.
   void conj();
   
   //: set self to the complex conjugate of quat.
   void conj( const Quat<dataType>& quat );
  
   //: normalize without the square root.  faster but not precise...
   //!POST: self = self / norm()
   //       normalizeFast() makes quat.norm() == 1
   void normalizeFast();
   
   //: set self to the unit quaternion of quat. fast, imprecise
   void normalizeFast( const Quat<dataType>& quat );
   
   //: set self to the normalized quaternion of self.
   //!POST: self = normalize(self), where normalize makes quat.length() == 1
   void normalize();
   
   //: set self to the normalized quaternion of quat.
   void normalize( const Quat<dataType>& quat );
  
   //: set self to the multiplicative inverse of self
   //!POST: self becomes the multiplicative inverse of self
   void invert();
   
   //: set self to the multiplicative inverse of quat
   //!POST: self becomes the multiplicative inverse of quat
   void invert( const Quat<dataType>& quat );

public:
   //: product of two quaternions (quaternion product)
   //!POST: this' = q1 * q2
   void mult( const Quat<dataType>& q1, const Quat<dataType>& q2 );

   //: scalar multiplication 
   // each element (4 total) scaled by s
   //!POST: this' = q1 * s
   void mult( const Quat<dataType>& q1, const dataType& s );

   //: scale the rotation angle
   // [angle,x,y,z] = [angle*s,x,y,z]
   // NOTE: this function will probably fail in certain cases...
   void scaleAngle( const Quat<dataType>& q1, const dataType& s );
   
   //: quotient of two quaternions
   //!POST: this' = q1 / q2
   void div( const Quat<dataType>& q1, const Quat<dataType>& q2 );

   // do an "add" of all quat components
   // TODO: add description for what this means geometrically
   void add( const Quat<dataType>& quat1, const Quat<dataType>& quat2 );
   
   // set self to quat1 - quat2
   // TODO: add description for what this means geometrically
   void sub( const Quat<dataType>& quat1, const Quat<dataType>& quat2 );
   
   //: complex exponentiation 
   //!POST: sets self to the exponentiation of quat
   // NOTE: safe to pass self as argument
   void exp( const Quat<dataType>& quat );
   
   //: complex logarithm
   //!POST: sets self to the log of quat
   void log( const Quat<dataType>& quat );
   
   //: make a quat from a twist (radians) about a vector (normalized)
   void makeRot( const dataType& rad, const dataType& x, const dataType& y, const dataType& z );
 
   //: get the quat's twist (radians) and vector
   void getRot( dataType& rad, dataType& xx, dataType& yy, dataType& zz ) const;
   
   //: Spherical quadratic interpolation
   // WARNING: not implemented (do not use)
   // Spherical quadratic interpolation is provided by squad and its
   // helper function, meanTangent.
   void squad( dataType t, const Quat<dataType>& q1, const Quat<dataType>& q2, const Quat<dataType>& a, const Quat<dataType>& b );

   // WARNING: not implemented (do not use)
   void meanTangent( const Quat<dataType> &q1, const Quat<dataType> &q2, const Quat<dataType> &q3 );
   
   //  Linear interpolation between two quaternion positions
   //
   //  Arguments: Quat<dataType>  (first and second quaternion)
   //             GLdataType  (interpolation parameter [0..1])
   //             Quat<dataType>  (resulting quaternion, inbetween)
   //  Comments:  Fast but not nearly as smooth as Slerp
   void lerp( const dataType &t, const Quat<dataType> &from, const Quat<dataType> &to );

   //: spherical linear interpolation
   // set self to the interpolated quat                             <BR>
   // t: is the interpolation param between [0..1]                  <BR>
   //!POST: if t == 0.0, then self is set to q1                     <BR>
   //!POST: if 0 < t < 1, then self is set to interpolated result   <BR>
   //!POST: if t == 1.0, then self is set to q2                     <BR>
   void slerp( dataType t, const Quat<dataType>& q1, const Quat<dataType>& q2 );
   
   //: Convert a set of Euler angles to a Quaternion
   // Arguments:   A rotation set of 3 angles, a quaternion to set
   // Discussion:  As the order of rotations is important I am
   //      using the Quantum Mechanics convention of( p,y,r)
   //      a Yaw-Pitch-Roll( y,p,r) system would have to be
   //      adjusted.  It is more efficient this way though.
   void setXYZEuler( const dataType& p, 
                     const dataType& y, 
                     const dataType& r );
   
   //: Convert a set of Euler angles( Y*P*R) to a Quaternion
   // Arguments:   A rotation set of 3 angles, a quaternion to set
   // Discussion:  a Yaw-Pitch-Roll( y,p,r) system.
   void setYXZEuler( const dataType& y, 
                     const dataType& p, 
                     const dataType& r );
   
   
   //: Convert a set of Euler angles to a Quaternion
   // Arguments:   A rotation set of 3 angles, a quaternion to set
   // Discussion:  This is a second variation.  It creates a
   //      Series of quaternions and multiplies them together
   //      It would be easier to extend this for other rotation orders
   void setXYZEuler2( const dataType& p, 
                      const dataType& y, 
                      const dataType& r );
   
public:
   //: compose two rotations (multiplication operator) 
   //!POST: temporary return value = self * quat 
   Quat<dataType> operator*( const Quat<dataType>& quat ) const;
   
   //: rotate a vector
   //  returns a vector rotated by "self" as a temporary object     <BR>
   //!PRE: give a vector
   //!POST: vector' = self * vector
   Vec3<dataType> operator*( const Vec3<dataType>& vector ) const;
   
   //: mult by scalar (order independant)
   // NOTE: less efficient (returns a copy), use mult() instead (faster)
   Quat<dataType> operator*( dataType s ) const;
   
   //: multiply by inverse quat.
   // NOTE: less efficient, use div() instead
   Quat<dataType> operator/( const Quat<dataType>& quat ) const;
   
   //: mult by inverse scalar.
   //!POST: returns a temporary == self scaled by s
   Quat<dataType> operator/( dataType s ) const;

   //: do an "add" of all quat components
   // TODO: add description for what this means geometrically
   Quat<dataType> operator+( const Quat<dataType>& quat ) const;
   
   //: do a "subtract" of all quat components
   // TODO: add description for what this means geometrically
   Quat<dataType> operator-( const Quat<dataType>& quat ) const;
   
public:
   //: Assignment operator *=
   Quat<dataType>& operator*=( const Quat<dataType>& quat );

   //: Assignment operator /=
   Quat<dataType>& operator/=( const Quat<dataType>& quat );
   
   //: does self == quat?
   //  return true if self == quat                                 <BR>
   //  return false if self != quat
   bool operator==( const Quat<dataType>& quat );
   
   //: does self != quat?
   // return true if self != quat                                  <BR>
   // return false if self == quat
   bool operator!=( const Quat<dataType>& quat );
   
   //: set self to quat
   Quat<dataType>& operator=( const Quat<dataType>& quat );
   
   //: output method
   std::ostream& outStreamRaw( std::ostream& out ) const;
   
   //: output method
   std::ostream& outStreamReadable( std::ostream& out ) const;
   
   //: output operator
   friend std::ostream& operator<<( std::ostream& out, const Quat<dataType>& q );
   
   //: quaternion data access for external function use (like quat to matrix)
   // non-const version                                           <BR>
   // use QUAT_W, QUAT_X, QUAT_Y, or QUAT_Z to access each component
   dataType& operator[]( int x );
   
   //: quaternion data access for external function use (like quat to matrix)
   // const version                                               <BR>
   // use QUAT_W, QUAT_X, QUAT_Y, or QUAT_Z to access each component
   const dataType& operator[]( int x ) const;

private:
   Vec4<dataType> vec;
};

//: quaternion data access for external function use (like quat to matrix)
// non-const version
// use QUAT_W, QUAT_X, QUAT_Y, or QUAT_Z to access each component
//
template<class dataType>
inline dataType& Quat<dataType>::operator[]( int x )
{ 
   return this->vec[x]; 
}

//: quaternion data access for external function use (like quat to matrix)
// const version
// use QUAT_W, QUAT_X, QUAT_Y, or QUAT_Z to access each component
//
template<class dataType>
inline const dataType& Quat<dataType>::operator[]( int x ) const 
{ 
   return this->vec[x];
}

//: copy the quaternion data from scalar: [w]  vec: [x y z]
//!POST: self = {w,x,y,z}
template<class dataType>
inline void Quat<dataType>::copy( dataType w, dataType x, dataType y, dataType z )
{
   this->vec[QUAT_W] = w;
   this->vec[QUAT_X] = x;
   this->vec[QUAT_Y] = y;
   this->vec[QUAT_Z] = z;
}   

//: copy the quaternion to self
//!POST: self = quat
template<class dataType>
inline void Quat<dataType>::copy( const Quat<dataType>& quat )
{
   vec = quat.vec;
}   

//: Construct Quat from 4 dataTypes
template<class dataType>
inline Quat<dataType>::Quat( dataType w,
                                       dataType x,
                                       dataType y,
                                       dataType z ) : vec()
{
   this->copy( w, x, y, z );
}

//: multiplication identity 
// So any quaternion multiplied with this identity quaternion will 
// not be changed.
// returns quaternion set to 0 rotation [1,0,0,0]
// NOTE: addition identity is [0,0,0,0]
template<class dataType>
inline const Quat<dataType>& Quat<dataType>::identity()
{
   // [0 deg, 1, 0, 0]  or  [cos(0deg) == 1, sin(0deg)==0 * [1,0,0]]
   static const Quat<dataType> ____identity___quaternion( 1.0f, 0.0f, 0.0f, 0.0f );
   return ____identity___quaternion;
}
   
//: multiplication identity 
// So any quaternion multiplied with this identity quaternion will 
// not be changed.
// sets self to 0 rotation [1,0,0,0]
// NOTE: addition identity is [0,0,0,0]
template<class dataType>
inline void Quat<dataType>::makeIdent()
{
   this->copy( Quat<dataType>::identity() );
}

//: Copy a pure quaternion to self
// quat = [0,w] 
//      = [0,w0,w1,w2]
//!POST: self = pure_quat
template<class dataType>
inline void Quat<dataType>::makePure( const Vec3<dataType>& pure_quat )
{
   vec[QUAT_W] = 0.0f; // by definition of pure quat == [0,w]
   vec[QUAT_X] = pure_quat[0];
   vec[QUAT_Y] = pure_quat[1];
   vec[QUAT_Z] = pure_quat[2];
}

//: default constructor
//!POST: initialize self to identity
template<class dataType>
inline Quat<dataType>::Quat() : vec()
{
   this->makeIdent();
}

//: Construct self from another Quat<dataType> 
template<class dataType>
inline Quat<dataType>::Quat( const Quat<dataType>& quat ) : vec()
{
   this->copy( quat );
}

//: returns the quaternion's norm (dot product)
// defined as sum of squares of components
template<class dataType>
inline dataType Quat<dataType>::norm() const
{
   return ((vec[0]*vec[0])+(vec[1]*vec[1])+(vec[2]*vec[2])+(vec[3]*vec[3]));
}

//: returns the quaternion's magnitude (also called absolute)
// defined as the norm of all four quaternion components
template<class dataType>
inline dataType Quat<dataType>::length() const { return kev::SQRT( this->norm() ); }

//: set self to the complex conjugate of self.
template<class dataType>
inline void Quat<dataType>::conj()
{ 
   vec[QUAT_X] = -vec[QUAT_X];
   vec[QUAT_Y] = -vec[QUAT_Y];
   vec[QUAT_Z] = -vec[QUAT_Z];
}

//: set self to the complex conjugate of quat.
template<class dataType>
inline void Quat<dataType>::conj( const Quat<dataType>& quat )
{ 
   this->copy( quat );
   this->conj();
}

//: normalize without the square root.  faster but not precise...
//!PRE: magnitude must be > 0
//!POST: self = self / norm()
//       normalizeFast() makes quat.norm() == 1
template<class dataType>
inline void Quat<dataType>::normalizeFast()
{ 
   dataType n = this->norm();
   
   // return if no magnitude (already as normalized as possible)
   if (n < 0.0001) 
      return;

   dataType n_inv = 1.0f / n;
   
   vec[QUAT_W] *= n_inv; 
   vec[QUAT_X] *= n_inv; 
   vec[QUAT_Y] *= n_inv; 
   vec[QUAT_Z] *= n_inv;
}

//: set self to the unit quaternion of quat. fast, imprecise
template<class dataType>
inline void Quat<dataType>::normalizeFast( const Quat<dataType>& quat )
{ 
   this->copy( quat );
   this->normalizeFast();
}

//: set self to the normalized quaternion of self.
//!PRE: magnitude must be > 0
//!POST: self = normalize(self), where normalize makes quat.length() == 1
template<class dataType>
inline void Quat<dataType>::normalize()
{ 
   dataType l = this->length();
   
   // return if no magnitude (already as normalized as possible)
   if (l < 0.0001f) 
      return;

   dataType l_inv = 1.0f / l;
   vec[QUAT_W] *= l_inv;
   vec[QUAT_X] *= l_inv;
   vec[QUAT_Y] *= l_inv;
   vec[QUAT_Z] *= l_inv;
}

//: set self to the normalized quaternion of quat.
template<class dataType>
inline void Quat<dataType>::normalize( const Quat<dataType>& quat )
{ 
   this->copy( quat );
   this->normalize();
}

//: set self to the multiplicative inverse of self
//!POST: self becomes the multiplicative inverse of self
template<class dataType>
inline void Quat<dataType>::invert()
{
   this->conj(); 
   this->normalizeFast();
}

//: set self to the multiplicative inverse of quat
//!POST: self becomes the multiplicative inverse of quat
template<class dataType>
inline void Quat<dataType>::invert( const Quat<dataType>& quat )
{ 
   this->copy( quat );
   this->invert();
}

//: scalar multiplication
//!POST: this' = q1 * s
template<class dataType>
inline void Quat<dataType>::mult( const Quat<dataType>& q1, const dataType& s )
{
   vec[QUAT_W] = q1.vec[QUAT_W] * s;
   vec[QUAT_X] = q1.vec[QUAT_X] * s;
   vec[QUAT_Y] = q1.vec[QUAT_Y] * s;
   vec[QUAT_Z] = q1.vec[QUAT_Z] * s;
}

//: scalar multiplication
//!POST: this' = q1 * s
// TODO: could we use a vector (pure quat) to scale a quat in a 
//        more robust way?  pretty sure we can... rewrite scaleAngle to use this
//        method instead....
// NOTE: this function will probably fail in certain cases...
template<class dataType>
inline void Quat<dataType>::scaleAngle( const Quat<dataType>& q1, const dataType& s )
{
   dataType rad, x, y, z;
   q1.getRot( rad, x, y, z );
   this->makeRot( rad * s, x, y, z );
}

//: quotient of two quaternions
//!POST: this' = q1 / q2
template<class dataType>
inline void Quat<dataType>::div( const Quat<dataType>& q1, const Quat<dataType>& q2 )
{
   Quat<dataType> q2_inv, r, s;

   // invert the vector component
   q2_inv.conj( q2 );

   r.mult( q1, q2_inv );
   s.mult( q2_inv, q2_inv );

   vec[QUAT_X] = r.vec[QUAT_X] / s.vec[QUAT_W];
   vec[QUAT_Y] = r.vec[QUAT_Y] / s.vec[QUAT_W];
   vec[QUAT_Z] = r.vec[QUAT_Z] / s.vec[QUAT_W];
   vec[QUAT_W] = r.vec[QUAT_W] / s.vec[QUAT_W];
}

// WARNING: not implemented (do not use)
template<class dataType>
inline void Quat<dataType>::meanTangent( const Quat<dataType> &q1, const Quat<dataType> &q2, const Quat<dataType> &q3 )
{
   vjASSERT( false && "not implemented" ); 
}   

//: compose two rotations (multiplication operator) 
//!POST: temporary return value = self * quat 
template<class dataType>
inline Quat<dataType> Quat<dataType>::operator*( const Quat<dataType>& quat ) const 
{
   Quat<dataType> dst; 
   dst.mult( *this, quat ); 
   return dst;
}

//: rotate vector by quat
//  returns a vector rotated by this.  result returned is a temporary
//!PRE: give a vector
//!POST: vector = self * vector 
template<class dataType>
inline Vec3<dataType> Quat<dataType>::operator*( const Vec3<dataType>& vector ) const
{
   // convert the vec3 to a pure quat
   Quat<dataType> pure_quat;
   pure_quat.makePure( vector );

   // get the inverse of self
   Quat<dataType> self_inv;
   self_inv.invert( *this );

   // do the multiplication, and return
   
   // shoemake original (left hand rule):
   //Quat<dataType> result = self_inv * pure_quat * (*this);
   
   // shoemake recent version (right hand rule):
   Quat<dataType> result = (*this) * pure_quat * self_inv;
   
   return Vec3<dataType>( result.vec[QUAT_X], result.vec[QUAT_Y], result.vec[QUAT_Z] );
}

// mult by scalar 
// NOTE: less efficient, use mult() instead
template<class dataType>
inline Quat<dataType> Quat<dataType>::operator*( dataType s ) const
{
   Quat<dataType> result;
   result.mult( *this, s );
   return result;
}

// multiply by inverse quat.
// NOTE: less efficient, use div() instead
template<class dataType>
inline Quat<dataType> Quat<dataType>::operator/( const Quat<dataType>& quat ) const 
{
   Quat<dataType> dst; 
   dst.div( *this, quat );
   return dst;
}

// mult by inverse scalar.
//!POST: returns a temporary == self scaled by s
template<class dataType>
inline Quat<dataType> Quat<dataType>::operator/( dataType s ) const
{
   s = 1.0f / s;
   Quat<dataType> result;
   result.mult( *this, s );
   return result;
}   

// do an "add" of all quat components
// TODO: add description for what this means geometrically
template<class dataType>
inline void Quat<dataType>::add( const Quat<dataType>& quat1, const Quat<dataType>& quat2 )
{
   this->vec[QUAT_W] = quat1.vec[QUAT_W] + quat2.vec[QUAT_W];
   this->vec[QUAT_X] = quat1.vec[QUAT_X] + quat2.vec[QUAT_X];
   this->vec[QUAT_Y] = quat1.vec[QUAT_Y] + quat2.vec[QUAT_Y];
   this->vec[QUAT_Z] = quat1.vec[QUAT_Z] + quat2.vec[QUAT_Z];
}

// set self to quat1 - quat2
// TODO: add description for what this means geometrically
template<class dataType>
inline void Quat<dataType>::sub( const Quat<dataType>& quat1, const Quat<dataType>& quat2 )
{
   this->vec[QUAT_W] = quat1.vec[QUAT_W] - quat2.vec[QUAT_W];
   this->vec[QUAT_X] = quat1.vec[QUAT_X] - quat2.vec[QUAT_X];
   this->vec[QUAT_Y] = quat1.vec[QUAT_Y] - quat2.vec[QUAT_Y];
   this->vec[QUAT_Z] = quat1.vec[QUAT_Z] - quat2.vec[QUAT_Z];
}

// do an "add" of all quat components
// TODO: add description for what this means geometrically
template<class dataType>
inline Quat<dataType> Quat<dataType>::operator+( const Quat<dataType>& quat ) const
{
   Quat<dataType> result;
   result.add( *this, quat );
   return result;
}

// do a "subtract" of all quat components
// TODO: add description for what this means geometrically
template<class dataType>
inline Quat<dataType> Quat<dataType>::operator-( const Quat<dataType>& quat ) const
{
   Quat<dataType> result;
   result.sub( *this, quat );
   return result;
}   

// Assignment operator *=
template<class dataType>
inline Quat<dataType>& Quat<dataType>::operator*=( const Quat<dataType>& quat )
{
   this->mult( *this, quat );
   return *this;
}
// Assignment operator /=
template<class dataType>
inline Quat<dataType>& Quat<dataType>::operator/=( const Quat<dataType>& quat ) 
{
   this->div( *this, quat );
   return *this;
}

// does self == quat?
// return true if self == quat
// return false if self != quat
template<class dataType>
inline bool Quat<dataType>::operator==( const Quat<dataType>& quat )
{
   if (quat.scalar() == this->scalar() &&
       quat.vector() == this->vector())
   {
      return true;
   }      
   else
   {
      return false;
   }       
} 

// does self != quat?
// return true if self != quat
// return false if self == quat
template<class dataType>
inline bool Quat<dataType>::operator!=( const Quat<dataType>& quat )
{
   if (quat.scalar() == this->scalar() &&
       quat.vector() == this->vector())
   {
      return false;
   }      
   else
   {
      return true;
   }  
}

//: set self to quat
template<class dataType>
inline Quat<dataType>& Quat<dataType>::operator=( const Quat<dataType>& quat )
{
   this->copy( quat );
   return *this;
}

// Convert a set of Euler angles to a Quaternion
// Arguments:   A rotation set of 3 angles, a quaternion to set
// Discussion:  As the order of rotations is important I am
//      using the Quantum Mechanics convention of (p,y,r)
//      a Yaw-Pitch-Roll (y,p,r) system would have to be
//      adjusted.  It is more efficient this way though.
template<class dataType>
inline void Quat<dataType>::setXYZEuler( const dataType &pitch, 
                                       const dataType &yaw, 
                                       const dataType &roll )
{
   dataType pOver2, yOver2, rOver2, 
   cosp, cosy, cosr, 
   sinp, siny, sinr, 
   cc, cs, sc, ss;

    // precompute half angles
    pOver2 = pitch * 0.5f;
    yOver2 = yaw * 0.5f;
    rOver2 = roll * 0.5f;
    
    cosp = kev::COS( pOver2 );
    cosy = kev::COS( yOver2 );
    cosr = kev::COS( rOver2 );
    
    sinp = kev::SIN( pOver2 );
    siny = kev::SIN( yOver2 );
    sinr = kev::SIN( rOver2 );

    cc = cosp * cosr;
    cs = cosp * sinr;
    sc = sinp * cosr;
    ss = sinp * sinr;

    this->vec[QUAT_W] = (cosy * cc) + (siny * ss);
    this->vec[QUAT_X] = (cosy * sc) - (siny * cs);
    this->vec[QUAT_Y] = (cosy * ss) + (siny * cc);
    this->vec[QUAT_Z] = (cosy * cs) - (siny * sc);
    
    // insure the quaternion is normalized
    this->normalize();
}

//////////////////////////////////////////////////////////////////
//
// Convert a set of Euler angles (Y*P*R) to a Quaternion
// Arguments:   A rotation set of 3 angles, a quaternion to set
// Discussion:  a Yaw-Pitch-Roll (y,p,r) system.
//
//////////////////////////////////////////////////////////////////
template<class dataType>
inline void Quat<dataType>::setYXZEuler( const dataType &y, 
                                         const dataType &p, 
                                         const dataType &r )
{
    dataType cosr, cosp, cosy, 
             sinr, sinp, siny, 
             cosp_cosy, sinp_siny;
    
    cosr = kev::COS(r * 0.5f);
    cosp = kev::COS(p * 0.5f);
    cosy = kev::COS(y * 0.5f);
    
    sinr = kev::SIN(r * 0.5f);
    sinp = kev::SIN(p * 0.5f);
    siny = kev::SIN(y * 0.5f);
    
    cosp_cosy = cosp * cosy;
    sinp_siny = sinp * siny;
    
    this->vec[QUAT_W] = (cosr * cosp_cosy)   + (sinr * sinp_siny);
    this->vec[QUAT_X] = (sinr * cosp_cosy)   - (cosr * sinp_siny);
    this->vec[QUAT_Y] = (cosr * sinp * cosy) + (sinr * cosp * siny);
    this->vec[QUAT_Z] = (cosr * cosp * siny) - (sinr * sinp * cosy);
    
    // insure the quaternion is normalized
    this->normalize();
}

///////////////////////////////////////////////////////////////////////////////
// Convert a set of Euler angles to a Quaternion
// Arguments:   A rotation set of 3 angles, a quaternion to set
// Discussion:  This is a second variation.  It creates a
//      Series of quaternions and multiplies them together
//      It would be easier to extend this for other rotation orders
///////////////////////////////////////////////////////////////////////////////
template<class dataType>
inline void Quat<dataType>::setXYZEuler2( const dataType &p, 
                                          const dataType &y, 
                                          const dataType &r)
{
    dataType pOver2, yOver2, rOver2;
    Quat<dataType> qx, qy, qz;
    
    // precompute half angles
    pOver2 = p * 0.5f;
    yOver2 = y * 0.5f;
    rOver2 = r * 0.5f;

    //make the pitch quat
    qx.vec[QUAT_W] = kev::COS(pOver2);
    qx.vec[QUAT_X] = kev::SIN(pOver2); 
    qx.vec[QUAT_Y] = 0.0f; 
    qx.vec[QUAT_Z] = 0.0f; 
    
    //make the yaw quat
    qy.vec[QUAT_W] = kev::COS(yOver2);
    qy.vec[QUAT_X] = 0.0f; 
    qy.vec[QUAT_Y] = kev::SIN(yOver2); 
    qy.vec[QUAT_Z] = 0.0f; 
    
    //make the roll quat
    qz.vec[QUAT_W] = kev::COS(rOver2);
    qz.vec[QUAT_X] = 0.0f; 
    qz.vec[QUAT_Y] = 0.0f; 
    qz.vec[QUAT_Z] = kev::SIN(rOver2); 
    
    //compose the three in pyr order...
    (*this) = qx * qy * qz;

    // insure the quaternion is normalized
    this->normalize();
}

//: make a quat from a twist (radians) about a vector (normalized)
template<class dataType>
void Quat<dataType>::makeRot( const dataType& rad, const dataType& x, const dataType& y, const dataType& z )
{
   // q = [ cos(rad/2), sin(rad/2) * [x,y,z] ]
   Vec3<dataType> vec_normalized( x, y, z );
   if (vec_normalized.length() > 0.0001f)
   {
      vec_normalized.normalize();
   }
   
   dataType half_angle = rad * 0.5f;
   dataType sin_half_angle = kev::SIN( half_angle );
   
   vec[QUAT_W] = kev::COS( half_angle );
   vec[QUAT_X] = sin_half_angle * vec_normalized[0];
   vec[QUAT_Y] = sin_half_angle * vec_normalized[1];
   vec[QUAT_Z] = sin_half_angle * vec_normalized[2];
   
   // should automagically be normalized (unit magnitude) now...
}

//: get the quat's twist (radians) and vector
template<class dataType>
void Quat<dataType>::getRot( dataType& rad, dataType& xx, dataType& yy, dataType& zz ) const
{
   // make sure we don't get a NaN result from acos...
   Quat<dataType> quat( *this );
   if (kev::ABS( quat.vec[QUAT_W] ) > 1.0f)
   {
      quat.normalize();
   }
   assert( kev::ABS( quat.vec[QUAT_W] ) <= 1.0f && "acos returns NaN when |arg| > 1" );
   
   
   // [acos( w ) * 2.0, v / (asin( w ) * 2.0)]
   
   // get the rotation:
   rad = kev::ACOS( quat.vec[QUAT_W] ) * 2.0f;
   
   // get the axis: (use sin(rad) instead of asin(w))
   dataType sin_half_angle = kev::SIN( rad * 0.5f );
   if (sin_half_angle >= 0.0001f)
   {
      dataType sin_half_angle_inv = 1.0f / sin_half_angle;
      xx = quat.vec[QUAT_X] * sin_half_angle_inv;
      yy = quat.vec[QUAT_Y] * sin_half_angle_inv;
      zz = quat.vec[QUAT_Z] * sin_half_angle_inv;
   }
      
   // avoid NAN
   else 
   {
      xx = 1.0f - quat.vec[QUAT_W]; // one of the terms should be a 1,
      yy = 0.0f;                  // so we can maintain unit-ness
      zz = 0.0f;                  // in case w is 0 (which here w is 0)
   }
}

// Multiply the two quaternions
// From gdmag
template<class dataType>
void Quat<dataType>::mult( const Quat<dataType>& q1, const Quat<dataType>& q2 )
{
   // Here is the easy to understand equation: (grassman product)
   // scalar_component = q1.s * q2.s - dot(q1.v, q2.v)
   // vector_component = q2.v * q1.s + q1.v * q2.s + cross(q1.v, q2.v)
   
   // Here is another version (euclidean product, just FYI)...
   // scalar_component = q1.s * q2.s + dot(q1.v, q2.v)
   // vector_component = q2.v * q1.s - q1.v * q2.s - cross(q1.v, q2.v)

   // Here it is, implemented using vector algebra (grassman product)
   /*
   const dataType& w1( q1[QUAT_W] ), w2( q2[QUAT_W] );
   Vec3<dataType> v1( q1[QUAT_X], q1[QUAT_Y], q1[QUAT_Z] ), v2( q2[QUAT_X], q2[QUAT_Y], q2[QUAT_Z] );
   
   dataType w = w1 * w2 - v1.dot( v2 );
   Vec3<dataType> v = (w1 * v2) + (w2 * v1) + v1.cross( v2 );
   
   vec[QUAT_W] = w;
   vec[QUAT_X] = v[0];
   vec[QUAT_Y] = v[1];
   vec[QUAT_Z] = v[2];
   */
         
   // Here is the same, only expanded... (grassman product)
   Quat<dataType> temporary; 
   temporary[QUAT_X] = q1[QUAT_W]*q2[QUAT_X] + q1[QUAT_X]*q2[QUAT_W] + q1[QUAT_Y]*q2[QUAT_Z] - q1[QUAT_Z]*q2[QUAT_Y];
   temporary[QUAT_Y] = q1[QUAT_W]*q2[QUAT_Y] + q1[QUAT_Y]*q2[QUAT_W] + q1[QUAT_Z]*q2[QUAT_X] - q1[QUAT_X]*q2[QUAT_Z];
   temporary[QUAT_Z] = q1[QUAT_W]*q2[QUAT_Z] + q1[QUAT_Z]*q2[QUAT_W] + q1[QUAT_X]*q2[QUAT_Y] - q1[QUAT_Y]*q2[QUAT_X];
   temporary[QUAT_W] = q1[QUAT_W]*q2[QUAT_W] - q1[QUAT_X]*q2[QUAT_X] - q1[QUAT_Y]*q2[QUAT_Y] - q1[QUAT_Z]*q2[QUAT_Z];

   // use a temporary, in case q1 or q2 is the same as self.
   vec[QUAT_X] = temporary[QUAT_X];
   vec[QUAT_Y] = temporary[QUAT_Y];
   vec[QUAT_Z] = temporary[QUAT_Z];
   vec[QUAT_W] = temporary[QUAT_W];
   
   // don't normalize, because it might not be rotation arithmetic we're doing
   // (only rotation quats have unit length)
}

//  Linear interpolation between two quaternion positions
//
//  Arguments: Quat<dataType>  (first and second quaternion)
//             GLdataType  (interpolation parameter [0..1])
//             Quat<dataType>  (resulting quaternion, inbetween)
//  Comments:  Fast but not nearly as smooth as Slerp
template<class dataType>
inline void Quat<dataType>::lerp( const dataType &t, const Quat<dataType> &from, const Quat<dataType> &to )
{
   Quat<dataType>     to1;
   dataType           cosom;
   dataType           scale0, scale1;

   // calc cosine
   cosom = from.vec[QUAT_X] * to.vec[QUAT_X] + 
   from.vec[QUAT_Y] * to.vec[QUAT_Y] + 
   from.vec[QUAT_Z] * to.vec[QUAT_Z] + 
   from.vec[QUAT_W]    * to.vec[QUAT_W];

   // adjust signs (if necessary)
   if ( cosom < 0.0f )
   {
      //could probably do a to1 = -to;
      to1.vec[QUAT_X] = - to.vec[QUAT_X];
      to1.vec[QUAT_Y] = - to.vec[QUAT_Y];
      to1.vec[QUAT_Z] = - to.vec[QUAT_Z];
      to1.vec[QUAT_W]    = - to.vec[QUAT_W];
   } 
   
   else  
   {
      to1.vec[QUAT_X] = to.vec[QUAT_X];
      to1.vec[QUAT_Y] = to.vec[QUAT_Y];
      to1.vec[QUAT_Z] = to.vec[QUAT_Z];
      to1.vec[QUAT_W]    = to.vec[QUAT_W];
   }

   // interpolate linearly
   scale0 = 1.0f - t;
   scale1 = t;

   // calculate final values
   res.vec[QUAT_X] = scale0 * from.vec[QUAT_X] + scale1 * to1.vec[QUAT_X];
   res.vec[QUAT_Y] = scale0 * from.vec[QUAT_Y] + scale1 * to1.vec[QUAT_Y];
   res.vec[QUAT_Z] = scale0 * from.vec[QUAT_Z] + scale1 * to1.vec[QUAT_Z];
   res.vec[QUAT_W] = scale0 * from.vec[QUAT_W] + scale1 * to1.vec[QUAT_W];
}

// From Adv Anim and Rendering Tech. Pg 364
template<class dataType>
void Quat<dataType>::slerp( dataType t, const Quat<dataType>& p, const Quat<dataType>& q )
{
   Quat<dataType> to;
   double omega, cosom, sinom, sclp, sclq;
   //int i;

   // calc cosine
   cosom = p[QUAT_X] * q[QUAT_X] + 
           p[QUAT_Y] * q[QUAT_Y] + 
           p[QUAT_Z] * q[QUAT_Z] +
           p[QUAT_W] * q[QUAT_W];

   // adjust signs (if necessary)
   if ( cosom < 0.0f )
   {
      cosom = -cosom;
      to.vec[0] = -q.vec[0];   // Reverse all signs
      to.vec[1] = -q.vec[1];  
      to.vec[2] = -q.vec[2];
      to.vec[3] = -q.vec[3];
   } 
   else
   {
      to = q;
   }

   // Calculate coefficients
   if ((1.0f - cosom) > 0.0001f)
   {
      // Standard case (slerp)
      omega = kev::ACOS(cosom);
      sinom = kev::SIN(omega);
      sclp  = kev::SIN((1.0f - t)*omega)/sinom;
      sclq  = kev::SIN(t*omega)/sinom;
   }
   else
   {
      // Very close, do linear interp
      sclp = 1.0f - t;
      sclq = t;
   }

   vec[QUAT_X] = sclp * p[QUAT_X] + sclq * to[QUAT_X];
   vec[QUAT_Y] = sclp * p[QUAT_Y] + sclq * to[QUAT_Y];
   vec[QUAT_Z] = sclp * p[QUAT_Z] + sclq * to[QUAT_Z];
   vec[QUAT_W] = sclp * p[QUAT_W] + sclq * to[QUAT_W];
}

template<class dataType>
void Quat<dataType>::squad(dataType _t, const Quat<dataType>& _q1, const Quat<dataType>& _q2, const Quat<dataType>& _a, const Quat<dataType>& _b)
{ 
   assert( false && "not implemented" ); 
}

//: complex exponentiation 
//!POST: sets self to the exponentiation of quat
// NOTE: safe to pass self as argument
template<class dataType>
void Quat<dataType>::exp( const Quat<dataType>& quat )
{
   dataType len1, len2;

   len1 = kev::SQRT( quat.vec[QUAT_X] * quat.vec[QUAT_X] + 
                          quat.vec[QUAT_Y] * quat.vec[QUAT_Y] + 
                          quat.vec[QUAT_Z] * quat.vec[QUAT_Z] );
   if (len1 > 0.0f)
      len2 = kev::SIN( len1 ) / len1;
   else
      len2 = 1.0f;

   vec[QUAT_X] = quat.vec[QUAT_X] * len2;
   vec[QUAT_Y] = quat.vec[QUAT_Y] * len2;
   vec[QUAT_Z] = quat.vec[QUAT_Z] * len2;
   vec[QUAT_W] = kev::COS( len1 );
}

//: complex logarithm
//!POST: sets self to the log of quat
template<class dataType>
void Quat<dataType>::log( const Quat<dataType>& quat ) 
{
   dataType length;

   length = kev::SQRT( quat.vec[QUAT_X] * quat.vec[QUAT_X] + 
                       quat.vec[QUAT_Y] * quat.vec[QUAT_Y] + 
                       quat.vec[QUAT_Z] * quat.vec[QUAT_Z] );

   // avoid divide by 0
   if (quat.vec[QUAT_W] != 0.0)
      length = kev::ATAN( length / quat.vec[QUAT_W] );
   else 
      length = kev::PI_D / 2.0f;

   vec[QUAT_W] = 0.0f;
   vec[QUAT_X] = quat.vec[QUAT_X] * length;
   vec[QUAT_Y] = quat.vec[QUAT_Y] * length;
   vec[QUAT_Z] = quat.vec[QUAT_Z] * length;
}

//: output method
template<class dataType>
std::ostream& Quat<dataType>::outStreamRaw( std::ostream& out ) const
{
   //out << "w: " << vec[QUAT_W] << "  x: " << vec[QUAT_X] << "  y: " << vec[QUAT_Y] << "  z: " << vec[QUAT_Z];
   out << vec[QUAT_W] << ", " << vec[QUAT_X] << ", " << vec[QUAT_Y] << ", " << vec[QUAT_Z];
   return out;
}

//: output method
template<class dataType>
std::ostream& Quat<dataType>::outStreamReadable( std::ostream& out ) const
{
   dataType rad;
   dataType x, y, z;
   this->getRot( rad, x, y, z );

   out << kev::rad2deg( rad ) << " deg, " << x << ", " << y << ", " << z;
   return out;
}

//: output operator
template<class dataType>
std::ostream& operator<<( std::ostream& out, const Quat<dataType>& q )
{
   q.outStreamReadable( out );
   //q.outStreamRaw( out );
   return out;
}

#endif

