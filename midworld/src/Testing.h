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


#include "NavNodeTree.h"


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

   class droidFuckedTesting : public lm::testing
   {
   public:
      droidFuckedTesting(Droid* e);
      virtual bool test();
   private:
      Droid* mDroid;
   };
   

   class droidChooseNewNodeTesting : public lm::testing
   {
   public:
      droidChooseNewNodeTesting(Droid* e, NavNodeTree* t);
      virtual bool test();
   private:
      Droid* mDroid;
      NavNodeTree* mTree;
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

   class droidFuckedCommand : public lm::command
   {
   public:
      droidFuckedCommand(Droid* e, NavNodeTree* t);
      virtual void execute();

   private:
      Droid* mDroid;
      NavNodeTree* mTree;
   };

   class droidFindCloseNodeCommand : public lm::command
   {
   public:
      droidFindCloseNodeCommand(Droid* e, NavNodeTree* t);
      virtual void execute();

   private:
      Droid* mDroid;
      NavNodeTree* mTree;
   };

   class droidMoveToNodeCommand : public lm::command
   {
   public:
      droidMoveToNodeCommand(Droid* e, NavNodeTree* t);
      virtual void execute();

   private:
      Droid* mDroid;
      NavNodeTree* mTree;
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
   
   
   class moveTests : public lm::testing
   {
   public:
      moveTests(){}
      virtual bool test(){return true;}
   };
   
   class tests : public lm::testing
   {
   public:
      virtual bool testing() {}

      bool alwaysTrue()
      {
         return true;
      }
      bool alwaysFalse()
      {
         return false;
      }
   private:
   };
} //end mw namespace
   
#endif 

