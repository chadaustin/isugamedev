#ifndef MW_JUKEBOX_H 
#define MW_JUKEBOX_H

#include <vector>
#include <string>
#include <audiere.h>

namespace mw
{
   /**
    * Describes a collection of music tracks that may be queued up so that they
    * are played in succession. You generally want to get your Jukebox instance
    * from and instance of the SoundManager class.
    *
    * \code
    *    SoundManager* sndMgr = new SoundManager();
    *    sndMgr->getJukebox()->addTrack("song1.ogg");
    *    sndMgr->getJukebox()->addTrack("whatever.wav");
    *    // ...
    *    sndMgr->getJukebox()->play();
    * \endcode
    *
    * @see SoundManager
    */
   class Jukebox
   {
   public:
      /**
       * The Jukebox uses a specified context to create audio streams.
       */
      Jukebox(audiere::Context* context);

      /**
       * Destroys this jukebox. The currently playing track will be stopped and
       * all memory released.
       */
      ~Jukebox();

      /**
       * Return current size of playlist.
       */
      int getTrackCount() const;

      /**
       * Return the filename at position index.
       */
      const std::string& getTrack(int index) const;

      /**
       * Append a sound filename to the end of the playlist.
       */
      void addTrack(const std::string& track);

      /**
       * Remove the track from the playlist if it exists.  Otherwise, do
       * nothing.
       */
      void removeTrack(const std::string& track);

      /**
       * Remove the track at position index from the playlist.
       */
      void removeTrack(int index);

      /**
       * Start playing tracks sequentially from the jukebox.
       */
      void play();

      /**
       * Tell Jukebox to stop playing sound.
       */
      void stop();

      /**
       * Updates the jukebox, moving to the next song if necessary.
       *
       * Call this once every frame or so.
       */
      void update();

   private:
      void tryOpenTrack();
      void nextTrack();

      audiere::Context* mContext;
      std::vector<std::string> mTracks;

      int mCurrentIndex;
      audiere::Stream* mCurrentTrack;
      bool mIsPlaying;
   };
}

#endif
