#include <gmtl/Generate.h>
#include <gmtl/LineSeg.h>
#include <gmtl/Point.h>
#include <gmtl/QuatOps.h>

#include "Testing.h"
#include "Droid.h"
#include "Player.h"
#include "Turret.h"

namespace mw
{

   droidTesting::droidTesting(Droid* e, Player* p)
   {
      mDroid = e;
      mPlayer = p;
   }

   droidFuckedTesting::droidFuckedTesting(Droid* e)
   {
      mDroid = e;
   }

   droidChooseNewNodeTesting::droidChooseNewNodeTesting(Droid* e, NavNodeTree* t)
   {
      mDroid = e;
      mTree = t;
   }

   

   turretTesting::turretTesting(Turret* t, Player* p)
   {
      mTurret = t;
      mPlayer = p;
   }

   droidCommand::droidCommand(Droid* e, Player* p)
   {
      mPlayer = p;
      mDroid = e;
   }

   droidFuckedCommand::droidFuckedCommand(Droid* e, NavNodeTree* t)
   {
      mDroid = e;
      mTree = t;
   }

   droidFindCloseNodeCommand::droidFindCloseNodeCommand(Droid* e, NavNodeTree* t)
   {
      mDroid = e;
      mTree = t;
   }

   droidMoveToNodeCommand::droidMoveToNodeCommand(Droid* e, NavNodeTree* t)
   {
      mDroid = e;
      mTree = t;
      mDroid->setWasFuckedFlag(true);
   }

   turretCommand::turretCommand(Turret* t, Player* p)
   {
      mTurret = t;
      mPlayer = p;
   }
   
   
   bool droidTesting::test()
   {
      gmtl::Vec3f drd, pA, pB, plyr;

      gmtl::Vec3f reach(0.0f, 0.0f, 30.0f);
      
      gmtl::Quatf nRot = gmtl::makeRot<gmtl::Quatf>(
         gmtl::AxisAnglef(45, 0, 1, 0));
      gmtl::Quatf mRot = gmtl::makeRot<gmtl::Quatf>(
         gmtl::AxisAnglef(-45, 0, 1, 0));

      
      drd = mDroid->getPos();
      plyr = mPlayer->getPos();
      pA = mDroid->getPos()+(mDroid->getRot()*nRot)*reach;
      pB = mDroid->getPos()+(mDroid->getRot()*mRot)*reach;

      // this big chunk checks to see if a point is inside a triangle given
      // the 3 triangles vertices. ugh!
      if(((((plyr[2]-drd[2])*(pA[0]-drd[0])) - ((plyr[0]-drd[0])*(pA[2]-drd[2]))) *
               (((plyr[2]-pA[2])*(pB[0]-pA[0])) - ((plyr[0]-pA[0])*(pB[2]-pA[2]))) > 0) &&
            ((((plyr[2]-pA[2])*(pB[0]-pA[0])) - ((plyr[0]-pA[0])*(pB[2]-pA[2]))) *
             (((plyr[2]-pB[2])*(drd[0]-pB[0])) - ((plyr[0]-pB[0])*(drd[2]-pB[2]))) > 0))

     {
         // we are in the droids sights now so we would return true
         return true;
      }
      else
      {
         return false;
      }
   }

   bool droidFuckedTesting::test()
   {
      if(mDroid->getFuckedFlag())
      {
         return true;
      }else{
         return false;
      }
   }

   bool droidChooseNewNodeTesting::test()
   {
      bool temp = true;
      for(int i=0; i<3;i++)
      {
         if(!((mDroid->getGoalNode()->loc[i] < mDroid->getPos()[i]+.5) && 
               (mDroid->getGoalNode()->loc[i] > mDroid->getPos()[i]-.5)))
               {
                  temp = false;
               }
      }
      return temp;
   }

   
   bool turretTesting::test()
   {
      gmtl::Point3f pos1, pos2;
      pos1 = mTurret->getPos();
      pos2 = mPlayer->getPos();
      gmtl::LineSegf dist(pos1, pos2);
      if(dist.getLength() < 20)
         return true;
      else
         return false;
   }

   

   void droidCommand::execute()
   {
      
      gmtl::Vec3f zeroVec(0.0f, 0.0f, 0.0f);
      
      // set this to true so that we can test to see if we aren't in our path
      // anymore ... oh my god what a shitty shitty hack
      mDroid->setFuckedFlag(true);
      if(!mDroid->getWasFuckedFlag())
      {
         mDroid->setWasFuckedFlag(true);
         mDroid->setVel(zeroVec);
      }
      
      

      
      
      gmtl::Vec3f upVec(0.0f, 0.0f, 1.0f);
      gmtl::Vec3f downVec(0.0f,0.0f,-1.0f);
      
      gmtl::Quatf currentQuat = mDroid->getRot(); /// Turret's current orientation
      gmtl::Vec3f vecToPlayer = mPlayer->getPos()-mDroid->getPos();
      gmtl::normalize(vecToPlayer);
      /// quaternion representing the rotation angle it would take to point at the player.
      gmtl::Quatf mQuat = gmtl::makeRot<gmtl::Quatf>(upVec, vecToPlayer); 
      /// the quat that we are actually going to rotate the turret by.
      gmtl::Quatf finalQuat;  
      

      gmtl::slerp(finalQuat, 0.055f, currentQuat, mQuat);  /// slerp to 4/10 the angle we need to have.
      mDroid->setRot(finalQuat); 
      
      // now that we have the new rotation move us forward in that direction
      mDroid->addForce(mDroid->getRot()*upVec);

      
      mQuat = gmtl::makeRot<gmtl::Quatf>(downVec, vecToPlayer);
      gmtl::slerp(finalQuat, 1.0f, finalQuat, mQuat);
      gmtl::Vec3f offset(0,0,3);
      mDroid->getGun()->setRot(finalQuat);
      mDroid->getGun()->setPos(mDroid->getPos()+(mDroid->getRot()*offset));
      mDroid->getGun()->trigger(true);
   }
   

   void droidFuckedCommand::execute()
   {
      mDroid->setGoalNode(mDroid->getTree()->findNearestNavNode(mDroid->getPos()));
      mDroid->setFakeNode(mDroid->getPos());
   }
   

   void droidFindCloseNodeCommand::execute()
   {
      gmtl::Vec3f zeroVec(0.0f, 0.0f, 0.0f);
      mDroid->setVel(zeroVec);
      // set the current Node to the node we are at (which is the goal node)
      mDroid->setCurrentNode(mDroid->getGoalNode());
      // possible nodes is a vector of all the possible nodes that we could go
      // to next.
      std::vector<Node*> possibleNodes;
      possibleNodes = mTree->allLinks(mDroid->getGoalNode()->name);
      // we get some number between 0 and the vectors size + .999
      // we actuall want to add 1 but the possibility exists that the returned
      // value would be the integer size of the vector and to add 1 and round
      // down would then still put us off the end of the vector so we can only
      // add .999
      int someNum = (int)gmtl::Math::rangeRandom(0, ((float)possibleNodes.size()-0.001f));
      mDroid->setGoalNode(possibleNodes[someNum]);
      mDroid->setFakeNode(mDroid->getCurrentNode()->loc);
      mDroid->setWasFuckedFlag(false);
   }

   void droidMoveToNodeCommand::execute()
   {
      gmtl::Vec3f result(0.0f, 0.0f, 0.0f);
      gmtl::Vec3f temp;
      std::cout << "in moveDroid (executed every frame):" << std::endl;
      if(mDroid->getFuckedFlag())
      {
         std::cout << "  * FuckedFlag is set" << std::endl;
      }
      else if(mDroid->getWasFuckedFlag())
      {  
         if(mDroid->getFirstTimeFlag()==true)
         {
            mDroid->setVel(result);
            mDroid->setFirstTimeFlag(false);
         }
            
         std::cout << "  * wasFuckedFlag is set" << std::endl;
         std::cout << "    * force is: " << mDroid->getVel() << std::endl;
         std::cout << "    * fakeNode: " << mDroid->getFakeNode()->loc << std::endl;
         std::cout << "    * goalNode: " << mDroid->getGoalNode()->loc << std::endl;
         std::cout << "    * droidPos: " << mDroid->getPos() << std::endl;
         temp = (mDroid->getGoalNode()->loc - mDroid->getFakeNode()->loc);
         result += temp;
         if(gmtl::length(mDroid->getVel()) < 120.0f)
         {  
            result /= 40;
            mDroid->addForce(result);
         }
      }else
      {
         std::cout << "  * default implemenatation" << std::endl;
         std::cout << "    * mDroid->name: " << mDroid->getGoalNode()->name << "  goal->pos: " << mDroid->getGoalNode()->loc << std::endl << std::endl;
         result = mDroid->getGoalNode()->loc - mDroid->getCurrentNode()->loc;
         if(gmtl::length(mDroid->getForce()) < 30.0f)
            
         {  
            result/=10;
            mDroid->addForce(result);
         }
      }
      mDroid->setFuckedFlag(false);
   }
            
   void turretCommand::execute()
   {
      gmtl::Vec3f upVec(0.0f, 0.0f, 1.0f);
      gmtl::Vec3f downVec(0.0f,0.0f,-1.0f);
      gmtl::Quatf currentQuat = mTurret->getRot(); /// Turret's current orientation
      gmtl::Vec3f vecToPlayer = mPlayer->getPos()-mTurret->getPos();
      gmtl::normalize(vecToPlayer);
      gmtl::Quatf mQuat = gmtl::makeRot<gmtl::Quatf>(upVec, vecToPlayer); /// quaternion representing the rotation angle it would take to point at the player.
      gmtl::Quatf finalQuat;  /// the quat that we are actually going to rotate the turret by.
      
      gmtl::slerp(finalQuat, 0.04f, currentQuat, mQuat);  /// slerp to 4/10 the angle we need to have.
      mTurret->setRot(finalQuat); 
         
      mQuat = gmtl::makeRot<gmtl::Quatf>(downVec, vecToPlayer);
      gmtl::slerp(finalQuat, 1.0f, finalQuat, mQuat);
      gmtl::Vec3f offset(0,0,6);
      mTurret->getGun()->setRot(finalQuat);
      mTurret->getGun()->setPos(mTurret->getPos()+(mTurret->getRot()*offset));
      mTurret->shoot();
    
   }
}


