#ifndef PHUI_DEBUG_H
#define PHUI_DEBUG_H

#include <loki/Singleton.h>
#include <iostream>

namespace phui
{
   /**
    * Utility class for outputting messages to a stream.
    */
   class DebugImpl
   {
   public:
      
      /**
       * Default Constructor
       */
      DebugImpl()
         : mStream(&std::cout)
      {}

      /**
       * Sets the stream to use for output.
       *
       * @param   stream      the stream to use for outputting messages.
       */
      void setStream(std::ostream& stream)
      {
         mStream = &stream;
      }

      /**
       * Gets the Debug stream.
       *
       * @param   debug       true if debug output, false otherwise.
       */
      std::ostream& getStream(bool debug)
      {
         (*mStream) << "[phui]:";
         if (debug)
         {
            (*mStream) << "[DBG] ";
         }
         else
         {
            (*mStream) << "[ERR] ";
         }
         return *mStream;
      }

   private:

      /// the stream to use for outputting messages.
      std::ostream*        mStream;
   };

   typedef Loki::SingletonHolder<DebugImpl> Debug;

#define phuiDEBUG(cat) phui::Debug::Instance().getStream(cat)

static const bool phuiDBG_DEBUG = 1;
static const bool phuiDBG_ERROR = 0;

}

#endif
