#include <iostream.h>
#include "pixmi/SgiImporter.h"
#include "pixmi/TgaImporter.h"
#include "pixmi/PcxImporter.h"
#include "pixmi/BmpImporter.h"
#include "pixmi/PngImporter.h"

#include "pixmi/SgiExporter.h"
#include "pixmi/TgaExporter.h"
#include "pixmi/PcxExporter.h"
#include "pixmi/BmpExporter.h"
#include "pixmi/CppImageExporter.h"

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
    cout<<"Memory Alignent - "<<image.rowAlignment()<<"-byte boundary addressing\n";
}

void main(int argc, char* argv[])
{
if (argc < 5)
{ 
   cout<<"iconvert extfrom extto filefrom fileto\n"<<flush;
   exit(1);
}

pixmi::Image image;

cout<<"iconvert extfrom extto filefrom fileto\n"<<flush;

std::string extfrom = argv[1];
std::string extto = argv[2];
std::string from = argv[3];
std::string to = argv[4];

if (extfrom == "sgi")
{
pixmi::SgiImporter i;
i.load( from.c_str(), image );
}
else if (extfrom == "tga")
{
pixmi::TgaImporter i;
i.load( from.c_str(), image );
}
else if (extfrom == "pcx")
{
pixmi::PcxImporter i;
i.load( from.c_str(), image );
}
else if (extfrom == "bmp")
{
pixmi::BmpImporter i;
i.load( from.c_str(), image );
}
else if (extfrom == "png")
{
pixmi::PngImporter i;
i.load( from.c_str(), image );
}


outputImageProperties( image );


if (extto == "sgi")
{
pixmi::SgiExporter i;
i.save( to.c_str(), image );
}
else if (extto == "pcx")
{
pixmi::PcxExporter i;
i.save( to.c_str(), image );
}
else if (extto == "tga")
{
pixmi::TgaExporter i;
i.save( to.c_str(), image );
}
else if (extto == "bmp")
{
pixmi::BmpExporter i;
i.save( to.c_str(), image );
}
else if (extto == "cpp")
{
pixmi::CppImageExporter i;
i.save( to.c_str(), image );
}
}
