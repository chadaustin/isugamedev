#include <iostream.h>
#include "pixmi/SgiImporter.h"
#include "pixmi/TgaImporter.h"
#include "pixmi/PcxImporter.h"
#include "pixmi/BmpImporter.h"
#include "pixmi/PngImporter.h"
#include "pixmi/CFileIO.h"

//////////////////////////////
// Output image statistics.
//////////////////////////////
inline void outputImageProperties(const pixmi::Image &image)
{
    cout<<"Image Properties:\n\n";
    cout<<"Name            - "<<image.name()<<"\n";
    cout<<"Color Depth     - "<<image.bpp()<<"-bit color\n";
    cout<<"Size            - "<<image.width()<<" x "<<image.height()<<"\n";
    cout<<"Channels        - "<<image.channels()<<" color channel(s).\n";
    cout<<"BPC             - "<<image.bpc()<<" byte(s) per channel\n";
    cout<<"Memory Alignent - "<<image.rowAlignment()<<"-byte boundary addressing\n"<<flush;
}

void main(int argc, char* argv[])
{
if (argc < 3)
{ 
   cout<<"Not enough args: iproperties ext filename.ext\n"<<flush;
   exit(1);
}

pixmi::Image image;

std::string ext = argv[1];
std::string name = argv[2];

bool result = false;

if (ext == "sgi")
{
pixmi::SgiImporter i;
result = i.load( name.c_str(), image );
}
else if (ext == "tga")
{
pixmi::TgaImporter i;
result = i.load( name.c_str(), image );
}
else if (ext == "pcx")
{
pixmi::PcxImporter i;
result = i.load( name.c_str(), image );
}
else if (ext == "bmp")
{
pixmi::BmpImporter i;
result = i.load( name.c_str(), image );
}
else if (ext == "png")
{
pixmi::PngImporter i;
result = i.load( name.c_str(), image );
}

if (result == false)
{
   cout<<"iproperties: Couldn't load image\n"<<flush;
   exit(1);
}
outputImageProperties( image );

}
