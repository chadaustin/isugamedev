
//////////////////////////////////////////////////////////////////
//
//                         -=     Vertex     =-
//
// Definition: "a vertex..., color, tex, point, normal"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Vertex.h,v $
//    $Date: 2001-09-14 05:02:34 $
//    $Revision: 1.1 $
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
#ifndef VERTEX_H
#define VERTEX_H

#include "Vec3.h"
#include "Vec2.h"
#include "Vec4.h"

namespace kev
{
      template <class dataType>
      class Vertex
      {
      public:
         Vertex() : mCoord(), mTexCoord(), mColor(), mNormal()
         {
         }
         
         Vertex( dataType x, dataType y, dataType z ) : mCoord(x, y, z), mTexCoord(), mColor(), mNormal()
         {
         }
         
         void outputDebug() const
         {
            std::cout<<"["<<mCoord[0]<<" "<<mCoord[1]<<" "<<mCoord[2]<<"], "<<std::flush;
         }

         inline void setCoord( const Vec3<dataType>& coord ) { mCoord = coord; }
         inline Vec3<dataType>& coord() { return mCoord; }
         inline const Vec3<dataType>& coord() const { return mCoord; }
         
         inline void setTexCoord( const Vec2<dataType>& texcoord ) { mTexCoord = texcoord; }
         inline Vec2<dataType>& texcoord() { return mTexCoord; }
         inline const Vec2<dataType>& texcoord() const { return mTexCoord; }
         
         inline void setColor( const Vec4<dataType>& color ) { mColor = color; }
         inline Vec4<dataType>& color() { return mColor; }
         inline const Vec4<dataType>& color() const { return mColor; }
         
         inline void setNormal( const Vec3<dataType>& normal ) { mNormal = normal; }
         inline Vec3<dataType>& normal() { return mNormal; }
         inline const Vec3<dataType>& normal() const { return mNormal; }
         

         Vertex( const Vertex& vertex ) : mCoord(vertex.coord()), mTexCoord(vertex.texcoord()), mColor(vertex.color()), mNormal(vertex.normal())
         {
         }
         
         Vertex& operator=( const Vertex& vertex )
         {
            this->setCoord( vertex.coord() );
            this->setColor( vertex.color() );
            this->setNormal( vertex.normal() );
            this->setTexCoord( vertex.texcoord() );
            return *this;
         }

                  
      private:
         Vec3<dataType> mCoord;
         Vec2<dataType> mTexCoord;
         Vec4<dataType> mColor;
         Vec3<dataType> mNormal;
      };
};


#endif
