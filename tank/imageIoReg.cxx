
#include <stdio.h>
#include "ImageManager.h"

//#include "BmpExporter.h"
#include "BmpImporter.h"

#include "CppImageExporter.h"
//#include "PngImporter.h"

//#include "PcxExporter.h"
//#include "PcxImporter.h"

//#include "SgiExporter.h"
//#include "SgiImporter.h"

//#include "TgaExporter.h"
#include "TgaImporter.h"

class ImageIoRegistrator
{
public:
//    BmpExporter bmpE;
    BmpImporter bmpI;

    CppImageExporter cppE;
	    
//    PcxExporter pcxE;
//    PcxImporter pcxI;

    //PngImporter pngI;
    
//    SgiExporter sgiE;
//    SgiImporter sgiI;

//    TgaExporter tgaE;
    TgaImporter tgaI;

    ImageIoRegistrator()
    {
        //ImageManager::instance().addImporter( pngI );
        
//        ImageManager::instance().addExporter( bmpE );
        ImageManager::instance().addImporter( bmpI );

        ImageManager::instance().addExporter( cppE );

//        ImageManager::instance().addImporter( pcxI );
//        ImageManager::instance().addExporter( pcxE );
        
//        ImageManager::instance().addImporter( sgiI );
//        ImageManager::instance().addExporter( sgiE );
        
        ImageManager::instance().addImporter( tgaI );
//        ImageManager::instance().addExporter( tgaE );
    }

    ~ImageIoRegistrator()
    {
        //ImageManager::instance().removeImporter( pngI );
        
//        ImageManager::instance().removeExporter( bmpE );
        ImageManager::instance().removeImporter( bmpI );

        ImageManager::instance().removeExporter( cppE );

//        ImageManager::instance().removeExporter( pcxE );
//        ImageManager::instance().removeImporter( pcxI );
        
//        ImageManager::instance().removeExporter( sgiE );
//        ImageManager::instance().removeImporter( sgiI );
        
//        ImageManager::instance().removeExporter( tgaE );
        ImageManager::instance().removeImporter( tgaI );
    }
};

// create myself (you'll need to tell your linker not to optimize out any symbols)
static ImageIoRegistrator iior;
