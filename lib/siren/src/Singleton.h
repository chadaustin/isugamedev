#ifndef SIREN_SINGLETON_H
#define SIREN_SINGELTON_H

namespace siren
{
   /**
    * Templated singleton holder. This class will make any object a singleton.
    */
   template<class T>
   class Singleton
   {
   public:
      /**
       * Gets the singleton instance of the contained class.
       */
      static T& instance()
      {
         if (! mInstance)
         {
            mInstance = new T();
            atexit(destroySingleton);
         }
         return *mInstance;
      }

   private:
      /**
       * Destroys this singleton. This is called when the application is
       * terminated.
       */
      static void destroySingleton()
      {
         delete mInstance;
         mInstance = 0;
      }

   private:
      /// The singleton instance
      static T* mInstance;
   };

   template<class T>
   T* Singleton<T>::mInstance = 0;
}

#endif
