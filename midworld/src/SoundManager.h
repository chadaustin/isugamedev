#ifndef MW_SOUND_MANAGER_H
#define MW_SOUND_MANAGER_H

#include <audiere.h>
#include "Jukebox.h"
#include "SoundEffectManager.h"

namespace mw
{
   /**
    * The SoundManager is a facade for creating and manipulating music and sound
    * effects in an application using Audiere as the backend. The SoundManager
    * has a Jukebox for queueing up and playing music tracks and a
    * SoundEffectManager for triggering non-music related sound effects.
    *
    * <h3>Example: Using the SoundManager</h3>
    * \code
    *    // Create a new sound manager
    *    SoundManager* mgr = new SoundManager();
    *
    *    // Queue up and play some music
    *    mgr->getJukebox()->addTrack("music/track1.ogg");
    *    mgr->getJukebox()->addtrack("music/track2.wav");
    *    mgr->getJukebox()->play();
    *
    *    // Trigger some sound effects
    *    mgr->getSoundEffectManager()->play("sfx/bullet_blast.wav");
    *    // ...
    *
    *    // Don't forget to free memory when we're done!
    *    delete mgr;
    * \endcode
    *
    * @see Jukebox
    * @see SoundEffectManager
    */
   class SoundManager
   {
   public:
      /**
       * Creates a new SoundManager and initializes the Audiere context.
       *
       * @throw std::runtime_error     if there was a failure initializing
       *                               Audiere.
       */
      SoundManager();

      /**
       * Terminates all playing audio and releases memory used by the audio
       * subsystem.
       */
      ~SoundManager();

      /**
       * Gets the jukebox for this manager. The jukebox is responsible for the
       * queueing and playing of music tracks. Audio played by the Jukebox is
       * usually streamed from the disk.
       *
       * @return  this manager's Jukebox
       */
      Jukebox* getJukebox();

      /**
       * Gets the sound effect manager which is responsible for triggering sound
       * effects. Audio played by the SoundEffectManager is usually loaded into
       * memory and played from there.
       *
       * @return  this manager's SoundEffectManager
       */
      SoundEffectManager* getSoundEffectManager();

   private:
      audiere::Context*   mContext;
      Jukebox*            mJukebox;
      SoundEffectManager* mSoundEffectManager;
   };
}

#endif
