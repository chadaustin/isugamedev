
//////////////////////////////////////////////////////////////////
//
//                         -=     render texture     =-
//
// Definition: "decoupled texture renderer for opengl"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: glRenderTexture.h,v $
//    $Date: 2001-09-10 15:49:57 $
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
#ifndef TEXTURE_BINDER
#define TEXTURE_BINDER

#include "Texture.h"
#include "Defines.h" // for kev::MAX
#include "ContextManager.h"

namespace kev
{
   // load texture data to hardware, making the texture current
   // NOTE: does not set any glEnable()s, use kev::render() instead of this function.
   // NOTE: this function results in slower performance than using the combination 
   //       of kev::bind() and kev::render()
   // NOTE: if you don't use the kev::bind() and kev::render() combination, then 
   //       kev::render() will call kev::load() after setting a lot of glEnable()s
   inline bool glTextureLoad( const Texture& texture, int mipmapLevelOfDetail = 0, int bordersize = 0 )
   {
      //cout<<"load "<<texture.image()->name()<<"\n"<<flush;
      if (texture.imageValid() == false) 
         return false;
      
      int format, type;
      const Image& image = *(texture.image());

      // set the way that gl reads the pixels.
      switch (image.channels())
      {
      case 1: format = GL_LUMINANCE; break;
      case 3: format = GL_RGB;  break;
      case 4: format = GL_RGBA; break;
      default: 
         return false;
      }

      // set the byte alignment of the pixels.   
      if (image.bpc() == 2)
         type = GL_UNSIGNED_SHORT;
      else
         type = GL_UNSIGNED_BYTE;   

      //make sure the alignment matches the pixel size in bytes
      ::glPixelStorei( GL_UNPACK_ALIGNMENT, image.bpc() );

      // fatal error. Nothing to render
      if( image.data() == NULL )
      return false; 

      // find out what dimension texture we're using
      int texDimension;
      if( image.height() == 1 || image.width() == 1 )
      {
         // handle one dimensional images...
         int length = kev::MAX( image.width(), image.height() );
         if (texture.filtering != Texture::NEAREST ||
             texture.filtering != Texture::LINEAR)
         {
            ::gluBuild1DMipmaps( GL_TEXTURE_1D, 
                                 image.channels(), length, 
                                 format, type, image.data() );
         } 
         else 
         {
            ::glTexImage1D( GL_TEXTURE_1D, mipmapLevelOfDetail, 
                           image.channels(), length, 
                           bordersize, format, type, image.data() );
         }

         texDimension = GL_TEXTURE_1D;	
      } 

      else 
      {
         // other wise, handle 2D images.
         if (texture.filtering == Texture::MIPMAP_NEAREST ||
             texture.filtering == Texture::MIPMAP_LINEAR)
         {
            ::gluBuild2DMipmaps( GL_TEXTURE_2D, 
                                 image.channels(), image.width(), 
                                 image.height(), format, type, 
                                 image.data() );
         }
         else 
         {
            ::glTexImage2D( GL_TEXTURE_2D, mipmapLevelOfDetail, 
                           image.channels(), image.width(), 
                           image.height(), bordersize, format, 
                           type, image.data() );
         }

         texDimension = GL_TEXTURE_2D;
      }

      // figure out what filtering to use.
      // set the filtering for the texture...
      switch (texture.filtering)
      {
      case Texture::NEAREST:
         ::glTexParameteri( texDimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
         ::glTexParameteri( texDimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
      break;

      case Texture::LINEAR:
         ::glTexParameteri( texDimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
         ::glTexParameteri( texDimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR );	
      break;

      case Texture::MIPMAP_NEAREST:
         ::glTexParameteri( texDimension, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
         ::glTexParameteri( texDimension, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
      break;

      case Texture::MIPMAP_LINEAR:
         ::glTexParameteri( texDimension, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
         ::glTexParameteri( texDimension, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
      break;
      default:
         assert(false);
      }

      return true;
   }
   
   // bind texture.  Caches image in hardware, associating with an ID
   // this makes texture changes very fast.
   inline void glTextureBind( const Texture& texture, int mipmapLevelOfDetail = 0, int bordersize = 0 )
   {
      kev::ResourceID<unsigned int> texObjectID = ContextManager::instance().lookup( texture.resourceId );
      
      //cout<<"bind "<<texture.image()->name()<<" id=="<<texObjectID<<"\n"<<flush;
      if (texObjectID.valid == true)
         return;
      
      // find out what dimension texture we're using
      int texDimension;
      if (texture.image()->height() == 1 || texture.image()->width() == 1)
         texDimension = GL_TEXTURE_1D;	
      else 
         texDimension = GL_TEXTURE_2D;

      // create the texture object, setting the texObjectID
      unsigned int id = 0xdeadface;
      #ifdef GL_VERSION_1_1
         ::glGenTextures( 1, &id );
         ::glBindTexture( texDimension, id );
      #else
         ::glGenTexturesEXT( 1, &id );
         ::glBindTextureEXT( texDimension, id );
      #endif
      texObjectID.id = id;
      texObjectID.valid = true;
      
      ContextManager::instance().associate( texture.resourceId, texObjectID );
      
      //cout<<"bind "<<texture.image()->name()<<" id=="<<texObjectID<<"\n"<<flush;
      // load the texture into hardware that will be referenced by the texObjectID
      kev::glTextureLoad( texture, mipmapLevelOfDetail, bordersize );
   }

   // unbind texture.  Uncaches image from hardware
   inline void glTextureUnbind( const Texture& texture )
   {
      // get the value
      kev::ResourceID<unsigned int> texObjectID = ContextManager::instance().lookup( texture.resourceId );
      
      if (texObjectID.valid == false)
         return;
      
      #ifdef GL_VERSION_1_1
         ::glDeleteTextures( 1, &texObjectID.id );
      #else
         ::glDeleteTexturesEXT( 1, &texObjectID.id );
      #endif

      texObjectID.id = 0; // unused
      texObjectID.valid = false;
      
      // put it back
      ContextManager::instance().associate( texture.resourceId, texObjectID );
   }

   //: render texture
   // will make current a texture that has been created as a texure object, or not...
   // and sets all relevent glEnable()s.  Using this, you shouldn't have to do anything 
   // else with the gl texture functions.
   //
   // texture: make sure it's set up properly with a valid Image object, etc...
   // texObjectID: if == -1 then function will load the texture.image() data each time
   //              you should use the texture bind function before calling render for
   //              better performance
   inline void glRender( const Texture& texture )
   {
      if (texture.imageValid() == false)
         return;
      
      const kev::ResourceID<unsigned int>& texObjectID = ContextManager::instance().lookup( texture.resourceId );
      int contextID = ContextManager::instance().context();

      const Image& image = *(texture.image());

      // find out what dimension texture we're using
      int texDimension;
      int texBindDimension;
      if (image.height() == 1 || image.width() == 1 )
      {
         texDimension = GL_TEXTURE_1D;	
         #ifdef GL_VERSION_1_1
            texBindDimension = GL_TEXTURE_BINDING_1D;
         #else
            texBindDimension = GL_TEXTURE_1D_BINDING;
         #endif
      }
      else 
      {
         texDimension = GL_TEXTURE_2D;
         #ifdef GL_VERSION_1_1
            texBindDimension = GL_TEXTURE_BINDING_2D;
         #else
            texBindDimension = GL_TEXTURE_2D_BINDING;
         #endif
      }

      // enable texturing for this dimension if not already
      if (::glIsEnabled( texDimension ) == GL_FALSE)
         ::glEnable( texDimension );

      // if we're rendering the same texture as what is current, then quit
      static int last_context_rendered = 9934999;
      int currentTexId;
      ::glGetIntegerv( texBindDimension, &currentTexId );
      if (currentTexId == texObjectID.id && texObjectID.valid == true && contextID == last_context_rendered)
         return;
      last_context_rendered = contextID;
      
      // Disable auto texture coord generation
      // TODO: oops, no way to enable...
      if (::glIsEnabled( GL_TEXTURE_GEN_T ) == GL_FALSE)
         ::glDisable( GL_TEXTURE_GEN_T );
      if (::glIsEnabled( GL_TEXTURE_GEN_S ) == GL_FALSE)
         ::glDisable( GL_TEXTURE_GEN_S );


	   // figure out which GL model the texture uses
      int tex_env_mode  = -1;
      glGetTexEnviv( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &tex_env_mode );
      switch (texture.model)
      {
      case Texture::MODULATE: 
         if (tex_env_mode != GL_MODULATE)
            ::glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
         break;
      case Texture::DECAL: 
         if (tex_env_mode != GL_DECAL)
            ::glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
         break;
      case Texture::BLEND: 
         if (tex_env_mode != GL_BLEND)
            ::glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
         break;
      }

	   // set the wrap mode the texture uses for 'S' if not set already
      int tex_parameter = -1;
      ::glGetTexParameteriv( texDimension, GL_TEXTURE_WRAP_S, &tex_parameter );
      switch (texture.wrapS)
      {
      case Texture::REPEAT:
         if (tex_parameter != GL_REPEAT)
            ::glTexParameteri( texDimension, GL_TEXTURE_WRAP_S, GL_REPEAT );
         break;
      case Texture::CLAMP: 
         if (tex_parameter != GL_CLAMP)
            ::glTexParameteri( texDimension, GL_TEXTURE_WRAP_S, GL_CLAMP );
         break;
      }

      // set the wrap mode the texture uses for 'T' if not set already
      ::glGetTexParameteriv( texDimension, GL_TEXTURE_WRAP_T, &tex_parameter );
      switch (texture.wrapT)
      {
      case Texture::REPEAT: 
         if (tex_parameter != GL_REPEAT)
            ::glTexParameteri( texDimension, GL_TEXTURE_WRAP_T, GL_REPEAT );
         break;
      case Texture::CLAMP: 
         if (tex_parameter != GL_CLAMP)
            ::glTexParameteri( texDimension, GL_TEXTURE_WRAP_T,  GL_CLAMP );
         break;
      }

      if (texObjectID.valid == true) 
      {
         #ifdef GL_VERSION_1_1
            ::glBindTexture( texDimension, texObjectID.id );
         #else
            ::glBindTextureEXT( texDimension, texObjectID.id );
         #endif
      }               
      // if the texture object is invalid, 
      // just load the pixels from memory to the graphics hardware
      // this will be major-slow but, you'll get results...
      // NOTE: if texObjectID==-1 then, you should use the texture bind function 
      //       before rendering for better performance
      else 
      {
         kev::glTextureLoad( texture );
      }
   }
   
   inline void glRenderAndBind( const Texture& texture )
   {
      if (texture.imageValid() == false)
         return;
      
      glTextureBind( texture );
      glRender( texture );
   }
};

#endif
