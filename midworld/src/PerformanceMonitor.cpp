#include <iomanip>
#include <sstream>
#include "PerformanceMonitor.h"


namespace
{

#ifdef WIN32

   #include <windows.h>
   inline float getNow()
   {
      return timeGetTime() / 1000.0f;
   }

#else

   #include <time.h>
   inline float getNow()
   {
      return float(clock()) / CLOCKS_PER_SEC;
   }

#endif

}


namespace mw
{

   void
   PerformanceMonitor::beginFrame()
   {
      mLastOutput = mOutput;
      mOutput.clear();
   }

   void
   PerformanceMonitor::beginBlock(const std::string& name)
   {
      mBlockStack.push(StackEntry(name, getTime()));
   }
   
   void
   PerformanceMonitor::endBlock()
   {
      if (!mBlockStack.empty())
      {
         StackEntry& t = mBlockStack.top();
         float duration = getTime() - t.second;
         
         std::string indent((mBlockStack.size() - 1) * 2, ' ');
         
         std::stringstream ss;
         ss << indent << t.first << ": " << std::setprecision(4) << duration;
         mOutput.push_back(ss.str());
         
         mBlockStack.pop();
      }
   }
   
   float
   PerformanceMonitor::getTime()
   {
      return getNow();
   }

}
