#ifndef MW_SOUND_EFFECT_MANAGER_H
#define MW_SOUND_EFFECT_MANAGER_H

#include <string>
#include <audiere.h>

namespace mw
{
   /**
    * Handles the triggering of sound effects for an application. Sounds played
    * through the SoundEffectManager are generally loaded into memory and played
    * from there rather than streaming from the disk.
    */
   class SoundEffectManager
   {
   public:
      /**
       * Creates a new SoundEffectManager for the given Audiere context.
       *
       * @param context    the Audiere context to use
       */
      SoundEffectManager(audiere::Context* context);

      /**
       * Destroys this manager and terminates all sounds currently being played
       * by this manager.
       */
      ~SoundEffectManager();

      /**
       * Plays the sound contained within the given file.
       *
       * @param sound      the filename in which the sound is stored
       */
      void playSound(const std::string& sound);

   private:
      enum { MAX_SOUNDS = 8 };
    
      audiere::Context* mContext;
      audiere::Stream* mStreams[MAX_SOUNDS];
      int mNextStream;
   };
}

#endif
