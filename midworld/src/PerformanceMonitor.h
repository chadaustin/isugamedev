#ifndef MW_PERFORMANCE_MONITOR_H
#define MW_PERFORMANCE_MONITOR_H


#include <stack>
#include <string>
#include <utility>
#include <vector>


namespace mw
{
   class PerformanceMonitor
   {
   public:
      void beginFrame();
      void beginBlock(const std::string& name);
      void endBlock();
      
      const std::vector<std::string>& getOutput() const
      {
         return mLastOutput;
      }
      
   private:
      typedef std::pair<std::string, float> StackEntry;
      
      static float getTime();
   
      std::stack<StackEntry> mBlockStack;
      std::vector<std::string> mOutput;      // current
      std::vector<std::string> mLastOutput;  // last complete frame
   };
   
   class PMBlock
   {
   public:
      PMBlock(PerformanceMonitor& monitor, const std::string& name)
        : mMonitor(monitor)
      {
         mMonitor.beginBlock(name);
      }
      
      ~PMBlock()
      {
         mMonitor.endBlock();
      }
   
   private:
      PerformanceMonitor& mMonitor;
   };
}


#endif
