
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
//    $Date: 2002-01-17 00:04:59 $
//    $Revision: 1.1.1.1 $
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

#ifndef _CONSTANTS_AND_TYPEDEFS_H__
#define _CONSTANTS_AND_TYPEDEFS_H__

#include <string>
#include <iostream>
#include <stdio.h>
#include <math.h>

// Undef MAX and MIN macros if they are already defined since they will cause
// some nasty compiler errors since they're defined as functions here in the kev
// namespace. This really only applies to builds against VRJuggler.
// NOTE: we should really change MAX to Max and MIN to Min
#ifdef MAX
#undef MAX
#endif

#ifdef MIN
#undef MIN
#endif


namespace pixmi
{
   /*******************************/
   /* math and assorted functions */
   /*******************************/
   inline double SIN( const double& arg )
   {
      return ::sin( arg );
   }
   
   inline float SIN( const float& arg )
   {
      return ::sinf( arg );
   }
   
   inline double SQRT( const double& arg )
   {
      return ::sqrt( arg );
   }
   
   inline float SQRT( const float& arg )
   {
      return ::sqrtf( arg );
   }
   
   inline double COS( const double& arg)
   {
      return ::cos( arg );
   }
   
   inline float COS( const float& arg )
   {
      return ::cosf( arg );
   }

   inline double TAN( const double& arg )
   {
      return ::tan( arg );
   }
   
   inline float TAN( const float& arg )
   {
      return ::tanf( arg );
   }
   
   inline double ATAN( const double& arg )
   {
      return ::atan( arg );
   }
   
   inline float ATAN( const float& arg )
   {
      return ::atanf( arg );
   }
   
   inline double ATAN2( const double& arg1, const double& arg2 )
   {
      return ::atan2( arg1, arg2 );
   }
   
   inline float ATAN2( const float& arg1, const float& arg2 )
   {
      return ::atan2f( arg1, arg2 );
   }
   
   inline double ACOS( const double& arg )
   {
      return ::acos( arg );
   }
   
   inline float ACOS( const float& arg )
   {
      return ::acosf( arg );
   }
   
   inline double ASIN( const double& arg )
   {
      return ::asin( arg );
   }
   
   inline float ASIN( const float& arg )
   {
      return ::asinf( arg );
   }
   
   
   
   // Compute the factorial
   // give - an object who's type has operator++, operator=, operator<=, and operator*= defined.
   //        it should be a single valued scalar type such as an int, float, double etc....
   // NOTE: This could be faster with a lookup table, but then wouldn't work templated : kevin
   template<class T>
   inline T FACTORIAL(T rhs)
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
   inline T ABS(const T& num)
       { return (num < 0) ? -num : num; }
       

   // test for equality with tolerance...
   template <class dataType>
   inline bool isEqual( const dataType& a, const dataType& b, const dataType& tolerance )
   {
      return ABS( a - b ) <= tolerance;
   }

   /*************/
   /* Max & min */
   /*************/

   // returns the maximum of a, b, and c.
   template<class T> 
   inline const T& MAX(const T& a, const T& b, const T& c)
       { return (a>=b) ? ((a>=c)?a:c) : ((b>=c)?b:c); }

   // returns the minimum of a, b, and c.
   template<class T> 
   inline const T& MIN(const T& a, const T& b, const T& c)
       { return (a<=b) ? ((a<=c)?a:c) : ((b<=c)?b:c); }

   // returns the maximum of a, b
   template<class T> 
   inline const T& MAX(const T& a, const T& b)
       { return (a > b) ? a : b; }

   // returns the minimum of a, b
   template<class T> 
   inline const T& MIN(const T& a, const T& b)
       { return (a < b) ? a : b; }

   //: [something] to the power of 2
   template<class T> 
   inline const T& POW2(const T& num)
      { return num * num; }

   //: [something] to the power of 3
   template<class T> 
   inline T POW3(const T& num)
      { return POW2(num) * num; }

   //: [something] to the power of 4
   template<class T> 
   inline T POW4(const T& num)
      { return POW3(num) * num; }

   //: [something] to the power of 5
   template<class T> 
   inline T POW5(const T& num) 
      { return POW4(num) * num; }

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
   
   //: Alert
   //  basically pops an informational message to the user if "verify" is false
   //  if expression "verify" is false, then "text" is logged
   inline void Alert( const bool& verify, const char* const text )
   {
      if (verify == false)
      {
         std::cerr<<text<<"\n"<<std::flush;
      }
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
