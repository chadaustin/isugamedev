/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: GameTimer.h,v $
 * Date modified: $Date: 2002-03-27 05:18:31 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 ************************************************************ brotha-cpr-end */
#ifndef UTIL_GAMETIMER_H
#define UTIL_GAMETIMER_H

#ifdef WIN32
#  include <sys/types.h>
#  include <sys/timeb.h>
#else
#  include <sys/time.h>
#endif // WIN32

namespace game
{
   /**
    * Keeps track of the time in the game assuming that the beginning of the
    * game is time zero. Time is tracked in milliseconds. This class works much
    * like a stopwatch allowing you to start, stop, pause and reset the timer.
    */
   class GameTimer
   {
   public:
      /**
       * Creates a new game timer with zero elapsed time.
       */
      GameTimer()
         : mGameTime(0), mLastTime(0), mStoppedTime(0), mStopped(true)
      {}

      /**
       * Starts the timer so that game time is incremented on subsequent calls
       * to update().
       *
       * @see start()
       * @see stop()
       */
      void start()
      {
         if ( isStopped() )
         {
            // get the current time
            double curTime = getSysTime();
            mStopped = false;

            // check if this is a resume rather than a restart
            if ( mStoppedTime != 0.0 )
            {
               mLastTime += (curTime - mStoppedTime);
               mStoppedTime = 0.0;
            }
            else
            {
               mLastTime = curTime;
            }
         }
      }

      /**
       * Stops the timer. Game time is no longer incremented on subsequent
       * calls to update() until start() is called.
       *
       * @see start()
       * @see update()
       */
      void stop()
      {
         if ( ! isStopped() )
         {
            mStoppedTime = getSysTime();
            mGameTime += (mStoppedTime - mLastTime);
            mStopped = true;
         }
      }

      /**
       * Tests if game time is stopped
       *
       * @return  true if game time is stopped; false otherwise
       */
      bool isStopped() const
      {
         return mStopped;
      }

      /**
       * Resets game time back to zero.
       */
      void reset()
      {
         mGameTime = 0.0;
         mLastTime = getSysTime();
         mStoppedTime = 0.0;
      }

      /**
       * Updates game time to reflect the amount of real time that has passed
       * since the last update. If game time is paused, game time will not be
       * incremented.
       */
      void update()
      {
         if ( ! isStopped() )
         {
            // determine the amount of time has elapsed since the last update
            double curTime = getSysTime();
            double deltaTime = curTime - mLastTime;
            mLastTime = curTime;

            // update game time as appropriate
            mGameTime += deltaTime;
         }
      }

      /**
       * Gets the current game time in milliseconds.
       *
       * @return  the current game time in ms
       */
      double getElapsedTime() const
      {
         return mGameTime;
      }

      /**
       * Cross platform method to get the current system time in milliseconds.
       *
       * This function is based on Kevin Meinert's StopWatch class released
       * under LGPL.
       *
       * @return  the current system time in milliseconds
       */
      static double getSysTime()
      {
#ifdef WIN32
         struct _timeb tv;
         _ftime( &tv );

         // consolidate to milliseconds
         return ( static_cast<double>(tv.time) +
                  static_cast<double>(tv.millitm) / 1000.0 );
#else
         struct timeval tv;
         gettimeofday( &tv, 0 );

         // consolidate to milliseconds
         return ( static_cast<double>(tv.tv_sec) +
                  static_cast<double>(tv.tv_usec) / 1000000.0 );
#endif // WIN32
      }

   private:
      /**
       * The current game time (elapsed game time).
       */
      double mGameTime;

      /**
       * The time of the last update.
       */
      double mLastTime;

      /**
       * The time of the last stop() call.
       */
      double mStoppedTime;

      /**
       * Stopped flag. True if game time is stopped.
       */
      bool mStopped;
   };
}

#endif
