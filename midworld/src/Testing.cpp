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
         
      mQuat = gmtl::makeRot<gmtl::Quatf>(downVec, vecToPlayer);
      gmtl::slerp(finalQuat, 1.0f, finalQuat, mQuat);
      gmtl::Vec3f offset(0,0,3);
      mDroid->getGun()->setRot(finalQuat);
      mDroid->getGun()->setPos(mDroid->getPos()+(mDroid->getRot()*offset));
      mDroid->getGun()->trigger(true);
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


