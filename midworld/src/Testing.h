#ifndef MW_TESTING_H
#define MW_TESTING_H

#include <gmtl/Point.h>
#include <gmtl/LineSeg.h>
#include <gmtl/Generate.h>
#include <gmtl/QuatOps.h>

#include <loom/reflex.h>
#include <loom/behavior.h>
#include <loom/command.h>
#include <loom/unit.h>
#include <loom/aiSystem.h>

#include <vector>



namespace mw
{

   class Droid;
   class Player;
   class Turret;

   class droidTesting : public lm::testing
   {
   public:
      droidTesting(Droid* e, Player* p);
         
      virtual bool test();

   private:
      Droid* mDroid;
      Player* mPlayer;
   };
   

   class turretTesting : public lm::testing
   {
   public:
      turretTesting(Turret* t, Player* p);


      virtual bool test();
         
   private:
      Turret* mTurret;
      Player* mPlayer;

   };

   class droidCommand : public lm::command
   {
   public:
      droidCommand(Droid* e, Player* p);

      virtual void execute();

   private:
      Droid* mDroid;
      Player* mPlayer;
   };

   class turretCommand : public lm::command
   {
      public:

      turretCommand(Turret* t, Player* p);

      virtual void execute();
         



      private:
         Turret* mTurret;
         Player* mPlayer;
   };
   
   
   
   class testing
   {
   public:
      testing() {}

      bool alwaysTrue()
      {
         return true;
      }
      bool alwaysFalse()
      {
         return false;
      }
      bool aimTrue()
      {
         return true;
      }
   private:
   };
} //end mw namespace
   
#endif 

