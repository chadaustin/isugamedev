
//////////////////////////////////////////////////////////////////
//
//                     -=     aux math functions     =-
//
// Definition: "collection of math routines that have dependencies on 
//              more than 1 math class"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: extend.h,v $
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
#ifndef AUX_MATH_FUNCS
#define AUX_MATH_FUNCS


// collection of math routines that have dependencies on more than 1 math class
namespace kev
{
   // do a full (point) transform
   void xform( Vec3<float>& point, const Matrix4f& mat, const Vec3<float>& b )
   {
      float a[4];
      float c[4] = { b[0], b[1], b[2], 1.0f };

      // full xform
      a[0] = mat[0] * c[0] + mat[4] * c[1] + mat[8]  * c[2] + mat[12] * c[3];
      a[1] = mat[1] * c[0] + mat[5] * c[1] + mat[9]  * c[2] + mat[13] * c[3];
      a[2] = mat[2] * c[0] + mat[6] * c[1] + mat[10] * c[2] + mat[14] * c[3];
      a[3] = mat[3] * c[0] + mat[7] * c[1] + mat[11] * c[2] + mat[15] * c[3];

      // divide by w coord
      a[3] = 1.0f / a[3];
      point.set( a[0] * a[3], a[1] * a[3], a[2] * a[3] );
   }

   // do a rotation (vector) transform
   void xformVec( Vec3<float>& vec, const Matrix4f& mat, const Vec3<float>& b )
   {
       float a[4];
       float c[4] = { b[0], b[1], b[2], 0.0f };

      // xform by rotation component only
      a[0] = mat[0] * c[0] + mat[4] * c[1] + mat[8]  * c[2];
      a[1] = mat[1] * c[0] + mat[5] * c[1] + mat[9]  * c[2];
      a[2] = mat[2] * c[0] + mat[6] * c[1] + mat[10] * c[2];

      vec.set( a[0], a[1], a[2] );
   }
}

#endif
