#include <cal3d/cal3d.h>
#include <siren/avatar/AvatarLoader.h>
#include <siren/ResourceManager.h>

namespace siren
{
   /**
    * Cache policy for Cal3D skeleton objects so that they can be used with the
    * resource management system.
    */
   template<>
   struct siren::CachePolicy<CalCoreSkeleton*>
   {
      static CalCoreSkeleton* copy(CalCoreSkeleton* cacheVal)
      {
         return cacheVal;
      }

      static CalCoreSkeleton* create(const std::string& name)
      {
         CalLoader loader;
         CalCoreSkeleton* skel = loader.loadCoreSkeleton(name);
         return skel;
      }

      static void destroy(CalCoreSkeleton* val)
      {
         // the CalCoreModel will destroy its contained skeleton
//         val->destroy();
//         delete val;
      }
   };

   /**
    * Cache policy for Cal3D animation objects so that they can be used with the
    * resource management system.
    */
   template<>
   struct siren::CachePolicy<CalCoreAnimation*>
   {
      static CalCoreAnimation* copy(CalCoreAnimation* cacheVal)
      {
         return cacheVal;
      }

      static CalCoreAnimation* create(const std::string& name)
      {
         CalLoader loader;
         CalCoreAnimation* anim = loader.loadCoreAnimation(name);
         return anim;
      }

      static void destroy(CalCoreAnimation* val)
      {
         // the CalCoreModel will destroy all of its contained animations
//         val->destroy();
//         delete val;
      }
   };

   /**
    * Cache policy for Cal3D mesh objects so that they can be used with the
    * resource management system.
    */
   template<>
   struct siren::CachePolicy<CalCoreMesh*>
   {
      static CalCoreMesh* copy(CalCoreMesh* cacheVal)
      {
         return cacheVal;
      }

      static CalCoreMesh* create(const std::string& name)
      {
         CalLoader loader;
         CalCoreMesh* mesh = loader.loadCoreMesh(name);
         return mesh;
      }

      static void destroy(CalCoreMesh* val)
      {
         // the CalCoreModel will destroy all of its contained meshes
//         val->destroy();
//         delete val;
      }
   };

   /**
    * Cache policy for Cal3D material objects so that they can be used with the
    * resource management system.
    */
   template<>
   struct siren::CachePolicy<CalCoreMaterial*>
   {
      static CalCoreMaterial* copy(CalCoreMaterial* cacheVal)
      {
         return cacheVal;
      }

      static CalCoreMaterial* create(const std::string& name)
      {
         CalLoader loader;
         CalCoreMaterial* material = loader.loadCoreMaterial(name);
         return material;
      }

      static void destroy(CalCoreMaterial* val)
      {
         // the CalCoreModel will destroy all of its contained material
//         val->destroy();
//         delete val;
      }
   };

   /**
    * Creates a new CalCoreSkeleton from the resource manager.
    */
   CalCoreSkeleton* createCoreSkeleton(const std::string& name)
   {
      return ResourceManagerSingleton::instance().get<CalCoreSkeleton*>(name);
   }

   /**
    * Creates a new CalCoreAnimation from the resource manager.
    */
   CalCoreAnimation* createCoreAnimation(const std::string& name)
   {
      return ResourceManagerSingleton::instance().get<CalCoreAnimation*>(name);
   }

   /**
    * Creates a new CalCoreMesh from the resource manager.
    */
   CalCoreMesh* createCoreMesh(const std::string& name)
   {
      return ResourceManagerSingleton::instance().get<CalCoreMesh*>(name);
   }

   /**
    * Creates a new CalCoreMaterial from the resource manager.
    */
   CalCoreMaterial* createCoreMaterial(const std::string& name)
   {
      return ResourceManagerSingleton::instance().get<CalCoreMaterial*>(name);
   }

   CalCoreModel*
   loadCoreModel(const std::string& filename)
   {
      //Load up the given config file
      //Create a new CalCoreModel
      //Add it to the map with the given lookup name

      float scaleFactor = 1.0;
      std::string currentPath = "./";

      std::cerr
         << "AvatarFactory: adding core avatar named " << filename << "\n"
         << std::endl;

      //Open the model configuration file
      std::ifstream file;

      //Try to open the local file first
      file.open(filename.c_str(), std::ios::in | std::ios::binary);

      if (!file)
      {
         std::cerr
            << "AvatarFactory: Failed to open model configuration file '" << filename << "'\n"
            << std::endl;

         return false;
      }

      //Create a new core model
      CalCoreModel* newCoreModel = new CalCoreModel();

      if (!newCoreModel->create("dummy"))
      {
         std::cerr
            << "AvatarFactory: could not create new core model\n"
            << std::endl;

         return false;
      }

      // parse all lines from the model configuration file
      int line;
      for (line = 1; ; line++)
      {
         // read the next model configuration line
         std::string strBuffer;
         std::getline(file, strBuffer);

         // stop if we reached the end of file
         if (file.eof())
         {
            break;
         }

         // check if an error happend while reading from the file
         if (!file)
         {
            std::cerr
               << "AvatarFactory: Error while reading from the model configuration file '" << filename << "'\n"
               << std::endl;

            return false;
         }

         // find the first non-whitespace character
         std::string::size_type pos;
         pos = strBuffer.find_first_not_of(" \t");

         // check for empty lines
         if ((pos == std::string::npos) || (strBuffer[pos] == '\n') ||
             (strBuffer[pos] == '\r') || (strBuffer[pos] == 0))
         {
            continue;
         }

         // check for comment lines
         if (strBuffer[pos] == '#')
         {
            continue;
         }

         // get the key
         std::string strKey;
         strKey = strBuffer.substr(pos, strBuffer.find_first_of(" =\t\n\r", pos) - pos);
         pos += strKey.size();

         // get the '=' character
         pos = strBuffer.find_first_not_of(" \t", pos);
         if ((pos == std::string::npos) || (strBuffer[pos] != '='))
         {
            std::cerr
               << "AvatarFactory: " << filename << "(" << line << "): Invalid syntax\n"
               << std::endl;

            return false;
         }

         // find the first non-whitespace character after the '=' character
         pos = strBuffer.find_first_not_of(" \t", pos + 1);

         // get the data
         std::string strData;
         strData = strBuffer.substr(pos, strBuffer.find_first_of("\n\r", pos) - pos);

         // handle the model creation
         if (strKey == "scale")
         {
            //Automatically set the avatar's scale factor
            scaleFactor = atof(strData.c_str());
         }
         else if (strKey == "skeleton")
         {
            CalCoreSkeleton* coreSkeleton = createCoreSkeleton(strData);

            //test to see if there was a loading error
            if (coreSkeleton == NULL)
            {
               std::cerr
                     << "AvatarFactory: Error loading skeleton '" << strData << "'\n"
                     << std::endl;

               return NULL;
            }

            //set the core model's skeleton
            newCoreModel->setCoreSkeleton(coreSkeleton);

         }
         else if (strKey == "animation")
         {
            CalCoreAnimation* coreAnimation = createCoreAnimation(strData);

            //test to see if there was a loading error
            if (coreAnimation == NULL)
            {
               std::cerr
                     << "AvatarFactory: Error loading animation '" << strData << "'\n"
                     << std::endl;

               return NULL;
            }

            //add the core model's animation
            newCoreModel->addCoreAnimation(coreAnimation);

         }
         else if (strKey == "mesh")
         {
            CalCoreMesh* coreMesh = createCoreMesh(strData);

            //test to see if there was a loading error
            if (coreMesh == NULL)
            {
               std::cerr
                     << "AvatarFactory: Error loading mesh '" << strData << "'\n"
                     << std::endl;

               return NULL;
            }

            //add the core model's mesh
            newCoreModel->addCoreMesh(coreMesh);
         }
         else if (strKey == "material")
         {
            CalCoreMaterial* coreMaterial = createCoreMaterial(strData);

            //test to see if there was a loading error
            if (coreMaterial == NULL)
            {
               std::cerr
                     << "AvatarFactory: Error loading material '" << strData << "'\n"
                     << std::endl;

               return NULL;
            }

            //set the core model's material
            newCoreModel->addCoreMaterial(coreMaterial);
         }
         else if (strKey == "bonedef")
         {
            //Add a new bone definition
            std::istringstream tempStream (strData);
            std::string boneName = "";
            int boneNum = -1;

            tempStream >> boneName >> boneNum;

            if ((boneName == "") || (boneNum < 0))
            {
               std::cerr
                  << "AvatarFactory: " << filename << "(" << line << "): Invalid syntax in bone definition\n"
                  << std::endl;
            }
            else
            {
               newCoreModel->addBoneHelper( boneName, boneNum );
            }

         }
         else if (strKey == "animdef" )
         {
            //Add a new animation definition
            std::istringstream tempStream (strData);
            std::string animName = "";
            int animNum = -1;

            tempStream >> animName >> animNum;

            if ((animName == "") || (animNum < 0))
            {
               std::cerr
                  << "AvatarFactory: " << filename << "(" << line << "): Invalid syntax in animation definition\n"
                  << std::endl;
            }
            else
            {
               newCoreModel->addAnimHelper( animName, animNum );
            }

         }
         else
         {
            // everything else triggers an error message, but is ignored
            std::cerr
               << "AvatarFactory: " << filename << "(" << line << "): Invalid syntax\n"
               << std::endl;
         }
      }

      // explicitely close the file
      file.close();

      //Create a new material thread for each material loaded
      for (int materialId = 0; materialId < newCoreModel->getCoreMaterialCount(); materialId++)
      {
         // create the a material thread
         newCoreModel->createCoreMaterialThread(materialId);
         // initialize the material thread
         newCoreModel->setCoreMaterialId(materialId, 0, materialId);
      }

      return newCoreModel;
   }
}
