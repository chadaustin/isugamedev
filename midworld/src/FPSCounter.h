#ifndef MW_FPS_COUNTER_H
#define MW_FPS_COUNTER_H


namespace mw
{
   class FPSCounter
   {
   public:
      FPSCounter()
      {
         mFPS = 0;
         mFrameCount = 0;
         mElapsedTime = 0;
      }
      
      void update(float dt)
      {
         mElapsedTime += dt;
         ++mFrameCount;
         if (mElapsedTime > 1.0f)
         {
            mFPS = mFrameCount;
            mFrameCount = 0;
            mElapsedTime -= 1.0f;
         }
      }
      
      int getFPS() const
      {
         return mFPS;
      }
      
   private:
      int mFPS;
      int mFrameCount;
      float mElapsedTime;
   };
}


#endif
