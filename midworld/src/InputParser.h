/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:

#ifndef MW_INPUT_PARSER_H
#define MW_INPUT_PARSER_H

#include <string>
#include <map>
#include <SDL.h>
#include "InputAction.h"
#include "InputSymbol.h"

namespace mw
{
   /**
    * This class parses a file for input bindings.
    * This class is a Singleton (see _Design Patterns_)
    */
   class InputParser
   {
   public:
   
      ~InputParser()
      {
      }

      /**
       * Gets the instance of this Singleton
       * @return the instance of this Singleton
       */
      static InputParser* instance();

      /**
       * Parses the file and stores the bindings.
       * @param name the name of the file to parse
       */
      void parseFile(const std::string &name);

      /**
       * Binds this action to the keys given from the config file
       * @param name the name action to bind the keys to
       * @param action the action object to bind
       * @return true if the action was successfully bound to a key,
       * false if the action has no keys bound to it.
       */
      bool bindAction(const std::string &name, InputAction *action);

   protected:
      
      /**
       * This class is a Singleton
       * Get at it from instance()
       */
      InputParser()
         : bParseFile(false)
      {
      }
   
   private:
      ///The instance of this Singleton
      static InputParser* mInstance;
      ///The map of actions to keys read
      std::multimap<std::string, InputKey> mActionKeys;
      ///Have we parsed a file yet?
      bool bParseFile;
   };
}//end of namespace mw
#endif
