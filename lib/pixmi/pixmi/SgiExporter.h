
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     SgiExport class     =-
//
// Description: "a class for loading of the SGI image format"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: SgiExporter.h,v $
//    $Date: 2002-01-17 00:04:59 $
//    $Revision: 1.1.1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
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
#ifndef SGIEXPORT_INCLUDED
#define SGIEXPORT_INCLUDED

#include "Image.h"
#include "ImageExporter.h"


namespace pixmi
{
   
/*
////////////////////////////////////////////////////////////////////////
// The general structure of an SGI image file is as shown below: 
// The header indicates whether the image is run length encoded (RLE). 
//     
//   If the image is not run length encoded, this is the structure: 
//   + The Header
//   + The Image Data      
//
//   If the image is run length encoded, this is the structure:
//   + The Header    
//   + The Offset Tables     
//   + The Image Data   
////////////////////////////////////////////////////////////////////////
*/

//SGI class definition
#include "ImageExporter.h"
//: SgiExporter
// Write an Image object out to file
//
// To use, declare an instance of this class,
// then call operator() with the filename and Image object you wish to act on.
// i.e:
//   Image image;
//   /* now do some changes to the image, white noise, a fractal, etc.. */
//   SgiExporter sgi_export;
//   sgi_export( "bugs.sgi", image );
// 
// alternately, you can call operator() this way:
//   sgi_export.operator()( "bugs.sgi", image );
//
class SgiExporter : public ImageExporter
{   
public:
   //: Default constructor
   SgiExporter();      
      
   //: Destructor
   virtual ~SgiExporter();
      
   //: Save the image as "filename"
   //  returns true or false for successful or unsuccessful
   virtual bool         save( const char* const filename, const Image& image );   
   
   //: a string that describes the files supported by this importer
   virtual const char* const   description() const;

protected:   
   //: 474 is the SGI magic number...
   unsigned short  _MAGIC;         
   
   //: storage type
   // Either RGB_RLE or RGB_VERBATIM
   unsigned char   _STORAGE;       
   
   //: Number of bytes per pixel channel == 1 or 2
   unsigned char   _BPC;           
   
   //1 for 1 color and 1 row, 
   //2 for 1 color and many rows, 
   //3 for many colors and rows
   unsigned short   _DIMENSION;   // Number of dimensions  
   
   //XSIZE - The width of the image in pixels 
    //YSIZE - The height of the image in pixels 
    //ZSIZE - The number of channels in the image.  
   // B/W (greyscale) images are stored as 2 dimensional images with an ZSIZE ofr 1.  
   // RGB color images are stored as 3 dimensional images with a ZSIZE of 3.  
   // RGBA color images are stored as a 3 dimensional image with a ZSIZE of 4.
   unsigned short   _XSIZE;      // X size in pixels 
   unsigned short   _YSIZE;      // Y size in pixels 
   unsigned short   _ZSIZE;      // Number of channels
   unsigned long   _PIXMIN ;       // Minimum pixel value that means full dark   (0)
   unsigned long   _PIXMAX;        // Maximum pixel value that means full bright (255)
    
   //0:  NORMAL - The data in the channels represent B/W values
    //    for images with 1 channel, RGB values for images with 3
    //    channels, and RGBA values for images with 4 channels.
    //    Almost all the SGI image files are of this type.  
    //1:  DITHERED - The image will have only 1 channel of data.
    //    For each pixel, RGB data is packed into one 8 bit value.
    //    3 bits are used for red and green, while blue uses 2 bits.
    //    Red data is found in bits[2..0], green data in bits[5..3],
    //    and blue data in bits[7..6].  This format is obsolete. 
    //2:  SCREEN - The image will have only 1 channel of data.
    //    This format was used to store color-indexed pixels.
    //    To convert the pixel values into RGB values a colormap
    //    must be used.  The appropriate color map varies from
    //    image to image.  This format is obsolete. 
    //3:  COLORMAP - The image is used to store a color map from
    //    an SGI machine.  In this case the image is not displayable
    //    in the conventional sense. 
   unsigned long  _COLORMAP;        //Colormap ID
   static const unsigned char  _BIGDUMMY[404]; // 404 bytes: Ignored, set to 0, makes the header == 512 bytes

   enum SgiImageConstants 
   { 
      //: MAGIC Number for an SGI image
      RGB_MAGIC = 474,

      //: Header tag in SGI image - means image data is not compressed
      RGB_VERBATIM = 0,

      //: Header tag in SGI image - means image data is run-length encoded
      RGB_RLE = 1,

      //: Header tag in SGI image - The data in the channels represent B/W values
      //  for images with 1 channel, RGB values for images with 3   <BR>
      //  channels, and RGBA values for images with 4 channels.     <BR>
      //  Almost all the SGI image files are of this type.          <BR>
      RGB_NORMAL = 0,

      //: Header tag in SGI image - The image will have only 1 channel of data.
      //  For each pixel, RGB data is packed into one 8 bit value.  <BR>
      //  3 bits are used for red and green, while blue uses 2 bits.<BR>
      //  Red data is found in bits[2..0], green data in bits[5..3],<BR>
      //  and blue data in bits[7..6].  This format is obsolete.    <BR>
      RGB_DITHERED = 1,

      //: Header tag in SGI image - The image will have only 1 channel of data.
      //  This format was used to store color-indexed pixels.    <BR>
      //  To convert the pixel values into RGB values a colormap <BR>
      //  must be used.  The appropriate color map varies from   <BR>
      //  image to image.  This format is obsolete.              <BR>
      RGB_SCREEN = 2,

      //: The image is used to store a color map from
      //    an SGI machine.  In this case the image is not displayable
      //   in the conventional sense.
      RGB_COLORMAP = 3
   };
};
} // namespace

#endif
