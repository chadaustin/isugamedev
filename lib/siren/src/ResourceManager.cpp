#include <stdexcept>
#include <iostream>
#include <fstream>
#include "ResourceManager.h"

namespace siren
{
   ResourceManagerBase::ResourceManagerBase()
   {
      // load the model mappings
      std::ifstream in("resources.txt");
      if (in.is_open())
      {
         std::string name, model;
         while (in >> name >> model)
         {
            defineResourceID(name, model);
         }
      }
   }

   ResourceManagerBase::~ResourceManagerBase()
   {}

   const std::string&
   ResourceManagerBase::lookup(const std::string& resid) const
   {
      if (resid.empty()) {
         static const std::string empty;
         return empty;
      }
   
      ResourceIDMap::const_iterator itr = mResourceIDs.find(resid);
      if (itr != mResourceIDs.end())
      {
         return itr->second;
      }
      std::cout << resid << std::endl;
      throw std::runtime_error("Invalid ResourceID");
   }

   void
   ResourceManagerBase::defineResourceID(const std::string& resid, const std::string& value)
   {
      ResourceIDMap::iterator itr = mResourceIDs.find(resid);
      if (itr == mResourceIDs.end())
      {
         mResourceIDs[resid] = value;
      }
      else
      {
         throw std::runtime_error("ResourceID already in use");
      }
   }

   void
   ResourceManagerBase::removeResourceID(const std::string& resid)
   {
      ResourceIDMap::iterator itr = mResourceIDs.find(resid);
      if (itr != mResourceIDs.end())
      {
         std::cout<<"Removed Resource: "<<resid<<" -> "<<(itr->second)<<std::endl;
         mResourceIDs.erase(itr);
      }
      else
      {
         throw std::runtime_error("Invalid ResourceID");
      }
   }

   ResourceManager::ResourceManager()
   {}

   ResourceManager::~ResourceManager()
   {
      for (CacheMap::iterator itr = mCaches.begin(); itr != mCaches.end(); ++itr)
      {
         /// XXX: We need to cast this to the right type before deleting ...
         delete itr->second;
      }
   }
}
