#ifndef SIREN_AVATAR_LOADER_H
#define SIREN_AVATAR_LOADER_H

#include <string>

class CalCoreModel;

namespace siren
{
   /**
    * Loads the Cal3D core model from the given file.
    */
   CalCoreModel* loadCoreModel(const std::string& filename);
}

#endif
