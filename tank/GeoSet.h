
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     geoset     =-
//
// Description: "geometry/mesh data.  color, tex, normal, and point info."
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: GeoSet.h,v $
//    $Date: 2001-09-13 23:43:07 $
//    $Revision: 1.2 $
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
#ifndef GEOSET_INCLUDED
#define GEOSET_INCLUDED

/*
    GeoSet::setDrawMode 
     further characterizes a GeoSet's primitive type
     as flat-shaded, wireframe or compiled.  mode is a symbolic token
     specifying the mode to set and is one of:

          GeoSet::FLATSHADE           Always render the GeoSet with a flat
                                   shading model.

          GeoSet::WIREFRAME           Always render and intersect the GeoSet in
                                   wireframe. For rendering in wireframe and
                                   intersection with solid geometry, enable
                                   wireframe on an attached pfGeoState (See
                                   pfGSetGState).

          GeoSet::COMPILE_GL          At the next draw for each pfState, compile
                                   the GeoSet's geometry into a GL display
                                   list and subsequently render the display
                                   list.

          GeoSet::DRAW_GLOBJ          Select the rendering of an already created
                                   display list and do not force a compile.

          GeoSet::PACKED_ATTRS        Use the  the GeoSet's packed attribute
                                   arrays, set with the GeoSet::PACKED_ATTRS to
                                   GeoSet::setAttr, to render geometry with
                                   GL vertex arrays.  This mode is only
                                   available under OpenGL operation.
*/

#include <vector>
#include <iostream>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "GState.h"
#include "RefObj.h"

class GeoSet : public RefObj
{
public:
   GeoSet() : mGstate( NULL ), mNumVerts( 6969 ), mPrimitiveType( GeoSet::TRIS ), mNumPrimitives( 9696 )
   {
   }

   ~GeoSet()
   {
      if ( mGstate != NULL)
      {
         mGstate->unref();
      }
   }

    //: sets a GeoSet attribute binding type, attribute list,
    // and attribute index list. These GeoSet attributes include vertex
    // coordinate, color specification, normal vector, texture coordinate, or
    // packed attribute array which is supplied in list form to the GeoSet.
    //
    // The optional attribute index list is a list of unsigned short integers
    // which index the attribute list. The attribute binding type specifies how
    // the lists are interpreted to define geometry, specifying for example,
    // that the color attribute list provides a color for each vertex
    // (GeoSet::PER_VERTEX) or just an overall color for the entire GeoSet
    // (GeoSet::OVERALL).
    //
    // Only certain combinations of attributes and binding types make sense.
    // For example, vertices clearly must be specified per-vertex and the
    // utility of texture coordinates specified other than per-vertex is
    // questionable.
    //
    //  give a list of normals, colors, verts, etc...
    //
    // attr  is a symbolic token that identifies a specific attribute type and
    //       is one of:
    //
    //       GeoSet::COLOR4              alist must be list of Vec4 colors
    //
    //       GeoSet::NORMAL3             alist must be list of Vec3 normals,
    //
    //       GeoSet::TEXCOORD2           alist must be list of Vec2 texture
    //                                coordinates,
    //
    //       GeoSet::COORD3              alist must be list of pfVec3 coordinates.
    //
    //       GeoSet::PACKED_ATTRS        specify packed attributes.
    //
    // bind  is a symbolic token that specifies an attribute binding type and is
    //       one of:
    //
    //       GeoSet::OFF                 attr is not specified and is thus
    //                                inherited,
    //
    //       GeoSet::OVERALL             attr is specified once for the entire
    //                                GeoSet,
    //
    //       GeoSet::PER_PRIM            attr is specified once per primitive,
    //
    //       GeoSet::PER_VERTEX          attr is specified once per vertex. (use this for COORD3)
    //
    //
    // ilist.  if not NULL, is an index array which indexes the attribute array,
    //  
    // alist.  If ilist is NULL, the GeoSet is non-indexed and accesses the
    //         attribute list in sequential order.
    //
    enum GsAttribute { 
        COLOR4,
        NORMAL3,        
        TEXCOORD2,      
        COORD3,         
        PACKED_ATTRS   
    };
    enum GsBind {
        OFF,          
        OVERALL,      
        PER_PRIM,     
        PER_VERTEX,
    // for packed attrs
        V2F, 
        V3F, 
        C4UB_V2F, 
        C4UB_V3F, 
        C3F_V3F, 
        N3F_V3F, 
        C4F_N3F_V3F, 
        T2F_V3F, 
        T4F_V4F, 
        T2F_C4UB_V3F, 
        T2F_C3F_V3F, 
        T2F_N3F_V3F, 
        T2F_C4F_N3F_V3F, 
        T4F_C4F_N3F_V4F
    };
    
    // overloaded func to set geometry attributes...  
    // color, normals, points (coords), texcoords.
    //
    // TODO: add check for each indexlist[0...n] being out of bounds.
    void setAttr( const GsAttribute& attr = GeoSet::COORD3, 
                const GsBind& bind = GeoSet::PER_VERTEX, 
                void* attrlist = NULL, unsigned int* indexlist = NULL )
    {
        

        // convert everything to T2F_C4F_N3F_V3F format
        switch (attr)
        {
        case GeoSet::COORD3:
            {
                if (bind == GeoSet::PER_VERTEX)
                {
                   Vec3<float>* verts = reinterpret_cast<Vec3<float> *>( attrlist );
                   for (int x = 0; x < mNumVerts; ++x)
                   {
                       if (indexlist == NULL)
                           mVertexArray[x].v = verts[x];
                       else
                           mVertexArray[x].v = verts[indexlist[x]];
                   }
                }
                else if (bind == GeoSet::PER_PRIM)
                {
                   assert( false );
                }
                else
                {
                   assert( false );
                }
                break;
            }
        case GeoSet::NORMAL3:
            {
                Vec3<float>* normals = reinterpret_cast<Vec3<float> *>( attrlist );
                if (bind == GeoSet::PER_VERTEX)
                {
                    assert (bind == GeoSet::PER_VERTEX);

                    for (int x = 0; x < mNumVerts; ++x)
                    {
                        if (indexlist == NULL)
                            mVertexArray[x].n = normals[x];
                        else
                            mVertexArray[x].n = normals[indexlist[x]];
                    }
                }

                else if (bind == GeoSet::PER_PRIM)
                {
                    switch (mPrimitiveType)
                    {
                    case QUADS:
                    {
                        // TODO; check that it's a multiple of 4
                        for (int x = 0; x < mNumPrimitives; ++x)
                        {
                            int in = 0;
                            if (indexlist == NULL)
                            {
                                in = x;
                            }
                            else
                            {
                                in = indexlist[x];
                            }

                            int y = x * 4;
                            mVertexArray[y].n = normals[in];
                            mVertexArray[y+1].n = normals[in];
                            mVertexArray[y+2].n = normals[in];
                            mVertexArray[y+3].n = normals[in];
                        }
                    }
                    break;
                     case TRISTRIPS:
                        {
                           int y = 0;
                           for (int x = 0; x < mNumPrimitives; ++x)
                           {
                               int in = 0;
                               if (indexlist == NULL)
                               {
                                   in = x;
                               }
                               else
                               {
                                   in = indexlist[x];
                               }

                               for (int g = 0; g < mNumVertsInEachPrim[x]; ++g)
                               {
                                  mVertexArray[y+g].n = normals[in];
                               }
                               y += mNumVertsInEachPrim[x];
                           }
                        }
                        break;
                    }
                }
                else if (bind == GeoSet::OVERALL)
                {
                   for (int x = 0; x < mNumVerts; ++x)
                   {
                      if (indexlist == NULL)
                          mVertexArray[x].n = normals[0];
                      else
                          mVertexArray[x].n = normals[indexlist[0]];
                   }
                }                
                break;
            }
        case GeoSet::TEXCOORD2:
            {
                assert (bind == GeoSet::PER_VERTEX);
                Vec2<float>* texcoords = reinterpret_cast<Vec2<float> *>( attrlist );
                for (int x = 0; x < mNumVerts; ++x)
                {
                    if (indexlist == NULL)
                        mVertexArray[x].t = texcoords[x];
                    else
                        mVertexArray[x].t = texcoords[indexlist[x]];
                }
                break;
            }
        case GeoSet::COLOR4:
            {
                Vec4<float>* colors = reinterpret_cast<Vec4<float> *>( attrlist );
                if (bind == GeoSet::PER_VERTEX)
                {
                    for (int x = 0; x < mNumVerts; ++x)
                    {
                        if (indexlist == NULL)
                        {
                            mVertexArray[x].c = colors[x];
                        }
                        else
                        {
                            mVertexArray[x].c = colors[indexlist[x]];
                        }
                    }
                }

                else if (bind == GeoSet::PER_PRIM)
                {
                    // TODO: add support for per_prim
                    assert (bind == GeoSet::PER_VERTEX);
                }
                else if (bind == GeoSet::OVERALL)
                {
                   for (int x = 0; x < mNumVerts; ++x)
                   {
                      if (indexlist == NULL)
                          mVertexArray[x].c = colors[0];
                      else
                          mVertexArray[x].c = colors[indexlist[0]];
                   }
                }
                break;
            }
        default:
            assert( false );
        }
    }

    void setGstate( kev::GState* g )
    {
       if ( mGstate != NULL)
       {
          mGstate->unref();
       }   
       mGstate = g;
       if ( mGstate != NULL)
       {
          mGstate->ref();
       }
    }
    kev::GState* gstate() { return mGstate; }
   
    // next pass of renderer makes this a display list
    void compile() { assert( false && "not implemented" ); }

    //: set the primitive type that this is.
    //  specifies the type of primitives found in a
    //  GeoSet.  Type is a symbolic token and is one of:
    enum GsPrimType {
        POINTS,
        LINES,
        LINESTRIPS,
        FLAT_LINESTRIPS,
        TRIS,
        QUADS,
        TRISTRIPS,
        FLAT_TRISTRIPS,
        TRIFANS,
        FLAT_TRIFANS,
        POLYS
    };
    // NOTE: setPrimLengths is nessesary for strip primitives, and polys
    void setPrimType( const GsPrimType& primType = GeoSet::TRIS )
    {
        mPrimitiveType = primType;
    }

    const GsPrimType& getPrimType() const
    {
        return mPrimitiveType;
    }

    //: nessesary for strip primitives, and polys
    //  set lengthList[x] = number of vertices in strip/polygon x
    //  give the size of the array
    void setPrimLengths( const int* const lengthList, const int& size )
    {
        // this is so push_back starts at [0].
        mNumVertsInEachPrim.clear();
        mPrimIndex.clear();

        mNumVertsInEachPrim.reserve( size );
        mPrimIndex.reserve( size );
        
        int sum = 0;
        for (int x = 0; x < size; ++x)
        {
            mNumVertsInEachPrim.push_back( lengthList[x] );
            mPrimIndex.push_back( sum );
            sum += lengthList[x];
        }
    }

    // give the primitive number you want to get the length of.
    const int& getPrimLength( const int& index = -1 ) const
    {
        int temp = mNumVertsInEachPrim[index];
        assert( index < mNumVertsInEachPrim.size() );
        return mNumVertsInEachPrim[index];
    }

    //: set the number of primitives contained within this GeoSet
    //  i.e.: # of points, # of lines, # of Tris, etc...
    void setNumPrims( const int numPrimitives )
    {
        mNumPrimitives = numPrimitives;
    }

    const int& getNumPrims() const
    {
        return mNumPrimitives;
    }
    
    
    // give the primitive number you want to get the length of.
    // or give -1 if you want the total verts in this GeoSet.
    int getNumVerts( const int& primIndex = -1 ) const
    {
        if (primIndex == -1)
            return mNumVerts;
        else 
        {
            assert( primIndex < mNumVertsInEachPrim.size() );
            return mNumVertsInEachPrim[primIndex];
        }
    }

   void allocate()
   {
        mNumVerts = 0;
      switch (mPrimitiveType)
        {
        case POINTS:
           mNumVerts = mNumPrimitives;
           break;
        case LINES:
           mNumVerts = mNumPrimitives * 2;
           break;
        case TRIS: 
           mNumVerts = mNumPrimitives * 3;
           break;
        case QUADS:
            mNumVerts = mNumPrimitives * 4;
           break;

        // strip and POLY primitives must use the length array: mNumVertsInEachPrim
        case TRIFANS:
        case FLAT_TRIFANS:
        case FLAT_TRISTRIPS:
        case TRISTRIPS:
        case LINESTRIPS:
        case FLAT_LINESTRIPS:
        case POLYS:
            {
                for (int x = 0; x < mNumPrimitives; ++x)
                {
                    mNumVerts += mNumVertsInEachPrim[x];
                }
            }
            break;
        default:
            assert (false);
            break;
        }

        // size the array.  push_back should begin at [0]
        mVertexArray.clear();
        mVertexArray.reserve( mNumVerts );
        dataT2F_C4F_N3F_V3F space;
        for (int x = 0; x < mNumVerts; ++x)
        {
            mVertexArray.push_back( space );
        }
   }

    //: get the vertex array (in T2F_C4F_N3F_V3F format)
    //  set x = primitive number if using strip or POLY primitives
    //  set x = -1 otherwise
   inline float* data( const int& x = -1 )
   {
        // get a pointer to the float data
        // NOTE: this will need to change if you 
        //       change the dataT2F_C4F_N3F_V3F struct.
      
        //TODO: keep track of if it's strip or POLY prim within this class.
        
       

        if (x == -1)
            return &mVertexArray[0].t[0];
        else
        {
            //int temp = mPrimIndex[x];
            return &mVertexArray[mPrimIndex[x]].t[0];
        }
   }

    void out()
    {
        for (int x = 0; x < mVertexArray.size(); ++x)
        {
            std::cout<<x<<".)\n"
            <<"T "<<mVertexArray[x].t[0]<<", "<<mVertexArray[x].t[1]<<"\n"
            <<"C "<<mVertexArray[x].c[0]<<", "<<mVertexArray[x].c[1]<<", "<<mVertexArray[x].c[2]<<", "<<mVertexArray[x].c[3]<<"\n"
            <<"N "<<mVertexArray[x].n[0]<<", "<<mVertexArray[x].n[1]<<", "<<mVertexArray[x].n[2]<<"\n"
            <<"V "<<mVertexArray[x].v[0]<<", "<<mVertexArray[x].v[1]<<", "<<mVertexArray[x].v[2]<<"\n"<<std::flush;
        }
    }

    inline void getAttr( const GsAttribute& attr, const GsPrimType& prim, int whichPrim, int whichVert, void* &a )
    {
       assert( a != NULL );
       assert( prim == TRIS );
       const int vertsInPrim = 3; // for tris.
       dataT2F_C4F_N3F_V3F& d = mVertexArray[vertsInPrim * whichPrim + whichVert];
       switch (attr)
       {
       case GeoSet::COORD3:
          a = (void*)&d.v;
          break;
       case GeoSet::TEXCOORD2:
          a = (void*)&d.t;
          break;
       case GeoSet::NORMAL3:
          a = (void*)&d.n;
          break;
       case GeoSet::COLOR4:
          a = (void*)&d.c;
          break;
       }         
    }    
    
    void clear()
    {
       mVertexArray.clear();
       mNumVertsInEachPrim.clear();
       mPrimIndex.clear();
            if (mGstate != NULL)
 
          {
             mGstate->unref();
             mGstate = NULL;
         }       
    }    
protected:
    struct dataT2F_C4F_N3F_V3F
    {
        Vec2<float> t;
        Vec4<float> c;
        Vec3<float> n;
        Vec3<float> v;
    };

private:
   // interlaced vertex array data format
   std::vector< dataT2F_C4F_N3F_V3F > mVertexArray;
   std::vector< int > mNumVertsInEachPrim;  //nessesary for strip primitives, and polys
   std::vector< int > mPrimIndex;  // mPrimIndex[n] is where prim [n] starts in the mVertexArray
   int mNumPrimitives, mNumVerts;
   GsPrimType mPrimitiveType;
    
   kev::GState* mGstate;

/*
    std::vector<Vec2<float> > mTexCoords;
    std::vector<Vec4<float> > mColors;
    std::vector<Vec3<float> > mNorms;
    std::vector<Vec3<float> > mVerts;
*/
    /*
    std::vector<int> mTexIndex;
    std::vector<int> mColorIndex;
    std::vector<int> mNormalIndex;
    std::vector<int> mVertIndex;
    */
};

#endif
