
//////////////////////////////////////////////////////////////////
//
//                         -=     Texture     =-
//
// Definition: "Texture class."
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Texture.h,v $
//    $Date: 2001-09-10 15:50:40 $
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

//////////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_INCLUDED
#define TEXTURE_INCLUDED

#include "Image.h"
#include "ResourceID.h" // each texture has a unique resource id

//: Texture node.
class Texture
{
public:
    Texture();
    Texture( const Texture &texture );
    virtual ~Texture()
    {
    }
    
    enum Model 
    {
    //The texture color is multiplied by the surface color
         MODULATE, 
    
    //The texture color replaces the surface color
         DECAL, 
    
    //Blends between the surface color and current geometry's color
         BLEND
    };
    
    enum Filtering
    {
       NEAREST,
       LINEAR,
       MIPMAP_NEAREST, 
       MIPMAP_LINEAR
    };

    enum Wrap 
    {
    //Repeats texture outside 0-1 texture coordinate range
         REPEAT, 
    
    //Clamps texture coordinates to lie within 0-1 range
         CLAMP
    };

    //: set the image of the texture.
    // if this is NULL, then texture will not render or compile.
    // Must do this before compile(), or render()
   void         setImage( const Image* i )
   {
      mImage = i;
   }
    
    //: an alias to this texture's image.
    //Image*          image();
    const Image*  image() const;
    bool imageValid() const { return mImage != NULL; }
   
    
    //:Specifies how to map texture onto surface.
    // MODULATE, DECAL, or BLEND
    Model      model;
    
    //: Specify how texture is wrapped onto surface
    // REPEAT, or CLAMP
    Wrap       wrapS;
    Wrap       wrapT;
    
    //WARNING: set this before requesting to use texture object.
    Filtering filtering;
    
    kev::ResourceID<unsigned short> resourceId;
    
protected:
   const Image* mImage;
   void setResourceID(); 
};

//: an alias to this texture's image.
/*inline Image*    Texture::image()
{ 
   return mImage; 
}
*/
inline const Image*    Texture::image() const
{ 
   return mImage; 
}

#endif
