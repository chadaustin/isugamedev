
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     image io registration     =-
//
// Description: "registers importers and exporters for the ImageManager"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: imageIoReg.cxx,v $
//    $Date: 2001-09-20 20:12:50 $
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
