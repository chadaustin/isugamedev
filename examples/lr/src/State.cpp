#include "State.h"
#include "Application.h"

namespace lr
{
   State::State( Application* a ) : mApp(a)
   {
      mIsQuitting = false;
      
   }

   State::~State()
   {
   }

   void State::quit()
   {
      mIsQuitting = true;
   }

   bool State::isQuitting()
   {
      return mIsQuitting;
   }
   
} // end of namespace
