#ifndef QUATERNION_CLASS_SELF_TEST_H
#define QUATERNION_CLASS_SELF_TEST_H

#include <iostream>

#include <TestCase.h>
#include <TestSuite.h>
#include <TestCaller.h>

#include "Defines.h"
#include "Quat.h"
#include "Vec3.h"

/*****************************************************************
 tests out the functionality expected of Quat<float>
*******************************************************************/

namespace tankTest
{

class QuatSelfTest : public TestCase
{
public:
   QuatSelfTest( std::string name ) : TestCase (name)
   {
   }
   
   
   virtual ~QuatSelfTest()
   {
   }

   void mathSanityTest()
   {
      //std::cout<<"test the sanity of the available math lib\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      float d = kev::deg2rad( 45.0f );
      //std::cout<<"deg2rad(45.0f) == "<<d<<"\n"<<std::flush;
      assertTest( d >= 0.7850 && d <= 0.7870 );
   }

   void identTest()
   {
      // the default identity is currently the multiplicative identity [1,0,0,0]
      // not the addition identity... [0,0,0,0]
      // consider allowing both kinds of identity to be made in the quat API...
      Quat<float> quat;
      quat.makeIdent();
      assertTest( quat == Quat<float>::identity() );
      assertTest( quat[Quat<float>::QUAT_W] == 1.0f && quat[Quat<float>::QUAT_X] == 0.0f && 
                  quat[Quat<float>::QUAT_Y] == 0.0f && quat[Quat<float>::QUAT_Z] == 0.0f );
   }

   void makePureTest()
   {
      //std::cout<<"make sure that makePure creates expected results...\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

    Quat<float> q;
      q.makePure( Vec3<float>( 0, 1.0f, 0 ) );
//      std::cout<<"q:           "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      assertTest( q[Quat<float>::QUAT_W] == 0 );
      assertTest( q[Quat<float>::QUAT_X] == 0 );
      assertTest( q[Quat<float>::QUAT_Y] == 1.0f );
      assertTest( q[Quat<float>::QUAT_Z] == 0 );

      q.makePure( Vec3<float>( 0, 0, -0.4f ) );
  //    std::cout<<"q:           "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      assertTest( q[Quat<float>::QUAT_W] == 0 );
      assertTest( q[Quat<float>::QUAT_X] == 0 );
      assertTest( q[Quat<float>::QUAT_Y] == 0 );
      assertTest( q[Quat<float>::QUAT_Z] == -0.4f );
      //assertTest( q[Quat<float>::QUAT_Z] >= -0.4001 && q[Quat<float>::QUAT_Z] <= -0.3998);

      q.makePure( Vec3<float>( 0, 1000.0f, 0 ) );
    //  std::cout<<"q:           "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      assertTest( q[Quat<float>::QUAT_W] == 0 );
      assertTest( q[Quat<float>::QUAT_X] == 0 );
      assertTest( q[Quat<float>::QUAT_Y] == 1000.0f );
      assertTest( q[Quat<float>::QUAT_Z] == 0 );

      q.makePure( Vec3<float>( -0.7f, 0.7f, -0.7f ) );
      //std::cout<<"q:           "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      assertTest( q[Quat<float>::QUAT_W] == 0 );
      assertTest( q[Quat<float>::QUAT_X] == -0.7f );
      assertTest( q[Quat<float>::QUAT_Y] == 0.7f );
      assertTest( q[Quat<float>::QUAT_Z] == -0.7f );

      q.makePure( Vec3<float>( -100.0f, 100.0f, 100.0f ) );
      //std::cout<<"q:           "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      assertTest( q[Quat<float>::QUAT_W] == 0 );
      assertTest( q[Quat<float>::QUAT_X] == -100.0f );
      assertTest( q[Quat<float>::QUAT_Y] == 100.0f );
      assertTest( q[Quat<float>::QUAT_Z] == 100.0f );
   }

   void makeRotTest()
   {
      //std::cout<<"make sure that makeRot creates expected results...\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      // deg2rad( 45.0f ) == 0.785398 
      // deg2rad( 45.0f )* 0.5f == 0.392699  
      // cosf( deg2rad( 45.0f ) * 0.5f) == 0.923879 
      // sinf( deg2rad( 45.0f ) * 0.5f) == 0.382683 
      // sinf( deg2rad( 45.0f ) * 0.5f) * 1.0f == 0.382683
      
      //std::cout<<kev::deg2rad( 45.0f )<<" "<<kev::deg2rad( 45.0f ) *
      //0.5f << "  " << cosf( kev::deg2rad( 45.0f ) * 0.5f) << " " <<
      //sinf( kev::deg2rad( 45.0f ) * 0.5f) << " " << sinf( kev::deg2rad(
      //45.0f ) * 0.5f) * 1.0f <<"\n"<<std::flush;


      Quat<float> q;
      q.makeRot( kev::deg2rad( 45.0f ), 0,-1,0 );
      //std::cout<<"q:           "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
 
      assertTest( q[Quat<float>::QUAT_W] <= 0.923880f && q[Quat<float>::QUAT_W] >= 0.923875f );
      assertTest( q[Quat<float>::QUAT_X] <= 0.0f && q[Quat<float>::QUAT_X] >= 0.0f );
      assertTest( q[Quat<float>::QUAT_Y] <= -0.382680f && q[Quat<float>::QUAT_Y] >= -0.382685 );
      assertTest( q[Quat<float>::QUAT_Z] <= 0.0f && q[Quat<float>::QUAT_Z] >= 0.0f );
     
      q.makeRot( kev::deg2rad( 45.0f ), 1,0,0 );
      //std::cout<<"q:           "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      assertTest( q[Quat<float>::QUAT_W] <= 0.923880f && q[Quat<float>::QUAT_W] >= 0.923875f );
      assertTest( q[Quat<float>::QUAT_X] <= 0.382685f && q[Quat<float>::QUAT_X] >= 0.382680 );
      assertTest( q[Quat<float>::QUAT_Y] <= 0.0f && q[Quat<float>::QUAT_Y] >= 0.0f );
      assertTest( q[Quat<float>::QUAT_Z] <= 0.0f && q[Quat<float>::QUAT_Z] >= 0.0f );
   }
      
   void makeRotNormalizeTest()
   {
      //std::cout<<"make sure that normalize doesn't change the rotation...\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      Quat<float> q1, q2, q3, q4;
      q1.makeRot( kev::deg2rad( 45.0f ), 0,1,0 );
      q2.makeRot( kev::deg2rad( 90.0f ), 1,0,0 );
      q3 = q1; 
      q4 = q2;
      q3.normalize();
      q4.normalize();

      /*
      std::cout<<"before: \n"<<std::flush;
      std::cout<<"q1:           "<<q1<<" .. "<<q1[Quat<float>::QUAT_W]<<" "<<q1[Quat<float>::QUAT_X]<<" "<<q1[Quat<float>::QUAT_Y]<<" "<<q1[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      std::cout<<"q2:           "<<q2<<" .. "<<q2[Quat<float>::QUAT_W]<<" "<<q2[Quat<float>::QUAT_X]<<" "<<q2[Quat<float>::QUAT_Y]<<" "<<q2[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      std::cout<<"after: \n"<<std::flush;
      std::cout<<"q1:           "<<q1<<" .. "<<q1[Quat<float>::QUAT_W]<<" "<<q1[Quat<float>::QUAT_X]<<" "<<q1[Quat<float>::QUAT_Y]<<" "<<q1[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      std::cout<<"q2:           "<<q2<<" .. "<<q2[Quat<float>::QUAT_W]<<" "<<q2[Quat<float>::QUAT_X]<<" "<<q2[Quat<float>::QUAT_Y]<<" "<<q2[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      std::cout<<"\n"<<std::flush;
      */

      // make sure that normalize doesn't change the rotation...         
      assertTest( q1.isEqual( q3, 0.0001 ) );
      assertTest( q2.isEqual( q4, 0.0001 ) );
   }

   void xformVecSweepTest()
   {
      //std::cout<<"xform vector by quat (sweep over range of rotations)\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;
      Quat<float> q;
      Vec3<float> v(0,0,1);
      q.makeIdent();

      //std::cout<<"Should go from 0,0,1 to 0,-1,0 to 0,0,-1 ....\n"<<std::flush;
      for (float x = 0; x <= 180.0f; x+=90)
      {
         q.makeRot( kev::deg2rad( x ), 1,0,0 );

         Vec3<float> result = q * v;
         //std::cout<<result<<"\n"<<std::flush;
         if (x == 0)
            assertTest( result[0] < 0.001 && result[1] < 0.001 && result[2] > 0.999 );
         if (x == 90)
            assertTest( result[0] < 0.001 && result[1] < -0.999 && result[2] < 0.001 );
         if (x == 180)
            assertTest( result[0] < 0.001 && result[1] < 0.001 && result[2] < -0.999 );
      }
      //std::cout<<"\n"<<std::flush;
   }

   void makeRotGetRotSanityTest()
   {
      //std::cout<<"testing sanity of makeRot and getRot, then makeRot again...\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      for (float i = -360; i <= 360; i+=20)
      {
         Quat<float> q, q2;
         float rad, x, y, z;
         q.makeRot( kev::deg2rad(i),1,0,0 );
         //std::cout<<i<<") "<<q<<" .. "<<q[Quat<float>::QUAT_W]<<" "<<q[Quat<float>::QUAT_X]<<" "<<q[Quat<float>::QUAT_Y]<<" "<<q[Quat<float>::QUAT_Z]<<" compare to: "<<std::flush;

         q.getRot( rad, x, y, z );
         q2.makeRot( rad, x, y, z );
         //std::cout<<q2[Quat<float>::QUAT_W]<<" "<<q2[Quat<float>::QUAT_X]<<" "<<q2[Quat<float>::QUAT_Y]<<" "<<q2[Quat<float>::QUAT_Z]<<"\n"<<std::flush;

         // make i a positive by x*360, store in b.  needed so I can use the % operator with neg values..
         assertTest( q.isEqual( q2, 0.0001 ) );

         float b = i;
         while ( b < 0.0f)
         {
            b += 360.0f;
         }      

         if (i >= 0.0f)
         {
            float c = kev::ABS( (float)((int)(kev::round(b))%360) );
            float temp1 = kev::rad2deg(rad); temp1 = (float)((int)(kev::round(temp1))%360);
            float temp2 = c + 0.5;
            float temp3 = kev::rad2deg(rad); temp3 = (float)((int)(kev::round(temp3))%360);
            float temp4 = c - 0.5;
            //   std::cout<<temp1<<" "<<temp2<<" "<<temp3<<" "<<temp4<<" "<<kev::rad2deg(rad)<<" "<<b<<"\n"<<std::flush;

            assertTest( temp1 <= temp2 && temp3 >= temp4 );     
         }    
      }
      //std::cout<<"\n"<<std::flush;
   }

   void scalarMultTest()
   {
      //std::cout<<"testing scaling...\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      for (float i = -360; i <= 360; i+=20)
      {
         Quat<float> q, q2;
         float rad, x, y, z;
         q.makeRot( kev::deg2rad(i),1,0,0 );
         q2.scaleAngle( q, 0.5 );
         q2.getRot( rad, x, y, z );

         // make i a positive by x*360, store in b.  needed so I can use the % operator with neg values..
          //std::cout<<kev::rad2deg(rad)<<" "<<(0.5 * i)<<"\n"<<std::flush;
          float half_quat_angle = kev::rad2deg(rad);
          float half_original_angle = (0.5 * i);
          half_quat_angle = kev::ABS( half_quat_angle );
          half_original_angle = kev::ABS( half_original_angle );

          float tol = 0.1;
          assertTest( (half_original_angle <= (half_quat_angle + tol)) &&
               (half_original_angle >= (half_quat_angle - tol)) );
      }

      //std::cout<<"\n"<<std::flush;
   }

   void simpleQuatProductTest()
   {
      //std::cout<<"Quat<float> product: no rotation * rotation\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      Quat<float> q1, q2, q3;
      q1.makeRot( 0, 1,0,0 );
      q2.makeRot( kev::deg2rad( 90.0f ), 1,0,0 );
      //std::cout<<"[0 rotation] * [90deg about x] should be [90deg about x]\n"<<std::flush;
      //std::cout<<"q1:           "<<q1<<" .. "<<q1[Quat<float>::QUAT_W]<<" "<<q1[Quat<float>::QUAT_X]<<" "<<q1[Quat<float>::QUAT_Y]<<" "<<q1[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      //std::cout<<"q2:           "<<q2<<" .. "<<q2[Quat<float>::QUAT_W]<<" "<<q2[Quat<float>::QUAT_X]<<" "<<q2[Quat<float>::QUAT_Y]<<" "<<q2[Quat<float>::QUAT_Z]<<"\n"<<std::flush;

      // first rotate by q2, then by q1
      q3 = q1 * q2;

      //std::cout<<"q3 = q1 * q2: "<<q3<<" .. "<<q3[Quat<float>::QUAT_W]<<" "<<q3[Quat<float>::QUAT_X]<<" "<<q3[Quat<float>::QUAT_Y]<<" "<<q3[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      //std::cout<<"\n"<<std::flush;

      Vec3<float> v( 0,1,0 ), r;
      r = q3 * v;
      //std::cout<<r<<"\n"<<std::flush;
      //std::cout<<"\n"<<std::flush;

      assertTest( r[2] > 0.99f );
   }

   // another quaternion product test
   void secondQuatProductTest()
   {
      //std::cout<<"Quat<float> product: rotation * rotation\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;
      Quat<float> q1, q2, q3;
      q1.makeRot( kev::deg2rad( 45.0f ), 0,1,0 );
      q2.makeRot( kev::deg2rad( 90.0f ), 1,0,0 );
      //std::cout<<"[45 about Y] * [90 about X] should be [90deg about .7,0,-.7]\n"<<std::flush;
      //std::cout<<"q1:           "<<q1<<" .. "<<q1[Quat<float>::QUAT_W]<<" "<<q1[Quat<float>::QUAT_X]<<" "<<q1[Quat<float>::QUAT_Y]<<" "<<q1[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      //std::cout<<"q2:           "<<q2<<" .. "<<q2[Quat<float>::QUAT_W]<<" "<<q2[Quat<float>::QUAT_X]<<" "<<q2[Quat<float>::QUAT_Y]<<" "<<q2[Quat<float>::QUAT_Z]<<"\n"<<std::flush;

      // first rotate by q2, then by q1
      q3 = q1 * q2;
      //q3.normalize();

      //std::cout<<"q3 = q1 * q2: "<<q3<<" .. "<<q3[Quat<float>::QUAT_W]<<" "<<q3[Quat<float>::QUAT_X]<<" "<<q3[Quat<float>::QUAT_Y]<<" "<<q3[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      //std::cout<<"\n"<<std::flush;

      Vec3<float> v( 0,1,0 ), r;
      r = q3 * v;
      //std::cout<<r<<"\n"<<std::flush;
      //std::cout<<"\n"<<std::flush;

      assertTest( r[0] > 0.7 && r[2] > 0.7 );
   }

   void xformVecTest()
   {
      //std::cout<<"xform vec by quat\n"<<std::flush;
      //std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;
      Quat<float> q1, q2;//, q3;
      q1.makeRot( kev::deg2rad( 45.0f ), 0,-1,0 );
      q2.makeRot( kev::deg2rad( 45.0f ), 1,0,0 );

      Vec3<float> v( 0,1,0 ), r;

      // (should not move)
      r = q1 * v;
      //std::cout<<r<<"\n"<<std::flush;
      assertTest( r[1] > 0.999 );

      // rotate forward
      r = q2 * v;
      //std::cout<<r<<", each elt should be > 0.7\n"<<std::flush;
      assertTest( r[1] > 0.7 && r[2] > 0.7 );

      //std::cout<<"\n"<<std::flush;
   }


   // just trying stuff out... TODO think of a good add test...
   void specialCases()
   {
      std::cout<<"special cases\n"<<std::flush;
      std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      Quat<float> q( 1, 0, -0.000313354, 0 );
      float rad, x, y, z;
      q.getRot( rad, x, y, z );

      std::cout<<rad<<" "<<x<<" "<<y<<" "<<z<<"\n"<<std::flush;

      // testing...
      double half_angle = 0.000626708 * 0.5f;
      double sin_half_angle = kev::SIN( half_angle );
      double w = kev::COS( half_angle );
      std::cout<<half_angle<<" "<<sin_half_angle<<" "<<w<<"\n"<<std::flush;


      //vjQuat<float> qq( 0,0,0,0 );

      std::cout<<"make sure that makeRot(180,0,1,0) doesn't yield [0,0,0,0]\n"<<std::flush;
      Quat<float> qqq;
      qqq.makeRot( kev::deg2rad( 180.0f ), 0, 1, 0 );
      std::cout<<"qqq: "<<qqq<<" .. "<<qqq[Quat<float>::QUAT_W]<<" "<<qqq[Quat<float>::QUAT_X]<<" "<<qqq[Quat<float>::QUAT_Y]<<" "<<qqq[Quat<float>::QUAT_Z]<<"\n"<<std::flush;
      assertTest( qqq[Quat<float>::QUAT_W] < 0.0001 && qqq[Quat<float>::QUAT_W] > -0.0001 &&
              qqq[Quat<float>::QUAT_X] == 0.0f &&
              qqq[Quat<float>::QUAT_Y] > (1.0f - 0.0001) && qqq[Quat<float>::QUAT_Y] < (1.0f + 0.0001) &&
              qqq[Quat<float>::QUAT_Z] == 0.0f );

      std::cout<<"\n"<<std::flush;
   }

   // just trying stuff out... TODO think of a good way to test this ability...
   // TODO: could we use a vector (pure quat) to scale a quat in a 
   //        more robust way?  pretty sure we can... rewrite scaleAngle to use this
   //        method instead....
   void vectorScaleTest()
   {
      std::cout<<"vector scale of a rotation quaternion\n"<<std::flush;
      std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      std::cout<<"vector scale of a rotation quaternion yields an invalid rotation (only unit-quats define a rotation).\n"<<std::flush;

      // non normalized
      for (int x = 0; x < 360; ++x)
      {
         Quat<float> q, q2;
         q.makeRot( kev::deg2rad( (float)x ), 0.7, 0, 0.7 );
         q2.mult( q, 0.5 );

         // no longer a valid rotation (non-unit length).  
         // should be normalized to define an actual rotation.
         assertTest( q2.length() <= (1.0f - 0.0001) ||
                 q2.length() >= (1.0f + 0.0001) );

         float rad, i,j,k;
         q2.getRot( rad, i,j,k );
         std::cout<<x<<") "<<kev::rad2deg( rad )<<" "<<i<<" "<<j<<" "<<k<<"\n"<<std::flush;
      }

      std::cout<<"If normalized, then the scaled quat is equal to the original."<<std::flush;
      // normalized.  
      for (int x = 0; x < 360; ++x)
      {
         Quat<float> q, q2;
         q.makeRot( kev::deg2rad( (float)x ), 0.7, 0, 0.7 );
         q2.mult( q, 0.5 );
         q2.normalize();

         assertTest( q2.isEqual( q, 0.0001 ) );
      }        

      std::cout<<"\n"<<std::flush;
   }

   // just trying stuff out... TODO think of a good add test...
   void quatAdd()
   {
      std::cout<<"quat add\n"<<std::flush;
      std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;


      {
         Quat<float> q, q1, q2;
         q1.makeRot( kev::deg2rad( 90.0f ), 1, 0, 0 );
         q2.makeRot( kev::deg2rad( 180.0f ), 1, 0, 0 );

         q.add( q1, q2 );
         q.normalize();

         std::cout<<q<<"\n"<<std::flush;
      }

      Quat<float> q, q1;//, q2;
      q1.makeRot( kev::deg2rad( 90.0f ), 1, 0, 0 );

      q = q1 * q;

      std::cout<<q<<"\n"<<std::flush;
   }

   // using a vector to increment rotation, much like angular velocity
   // here angular velocity is defined as a Vec3<float> "w", using right hand rule
   // things spin at |w| speed and on the w vector.
   //
   // just trying stuff out... TODO think of a good way to test this ability...
   void pureQuatMultTest()
   {
      std::cout<<"pureQuatMultTest (angular velocity test)\n"<<std::flush;
      std::cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"<<std::flush;

      for (float x = 0; x < 100; ++x)
      {
         Quat<float> q1, q2, wq;
         Vec3<float> w(0, x, 0); // angular velocity
         wq.makePure( w );
         q1.makeRot( kev::deg2rad( 90.0f ), 0, 1, 0 );

         q2 = wq * q1;
         //////q2.normalize();  // don't normalize, will not work!!!!!!!!!

         std::cout<<"["<<q2<<"] == ["<<wq<<"] * ["<<q1<<"]\n"<<std::flush;
      }

      Quat<float> q1, wq;
      Vec3<float> ww(0, 56, 0);
      wq.makePure( ww );
      q1.makeRot( kev::deg2rad( 90.0f ), 0, 1, 0 );

      const float& w1( wq[Quat<float>::QUAT_W] );
      const float& w2( q1[Quat<float>::QUAT_W] );
      Vec3<float> v1( wq[Quat<float>::QUAT_X], wq[Quat<float>::QUAT_Y], wq[Quat<float>::QUAT_Z] );
      Vec3<float> v2( q1[Quat<float>::QUAT_X], q1[Quat<float>::QUAT_Y], q1[Quat<float>::QUAT_Z] );

      float w = w1 * w2 - v1.dot( v2 );
      Vec3<float> v = (v2 * w1) + (v1 * w2) + v1.cross( v2 );

      std::cout<<"["<<w<<", "<<v[0]<<", "<<v[1]<<", "<<v[2]<<"] == ["<<wq<<"] * ["<<q1<<"]\n"<<std::flush;
      std::cout<<(v2 * w1)<<"  == (w1 * v2) \n"<<std::flush;
      std::cout<<(v1 * w2)<<"  == (w2 * v1) \n"<<std::flush;
      std::cout<<v1.cross( v2 )<<"  == v1.cross( v2 ) \n"<<std::flush;
      std::cout<<v1<<" dot "<<v2<<" == "<<v1.dot( v2 )<<"\n"<<std::flush;
   }

   //assertTest( a != b.code() );
   
   
   static Test* suite()
   {
      TestSuite *test_suite = new TestSuite ("QuatSelfTest");

      test_suite->addTest( new TestCaller<QuatSelfTest>("basic math sanity test", &QuatSelfTest::mathSanityTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("identity test", &QuatSelfTest::identTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("makePureTest", &QuatSelfTest::makePureTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("makeRotTest", &QuatSelfTest::makeRotTest));        
      test_suite->addTest( new
      TestCaller<QuatSelfTest>("makeRotNormalizeTest",
      &QuatSelfTest::makeRotNormalizeTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("xformVecTest", &QuatSelfTest::xformVecTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("xformVecSweepTest", &QuatSelfTest::xformVecSweepTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("makeRotGetRotSanityTest", &QuatSelfTest::makeRotGetRotSanityTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("scalarMultTest", &QuatSelfTest::scalarMultTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("simpleQuatProductTest", &QuatSelfTest::simpleQuatProductTest));        
      test_suite->addTest( new TestCaller<QuatSelfTest>("secondQuatProductTest", &QuatSelfTest::secondQuatProductTest));        
      //test_suite->addTest( new TestCaller<QuatSelfTest>("specialCases", &QuatSelfTest::specialCases));
      //test_suite->addTest( new TestCaller<QuatSelfTest>("vectorScaleTest", &QuatSelfTest::vectorScaleTest));
      //test_suite->addTest( new TestCaller<QuatSelfTest>("quatAdd", &QuatSelfTest::quatAdd));
      //test_suite->addTest( new TestCaller<QuatSelfTest>("pureQuatMultTest", &QuatSelfTest::pureQuatMultTest));
      return test_suite;
   }
};

}

#endif
