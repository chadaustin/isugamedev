
//////////////////////////////////////////////////////////////////
//
//                         -=  Conversion routines   =-
//
// Definition: ""
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: convert.h,v $
//    $Date: 2002-01-11 00:59:29 $
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
#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

#include "Vec3.h"
#include "Matrix4f.h"

namespace kev
{
   //: matrix = quat
   inline void quat2mat( const Quat<float>& quat, Matrix4f& mat )
   {
      const int W = Quat<float>::QUAT_W;
      const int X = Quat<float>::QUAT_X;
      const int Y = Quat<float>::QUAT_Y;
      const int Z = Quat<float>::QUAT_Z;

      mat[0]  = 1.0f  - 2.0f * (quat[Y] * quat[Y] + quat[Z] * quat[Z]);
      mat[1]  = 2.0f         * (quat[X] * quat[Y] + quat[W] * quat[Z]);
      mat[2]  = 2.0f         * (quat[X] * quat[Z] - quat[W] * quat[Y]);
      mat[3]  = 0.0f;

      mat[4]  = 2.0f         * (quat[X] * quat[Y] - quat[W] * quat[Z]);
      mat[5]  = 1.0f  - 2.0f * (quat[X] * quat[X] + quat[Z] * quat[Z]);
      mat[6]  = 2.0f         * (quat[Y] * quat[Z] + quat[W] * quat[X]);
      mat[7]  = 0.0f;

      mat[8]  = 2.0f         * (quat[X] * quat[Z] + quat[W] * quat[Y]);
      mat[9]  = 2.0f         * (quat[Y] * quat[Z] - quat[W] * quat[X]);
      mat[10] = 1.0f  - 2.0f * (quat[X] * quat[X] + quat[Y] * quat[Y]);
      mat[11] = 0.0f;

      mat[12] = 0.0f;
      mat[13] = 0.0f;
      mat[14] = 0.0f;
      mat[15] = 1.0f;
   }
   
   //: matrix = quat and pos
   inline void quat2mat( const Vec3<float>& pos, const Quat<float>& quat, Matrix4f& mat )
   {
      kev::quat2mat( quat, mat );

      mat[12] = pos[0];
      mat[13] = pos[1];
      mat[14] = pos[2];
      mat[15] = 1.0f;
   }


   //: quat and pos = matrix
   inline void mat2quat( const Matrix4f& m, Vec3<float>& pos, Quat<float>& quat )
   {
      float    tr, s;
      float    q[4];
      int      i, j, k;
      int      nxt[3] = {1, 2, 0};

      tr = m[0] + m[5] + m[10];

      m.getTrans( pos );

      // check the diagonal
      if (tr > 0.0f) 
      {
         s = kev::SQRT( tr + 1.0f );
         quat[Quat<float>::QUAT_W] = s * 0.5f;
         s = 0.5f / s;

         quat[Quat<float>::QUAT_X] = (m[6] - m[9]) * s;
         quat[Quat<float>::QUAT_Y] = (m[8] - m[2]) * s;
         quat[Quat<float>::QUAT_Z] = (m[1] - m[4]) * s;
      }
      // diagonal is negative
      else 
      {
         i = 0;

         if (m[5]  > m[0]) i = 1;
         if (m[10] > m(i, i)) i = 2;

         j = nxt[i];
         k = nxt[j];

         s = kev::SQRT(( m(i, i) - (m(j, j)+m(k, k)) ) + 1.0f );

         q[i] = s * 0.5f;

         if ( s != 0.0f ) 
            s = 0.5f / s;

         q[3] = (m(j, k) - m(k, j)) * s;
         q[j] = (m(i, j) + m(j, i)) * s;
         q[k] = (m(i, k) + m(k, i)) * s;

         quat[Quat<float>::QUAT_X] = q[0];
         quat[Quat<float>::QUAT_Y] = q[1];
         quat[Quat<float>::QUAT_Z] = q[2];
         quat[Quat<float>::QUAT_W] = q[3];
      }
   }
};


#endif // ! CONVERT_H_INCLUDED
