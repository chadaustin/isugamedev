
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     Defines.h     =-
//
//  Define.h: Typesafe constant definitions, 
//            templated functions, 
//            and macros.
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Defines.h,v $
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

//////////////////////////////////////////////////////////////////////////////

#ifndef _CONStanTS_AND_TYPEDEFS_H__
#define _CONStanTS_AND_TYPEDEFS_H__

#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>

// Undef Max and Min macros if they are already defined since they will cause
// some nasty compiler errors since they're defined as functions here in the kev
// namespace. This really only applies to builds against VRJuggler.
// NOTE: we should really change Max to Max and Min to Min
#ifdef Max
#undef Max
#endif

#ifdef Min
#undef Min
#endif

// Put everything in the kev namespace
namespace defines
{

   /********/
   /* Misc */
   /********/
   // Converts a number in radians to a number in degrees
   const double    TO_DEG_D         = 57.2957795131;

   // Converts a number in radians to a number in degrees
   const float     TO_DEG_F         = 57.2957795131f;

   // Converts a number in degrees to a number in radians
   const double    TO_RAD_D         = 0.01745329252;

   // Converts a number in degrees to a number in radians
   const float     TO_RAD_F         = 0.01745329252f;

   // Zero - Why?
   const double    ZERO_D           = 1e-6;

   // Zero - Why?
   const float     ZERO_F           = 1e-6f;

   // A huge number - not nessesarily the largest for a 64 bit number
   const double    INFINITY_D       = 1e20;

   // A huge number - not nessesarily the largest for a 32 bit number
   const float     INFINITY_F       = 1e20f;

   // Powell tau d - in 64bit precision
   const double    POWELL_TAU_D     = 0.6180339887499;

   // Powell tau d - in 32bit precision
   const float     POWELL_TAU_F     = 0.6180339887499f;

   // log of Powell tau d - in 64bit precision
   const double    LOG_POWELL_TAU_D   = -0.20898764025;

   // log of Powell tau d - in 32bit precision
   const float     LOG_POWELL_TAU_F   = -0.20898764025f;

   /*************/
   /* Log stuff */
   /*************/
   // e
   const float     E_F           = 2.7182818284590452354f;

   // e
   const double    E_D           = 2.7182818284590452354;

   // Log (base 10) 2E
   const double    LOG2E_D       = 1.4426950408889634074;

   // Log (base 10) 2E
   const float     LOG2E_F       = 1.4426950408889634074f;

   // Log (base 10) 10E
   const double    LOG10E_D      = 0.43429448190325182765;

   // Log (base 10) 10E
   const float     LOG10E_F      = 0.43429448190325182765f;

   // Natural Log of 2
   const float     LN2_F         = 0.69314718055994530942f;

   // Natural Log of 2
   const double    LN2_D         = 0.69314718055994530942;

   // Natural Log of 10
   const float     LN10_F        = 2.30258509299404568402f;

   // Natural Log of 10
   const double    LN10_D        = 2.30258509299404568402;

   /*****************/
   /* Trig/pi stuff */
   /*****************/
   // PI - 64 bit precision
   const double    PI_D          = 3.14159265358979323846264338327950288419716939937510;

   // PI - 32 bit precision
   const float     PI_F          = 3.14159265358979323846f;

   // 2 * PI - 32 bit precision
   const float     TWO_PI_F        = 6.28318530718f;

   // 2 * PI - 64 bit precision
   const double    TWO_PI_D        = 6.28318530718;

   // 1 / PI - 64 bit precision
   const double    INV_PI_D      = 0.31830988618379067154;

   // 1 / PI - 32 bit precision
   const float     INV_PI_F      = 0.31830988618379067154f;

   // 1 / (2*PI) - 64 bit precision
   const double    INV_TWO_PI_D    = 0.159154943092;

   // 1 / (2*PI) - 32 bit precision
   const float     INV_TWO_PI_F    = 0.159154943092f;

   // PI / 2 - 64 bit precision
   const double    PI_OVER_TWO_D   = 1.57079632679489661923;

   // PI / 2 - 32 bit precision
   const float     PI_OVER_TWO_F   = 1.57079632679489661923f;

   // PI / 4  - 64 bit precision
   const double    PI_OVER_FOUR_D   = 0.78539816339744830962;

   // PI / 4  - 32 bit precision
   const float     PI_OVER_FOUR_F   = 0.78539816339744830962f;

   // 2 / PI  - 64 bit precision
   const double    TWO_OVER_PI_D   = 0.63661977236758134308;

   // 2 / PI  - 32 bit precision
   const float     TWO_OVER_PI_F   = 0.63661977236758134308f;

   // 2 / sqrt(PI) - 64 bit precision
   const double    TWO_OVER_sqrt_PI_D = 1.12837916709551257390;

   // 2 / sqrtf(PI) - 32 bit precision
   const float     TWO_OVER_sqrt_PI_F = 1.12837916709551257390f;

   // (2 * PI) / 3 - 64 bit precision
   const double    TWO_PI_OVER_THREE_D = 2.0943951023933334;

   // (2 * PI) / 3 - 32 bit precision
   const float     TWO_PI_OVER_THREE_F = 2.0943951023933334f;

   /**********/
   /* Square */
   /* Root   */
   /* Stuff  */
   /**********/

   // Same as sqrt(2.0)
   const double    sqrt_TWO_D      = 1.41421356237309504880;

   // Same as sqrtf(2.0f)
   const float     sqrt_TWO_F      = 1.41421356237309504880f;

   // Same as 1.0 / sqrt(2.0)
   const double    INV_sqrt_TWO_D  = 0.70710678118654752440;

   // Same as 1.0f / sqrtf(2.0f)
   const float     INV_sqrt_TWO_F  = 0.70710678118654752440f;

   // Same as sqrt(3.0)
   const double    sqrt_THREE_D      = 1.73205080757;

   // Same as sqrtf(3.0f)
   const float     sqrt_THREE_F      = 1.73205080757f;

   // Same as 1.0 / sqrt(3.0)
   const double    INV_sqrt_THREE_D    = 0.577350269189;

   // Same as 1.0f / sqrtf(3.0f)
   const float     INV_sqrt_THREE_F    = 0.577350269189f;

   /********/
   /* Bool */
   /********/
   // True
   const bool XzTrue               = true;

   // False
   const bool XzFalse                = false;

   /*********/
   /* Color */
   /*********/
   // should move this someday to the color class
   const float UNDEFINED_HUE_COLOR = 6.9696969696969f;

   /*******************************/
   /* Standard Data Type Typedefs */
   /*******************************/
   //: Bool
   typedef bool               XzBool;

   //: char
   typedef char               XzChar;

   //: unsigned char
   typedef unsigned char         XzUchar;

   //: unsigned short
   typedef unsigned short         XzUshort;

   //: short
   typedef   short               XzShort;

   //: integer
   typedef int                  XzInt;

   //: unsigned integer
   typedef unsigned int         XzUint;

   //: long
   typedef   long               XzLong;

   //: unsigned long
   typedef unsigned long         XzUlong;

   //: float
   typedef float               XzFloat;

   //: double
   typedef double               XzDouble;

   /***********************************/
   /* Unambiguous Data Type Typedefs  */
   /***********************************/
   //: an 8bit value
   typedef char               XzInt8;

   //: an unsigned 8bit integer
   typedef unsigned char         XzUint8;

   //: a 16bit value
   typedef short               XzInt16;

   //: an unsigned 16bit value
   typedef unsigned short         XzUint16;

   //: a 32bit integer
   typedef int                  XzInt32;

   //: an unsigned 32bit integer
   typedef unsigned int         XzUint32;

   //: 32bit floating point number
   typedef float               XzFloat32;

   //: a 64bit floating point number
   typedef double               XzFloat64;

   //: a 64bit integer
   typedef long               XzInt64;

   //: an unsigned 64bit integer
   typedef unsigned long         XzUint64;


   /*****************************/
   /* Other Data Type Typedefs  */
   /*****************************/
   //: One byte - an 8 bit unsigned number
   typedef   unsigned char         XzByte;

   //: One word - a 16 bit unsigned number
   typedef   unsigned short         XzWord;

   //: a double word - a 32 bit unsigned number
   typedef   unsigned int         XzDword;
};
using namespace defines;

namespace kev
{
   /*******************************/
   /* math and assorted functions */
   /*******************************/
   inline double sin( const double& arg )
   {
      return ::sin( arg );
   }
   
   inline float sin( const float& arg )
   {
      return ::sinf( arg );
   }
   
   inline double sqrt( const double& arg )
   {
      return ::sqrt( arg );
   }
   
   inline float sqrt( const float& arg )
   {
      return ::sqrtf( arg );
   }
   
   inline double cos( const double& arg)
   {
      return ::cos( arg );
   }
   
   inline float cos( const float& arg )
   {
      return ::cosf( arg );
   }

   inline double tan( const double& arg )
   {
      return ::tan( arg );
   }
   
   inline float tan( const float& arg )
   {
      return ::tanf( arg );
   }
   
   inline double atan( const double& arg )
   {
      return ::atan( arg );
   }
   
   inline float atan( const float& arg )
   {
      return ::atanf( arg );
   }
   
   inline double atan2( const double& arg1, const double& arg2 )
   {
      return ::atan2( arg1, arg2 );
   }
   
   inline float atan2( const float& arg1, const float& arg2 )
   {
      return ::atan2f( arg1, arg2 );
   }
   
   inline double acos( const double& arg )
   {
      return ::acos( arg );
   }
   
   inline float acos( const float& arg )
   {
      return ::acosf( arg );
   }
   
   inline double asin( const double& arg )
   {
      return ::asin( arg );
   }
   
   inline float asin( const float& arg )
   {
      return ::asinf( arg );
   }
   
   
   
   // Compute the factorial
   // give - an object who's type has operator++, operator=, operator<=, and operator*= defined.
   //        it should be a single valued scalar type such as an int, float, double etc....
   // NOTE: This could be faster with a lookup table, but then wouldn't work templated : kevin
   template<class T>
   inline T factorial(T rhs)
   {
      T lhs = 1;
    
      for( T x = 1; x <= rhs; ++x )
      {
         lhs *= x;
      }
    
      return lhs;
   }

   //: Absolute value
   // give - any single value type that can be 
   //        compared to a scalar such as int, float, double, complex, short, etc...
   // i.e: 1, 1.0, or 1.0f are all valid
   template<class T>
   inline T abs(const T& num)
       { return (num < 0) ? -num : num; }
       

   // test for equality with tolerance...
   template <class dataType>
   inline bool isEqual( const dataType& a, const dataType& b, const dataType& tolerance )
   {
      return abs( a - b ) <= tolerance;
   }

   /*************/
   /* Max & min */
   /*************/

   // returns the maximum of a, b, and c.
   template<class T> 
   inline const T& Max(const T& a, const T& b, const T& c)
       { return (a>=b) ? ((a>=c)?a:c) : ((b>=c)?b:c); }

   // returns the minimum of a, b, and c.
   template<class T> 
   inline const T& Min(const T& a, const T& b, const T& c)
       { return (a<=b) ? ((a<=c)?a:c) : ((b<=c)?b:c); }

   // returns the maximum of a, b
   template<class T> 
   inline const T& Max(const T& a, const T& b)
       { return (a > b) ? a : b; }

   // returns the minimum of a, b
   template<class T> 
   inline const T& Min(const T& a, const T& b)
       { return (a < b) ? a : b; }

   //: [something] to the power of 2
   template<class T> 
   inline const T& pow2(const T& num)
      { return num * num; }

   //: [something] to the power of 3
   template<class T> 
   inline T pow3(const T& num)
      { return pow2(num) * num; }

   //: [something] to the power of 4
   template<class T> 
   inline T pow4(const T& num)
      { return pow3(num) * num; }

   //: [something] to the power of 5
   template<class T> 
   inline T pow5(const T& num) 
      { return pow4(num) * num; }

   // Round the floating point value up or down 
   // result - rounds up if value is >= x.5
   //          rounds down if value is < x.5
   template<class T> 
   inline T round( T value )
   {
      return static_cast<T>( static_cast<int>( value + static_cast<T>(0.5) ) );
   }

   // Linear Interpolation for a single value
   template<class DataType>
   inline void lerp( DataType& result, const float& lerp, 
                     const DataType& from, 
                     const DataType& to )
   {
       DataType offset = to - from;
       result = from + offset*lerp;
   }
   
   inline float rad2deg( float rad )
   {
      return rad * TO_DEG_F;
   }
   inline double rad2deg( double rad )
   {
      return rad * TO_DEG_D;
   }   
   inline float deg2rad( float deg )
   {
      return deg * TO_RAD_F;
   }
   inline double deg2rad( double deg )
   {
      return deg * TO_RAD_D;
   }   
   
   inline void string2int( const std::string& s, int& i )
   {
      i = ::atoi( s.c_str() );
   }
   inline void string2float( const std::string& s, float& f )
   {
      f = ::atof( s.c_str() );
   }
   inline void string2bool( const std::string& s, bool& b )
   {
      if (s == "1" || s == "true") b = true; else b = false;
   }
}; // end of namespace kev



#endif
