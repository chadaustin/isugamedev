#ifndef SIREN_AVATAR_LOADER_H
#define SIREN_AVATAR_LOADER_H

#include <string>
#include <siren/Export.h>

class CalCoreModel;

namespace siren
{
   /**
    * Loads the Cal3D core model from the given file.
    */
   SIREN_EXPORT(CalCoreModel*) loadCoreModel(const std::string& filename);
}

#endif
