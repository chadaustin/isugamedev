#include "pixmi/SgiExporter.h"
#include "pixmi/TgaExporter.h"
#include "pixmi/PcxExporter.h"
#include "pixmi/BmpExporter.h"
#include "pixmi/CppImageExporter.h"

void main()
{
   // this is your source image
   const int width = 128, height = 128, bpp = 24, channels = 3;
   const int alignment = 1; // memory is aligned to 1 byte boundries.
   unsigned char data[ width * height * channels ];
   
   // this is how you write it out...
   pixmi::Image image;
   image.setName( "Whatever is in memory at the time, hacky hacky... :)" );
   image.setData( data, true, width, height, bpp, channels, alignment );
   
  
   {
      pixmi::SgiExporter exporter;
      exporter.save( "garbage.rgb", image );
   }//pops "exporter" off the stack...
   
   {
      pixmi::TgaExporter exporter;
      exporter.save( "garbage.tga", image );
   }//pops "exporter" off the stack...
   
   {
      pixmi::PcxExporter exporter;
      exporter.save( "garbage.pcx", image );
   }//pops "exporter" off the stack...
   
   {
      pixmi::BmpExporter exporter;
      exporter.save( "garbage.bmp", image );
   }//pops "exporter" off the stack...
   
   
   // ever wanted to imbed source code into your application??? 
   // this is real nice... :)
   {
      pixmi::CppImageExporter exporter;
      exporter.save( "garbage.cpp", image );
   }//pops "exporter" off the stack...
}
